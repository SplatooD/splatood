/*
 *
 *  SplatooD - A Splatoon Demake
 *
 */

#if !defined(__NES__)
#  error This program can only be compiled for the NES at the moment!
#endif

/* NESlib */
#include "neslib.h"

#include <stdlib.h>
#include <string.h>

/* Name tables */
#include "levels/splat_title.h"

#include "levels/kelpdome.h"
#include "levels/bluefin.h"
#include "levels/saltspray.h"
#include "levels/twofish.h"

#include "levels/endgame.h"

/* Metasprite definitions */
#include "metasprites.h"

/* Music data comes from music.s */
extern const unsigned char music_music_data[];

/* 12:4 fixed-point math for player movement */
#define FP_BITS 4

/* Map dimensions */
#define MAP_WDT         16
#define MAP_WDT_BIT     4
#define MAP_HGT         15

/* Convert screen offset to map offset */
#define MAP_ADR(x,y)    ((((y))<<MAP_WDT_BIT)|(x))

/* Map tiles */
#define TILE_SIZE       16
#define TILE_SIZE_BIT   4

/* Movement */
#define DIR_NONE        0
#define DIR_LEFT        PAD_LEFT
#define DIR_RIGHT       PAD_RIGHT
#define DIR_UP          PAD_UP
#define DIR_DOWN        PAD_DOWN
#define WALK_CYCLE      2
#define FRAMES_PER_STEP 10

/* Sprite indices */
#define SPR_DOWN        0
#define SPR_RIGHT       1
#define SPR_UP          2
#define SPR_LEFT        3

/* Weapons */
#define NUM_WPNS        2
#define WPN_SQUID       0
#define WPN_ROLLER      1
#define WPN_CHARGER     2
//#define WPN_AI2

#define MODE_NORMAL	0
#define MODE_SQUID	1

/* Tuneable gameplay parameters */
#define RESPAWN_TIME    64
#define PROJECTILE_WAIT_TIME_ROLLER 32
#define PROJECTILE_WAIT_TIME_CHARGER 8
#define PROJECTILE_DISTANCE_ROLLER 4
#define PROJECTILE_DISTANCE_CHARGER 16
#define PROJECTILE_SPEED_ROLLER 8<<FP_BITS
#define PROJECTILE_SPEED_CHARGER 16<<FP_BITS

#define ROLLER_MOVEMENT_SPEED 3<<3
#define CHARGER_MOVEMENT_SPEED 3<<FP_BITS

//#define CHARGE_FRAMES   64
#define CHARGE_FRAMES   16
#define TIMER_START     60
#define TIMER_CYCLE     0x20

/* Tile numbers for important things */
#define TILE_PLAYERA    0x10
#define TILE_PLAYERB    0x11

#define PLAYER_MAX  2

/* Sound effects */
#define SFX_START       0
#define SFX_SPLAT       1
#define SFX_RESPAWN1    2
#define SFX_DEATH       3

/* Music */
#define MUSIC_LEVEL         0
#define MUSIC_GAME          1
#define MUSIC_CLEAR         2
#define MUSIC_GAME_OVER     3
#define MUSIC_WELL_DONE     4
#define MUSIC_LOSE          4
#define MUSIC_TITLE         5
#define MUSIC_STAGE_SELECT         6

/* Palettes */
const unsigned char palTitle[16]={ 0x0f,0x30,0x0f,0x0f,0x0f,0x30,0x0f,0x0f,0x0f,0x30,0x0f,0x0f,0x0f,0x30,0x0f,0x0f };
                            /*   { 0x0f,0x30,0x14,0x0f,0x0f,0x30,0x29,0x0f,0x0f,0x30,0x27,0x0f,0x0f,0x30,0x0f,0x0f }; */

const unsigned char palInkable[16]={ 0x0f,0x10,0x30,0x30,0x0f,0x04,0x14,0x24,0x0f,0x19,0x29,0x3a,0x0f,0x01,0x21,0x31 };
const unsigned char palEndgame[16]={ 0x0f,0x30,0x30,0x30,0x0f,0x24,0x24,0x14,0x0f,0x29,0x29,0x3a,0x0f,0x21,0x21,0x11 };

const unsigned char palPaused[] = {0x0f,0x2d,0x2D,0x2D, 0x0f,0x0f,0x00,0x2d, 0x0f,0x0f,0x00,0x2d, 0x0f,0x00,0x30,0x30 };

const unsigned char palCharacters[8]={ 0x0f,0x04,0x30,0x0f,0x0f,0x19,0x30,0x0f };
const unsigned char palCharPaused[8] = {0x0f,0x00,0x2d,0x0f,0x0f,0x00,0x2d,0x0f};
const unsigned char palJudd[]={ 0x0f,0x26,0x27,0x30,0x0f,0x14,0x27,0x30,0x0f,0x2a,0x27,0x30,0x0f,0x26,0x27,0x30 };

                                  /* v   1   .   0   .   6  */
const unsigned char versionStr[] = {230,232,241,231,241,237};
const unsigned char victoryMsg[] = "Victory!";
const unsigned char fourSpaces[] = "    ";
const unsigned char tieMsg[] = "It's a tie!";
const unsigned char zero[]={0};

const unsigned char credits_0[]  = "      SplatooD";
const unsigned char credits_1[]  = " a Splatoon demake";
const unsigned char credits_2[]  = "    Project Lead";
const unsigned char credits_3[]  = "  John Carmackerel";
const unsigned char credits_4[]  = "       Music";
const unsigned char credits_5[]  = " Nobuo Squidimatsu";
const unsigned char credits_6[]  = "  Title & Postgame";
const unsigned char credits_7[]  = "   Koji Ikarashi";
const unsigned char credits_8[]  = "    Game Design";
const unsigned char credits_9[]  = "   Squideo Kojima";
const unsigned char credits_10[] = "      Graphics";
const unsigned char credits_11[] = "    Squid Meier";
const unsigned char credits_12[] = "   Game Mechanics";
const unsigned char credits_13[] = "  American McGill";
const unsigned char credits_14[] = "   AI Programming";
const unsigned char credits_15[] = "  Simon U. Richter";
const unsigned char credits_16[] = " Splatoon (C) 2015";
const unsigned char credits_17[] = "      Nintendo";
const unsigned char credits_18[] = "Thanks for playing!";

const unsigned char * credits[] = { credits_0, credits_1, credits_2, credits_3, credits_4, credits_5, credits_6, credits_7, credits_8, credits_9, credits_10, credits_11, credits_12, credits_13, credits_14, credits_15, credits_16, credits_17, credits_18, zero, zero, zero};

