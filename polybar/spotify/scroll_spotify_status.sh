#!/bin/bash

# see man zscroll for documentation of the following parameters

# --- old configuration ---
##zscroll -l 40 \
        ##--delay 0.3 \
        ##--scroll-padding "              " \

#-------------------------------

##        --delay 0.07 \

zscroll -l 20 \
        --delay 0.5 \
        --scroll-padding "        " \
        --match-command "$HOME/.config/polybar/scripts/spotify/get_spotify_status.sh --status" \
        --match-text "Playing" "--scroll 1" \
        --match-text "Paused" "--scroll 0" \
        --update-check true "$HOME/.config/polybar/scripts/spotify/get_spotify_status.sh" \
        --update-interval=1 &

wait
