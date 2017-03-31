# N-body-Treecode
A N-body simulation (NlogN cost) based on treecode structure and leapfrog algorithm in C++

The code will read in galaxy data from INPUTFILE in the sequence of (Mass Position_x Position_y Position_z Velocity_x Velocity_y Velocity_z)XN

Afterwards a Treecode helps construct a tree for analyzing the forces between each object, and obtains its acceleration.
The LEAPFROG algorithm is employed to calculate the movement of all objects.

The gravity constant is set to 1.
The dimension of the Tree is set to (100,100,100) in x/y/z, with the original at (0,0,0). 
Soften Distance can be inputed as parameters:  F = -G * M_1 * M_2 /  (r^2 + soften_distance^2) 

The distance criterion is set for evaluating if the object is far away enough to a given node : 
The node dimension is D and the distance between node center and the object is R. If D/R < distance_criterion, 
the node may be treat as far from the object so that all objects inside the node can be integrated as ONE mass point in the node.


Usage: 
ExecutiveFileName  Inputfilename  SoftenDistance  DistanceCriterion  TotalSteps  StepInterval_dt  [number_of_objects_in_each_celecial_body]

Example:
Stars.txt contains:
0.05  1  1  1   0.5  0.5 0.5       //  Star No.1 in Galaxy Bulge
0.05  1  2  1   0.4  -0.2  0.3     //  Star No.2
0.13  6  5   5   0.4  0.7  -0.2    //  Star No.1 in Galaxy Disk
0.13 -6 -5  -5  -0.4  0.2  0.3     //  Star No.2
0.13  6 -5  -5   0.4  0.2  0.3     //  Star No.3
0.13 -6 -5   5  -0.4  0.2 -0.3     //  Star No.4
0.13 -6  5  -5  -0.4  -0.2  0.3     //  Star No.5
0.13  6  5  -5   0.4  0.2  0.3     //  Star No.6

To run: 
ExecutiveFileName  Stars.txt  0.25  0.5  200 0.1  2 6
