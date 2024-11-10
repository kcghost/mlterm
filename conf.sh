#!/bin/bash

# based off debian choices
./configure \
--x-includes=/usr/X11R6/include \
--x-libraries=/usr/X11R6/lib \
--disable-rpath \
--disable-iiimf \
--enable-vt52 \
--x-includes=/usr/X11R6/include \
--with-imagelib=gdk-pixbuf \
--with-type-engines=xcore,xft,cairo \
--enable-optimize-redrawing \
--with-tools=mlclient,mlconfig,mlterm-menu,mlcc,mlterm-zoom \
--with-scrollbars=sample,extra,pixmap_engine