const unsigned char select_map[] = "Select Map";
const unsigned char level_kelpdome[] = "Kelp Dome";
const unsigned char level_bluefin_depot[] = "Bluefin Depot";
const unsigned char level_saltspray[] = "Saltspray Rig";
const unsigned char level_twofish[] = "Two Fish";

/* Level count */
#define LEVELS_ALL 4

/* Number of pointers in a level entry in the following list. */
#define LEVEL_ENTRY 4

/*
 * Level list.
 *
 * Nametable, Background palette, Sprite palette, Name
 */
const unsigned char* const levelList[LEVELS_ALL*4]={
    kelpdome,palInkable,palCharacters,level_kelpdome,
    bluefin_depot,palInkable,palCharacters,level_bluefin_depot,
    saltspray,palInkable,palCharacters,level_saltspray,
    twofish,palInkable,palCharacters,level_twofish,
};

/* Weapon Select */
const unsigned char select_weapon[] =  "Select Weapon";
const unsigned int projectile_speed[] = { 0, PROJECTILE_SPEED_ROLLER, PROJECTILE_SPEED_CHARGER };
const unsigned char weapon_ranges[] = { 0, PROJECTILE_DISTANCE_ROLLER, PROJECTILE_DISTANCE_CHARGER };
const unsigned char weapon_cooldown[] = { 0, PROJECTILE_WAIT_TIME_ROLLER, PROJECTILE_WAIT_TIME_CHARGER };
const unsigned char weapon_movement_speed[] = { 0, ROLLER_MOVEMENT_SPEED, CHARGER_MOVEMENT_SPEED };

/* This is used to ensure the updatelist starts empty. */
const unsigned char updateListData[]={
    NT_UPD_EOF
};

/* (play-time) map data */
static unsigned char map[MAP_WDT*MAP_HGT];

static unsigned char palette_state[64];

/* All the globals after this end up in the zeropage. */

#pragma bss-name (push,"ZEROPAGE")
#pragma data-name (push,"ZEROPAGE")

static unsigned char i,j,k;
static unsigned char ptr,spr;
static unsigned char px,py;
static unsigned char wait;
static unsigned int i16;
static unsigned int sum,divvar;

static unsigned char nameRow[32];

static unsigned char player_all;

static unsigned int  player_x_spawn [PLAYER_MAX];
static unsigned int  player_y_spawn [PLAYER_MAX];

static unsigned int  player_x        [PLAYER_MAX];
static unsigned int  player_y        [PLAYER_MAX];
static unsigned char player_dir_index [PLAYER_MAX];
static unsigned char player_dir      [PLAYER_MAX];
static int           player_cnt      [PLAYER_MAX];
static unsigned int  player_speed    [PLAYER_MAX];
static unsigned char player_wait     [PLAYER_MAX];
static unsigned char player_cooldown     [PLAYER_MAX];
static unsigned char player_anim_cnt [PLAYER_MAX];
static unsigned char player_diag_flip[PLAYER_MAX];
static unsigned char player_wpn      [PLAYER_MAX];
static unsigned char player_charge   [PLAYER_MAX];

static unsigned char player_mode   [PLAYER_MAX];

static unsigned char player_ai [PLAYER_MAX];
static unsigned char ai_aggression[PLAYER_MAX];
const unsigned char dirs[4]={ DIR_LEFT,DIR_UP,DIR_RIGHT,DIR_DOWN }; //basic maze strategy: always turn right

static unsigned int  projectile_x        [PLAYER_MAX];
static unsigned int  projectile_y        [PLAYER_MAX];
static unsigned char projectile_dir      [PLAYER_MAX];
static int           projectile_cnt      [PLAYER_MAX];
static unsigned char projectile_dist [PLAYER_MAX];

static unsigned char game_level;

static unsigned char game_done;
static unsigned char game_paused;

static unsigned char frame_cnt;
static unsigned char anim_frame;
static unsigned char spr_dir;
static unsigned char bright;

static unsigned char timer;


/* PPU Update list */
static unsigned char update_list[13*3+1];
static unsigned char update_list_index = 0;

void insert_into_update_list(unsigned char addr1, unsigned char addr2, unsigned char value) {
    update_list[update_list_index] = addr1;
    update_list[update_list_index+1] = addr2;
    update_list[update_list_index+2] = value;
    update_list[update_list_index+3] = NT_UPD_EOF;
    update_list_index += 3;

}

void set_tile_at(unsigned int nametable, unsigned char x, unsigned char y, unsigned char value) {
    unsigned char a = (nametable + y * 32) >> 8;
    unsigned char b = y * 32 + x;
    insert_into_update_list(a,b,value);
}

void clear_update_list() {
    update_list_index = 0;
    update_list[0] = NT_UPD_EOF;
}


/**
 * Get the palette value for a tile in the attribute table.
 */
unsigned char get_tile_palette(unsigned char x_idx, unsigned char y_idx) {
    unsigned char palette_mask;
    unsigned char palette_address;
    unsigned char palette_shift_val;
    palette_address =  (y_idx / 2) * 8 + x_idx / 2;
    palette_shift_val = (y_idx % 2)*4 + (x_idx % 2)*2;
    palette_mask = (0x03 << palette_shift_val);
    return (palette_state[palette_address]&palette_mask)>>palette_shift_val;
}

/**
 * Set the palette value for a tile in the attribute table.
 */
void set_tile_palette(unsigned char x_idx, unsigned char y_idx, unsigned char value) {
    unsigned char palette_mask;
    unsigned char palette_address;
    unsigned char palette_shift_val;
    palette_address =  (y_idx / 2) * 8 + x_idx / 2;
    palette_shift_val = (y_idx % 2)*4 + (x_idx % 2)*2;
    palette_mask = ~(0x03 << palette_shift_val);
    palette_state[palette_address] = (palette_state[palette_address] & palette_mask) + (value << palette_shift_val);
    insert_into_update_list((NAMETABLE_A >> 8) + 3, 0xc0 + palette_address, palette_state[palette_address]);
}

void reset_palette_state() {
    unsigned char i;
    for (i = 0; i < 64; i++) {
        palette_state[i] = 0;
    }
}

/* Player scores */
static unsigned int player_score[2] = { 0 };

/**
 * Calculate a player's score from map data.
 */
