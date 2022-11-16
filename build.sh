#!/bin/sh
clear
cc breakout.c `pkg-config --libs --cflags raylib` -o breakout
./breakout