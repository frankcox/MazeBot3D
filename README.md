MazeBot3D
=========

A C++ class which tries to solves a text based 3D maze in the shortest path using a adaptation of Dijstra's algorithm.



DATA FILE FORMAT
----------------

The first line in the text based maze format is a number representing the number of levels in the maze. The next n lines are the rows and columns of the bottom level. Then there is one space and the next level, which must have the same width and height as the first. And so on, up to the number of levels. A "#" is a solid cell which the bot can't pass through. A "." is an empty cell that the bot can pass through and leave in one of up to six directions: North, South, East, West, Up, Down. The outside boundaries of the maze are also solid, and there is, at most, one exit. The beginning point has a "B" and the end point has a "E". There will be one each of B and E and they can be anywhere on any level.


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


The method printPathe() will print "Not Escapable" if no path to the exit is found. Otherwise, "Escapable" is printed along with a shortest path. For example:

Escapable SSSEEEEUNNNU


