#!/bin/bash

STATUS=$(playerctl shuffle)

if [ $STATUS == "On" ]; then
    playerctl shuffle off;
    #echo "";
else
    playerctl shuffle on;
    #echo "";
fi