unsigned int score_player(unsigned char player_id) {
    unsigned char mask;
    unsigned char intermediate;
    unsigned int score = 0;
    unsigned char i;
    mask = player_id + 1;
    mask = ((mask << 2) | mask );
    mask = ((mask << 4) | mask );
    for (i = 0; i < 64; i++) {
        intermediate = palette_state[i] ^ (~ mask);
        intermediate = 0x55 & intermediate & (intermediate >> 1);
        intermediate = (intermediate >> 4) + (intermediate & 0x0f);
        score += (intermediate >> 2) + (intermediate & 0x03);
    }
    return score;
}

/**
 * Determine if a given map tile can be inked.
 */
unsigned char can_ink(unsigned char map_type) {
    if (map_type == 0x2c ||
        map_type == 0x2d ||
        map_type == 0x3c ||
        map_type == 0x3d ||
        map_type == 0x2a ||
        map_type == 0x2b ||
        map_type == 0x3a ||
        map_type == 0x3b) {
            return FALSE;
    }
    return TRUE;
}

/* Make sure this stays a multiple of 2 */
#define TITLE_ROLL_HEIGHT 110

/**
 * Used on title and credits screens to
 * delay while waiting for "START" to be pressed.
 *
 * Allows for skippable animations.
 */
#define WAIT_WITH_SKIP(w) \
    wait = w; \
    while (1) { \
        if (wait == 0) break; \
        wait--; \
        ppu_wait_frame(); \
        if ((pad_trigger(0) | pad_trigger(1)) & PAD_START) { \
            goto _skip_title; \
        } \
    }

/**
 * Show title screen.
 */
void show_title(void) {
    /* Ensure we have the write CHR bank set for the title, and reset scroll to 0. */
    ppu_off();
    bank_bg(0);
    scroll(0,TITLE_ROLL_HEIGHT);

    /* Load title screen into NAME A */
    vram_adr(NAMETABLE_A);
    vram_write(splat_title,sizeof(splat_title));

    /* Clear nametable C to avoid artifacts when bouncing. */
    vram_adr(NAMETABLE_C);
    vram_fill(0,1024);

    vram_adr(NAMETABLE_A+0x342);
    vram_write(versionStr,sizeof(versionStr));

    pal_bright(4);
    pal_bg(palTitle);
    ppu_on_bg();
    WAIT_WITH_SKIP(20);

    frame_cnt=0;
    wait=10;

    /* Scroll */
    while (1) {
        frame_cnt += 2;
        scroll(0,TITLE_ROLL_HEIGHT-frame_cnt);

        if (frame_cnt == TITLE_ROLL_HEIGHT) break;

        ppu_wait_frame();

        if ((pad_trigger(0) | pad_trigger(1)) & PAD_START) {
            goto _skip_title;
        }
    }

    scroll(0,0);

    /* Splat splat splat */
    WAIT_WITH_SKIP(20);
    sfx_play(SFX_SPLAT,0);
    pal_col(10,0x27);
    WAIT_WITH_SKIP(20);
    sfx_play(SFX_SPLAT,0);
    pal_col(2,0x14);
    WAIT_WITH_SKIP(20);
    sfx_play(SFX_SPLAT,0);
    pal_col(6,0x29);
    WAIT_WITH_SKIP(20);
    music_play(MUSIC_TITLE);

    pal_col(3,0x30);
    pal_col(15,0x30);

    wait = 10;
    frame_cnt = 0;

    while (1) {

        /* Flash start between white and gray. */
        wait--;
        if (!wait) {
            pal_col(15,(frame_cnt&1)?0x30:0x20);
            wait = 10;
            frame_cnt++;
        }

        ppu_wait_frame();

        /* Wait for input to start game. */
        if ((pad_trigger(0) | pad_trigger(1)) & PAD_START) {
            break;
        }
    }

_skip_title:
    scroll(0,0);
    pal_bg(palTitle);
    pal_col(10,0x27);
    pal_col(2,0x14);
    pal_col(6,0x29);
    pal_col(3,0x30);

    music_stop();

    sfx_play(SFX_START,0);

    /* Blink rapidly. */
    for (i=0;i<16;++i) {
        pal_col(15, (i & 1) ? 0x0f : 0x20);
        delay(4);
    }

}

/* Where numbers start in the EBCDIC tileset */
#define NUM_START 0xB0

/**
 * Put a number into the vram nametable when not rendering.
 * Cheaper than an update table, but only use this when
 * initializing VRAM and not during play.
 */
void put_num(unsigned int adr,unsigned int num,unsigned char len) {
    vram_adr(adr);

    if (len>2) vram_put(NUM_START+(num/100)%10);
    if (len>1) vram_put(NUM_START+(num/10)%10);
    vram_put(NUM_START+(num%10));
}

/**
 * Print a string into VRAM.
 * Use only between frames!
 */
void print_str(unsigned int adr, const unsigned char * str) {
    vram_adr(adr);
    while (*str) {
        vram_put((*str)+0x80);
        str++;
    }
}

/**
 * Map select screen.
 */
void show_select_map() {
    /* Use bank 1 to get full characterset tiles */
    bank_bg(1);
    bank_spr(1);
    music_play(MUSIC_STAGE_SELECT);

    ppu_off();
    pal_bg(palEndgame);

    /* We don't use an existing nametable, but instead clear out NAMETABLE_A */
    vram_adr(NAMETABLE_A);
    vram_fill(0xa0,1024-64);
    vram_fill(0,64);

    /* "Select Map" */
    print_str(NAMETABLE_A+0x0EB,select_map);

    /* Map names */
    for (i = 0; i < LEVELS_ALL; ++i) {
        print_str(NAMETABLE_A+0x148+0x20*i,levelList[i*LEVEL_ENTRY+3]);
    }

    ppu_on_bg();

    clear_update_list();
    set_vram_update(update_list);

    while (1) {
        /*
         * A squid represents the current selection.
         */
        int tmp = NAMETABLE_A + 0x146 + 0x20 * game_level;
        insert_into_update_list(tmp>>8,tmp&0xFF,'*'+0x80);

        /* Loop waiting for input. */
        while (1) {
            ppu_wait_frame();
            clear_update_list();
            j = pad_trigger(0) | pad_trigger(1);
            /* Start - Select map */
            if (j & PAD_START) return;
            /* Up - move cursor up */
            if (j & PAD_UP) {
                insert_into_update_list(tmp>>8,tmp&0xFF,' '+0x80);
                if (game_level == 0) {
                    game_level = LEVELS_ALL-1;
                } else {
                    game_level -= 1;
                }

                break;
            }
            /* Select or Down - move cursor down */
            if (j & PAD_SELECT || j & PAD_DOWN) {
                insert_into_update_list(tmp>>8,tmp&0xFF,' '+0x80);
                game_level += 1;
                if (game_level == LEVELS_ALL) game_level = 0;
                break;
            }
        }

    }
}

