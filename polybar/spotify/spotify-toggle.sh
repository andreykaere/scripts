#!/bin/bash

#playerctl play-pause spotify


STATUS=$(~/.config/polybar/scripts/spotify/get_spotify_status.sh --status)

if [ "$STATUS" == "Playing" ]; then
    playerctl --all-players pause;
    echo "%{T3}";
else 
    playerctl --all-players play;
    echo "%{T3}";
fi



echo $STATUS
