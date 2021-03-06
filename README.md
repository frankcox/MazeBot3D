MazeBot3D
=========

A C++ class which tries to solves a text based 3D maze in the shortest path using a adaptation of Dijkstra's algorithm.

THE GAME
--------

A bot begins in a 3D maze of empty and solid cells. It's inside the cell "start", and tries to find the shortest path to the cell "end" where it can escape the maze. It can only examine adjacent cells and only if they are north, south, east, west, up, or down. No diagonals. It can move in those same directions into adjacent cells, only if they're empty. The bot can't move outside the maze except through the exit at the end.

The program knows the location of the end point but doesn't use it to find the route. It only uses it to identify the exit. That's an arbitrary rule of this version of the game. It might be interesting to relax this rule and try to apply the ideas in the A* algorithum to speed things up in big open playgrounds. Give it a try!

    Also, The lack of diagonals means the path SESE 

    x
    xx
     xx

    is the same length as SSEE

    x
    x
    xxx

It would be interesting to add diagonals. This would be tedious with the current code but totally doable. Of course we'd have to come up with names for all the, what? Twenty something new directions... And why stop there? Why not just cut loose and use 3D vectors of any direction? Dijkstra's could still handle it!


DATA FILE FORMAT
----------------

The first line in the text based maze file format is a number representing the number of levels in the maze. The next n lines are the rows and columns of the bottom level. Then there is one space and the next level, which must have the same width and height as the first. And so on, up to the number of levels. A "#" is a solid cell which the bot can't pass through. A "." is an empty cell that the bot can move into, and leave, in one of up to six directions: North, South, East, West, Up, Down. The outside boundaries of the maze are also solid, and there is, at most, one exit. The beginning point has a "B" and the end point has a "E". There will be one each of B and E and they can be anywhere on any level.


EXAMPLE:

    3
    B####
    .####
    .####
    .....

    #..#.
    #..#.
    #..#.
    ####.

    ..#.E
    ..#..
    ..#..
    .....


The method printPath() will print "Not Escapable" if no path to the exit is found. Otherwise, "Escapable" is printed along with a shortest path. For example:

Escapable SSSEEEEUNNNU

How to Build
------------

I built this with g++ on Linux but it should build on any modern C++. 
There's a simple Make file, but "g++ client.cpp" on the command
line should be all you need. If you use Make the executable is mazebot.exe.