/*
 * Two-player weapon select.
 *
 * This needs to be expanded to support more than two players,
 * but I leave that as an exercise for later.
 */
void show_select_weapon(void) {
    int player_id;
    player_wpn[0] = WPN_ROLLER;
    player_wpn[1] = WPN_ROLLER;

    ppu_off();
    pal_bg(palEndgame);
    pal_spr(palCharacters);

    /* We don't use an existing nametable, but instead clear out NAMETABLE_A */
    vram_adr(NAMETABLE_A);
    vram_fill(0xa0,1024-64);
    vram_fill(0,64);

    print_str(NAMETABLE_A+0x0E9,select_weapon);

    oam_clear();

    ppu_on_all();

    anim_frame = 0;

    //default aggressive ai for player 2
    ai_aggression[0]=1;
    ai_aggression[1]=1;
    player_ai[0]=0;
    player_ai[1]=1;

    player_mode[0]=MODE_SQUID;
    player_mode[1]=MODE_SQUID;

    while (1) {
next:

#define A_HEIGHT 80
#define B_HEIGHT 120
#define LEFT     100
#define RIGHT    140

        if (player_wpn[0] == WPN_ROLLER) {
            oam_meta_spr(LEFT,  A_HEIGHT, 0<<4, SprPlayers[0][WPN_ROLLER][0][anim_frame]);
            oam_meta_spr(RIGHT, A_HEIGHT, 1<<4, unselected_charger);
        } else {
            oam_meta_spr(LEFT,  A_HEIGHT, 0<<4, unselected_roller);
            oam_meta_spr(RIGHT, A_HEIGHT, 1<<4, SprPlayers[0][WPN_CHARGER][0][anim_frame]);
        }

        if (player_wpn[1] == WPN_ROLLER) {
            oam_meta_spr(LEFT,  B_HEIGHT, 2<<4, SprPlayers[1][WPN_ROLLER][0][anim_frame]);
            oam_meta_spr(RIGHT, B_HEIGHT, 3<<4, unselected_charger);
        } else {
            oam_meta_spr(LEFT,  B_HEIGHT, 2<<4, unselected_roller);
            oam_meta_spr(RIGHT, B_HEIGHT, 3<<4, SprPlayers[1][WPN_CHARGER][0][anim_frame]);
        }

        i = 0;
        anim_frame = 1 - anim_frame;
        while (i < 10) {
            ppu_wait_frame();
            i++;
            for (player_id = 0; player_id < 2; player_id++) {
                j = pad_trigger(player_id);
		if((j!=0)&&(player_id==1)) player_ai[player_id]=0; //disable ai if player 2 presses any key at weapon select screen
                /* Start - Select weapon */
                if (j & PAD_START) return;
                /* Up - move cursor up */
                if (j & PAD_UP) {
                    if (player_wpn[player_id] == 1) {
                        player_wpn[player_id] = NUM_WPNS;
                    } else {
                        player_wpn[player_id] -= 1;
                    }

                    goto next;
                }
                /* Select or Down - move cursor down */
                if (j & PAD_SELECT || j & PAD_LEFT || j & PAD_RIGHT) {
                    player_wpn[player_id] += 1;
                    if (player_wpn[player_id] > NUM_WPNS) player_wpn[player_id] = 1;
                    goto next;
                }
            }
        }
    }
}

/**
 * Credits sequence.
 */
void show_credits() {
    bank_bg(1);
    bank_spr(1);

    /* Clear the screen. */
    ppu_off();
    pal_bg(palEndgame);

    /* Write credits. */
    i = 0;
    j = 0;
    divvar = 0;

    /* Clear the scrolling nametables, A and C */
    vram_adr(NAMETABLE_C);
    vram_fill(0xa0,1024-64);
    vram_fill(0,64);

    sum = NAMETABLE_C;

    while (i < 19) { /* 4 6 A C */
        ppu_wait_nmi();
        ppu_off();
        vram_adr(sum);
        vram_fill(0xa0,1024-64);
        vram_fill(0,64);
        print_str(sum+0x126, credits[i]);
        print_str(sum+0x166, credits[i+1]);
        print_str(sum+0x1C6, credits[i+2]);
        print_str(sum+0x206, credits[i+3]);
        ppu_on_all();

        do {
            scroll(0,divvar);

            /* Judd as a sprite. */
            if (i == 0 && divvar < 0x62) {
                oam_meta_spr(0x70,0x48-divvar,0,(char*)i16);
            }

            divvar++;
            WAIT_WITH_SKIP(1);
        } while (divvar % 240);
        if (divvar == 480) divvar = 0;

        if (sum == NAMETABLE_A) sum = NAMETABLE_C;
        else sum = NAMETABLE_A;

        WAIT_WITH_SKIP(50);
        i+=4;
    }
    WAIT_WITH_SKIP(100);

    ppu_off();
    vram_adr(sum);
    vram_fill(0xa0,1024-64);
    ppu_on_all();

    while (divvar % 240 < 100) {
        WAIT_WITH_SKIP(1);
        scroll(0,divvar);
        divvar++;
    }

_skip_title:
    delay(20);
}

/**
 * Post Game Screen
 *
 * Shows Judd pointing to the winner,
 * inked % of map, total inked cells,
 * and a gauge.
 */
