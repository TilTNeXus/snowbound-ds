#!/usr/bin/env python3

import os
import sys
sys.path.insert(0, "architectds/architectds")
from architectds import *
import crc

examplesdir = os.path.join("src", "tiny-json", "examples")
if os.path.exists(examplesdir):
    for file in os.listdir(examplesdir):
        os.remove(os.path.join(examplesdir, file))

testdir = os.path.join("src", "tiny-json", "test")
if os.path.exists(testdir):
    for file in os.listdir(testdir):
        os.remove(os.path.join(testdir, file))

nitrofs = NitroFS()
nitrofs.add_files_unchanged(['assets/audio'], 'audio')
nitrofs.add_grit(['assets/backgrounds'], 'backgrounds')
nitrofs.add_grit(['assets/characters'], 'characters')
nitrofs.add_grit(['assets/font'], 'font')
nitrofs.add_bmfont_fnt(['assets/font'], 'font')
nitrofs.add_grit(['assets/gui'], 'gui')
nitrofs.add_grit(['assets/images'], 'images')
nitrofs.add_nflib_bg_tiled(['assets/nf'], 'nf')
nitrofs.add_files_unchanged(['assets/scripts'], 'scripts')
nitrofs.generate_image()

arm9 = Arm9Binary(
    sourcedirs=['src'],
    libs=['NE', 'nflib', 'nds9'],
    libdirs=[
        '${BLOCKSDS}/libs/libnds',
        '${BLOCKSDSEXT}/nitro-engine',
        '${BLOCKSDSEXT}/nflib'
    ]
)
arm9.generate_elf()

nds = NdsRom(
    binaries=[arm9, nitrofs],
    game_title='Snowbound Blood',
    game_subtitle='',
    game_author='Deconreconstruction',
    game_icon='banner.png'
)
nds.generate_nds()

nds.run_command_line_arguments()

if len(sys.argv) == 1:
    calculator = crc.Calculator(crc.Crc16.MODBUS)
    with open("snowbound-ds.nds", "rb+") as rom:
        rom.write("SNOWBOUND_BL".encode(encoding="ascii"))
        check_range = rom.read()[0:350]
        checksum = calculator.checksum(check_range)
        rom.seek(350, 0) 
        rom.write(checksum.to_bytes(2, byteorder="little"))