#!/bin/bash



STATUS=$(playerctl shuffle 2> /dev/null || true)



if [ "$STATUS" == "On" ]; then
    printf "%%{F#dfdfdf}" #default color
    echo ""
else
    printf "%%{F#7f7f7f}";
    echo ""
    #echo ""
fi

#echo "$STATUS"

