/* Player metaprites!
 * Player metasprites are organized as:
 * SprPlayers[player number][player weapon][player direction][animation frame]
 * Player weapons are ordered ROLLER CHARGER (see WPN_ROLLER, etc in game.c)
 * Player directions need to be ordered DOWN RIGHT UP LEFT (see SPR_DOWN, etc in game.c)
 */
const unsigned char SprPlayer1SquidUpFrame1[] = {
    0,-1,0x66,0,
    8,-1,0x67,0,
    0, 7,0x76,0,
    8, 7,0x77,0,
    128
};

const unsigned char SprPlayer1SquidUpFrame2[] = {
    0,-1,0x66,0,
    8,-1,0x67,0,
    0, 7,0x77,0|OAM_FLIP_H,
    8, 7,0x76,0|OAM_FLIP_H,
    128
};

const unsigned char SprPlayer1SquidRightFrame1[] = {
    0,-1,0x68,0,
    8,-1,0x69,0,
    0, 7,0x78,0,
    8, 7,0x79,0,
    128
};

const unsigned char SprPlayer1SquidDownFrame1[] = {
    0,-1,0x76,0|OAM_FLIP_V,
    8,-1,0x77,0|OAM_FLIP_V,
    0, 7,0x66,0|OAM_FLIP_V,
    8, 7,0x67,0|OAM_FLIP_V,
    128
};

const unsigned char SprPlayer1SquidLeftFrame1[] = {
    0,-1,0x69,0|OAM_FLIP_H,
    8,-1,0x68,0|OAM_FLIP_H,
    0, 7,0x79,0|OAM_FLIP_H,
    8, 7,0x78,0|OAM_FLIP_H,
    128
};

const unsigned char SprPlayer1SquidRightFrame2[] = {
    0,-1,0x78,0|OAM_FLIP_V,
    8,-1,0x79,0|OAM_FLIP_V,
    0, 7,0x68,0|OAM_FLIP_V,
    8, 7,0x69,0|OAM_FLIP_V,
    128
};

const unsigned char SprPlayer1SquidDownFrame2[] = {
    0,-1,0x77,0|OAM_FLIP_V|OAM_FLIP_H,
    8,-1,0x76,0|OAM_FLIP_V|OAM_FLIP_H,
    0, 7,0x67,0|OAM_FLIP_V|OAM_FLIP_H,
    8, 7,0x66,0|OAM_FLIP_V|OAM_FLIP_H,
    128
};

const unsigned char SprPlayer1SquidLeftFrame2[] = {
    0,-1,0x79,0|OAM_FLIP_H|OAM_FLIP_V,
    8,-1,0x78,0|OAM_FLIP_H|OAM_FLIP_V,
    0, 7,0x69,0|OAM_FLIP_H|OAM_FLIP_V,
    8, 7,0x68,0|OAM_FLIP_H|OAM_FLIP_V,
    128
};

const unsigned char* const SprPlayer1SquidDown[] = {SprPlayer1SquidDownFrame1, SprPlayer1SquidDownFrame2};
const unsigned char* const SprPlayer1SquidRight[] = {SprPlayer1SquidRightFrame1, SprPlayer1SquidRightFrame2};
const unsigned char* const SprPlayer1SquidUp[] = {SprPlayer1SquidUpFrame1, SprPlayer1SquidUpFrame2};
const unsigned char* const SprPlayer1SquidLeft[] = {SprPlayer1SquidLeftFrame1, SprPlayer1SquidLeftFrame2};
const unsigned char* const * const SprPlayer1Squid[] = {SprPlayer1SquidDown, SprPlayer1SquidRight, SprPlayer1SquidUp, SprPlayer1SquidLeft};

const unsigned char SprPlayer2SquidUpFrame2[] = {
    0,-1,0x66,1,
    8,-1,0x67,1,
    0, 7,0x76,1,
    8, 7,0x77,1,
    128
};

const unsigned char SprPlayer2SquidUpFrame1[] = {
    0,-1,0x66,1,
    8,-1,0x67,1,
    0, 7,0x77,1|OAM_FLIP_H,
    8, 7,0x76,1|OAM_FLIP_H,
    128
};

