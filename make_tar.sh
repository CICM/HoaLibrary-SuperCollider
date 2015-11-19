#!/bin/bash

rm ~/Desktop/Hoa_SC/*

rm ~/Desktop/Hoa_SC.tar

cp *.scx ~/Desktop/Hoa_SC/

cp /Users/claudiocabral/GIT/HoaLibrary-SuperCollider/src/sc/Classes/*.sc ~/Desktop/Hoa_SC/

cd ~/Desktop/

tar -cf Hoa_SC.tar Hoa_SC 

