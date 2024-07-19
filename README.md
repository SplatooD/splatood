# SplatooD: A Splatoon demake for NES

This is a modified version of splatood. I am not the original creator, I simply changed some things I didn't like about the original to learn some cc65 NES c programming.

![s](https://i.imgur.com/E1oPhVa.png) ![screenshot](http://i.imgur.com/jGOvsaF.png) ![s](https://i.imgur.com/y7Z1OsG.png)

## Game Manual

Check out http://splatood.github.io/

## Controls

D-pad to move, A to flick roller or fire charger, START to pause. Menus accept D-pad to move cursor and START to select an item.

## Building

Install [cc65](ftp://ftp.musoftware.de/pub/uz/cc65/cc65-sources-2.13.3.tar.bz2) v2.13.3 or thereabouts and then run `make`.

Assets were created in NESST and Famitracker.

### Updating Nametable Headers

There is a tool to convert binary nametables into C headers in `util/bin-to-h.py`.

## Cartridge Details

We target an NROM256 cartridge with two 16kB PRG ROMs and one 8kB CHR ROM.
