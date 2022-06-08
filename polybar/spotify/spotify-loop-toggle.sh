#!/bin/bash

STATUS=$(playerctl loop)

LOOP[0]="None"
LOOP[1]="Playlist"
LOOP[2]="Track"


for i in {0..2}; do
    if [ ${LOOP[${i}]} == $STATUS ]; then
        break
    fi;
done;

i=$((i + 1))
i=$((i%3))

NEW_STATUS=${LOOP[${i}]}

playerctl loop $NEW_STATUS

#echo $i


#if [ $STATUS == "On" ]; then
#    playerctl shuffle off;
#    #echo "";
#else
#    playerctl shuffle on;
#    #echo "";
#fi

