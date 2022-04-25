# Several experiments were carried out

These are simple visualizations and input data for the algorithm

## №1 - 3 cyclic objectives

![image](https://user-images.githubusercontent.com/90105119/165098731-ab44487b-56dc-4066-a0d3-16cc0249f90b.png)

    3

    3.5 0.5
    8 0
    0 0

    3.5 0.5
    4 -7
    8 0

    3.5 0.5
    0 0
    4 -7
    
## №2 - 4 cyclic objectives

![image](https://user-images.githubusercontent.com/90105119/165099105-d92fa4ed-b5eb-455e-9fd2-a18636aae144.png)


    4

    2.4 0.3
    -3 3
    3 3

    2.4 0.3
    -3 -3
    -3 3

    2.4 0.3
    3 -3
    -3 -3

    2.4 0.3
    3 3
    3 -3
    
 
## №3 - slight trade-off 

![image](https://user-images.githubusercontent.com/90105119/165101127-82ace10e-c983-4ada-b70e-f080577f13df.png)

    2

    2 0.3
    10 1
    0 1

    2 0.3
    -2 0
    8 0
    
## №4 - easy crossroad

![image](https://user-images.githubusercontent.com/90105119/165101308-163ac6ac-5fb9-4483-a62f-1372c555ebe5.png)

    3

    1 0.3
    10 1
    0 1

    1 0.3
    -2 0
    8 0

    1 0.3
    5 -4
    5 5
    
# Deadlocks and fails

## №1 - goals on one line

![image](https://user-images.githubusercontent.com/90105119/165101787-fd531777-8e85-4236-8d85-cf7c19dbfd19.png)

    2

    3.5 0.5
    8 0
    0 0

    3.5 0.5
    0 0
    8 0
    
## №2 - crossroad that failed

![image](https://user-images.githubusercontent.com/90105119/165102021-1360a0f6-88f9-41f3-ac19-3e649fa21362.png)

    3

    1 0.3
    10 1
    0 1

    1 0.3
    -2 0
    8 0

    1 0.3
    5 -4
    5 3

![image](https://user-images.githubusercontent.com/90105119/165102060-290b18a9-97c9-46b3-87dc-09f697648786.png)

    3

    1 0.3
    10 1
    0 1

    1 0.3
    -2 0
    8 0

    1 0.3
    5 -4
    5 4

## №3 - static object doesn't work 

![image](https://user-images.githubusercontent.com/90105119/165102391-4af34a46-3f91-45f6-b11d-4c6507e3d7a3.png)

(and then we allow the static object to be pushed with a certain `v_max`)

![image](https://user-images.githubusercontent.com/90105119/165102590-e3532f47-bae7-4584-9fcb-316803ce909a.png)