void show_endgame(void) {
    bank_bg(1);
    bank_spr(1);

    /* Set up the background (meter, "Game Over") */
    ppu_off();
    vram_adr(NAMETABLE_A);
    vram_write(endgame,1024);
    pal_bg(palEndgame);
    pal_spr(palJudd);
    oam_clear();

    /* We're going to use the update lists to set background palettes */
    clear_update_list();

    /* Give players with no points a freebie to help with the math. */
    if (player_score[0] == 0) player_score[0] = 1;
    if (player_score[1] == 0) player_score[1] = 1;

    /*
     * We calculate percentages and bar gauge based on total inked
     * not total available for inking. This is a bit different from
     * the real deal.
     */
    sum = (player_score[0] + player_score[1]);

    /* Calculate percentage for player 1 */
    divvar = player_score[0] * 100;
    divvar /= sum;
    if (divvar == 100) divvar = 99;
    if (divvar == 0) divvar = 1;
    put_num(NAMETABLE_A+0x1EA,divvar,2);

    /* Player 2 must be 100% - (player 1) */
    divvar = 100 - divvar;
    put_num(NAMETABLE_A+0x1F4,divvar,2);

    /* Convert Player 2's percentage to a gauge width */
    divvar *= 9;
    divvar /= 100;

    /* Print the victory message. */
    if (player_score[0] > player_score[1]) {
        print_str(NAMETABLE_A+0x1C9,victoryMsg);
        i16 = (int)judd_left;
    } else if (player_score[0] == player_score[1]) {
        /* If both players have the same score, it was a tie. */
        print_str(NAMETABLE_A+0x1CB,tieMsg);
        i16 = (int)judd_tie;
    } else {
        print_str(NAMETABLE_A+0x1CF,victoryMsg);
        i16 = (int)judd_right;
    }

    oam_meta_spr(0x70,0x48,0,(char*)i16);

    /* Print raw player scores below the gauge */
    put_num(NAMETABLE_A+0x24A,player_score[0],3);
    put_num(NAMETABLE_A+0x253,player_score[1],3);

    /* Enable the background */
    ppu_on_all();

    /* Play the post-game music. */
    music_play(MUSIC_WELL_DONE);

    /* Set the gauge palettes. */
    clear_update_list();
    for (i = 4; i < 12 - divvar; ++i) {
        /* Player 1 on the left. */
        set_tile_palette(i,8,1);
    }
    for (i = 12 - divvar; i <= 11; ++i) {
        /* Player 2 on the right. */
        set_tile_palette(i,8,2);

    }
    set_vram_update(update_list);

    while (1) {
        /* Wait for someone to hit start. */
        ppu_wait_frame();
        clear_update_list();
        if ((pad_trigger(0) | pad_trigger(1)) & PAD_START) break;
    }
    reset_palette_state();
}

/* 
 * Move a projectile if there is no wall
 */
void projectile_move(unsigned char id) {
    unsigned char map_type = 0;
    unsigned char dir = projectile_dir[id];

    /*
     * Reset speed; if the last direction we check is valid, we'll set speed, but we
     * shouldn't let players input a valid direction that sets speed plus a higher priority
     * invalid direction to let them move in the invalid direction
     */
    projectile_cnt[id]=0;
    projectile_dist[id]-=1;

    if (projectile_dist[id] == 0) {
            projectile_dir[id]=DIR_NONE;
            return;
    }

    px=projectile_x[id]>>(TILE_SIZE_BIT+FP_BITS);
    py=projectile_y[id]>>(TILE_SIZE_BIT+FP_BITS);

    switch (dir) {
        case DIR_NONE: return; break;
        case DIR_LEFT:   --px; break;
        case DIR_RIGHT:  ++px; break;
        case DIR_UP:     --py; break;
        case DIR_DOWN:   ++py; break;
    }


    if (px > MAP_WDT-1) {
            projectile_dir[id]=DIR_NONE;
            return;
    }

    if (py > MAP_HGT-1) {
            projectile_dir[id]=DIR_NONE;
            return;
    }

    map_type = map[MAP_ADR(px, py)];

    if (can_ink(map_type)) {
        set_tile_palette(px, py, id+1);
    }

    if ((map_type >= 0x22 && map_type <= 0x29) || (map_type >= 0x32 && map_type <= 0x39)) {
            projectile_dir[id]=DIR_NONE;
            return;
    }

    projectile_cnt[id]=TILE_SIZE<<FP_BITS;
}


/**
 * Calculate player distance
 *
 * Uses Manhattan metric
 */
unsigned int player_dist(unsigned char id1, unsigned char id2){
   int px2=player_x[id1]>>(TILE_SIZE_BIT+FP_BITS);
   int py2=player_y[id1]>>(TILE_SIZE_BIT+FP_BITS);
   int px=player_x[id2]>>(TILE_SIZE_BIT+FP_BITS);
   int py=player_y[id2]>>(TILE_SIZE_BIT+FP_BITS);
   return abs(px2-px)+abs(py2-py);
}

/**
 * Player movement test.
 *
 * Allows AI to test movement directions without actual movement.
 */
unsigned char player_move_test(unsigned char id,unsigned char dir_index) {
    unsigned char map_type = 0;
    unsigned char tile_palette;
    unsigned char is_wall=0;
    /*if (player_cooldown[id]) {
        return 0;
    }*/

    px=player_x[id]>>(TILE_SIZE_BIT+FP_BITS);
    py=player_y[id]>>(TILE_SIZE_BIT+FP_BITS);

    switch (dir_index%4) {
        case 0:  --px; break;
        case 2: ++px; break;
        case 1:    --py; break;
        case 3:  ++py; break;
    }


    if (px > MAP_WDT-1) {
            return 0;
    }

    if (py > MAP_HGT-1) {
            return 0;
    }

    /*
     * Wall tiles:
     * 0x22~0x29
     * 0x32~0x39
     */
    map_type = map[MAP_ADR(px, py)];

	//water
//    if(map_type == 0x2c || map_type == 0x2d || map_type == 0x3c || map_type == 0x3d) return 0;
    if((map_type == 0x2c || map_type == 0x2d || map_type == 0x3c || map_type == 0x3d) && player_mode[id] != MODE_SQUID) return 0;

 
    if((map_type >= 0x22 && map_type <= 0x29) || (map_type >= 0x32 && map_type <= 0x39)) is_wall=1;

	//inkable
    if(can_ink(map_type)){

     tile_palette=get_tile_palette(px,py);

     if(tile_palette==id+1) return 1-is_wall; //already inked
     if(tile_palette==2-id) return 4; //enemy ink
     else return 3-is_wall; //uninked
    }

    return 0;
}


/**
 * Player movement.
 *
 * Player movement is tile-by-tile with an animation between
 * tiles that we need to initialize.
 */
void player_move(unsigned char id,unsigned char dir_index) {
    unsigned char map_type = 0;
    if (player_cooldown[id]) {
        return;
    }

    /* We always set direction so sprites update facing */
    player_dir_index[id]=dir_index;
    player_dir[id]=dirs[dir_index];

    /* A pad direction is being held, so animate */
    player_anim_cnt[id] += 1;

    /*
     * Reset speed; if the last direction we check is valid, we'll set speed, but we
     * shouldn't let players input a valid direction that sets speed plus a higher priority
     * invalid direction to let them move in the invalid direction
     */
    player_cnt[id]=0;

    px=player_x[id]>>(TILE_SIZE_BIT+FP_BITS);
    py=player_y[id]>>(TILE_SIZE_BIT+FP_BITS);

    switch (dir_index) {
        case 0:  --px; break;
        case 2: ++px; break;
        case 1:    --py; break;
        case 3:  ++py; break;
    }


    if (px > MAP_WDT-1) {
            return;
    }

    if (py > MAP_HGT-1) {
            return;
    }

    /*
     * Wall tiles:
     * 0x22~0x29
     * 0x32~0x39
     */
    map_type = map[MAP_ADR(px, py)];

    if (player_mode[id]==MODE_NORMAL && player_wpn[id] == WPN_ROLLER && can_ink(map_type)) {
        set_tile_palette(px, py, id+1);
    }

    if (((map_type >= 0x22 && map_type <= 0x29) || (map_type >= 0x32 && map_type <= 0x39)) && (player_mode[id]!=MODE_SQUID || get_tile_palette(px,py)!=id+1)) {
            return;
    }

    player_cnt[id]=TILE_SIZE<<FP_BITS;
    player_diag_flip[id]=1;
    //APU.pulse[0].control=0x12;

    sfx_play_damped(SFX_SPLAT,0,(player_dist(0,1)>>1)); //positional audio for maximum player distance of 31
}

