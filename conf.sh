#!/bin/bash

# TODO: try debian "tiny" config

OPTS_COMMON=--x-includes=/usr/X11R6/include \
            --x-libraries=/usr/X11R6/lib \
            --disable-rpath \
            --disable-iiimf \
            --enable-vt52
          # --enable-utmp \

OPTS_TINY=$(OPTS_COMMON) \
          --with-type-engines=xcore \
          --with-tools=no \
          --with-scrollbars=sample \
          --disable-uim \
          --disable-m17nlib \
          --disable-scim \
          --disable-fcitx \
          --disable-ibus \
          --disable-wnn \
          --disable-canna \
          --disable-skk

OPTS_MAIN=$(OPTS_COMMON) \
          --with-imagelib=gdk-pixbuf --with-type-engines=xcore,xft,cairo \
          --enable-optimize-redrawing \
          --with-tools=mlclient,mlconfig,mlterm-menu,mlcc,mlterm-zoom \
          --with-scrollbars=sample,extra,pixmap_engine

./configure \
--x-includes=/usr/X11R6/include \
--x-libraries=/usr/X11R6/lib \
--x-includes=/usr/X11R6/include \
--with-type-engines=xcore \
--with-scrollbars=simple \
--with-utmp=none