const unsigned char SprPlayer2SquidRightFrame2[] = {
    0,-1,0x68,1,
    8,-1,0x69,1,
    0, 7,0x78,1,
    8, 7,0x79,1,
    128
};

const unsigned char SprPlayer2SquidDownFrame2[] = {
    0,-1,0x76,1|OAM_FLIP_V,
    8,-1,0x77,1|OAM_FLIP_V,
    0, 7,0x66,1|OAM_FLIP_V,
    8, 7,0x67,1|OAM_FLIP_V,
    128
};

const unsigned char SprPlayer2SquidLeftFrame2[] = {
    0,-1,0x69,1|OAM_FLIP_H,
    8,-1,0x68,1|OAM_FLIP_H,
    0, 7,0x79,1|OAM_FLIP_H,
    8, 7,0x78,1|OAM_FLIP_H,
    128
};

const unsigned char SprPlayer2SquidRightFrame1[] = {
    0,-1,0x78,1|OAM_FLIP_V,
    8,-1,0x79,1|OAM_FLIP_V,
    0, 7,0x68,1|OAM_FLIP_V,
    8, 7,0x69,1|OAM_FLIP_V,
    128
};

const unsigned char SprPlayer2SquidDownFrame1[] = {
    0,-1,0x77,1|OAM_FLIP_V|OAM_FLIP_H,
    8,-1,0x76,1|OAM_FLIP_V|OAM_FLIP_H,
    0, 7,0x67,1|OAM_FLIP_V|OAM_FLIP_H,
    8, 7,0x66,1|OAM_FLIP_V|OAM_FLIP_H,
    128
};

const unsigned char SprPlayer2SquidLeftFrame1[] = {
    0,-1,0x79,1|OAM_FLIP_H|OAM_FLIP_V,
    8,-1,0x78,1|OAM_FLIP_H|OAM_FLIP_V,
    0, 7,0x69,1|OAM_FLIP_H|OAM_FLIP_V,
    8, 7,0x68,1|OAM_FLIP_H|OAM_FLIP_V,
    128
};

const unsigned char* const SprPlayer2SquidDown[] = {SprPlayer2SquidDownFrame1, SprPlayer2SquidDownFrame2};
const unsigned char* const SprPlayer2SquidRight[] = {SprPlayer2SquidRightFrame1, SprPlayer2SquidRightFrame2};
const unsigned char* const SprPlayer2SquidUp[] = {SprPlayer2SquidUpFrame1, SprPlayer2SquidUpFrame2};
const unsigned char* const SprPlayer2SquidLeft[] = {SprPlayer2SquidLeftFrame1, SprPlayer2SquidLeftFrame2};
const unsigned char* const * const SprPlayer2Squid[] = {SprPlayer2SquidDown, SprPlayer2SquidRight, SprPlayer2SquidUp, SprPlayer2SquidLeft};

const unsigned char SprPlayer1RollerDownFrame1[] = {
    0,-1,0x40,0,
    8,-1,0x41,0,
    0, 7,0x50,0,
    8, 7,0x51,0,
    128
};

const unsigned char SprPlayer1RollerDownFrame2[] = {
    0,-1,0x42,0,
    8,-1,0x43,0,
    0, 7,0x52,0,
    8, 7,0x53,0,
    128
};

const unsigned char* const SprPlayer1RollerDown[] = {SprPlayer1RollerDownFrame1, SprPlayer1RollerDownFrame2};

const unsigned char SprPlayer1RollerRightFrame1[] = {
    0,-1,0x44,0,
    8,-1,0x45,0,
    0, 7,0x54,0,
    8, 7,0x55,0,
    128
};

const unsigned char SprPlayer1RollerRightFrame2[] = {
    0,-1,0x46,0,
    8,-1,0x47,0,
    0, 7,0x56,0,
    8, 7,0x57,0,
    128
};

const unsigned char* const SprPlayer1RollerRight[] = {SprPlayer1RollerRightFrame1, SprPlayer1RollerRightFrame2};

const unsigned char SprPlayer1RollerUpFrame1[] = {
    0,-1,0x48,0,
    8,-1,0x49,0,
    0, 7,0x58,0,
    8, 7,0x59,0,
    128
};

const unsigned char SprPlayer1RollerUpFrame2[] = {
    0,-1,0x4a,0,
    8,-1,0x4b,0,
    0, 7,0x5a,0,
    8, 7,0x5b,0,
    128
};

