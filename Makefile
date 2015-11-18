ROM_CONFIG = nrom.cfg
CRT_OBJ = crt0.o
GAME_OBJ = game.o
RUNTIME_LIB = runtime.lib

EXECUTABLE = splatood.nes

ASM = ca65
CC = cc65
LD = ld65


all: $(EXECUTABLE) ${CRT_OBJ}

crt0.o: *.s

%.s: %.c *.h
	$(CC) -Oi $< --add-source

%.o: %.s
	$(ASM) $<

$(EXECUTABLE): $(GAME_OBJ) $(ROM_CONFIG) $(CRT_OBJ) $(RUNTIME_LIB)
	$(LD) -C $(ROM_CONFIG) -o $(EXECUTABLE) $(CRT_OBJ) $(GAME_OBJ) $(RUNTIME_LIB)

clean:
	rm -f game.s *.o *.nes


.SECONDARY: # suppress removal of intermediate build files
%.o: %.c # suppress built in rule to build .o from .c
