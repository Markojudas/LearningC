* Programmer:       Jose R Hernandez
* Panther ID:         1398700
* Course:               Systems Programming - COP4338 U01 1211
* Instructor:           Kianoosh G. Boroojeni, Ph.D.
* Assignment:        4


README FILE:

IMPLEMENTED

commands:

*'quit' command: Terminates the program by escaping the infinite while loop

*'add <x1y1x2y2........xnyx>' command: creates a polygon with the given input. It accepts a total of 100 vertices. Once the polygon is created it is then stored into the program's list of polygons.
                                                        Accepts about 1000 polygons

*'turn <k> <DIRECTION>' command: sets the polygon's shift direction from NONE (0) to a chosen direction: up (1) down (2) left (4) right (8) up-right(9) up-left(5) down-right(10) down-left(6)

*'shift <k> <N>' command: it moves the polygon, updating the x-y coordinates of each vertices of polygon k, N number of spaces in the chosen direction.


---
*Created a static array of type Polygon to store all polygons created.
*Created a struct  function of type Vertex to create a vertex from the input
*inside the add command created an array of type Vertex* to keep a list of vertices of the polygons


