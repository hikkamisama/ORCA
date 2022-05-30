#!/bin/bash

read num_exp

in_name="input"
in_name+=$num_exp
in_name+=".txt"

gif_name="mygif"
gif_name+=$num_exp
gif_name+=".gif"

rm gifs/$in_name

rm gifs/$gif_name