/**
 * Generate a projectile from a player.
 */
void player_make_projectile(unsigned char id) {
    unsigned char map_type = 0;
    if (player_cooldown[id]) return;

    if (player_wpn[id] == WPN_CHARGER && player_charge[id] < CHARGE_FRAMES) {
        ++player_charge[id];
        return;
    }
    projectile_dist[id] = weapon_ranges[player_wpn[id]];
    projectile_dir[id] = player_dir[id];
    projectile_x[id] = player_x[id];
    projectile_y[id] = player_y[id];
    player_cooldown[id] = weapon_cooldown[player_wpn[id]];
    player_charge[id] = 0;

    px=projectile_x[id]>>(TILE_SIZE_BIT+FP_BITS);
    py=projectile_y[id]>>(TILE_SIZE_BIT+FP_BITS);
    map_type = map[MAP_ADR(px, py)];
    if (can_ink(map_type)) {
        set_tile_palette(px, py, id+1);
    }
}

/**
 * Splat!
 */
void player_die(unsigned char id) {
    /* Reset to spawn. */
    player_x[id] = player_x_spawn[id];
    player_y[id] = player_y_spawn[id];
    player_cnt[id]=0;
    player_anim_cnt[id]=0;
    player_diag_flip[id]=0;
    player_dir[id] = DIR_NONE;
    player_mode[id]=MODE_SQUID;

    player_wait[id] = RESPAWN_TIME;
    sfx_play(SFX_DEATH,0);
}

/**
 * AI movement with aggressive weapon mode.
 */
unsigned char ai_move(unsigned char id){
  unsigned char diri,dirv,dirtest;
  unsigned char px2,py2;
  if(player_dir[id]==DIR_NONE) j=rand8()%4; //random start direction
  else j=player_dir_index[id]; //prefer movements in the same direction
  diri=255; dirv=0;
  for(k=0;k<4;k++){
   dirtest=player_move_test(id,j+k);
   if(dirtest>dirv){dirv=dirtest; diri=j+k; if(dirtest==4) break;}
   else if((dirtest==dirv)&&(dirv==1)&&(rand8()<8)){dirv=dirtest; diri=j+k;}
  }
  if(dirv==0) j=PAD_A; //if no movement is possible just fire weapon
  else j=dirs[diri%4];

  if((player_cooldown[id]==0)&&(ai_aggression[id]>=1)&&(player_mode[1-id]!=MODE_SQUID)){
	px=player_x[id]>>(TILE_SIZE_BIT+FP_BITS);
	py=player_y[id]>>(TILE_SIZE_BIT+FP_BITS);
        px2=player_x[1-id]>>(TILE_SIZE_BIT+FP_BITS);
        py2=player_y[1-id]>>(TILE_SIZE_BIT+FP_BITS);
	  if(px==px2){
	   if(py>py2){
	    if(py-py2<=3){
	     if(player_dir[id]==DIR_UP){ j=PAD_A; }
	     else if(player_move_test(id,1)>0){ j=dirs[1]; }
	   }}else if((py2-py<=3)&&(py2-py>0)){
	    if(player_dir[id]==DIR_DOWN){ j=PAD_A; }
	    else if(player_move_test(id,3)>0){ j=dirs[3]; }
	  }}else if(py==py2){
	   if(px>px2){
	    if(px-px2<=3){
	     if(player_dir[id]==DIR_LEFT){ j=PAD_A; }
	     else if((player_move_test(id,0)>0)){ j=dirs[0]; }
	   }}else if((px2-px<=3)&&(px2-px>0)){
	    if(player_dir[id]==DIR_RIGHT){ j=PAD_A; }
	    else if(player_move_test(id,2)>0){ j=dirs[2]; }
	  }}
  }
  
 return j;
}


/**
 * Main gameplay loop.
 */