const unsigned char* const SprPlayer1RollerUp[] = {SprPlayer1RollerUpFrame1, SprPlayer1RollerUpFrame2};

const unsigned char SprPlayer1RollerLeftFrame1[] = {
    0,-1,0x45,0|OAM_FLIP_H,
    8,-1,0x44,0|OAM_FLIP_H,
    0, 7,0x55,0|OAM_FLIP_H,
    8, 7,0x54,0|OAM_FLIP_H,
    128
};

const unsigned char SprPlayer1RollerLeftFrame2[] = {
    0,-1,0x47,0|OAM_FLIP_H,
    8,-1,0x46,0|OAM_FLIP_H,
    0, 7,0x57,0|OAM_FLIP_H,
    8, 7,0x56,0|OAM_FLIP_H,
    128
};

const unsigned char* const SprPlayer1RollerLeft[] = {SprPlayer1RollerLeftFrame1, SprPlayer1RollerLeftFrame2};

const unsigned char* const * const SprPlayer1Roller[] = {SprPlayer1RollerDown, SprPlayer1RollerRight, SprPlayer1RollerUp, SprPlayer1RollerLeft};

const unsigned char SprPlayer1ChargerDownFrame1[] = {
    0,-1,0x00,0,
    8,-1,0x01,0,
    0, 7,0x10,0,
    8, 7,0x11,0,
    128
};

const unsigned char SprPlayer1ChargerDownFrame2[] = {
    0,-1,0x02,0,
    8,-1,0x03,0,
    0, 7,0x12,0,
    8, 7,0x13,0,
    128
};

const unsigned char* const SprPlayer1ChargerDown[] = {SprPlayer1ChargerDownFrame1, SprPlayer1ChargerDownFrame2};

const unsigned char SprPlayer1ChargerRightFrame1[] = {
    0,-1,0x04,0,
    8,-1,0x05,0,
    0, 7,0x14,0,
    8, 7,0x15,0,
    128
};

const unsigned char SprPlayer1ChargerRightFrame2[] = {
    0,-1,0x06,0,
    8,-1,0x07,0,
    0, 7,0x16,0,
    8, 7,0x17,0,
    128
};

const unsigned char* const SprPlayer1ChargerRight[] = {SprPlayer1ChargerRightFrame1, SprPlayer1ChargerRightFrame2};

const unsigned char SprPlayer1ChargerUpFrame1[] = {
    0,-1,0x08,0,
    8,-1,0x09,0,
    0, 7,0x18,0,
    8, 7,0x19,0,
    128
};

const unsigned char SprPlayer1ChargerUpFrame2[] = {
    0,-1,0x0a,0,
    8,-1,0x0b,0,
    0, 7,0x1a,0,
    8, 7,0x1b,0,
    128
};

const unsigned char* const SprPlayer1ChargerUp[] = {SprPlayer1ChargerUpFrame1, SprPlayer1ChargerUpFrame2};

const unsigned char SprPlayer1ChargerLeftFrame1[] = {
    0,-1,0x05,0|OAM_FLIP_H,
    8,-1,0x04,0|OAM_FLIP_H,
    0, 7,0x15,0|OAM_FLIP_H,
    8, 7,0x14,0|OAM_FLIP_H,
    128
};

const unsigned char SprPlayer1ChargerLeftFrame2[] = {
    0,-1,0x07,0|OAM_FLIP_H,
    8,-1,0x06,0|OAM_FLIP_H,
    0, 7,0x17,0|OAM_FLIP_H,
    8, 7,0x16,0|OAM_FLIP_H,
    128
};

const unsigned char* const SprPlayer1ChargerLeft[] = {SprPlayer1ChargerLeftFrame1, SprPlayer1ChargerLeftFrame2};

const unsigned char* const * const SprPlayer1Charger[] = {SprPlayer1ChargerDown, SprPlayer1ChargerRight, SprPlayer1ChargerUp, SprPlayer1ChargerLeft};
const unsigned char* const * const * const SprPlayer1[] = {SprPlayer1Squid, SprPlayer1Roller, SprPlayer1Charger};

const unsigned char SprPlayer2RollerDownFrame1[] = {
    0,-1,0x40,1,
    8,-1,0x41,1,
    0, 7,0x50,1,
    8, 7,0x51,1,
    128
};

