#!/bin/bash

make install
UI_INSTALL_DIR=/usr/share/covcrav_rhw/ui
SOUNDS_INSTALL_DIR=/usr/share/covcrav_rhw/sounds
PIXMAPS_INSTALL_DIR=/usr/share/pixmaps
UI_FONTS_DIR=/usr/share/fonts
if [[ ! -d $UI_INSTALL_DIR ]]; then
	mkdir -p $UI_INSTALL_DIR
else
	echo "$UI_INSTALL_DIR already exist"
fi

if [[ ! -d $UI_INSTALL_SOUNDS ]]; then
        mkdir -p $SOUNDS_INSTALL_DIR
else
    	echo "$SOUNDS_INSTALL_DIR already exist"
fi

cp -v src/covcrav.ui  $UI_INSTALL_DIR/
cp -v po/pics/* $PIXMAPS_INSTALL_DIR/
cp -v po/pics/* $UI_INSTALL_DIR/
cp -rv po/zekton $UI_FONTS_DIR;cp -rv po/monofur $UI_FONTS_DIR
cp -rv po/sounds/* $SOUNDS_INSTALL_DIR