void game_loop(void) {
    unsigned char map_type;

    ppu_off();

    oam_clear();

    bank_bg(1);
    bank_spr(1);
    scroll(0,0);

    /* Load map */
    vram_adr(NAMETABLE_A);
    vram_write(levelList[game_level*LEVEL_ENTRY],1024);

    vram_adr(NAMETABLE_A+0x3c0);
    vram_read(palette_state, sizeof(palette_state));

    /* Clear nametable C to avoid artifacts when bouncing. */
    vram_adr(NAMETABLE_C);
    vram_fill(0,1024);

    /* Set palette */
    pal_bright(4);
    pal_bg(levelList[game_level*LEVEL_ENTRY+1]);
    pal_spr(levelList[game_level*LEVEL_ENTRY+2]);

    player_all=0;

    timer = TIMER_START;

    i16=NAMETABLE_A;
    ptr=0;
    wait=0;

    vram_adr(NAMETABLE_A);

    /*
     * Read through the map in VRAM to find where
     * players should spawn and replace their spawn
     * locations with the appropriate map tile
     * for the upper left corner of a spawn point.
     */
    for (i = 0; i < MAP_HGT; ++i) {
        vram_adr(i16);
        vram_read(nameRow,32);
        vram_adr(i16);

        for (j = 0; j < (MAP_WDT << 1); j += 2) {
            spr=nameRow[j];

            switch (spr) {
            case TILE_PLAYERA:
            case TILE_PLAYERB:
                player_dir       [player_all] = DIR_NONE;
                player_x_spawn   [player_all] = (j<<3)<<FP_BITS;
                player_y_spawn   [player_all] = (i<<4)<<FP_BITS;
                player_cnt       [player_all] = 0;
                player_anim_cnt  [player_all] = 0;
                player_diag_flip [player_all] = 0;
                player_wait      [player_all] = 16+((spr-TILE_PLAYERA)<<4);
                player_cooldown  [player_all] = 0;
                player_speed     [player_all] = 2<<FP_BITS;
                player_charge    [player_all] = 0;

                projectile_cnt   [player_all] = 0;
                projectile_dir   [player_all] = DIR_NONE;

                ++player_all;
                wait+=16;
                spr=0x2a;
                break;
            }

            map[ptr++]=spr;

            vram_put(spr);
            vram_put(nameRow[j+1]);
        }

        i16+=64;
    }

    /* Store spawn locations for respawn. */
    for (i = 0; i < player_all; ++i) {
        player_x[i] = player_x_spawn[i];
        player_y[i] = player_y_spawn[i];
    }

    /* Clear the update list */
    memcpy(update_list,updateListData,sizeof(updateListData));
    set_vram_update(update_list);

    /* Start rendering. */
    ppu_on_all();

    game_done = FALSE;
    game_paused = FALSE;

    bright = 0;
    frame_cnt = 0;

    while (!game_done) {
        /* Place sprites in the OAM for players. */

        spr=(player_all-1)<<4;

        for (i=0;i<player_all;++i) {
            py=player_y[i]>>FP_BITS;

            if (player_wait[i]) {
                if (player_wait[i]>=16||player_wait[i]&2) py=240;
            }

            px = player_x[i]>>FP_BITS;

            anim_frame = (player_anim_cnt[i] / FRAMES_PER_STEP) % WALK_CYCLE;

            switch (player_dir[i]) {
                case DIR_NONE:
                case DIR_UP: spr_dir = SPR_UP; break;
                case DIR_DOWN: spr_dir = SPR_DOWN; break;
                case DIR_LEFT: spr_dir = SPR_LEFT; break;
                case DIR_RIGHT: spr_dir = SPR_RIGHT; break;
            }
	    if(player_mode[i]==MODE_SQUID) oam_meta_spr(px, py, spr, SprPlayers[i][0][spr_dir][anim_frame]);
	    else oam_meta_spr(px, py, spr, SprPlayers[i][player_wpn[i]][spr_dir][anim_frame]);
            spr-=16;
        }

        /* Wait for the next frame. */
        ppu_wait_frame();
        clear_update_list();

        /* Tick the timer */
        ++frame_cnt;
        if (!game_paused && (frame_cnt % TIMER_CYCLE == 0)) {
            timer--;
        }
        /* And update it on screen. */
        insert_into_update_list(0x20,0x4f,timer/10 + 0xb0);
        insert_into_update_list(0x20,0x50,timer%10 + 0xb0);


        /* Read both inputs for "START" in trigger mode. */
        i = pad_trigger(0);
        i |= pad_trigger(1);

        /* Pause the game if someone hit start. */
        if (i & PAD_START) {
            game_paused ^= TRUE;
            if (game_paused) {
                /* When the game is paused, we switch to a grayscale palette */
                pal_bg(palPaused);
                pal_spr(palCharPaused);
            } else {
                /* Switch back to level palette. */
                pal_bg(levelList[game_level*LEVEL_ENTRY+1]);
                pal_spr(levelList[game_level*LEVEL_ENTRY+2]);
            }
            music_pause(game_paused);
            sfx_play(SFX_SPLAT,0);
        }

        /* Skip processing inputs when the game is paused. */
        if (game_paused) continue;

        /*
         * When players spawn, they flash a bit.
         * We don't start the music until they are done flashing.
         */
        if (wait) {
            --wait;

            if (!wait) {
                music_play_gated(MUSIC_GAME,8);
            }
        }

        /* When the timer reaches 0, the game is over. */
        if (timer == 0) {
            music_play(MUSIC_CLEAR);
            game_done = TRUE;
        }

        /*
         * Process player actions.
         */
        for (i = 0; i < player_all; ++i) {
            /* Flash respawning players, and prevent them from providing input. */
            if (player_wait[i]) {
                if (player_wait[i] == 16) {
                    sfx_play(SFX_RESPAWN1,0);
                }
                --player_wait[i];
                //continue;
            }else{

            if (wait) continue; /* Avoid processing input during initial spawn. */

            /* This player is moving, so animate their movement. */
            if (player_cnt[i])  {
            	px = player_x[i] >> (TILE_SIZE_BIT + FP_BITS);
            	py = player_y[i] >> (TILE_SIZE_BIT + FP_BITS);
		map_type = map[MAP_ADR(px, py)];
                //if((tile_pal==2-i) && (player_mode[i]==MODE_SQUID)) player_speed[i]=1<<FP_BITS; //enemy ink is slow for squid
		if((map_type == 0x2c || map_type == 0x2d || map_type == 0x3c || map_type == 0x3d) && (player_mode[i]==MODE_SQUID)) player_speed[i]=1<<FP_BITS; //water is slow for squid!
		else player_speed[i]=weapon_movement_speed[player_wpn[i]];                                                                                     //otherwise have normal speed, squid or kid.

                switch (player_dir[i]) {
                    case DIR_RIGHT: player_x[i]+=player_speed[i]; break;
                    case DIR_LEFT:  player_x[i]-=player_speed[i]; break;
                    case DIR_DOWN:  player_y[i]+=player_speed[i]; break;
                    case DIR_UP:    player_y[i]-=player_speed[i]; break;
                }

                player_cnt[i]-=player_speed[i];

                /* Finish movement. */
                if (player_cnt[i] <= 0) {
                    if (player_cnt[i] < 0) {
                        player_cnt[i] = 0;

                        /* Align player to grid. */
                        player_x[i]=(player_x[i]&0xff00)+(player_dir[i]==DIR_LEFT?0x100:0);
                        player_y[i]=(player_y[i]&0xff00)+(player_dir[i]==DIR_UP  ?0x100:0);
                    }

                } else {
                    /* Continue animating movement. */
                    player_anim_cnt[i] += 1;
                }
            }

            /* No current movement, accept input. */
            if (!player_cnt[i]) {

		if(player_ai[i]!=0){
		 // AI
		 j=ai_move(i);
		}else{
                 /* Read pad state if ai is disabled. */
                 j = pad_state(i);
		}

                if (player_cooldown[i]) {
                    player_cooldown[i] -= 1;
                }


                if (j&PAD_B) player_mode[i]=MODE_SQUID; else player_mode[i]=MODE_NORMAL;

                if (j & player_dir[i] && player_diag_flip[i]) {
                    /* Give priority to new direction (useful for cornering) */
                    j &= ~player_dir[i];
                    player_diag_flip[i] = 0;
                    //player_move(i, player_dir_index[i]);
                }

                if (j&PAD_LEFT)  player_move(i,0);
                if (j&PAD_RIGHT) player_move(i,2);
                if (j&PAD_UP)    player_move(i,1);
                if (j&PAD_DOWN)  player_move(i,3);

		if (player_dir[i]==DIR_NONE) player_mode[i]=MODE_SQUID;

                if ((j&PAD_A)&&(player_mode[i]==MODE_NORMAL)) player_make_projectile(i); else player_charge[i] = 0;

            }}

            /* If this player has a projectile, move it as well. */
            if (projectile_cnt[i]) {
                if (projectile_cnt[i] <= 0) {
                    if (projectile_cnt[i] < 0) {
                        projectile_cnt[i] = 0;

                        /* Projectiles also lock to tiles, like players. */

                        projectile_x[i]=(projectile_x[i]&0xff00)+(projectile_dir[i]==DIR_LEFT?0x100:0);
                        projectile_y[i]=(projectile_y[i]&0xff00)+(projectile_dir[i]==DIR_UP  ?0x100:0);
                    }
                }
            }

            if (!projectile_cnt[i]) {
                projectile_move(i);
            }

            if (projectile_cnt[i]) {
                switch (projectile_dir[i]) {
                    case DIR_RIGHT: projectile_x[i]+=projectile_speed[player_wpn[i]]; break;
                    case DIR_LEFT:  projectile_x[i]-=projectile_speed[player_wpn[i]]; break;
                    case DIR_DOWN:  projectile_y[i]+=projectile_speed[player_wpn[i]]; break;
                    case DIR_UP:    projectile_y[i]-=projectile_speed[player_wpn[i]]; break;
                }

                projectile_cnt[i]-=projectile_speed[player_wpn[i]];
            }

        }

        /* Kill players that collide with eachother. */
        for (i = 0; i < player_all; ++i) {
            for (j = i + 1; j < player_all; ++j) {
                if (((player_x[i]&0xff00) == (player_x[j]&0xff00)) && ((player_y[i]&0xff00) == (player_y[j]&0xff00))) {
                    // If you have a roller, kill the player you collide with
                    // If both players have rollers, both of them die
                    // If one of the players is a squid, only squid dies
                    if ((player_wpn[i] == WPN_ROLLER)&&(player_mode[i]!=MODE_SQUID)&&(player_mode[j]!=MODE_SQUID)){
			 player_die(j);
			 player_die(i);
		    }
                    if ((player_wpn[j] == WPN_ROLLER)&&(player_mode[j]!=MODE_SQUID)&&(player_mode[i]!=MODE_SQUID)){
			 player_die(i);
                         player_die(j);
                    }
		    if ((player_wpn[i] == WPN_ROLLER)&&(player_mode[i]!=MODE_SQUID)&&(player_mode[j]==MODE_SQUID)) player_die(j);
                    if ((player_wpn[j] == WPN_ROLLER)&&(player_mode[j]!=MODE_SQUID)&&(player_mode[i]==MODE_SQUID)) player_die(i);

                }
                if (projectile_dir[j] != DIR_NONE &&
                        (player_x[i]&0xff00) == (projectile_x[j]&0xff00) &&
                        (player_y[i]&0xff00) == (projectile_y[j]&0xff00)) {
                    /* Player j kills player i using a projectile */
                    if((player_mode[i]==MODE_NORMAL) || (player_mode[i]==MODE_SQUID)) player_die(i);
                }
                if (projectile_dir[i] != DIR_NONE &&
                        (player_x[j]&0xff00) == (projectile_x[i]&0xff00) &&
                        (player_y[j]&0xff00) == (projectile_y[i]&0xff00)) {
                    /* Player i kills player j using a projectile */
                    if((player_mode[j]==MODE_NORMAL) || (player_mode[j]==MODE_SQUID)) player_die(j);
                }
            }
        }

        /* Kill players that fall in water. */
        for ( i = 0; i < player_all; ++i) {
            px = player_x[i] >> (TILE_SIZE_BIT + FP_BITS);
            py = player_y[i] >> (TILE_SIZE_BIT + FP_BITS);
            map_type = map[MAP_ADR(px, py)];
            /* Water tiles are 0x2c, 0x2d, 0x3c, 0x3d */
            if ((map_type == 0x2c || map_type == 0x2d || map_type == 0x3c || map_type == 0x3d) && player_mode[i] != MODE_SQUID) {
                player_die(i);
            }
        }
    }

    /* Game is over, calculate score. */
    for (i = 0; i < player_all; ++i) {
        player_score[i] = score_player(i);
    }

    /* Make sure the timer says 00 */
    insert_into_update_list(0x20,0x50,timer%10 + 0xb0);
    ppu_wait_frame();

    /* Whistle */
    sfx_play(SFX_START,0);

    /* Stop battling! */
    for (i = 0; i < 32; i += 8) {
        for (j = 10; j < 13; ++j) {
            clear_update_list();
            set_tile_at(NAMETABLE_A,i+0,j,' '+0x80);
            set_tile_at(NAMETABLE_A,i+1,j,' '+0x80);
            set_tile_at(NAMETABLE_A,i+2,j,' '+0x80);
            set_tile_at(NAMETABLE_A,i+3,j,' '+0x80);
            set_tile_at(NAMETABLE_A,i+4,j,' '+0x80);
            set_tile_at(NAMETABLE_A,i+5,j,' '+0x80);
            set_tile_at(NAMETABLE_A,i+6,j,' '+0x80);
            set_tile_at(NAMETABLE_A,i+7,j,' '+0x80);
            ppu_wait_frame();
        }
        clear_update_list();
        set_tile_palette(i/2+0,5,0);
        set_tile_palette(i/2+1,5,0);
        set_tile_palette(i/2+2,5,0);
        set_tile_palette(i/2+3,5,0);
        ppu_wait_frame();
    }

    clear_update_list();
    set_tile_at(NAMETABLE_A,13,11,'G'+0x80);
    set_tile_at(NAMETABLE_A,14,11,'A'+0x80);
    set_tile_at(NAMETABLE_A,15,11,'M'+0x80);
    set_tile_at(NAMETABLE_A,16,11,'E'+0x80);
    set_tile_at(NAMETABLE_A,17,11,'!'+0x80);
    set_tile_at(NAMETABLE_A,18,11,'!'+0x80);
    ppu_wait_frame();

    delay(100);

    reset_palette_state();
}



void main(void) {

    while (1) {
        /* Show the main title. */
        show_title();

        /* Select a map. */
        show_select_map();

        /* Select weapons */
        show_select_weapon();

        /* Start the game. */
        game_loop();

        /* Show the final scores. */
        show_endgame();

        /* Play the credits. */
        show_credits();

        /* Loop back to the title... */
    }
}
