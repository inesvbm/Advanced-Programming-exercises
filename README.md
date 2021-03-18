# Advanced-Programming-exercises

## Dynamic programming
Given a set of n distinct points in the plane, p1,..., pn, and assuming that no point has larger or equal coordinate values than any other point in the set for both x and y-axis. Having k ≤ n, the goal is to choose a subset of k points that maximizes the union of the area covered by those points. The figure bellow is an example with n=4 and k=2; the pink region is the union of the area covered by two of the four points.

![image](https://user-images.githubusercontent.com/41116942/111553554-9034b580-877c-11eb-805c-57372080860a.png)

### Input
The first line of the test case gives the value of n (n ≤ 1200) and k, as positive integers. Then, in the following n lines, each point is described by its x and y coordinates as nonnegative reals with 12 digits of precision.
A file with an test case was added to the exercise folder.

### Output
The result will be the maximum area with 12 digits of precision.

### Solution
Bottom-up dynnamic programming algorithm, having in consideration that: P(i,j) is the subproblem of finding a subset of i points from the set pj,...., pn that contains pj and that maximizes the union of the area covered by those points.

## Finding connections
There are some main networks, and each one of these networks connects to the remaining networks only through a server. The current network cables do not support fast copies between servers, so one of the options is to directly connect all pairs of servers by cable, which is fast but expensive, and the other option is to use a tree topology, which is cheaper but slower.
The goal is to implement a program that locates all departmental servers and computes the amount of cable that is required for both options. In order to be cost effective, it must be considered the least amount of cable.
The following image shows the map of the network (servers in gray). 

![image](https://user-images.githubusercontent.com/41116942/111554772-e4409980-877e-11eb-8ab8-6cd6caf45e82.png)

### Input
The first line of each test case gives the amount of network equipment (n ≤ 1000) at the communication network (it is not known which nodes are servers). The following lines are pairs that correspond to the internal id of the network equipment that is directly connected with the existing cable and the length of that cable.

### Output
For each test case, print the number of servers, the total amount of cable for the case of
a fully connected network and the total amount of cable for a tree topology.

### Solution
- To know which equipments are servers, it was used Articulation Points algorithm;
- To find the direct path between each pair of equipments the Floyd-Warshall algorithm was chosen above Dijkstra and Bellman-Ford algorithms because it searches the shortest path between all pairs of vertexes (all-pairs shortest path), while the other algorithms start from a single vertex (single source shortest path);
- To find the best tree, it was used Kruskal algorithm.