const unsigned char SprPlayer2RollerDownFrame2[] = {
    0,-1,0x42,1,
    8,-1,0x43,1,
    0, 7,0x52,1,
    8, 7,0x53,1,
    128
};

const unsigned char* const SprPlayer2RollerDown[] = {SprPlayer2RollerDownFrame1, SprPlayer2RollerDownFrame2};

const unsigned char SprPlayer2RollerRightFrame1[] = {
    0,-1,0x44,1,
    8,-1,0x45,1,
    0, 7,0x54,1,
    8, 7,0x55,1,
    128
};

const unsigned char SprPlayer2RollerRightFrame2[] = {
    0,-1,0x46,1,
    8,-1,0x47,1,
    0, 7,0x56,1,
    8, 7,0x57,1,
    128
};

const unsigned char* const SprPlayer2RollerRight[] = {SprPlayer2RollerRightFrame1, SprPlayer2RollerRightFrame2};

const unsigned char SprPlayer2RollerUpFrame1[] = {
    0,-1,0x48,1,
    8,-1,0x49,1,
    0, 7,0x58,1,
    8, 7,0x59,1,
    128
};

const unsigned char SprPlayer2RollerUpFrame2[] = {
    0,-1,0x4a,1,
    8,-1,0x4b,1,
    0, 7,0x5a,1,
    8, 7,0x5b,1,
    128
};

const unsigned char* const SprPlayer2RollerUp[] = {SprPlayer2RollerUpFrame1, SprPlayer2RollerUpFrame2};

const unsigned char SprPlayer2RollerLeftFrame1[] = {
    0,-1,0x45,1|OAM_FLIP_H,
    8,-1,0x44,1|OAM_FLIP_H,
    0, 7,0x55,1|OAM_FLIP_H,
    8, 7,0x54,1|OAM_FLIP_H,
    128
};

const unsigned char SprPlayer2RollerLeftFrame2[] = {
    0,-1,0x47,1|OAM_FLIP_H,
    8,-1,0x46,1|OAM_FLIP_H,
    0, 7,0x57,1|OAM_FLIP_H,
    8, 7,0x56,1|OAM_FLIP_H,
    128
};

const unsigned char* const SprPlayer2RollerLeft[] = {SprPlayer2RollerLeftFrame1, SprPlayer2RollerLeftFrame2};

const unsigned char* const * const SprPlayer2Roller[] = {SprPlayer2RollerDown, SprPlayer2RollerRight, SprPlayer2RollerUp, SprPlayer2RollerLeft};

const unsigned char SprPlayer2ChargerDownFrame1[] = {
    0,-1,0x00,1,
    8,-1,0x01,1,
    0, 7,0x10,1,
    8, 7,0x11,1,
    128
};

const unsigned char SprPlayer2ChargerDownFrame2[] = {
    0,-1,0x02,1,
    8,-1,0x03,1,
    0, 7,0x12,1,
    8, 7,0x13,1,
    128
};

const unsigned char* const SprPlayer2ChargerDown[] = {SprPlayer2ChargerDownFrame1, SprPlayer2ChargerDownFrame2};

const unsigned char SprPlayer2ChargerRightFrame1[] = {
    0,-1,0x04,1,
    8,-1,0x05,1,
    0, 7,0x14,1,
    8, 7,0x15,1,
    128
};

const unsigned char SprPlayer2ChargerRightFrame2[] = {
    0,-1,0x06,1,
    8,-1,0x07,1,
    0, 7,0x16,1,
    8, 7,0x17,1,
    128
};

const unsigned char* const SprPlayer2ChargerRight[] = {SprPlayer2ChargerRightFrame1, SprPlayer2ChargerRightFrame2};

const unsigned char SprPlayer2ChargerUpFrame1[] = {
    0,-1,0x08,1,
    8,-1,0x09,1,
    0, 7,0x18,1,
    8, 7,0x19,1,
    128
};

const unsigned char SprPlayer2ChargerUpFrame2[] = {
    0,-1,0x0a,1,
    8,-1,0x0b,1,
    0, 7,0x1a,1,
    8, 7,0x1b,1,
    128
};

