#!/bin/bash


#printf "%%{F#7f7f7f}";
#echo ""

STATUS=$(playerctl loop 2> /dev/null || true)

#echo $STATUS


if [ "$STATUS" == "Track" ]; then
    printf "%%{F#dfdfdf}";
    echo ""
elif [ "$STATUS" == "Playlist" ]; then
    printf "%%{F#dfdfdf}";
    echo ""
else
    #printf "%%{F#b6b6b6}";
    printf "%%{F#7f7f7f}";
    echo ""
fi
