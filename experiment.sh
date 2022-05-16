#!/bin/bash

read num_exp

in_name="input"
in_name+=$num_exp
in_name+=".txt"

gif_name="mygif"
gif_name+=$num_exp
gif_name+=".gif"

./zapusk.sh

touch gifs/$in_name

cat input.txt > gifs/$in_name

cp mygif.gif gifs/$gif_name