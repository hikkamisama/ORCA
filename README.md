# ORCA
a simple version of ORCA algorithm; a programming project for HSE university

## Preset

Agents are represented by circles on a 2d grid, each willing to reach their goal point. They move simultaneously, with the ability to view each other's positions, radiuses and current velocities. ORCA algorithm provides the possibility of collision avoidant movement and goal achievement for all agents (except for deadlock scenarios).

## How does it work?

### Input data

In a **.txt** file, the following data is required for the algorithm:

    <Number of agents>
   
    (for each agent): 
  
    <radius> <max speed>
    <goal x coordinate> <goal y coordinate>
    <starting x coordinate> <starting y coordinate>

### Stages of the algorithm

Each **tau** seconds the movement is interrupted, and the following calculations are performed for each pair of agents:

1. Velocity obstacle (VO) is structed

<img width="446" alt="image" src="https://user-images.githubusercontent.com/90105119/164917107-2da85d59-25e7-40ae-8dae-9ab874b1bdf9.png">

2. Vectors **u** and **n** are found, creating the ORCA half-plane 

<img width="556" alt="image" src="https://user-images.githubusercontent.com/90105119/164917186-78b42c10-ce65-44f4-9278-906c90797ae8.png">

3. Half planes are intersected (and intersected with a polygon, representing maximal speed for the agent)

<img width="711" alt="image" src="https://user-images.githubusercontent.com/90105119/164918036-5fe2c350-2879-42f7-bf57-2046c3432bbb.png">

4. Agents adopt new velocities and move to new positions

## How to compile?

The folowing line builds the project:

    g++ main.cpp -std=c++17 -Wall -w -o ORCA.out
    
You may want to reload input and output, as the program dumps a lot of information to **std::cout** and to **std::cerr**:

    ./ORCA.out < input.txt > output.txt
    
Information from **std::cerr** can be pasted to [this geometry widget](https://csacademy.com/app/geometry_widget/) to look at the paths


## To do:

1. Convex hull is built with a primitive O(n^2) algorithm, should improve to O(n)
2. In case of dense conditions the algorithm fails almost certainly, should add deadlock solutions
3. Should implement a normal visual interpreter, with colors and animation (using python)
