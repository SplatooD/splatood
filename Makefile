ROM_CONFIG = nrom.cfg
CRT_OBJ = crt0.o
GAME_OBJ = game.o
RUNTIME_LIB = nes.lib
CC65_HOME = /usr/share/cc65
EXECUTABLE = splatood.nes

ASM = ca65
CC = cc65
LD = ld65


all: $(EXECUTABLE) ${CRT_OBJ}

crt0.o: *.s *.chr

%.s: %.c *.h levels/*.h
	$(CC) -Oi $< --add-source

%.o: %.s
	CC65_HOME=$(CC65_HOME) $(ASM) $<

$(EXECUTABLE): $(GAME_OBJ) $(ROM_CONFIG) $(CRT_OBJ)
	CC65_HOME=$(CC65_HOME) $(LD) -C $(ROM_CONFIG) -o $(EXECUTABLE) $(CRT_OBJ) $(GAME_OBJ) $(RUNTIME_LIB)

clean:
	rm -f game.s *.o *.nes


.SECONDARY: # suppress removal of intermediate build files
%.o: %.c # suppress built in rule to build .o from .c
