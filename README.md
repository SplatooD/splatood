# SplatooD: A Splatoon demake for NES

![screenshot](http://i.imgur.com/jGOvsaF.png)

## Controls

D-pad to move, A to flick roller, START to pause. Menus accept D-pad to move cursor and START to select an item.

## Building

Install [cc65](ftp://ftp.musoftware.de/pub/uz/cc65/cc65-sources-2.13.3.tar.bz2) v2.13.3 or thereabouts and then run `make`.

Assets were created in NESST and Famitracker.

### Updating Nametable Headers

There is a tool to convert binary nametables into C headers in `util/bin-to-h.py`.

## Cartridge Details

We target an NROM256 cartridge with two 16kB PRG ROMs and one 8kB CHR ROM.
