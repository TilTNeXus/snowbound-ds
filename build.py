#!/usr/bin/env python3

from architectds import *

nitrofs = NitroFS()
nitrofs.add_files_unchanged(['assets/audio'], 'audio')
nitrofs.add_grit(['assets/backgrounds'], 'backgrounds')
nitrofs.add_grit(['assets/characters'], 'characters')
nitrofs.add_nflib_font(['assets/font'], 'font')
nitrofs.add_grit(['assets/gui'], 'gui')
nitrofs.add_grit(['assets/images'], 'images')
nitrofs.add_nflib_bg_tiled(['assets/nf'], 'nf')
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