const unsigned char* const SprPlayer2ChargerUp[] = {SprPlayer2ChargerUpFrame1, SprPlayer2ChargerUpFrame2};

const unsigned char SprPlayer2ChargerLeftFrame1[] = {
    0,-1,0x05,1|OAM_FLIP_H,
    8,-1,0x04,1|OAM_FLIP_H,
    0, 7,0x15,1|OAM_FLIP_H,
    8, 7,0x14,1|OAM_FLIP_H,
    128
};

const unsigned char SprPlayer2ChargerLeftFrame2[] = {
    0,-1,0x07,1|OAM_FLIP_H,
    8,-1,0x06,1|OAM_FLIP_H,
    0, 7,0x17,1|OAM_FLIP_H,
    8, 7,0x16,1|OAM_FLIP_H,
    128
};

const unsigned char* const SprPlayer2ChargerLeft[] = {SprPlayer2ChargerLeftFrame1, SprPlayer2ChargerLeftFrame2};

const unsigned char* const * const SprPlayer2Charger[] = {SprPlayer2ChargerDown, SprPlayer2ChargerRight, SprPlayer2ChargerUp, SprPlayer2ChargerLeft};
const unsigned char* const * const * const SprPlayer2[] = {SprPlayer2Squid, SprPlayer2Roller, SprPlayer2Charger};

const unsigned char* const * const * const * const SprPlayers[] = {SprPlayer1, SprPlayer2};

/* Judd metasprites for post-game screen. */
const unsigned char judd_left[] = {
     0,0,0x60,1,
     8,0,0x61,1,
    16,0,0x62,0,
    24,0,0x63,0,
    32,0,0x64,0,

     0,8,0x70,1,
     8,8,0x71,1,
    16,8,0x72,0,
    24,8,0x73,0,
    32,8,0x74,0,

     0,16,0x80,1,
     8,16,0x81,1,
    16,16,0x82,0,
    24,16,0x83,0,
    32,16,0x84,0,

     0,24,0x90,1,
     8,24,0x91,1,
    16,24,0x92,0,
    24,24,0x93,0,
    32,24,0x94,0,

    128,
};

const unsigned char judd_tie[] = {
    0,0,0x65,0,
    8,0,0x62,0,
    16,0,0x63,0,
    24,0,0x64,0,

    0,8,0x75,0,
    8,8,0x72,0,
    16,8,0x73,0,
    24,8,0x74,0,

    0,16,0x85,0,
    8,16,0x82,0,
    16,16,0x83,0,
    24,16,0x84,0,

    0,24,0x95,0,
    8,24,0x92,0,
    16,24,0x93,0,
    24,24,0x94,0,

    128,
};

const unsigned char judd_right[] = {
    32,0,0x60,2|OAM_FLIP_H,
    24,0,0x61,2|OAM_FLIP_H,
    16,0,0x62,0|OAM_FLIP_H,
     8,0,0x63,0|OAM_FLIP_H,
     0,0,0x64,0|OAM_FLIP_H,

    32,8,0x70,2|OAM_FLIP_H,
    24,8,0x71,2|OAM_FLIP_H,
    16,8,0x72,0|OAM_FLIP_H,
     8,8,0x73,0|OAM_FLIP_H,
     0,8,0x74,0|OAM_FLIP_H,

    32,16,0x80,2|OAM_FLIP_H,
    24,16,0x81,2|OAM_FLIP_H,
    16,16,0x82,0|OAM_FLIP_H,
     8,16,0x83,0|OAM_FLIP_H,
     0,16,0x84,0|OAM_FLIP_H,

    32,24,0x90,2|OAM_FLIP_H,
    24,24,0x91,2|OAM_FLIP_H,
    16,24,0x92,0|OAM_FLIP_H,
     8,24,0x93,0|OAM_FLIP_H,
     0,24,0x94,0|OAM_FLIP_H,

    128,
};

/* Sprites for unselected stuff */
const unsigned char unselected_roller[] = {
    0,-1,0x40,2,
    8,-1,0x41,2,
    0, 7,0x50,2,
    8, 7,0x51,2,
    128
};

const unsigned char unselected_charger[] = {
    0,-1,0x00,2,
    8,-1,0x01,2,
    0, 7,0x10,2,
    8, 7,0x11,2,
    128
};
