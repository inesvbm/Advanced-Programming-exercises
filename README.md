# Advanced-Programming-exercises

## Dynamic programming
Given a set of n distinct points in the plane, p1,..., pn, and assuming that no point has larger or equal coordinate values than any other point in the set for both x and y-axis. Having k ≤ n, the goal is to choose a subset of k points that maximizes the union of the area covered by those points. The figure bellow is an example with n=4 and k=2; the pink region is the union of the area covered by two of the four points.

![image](https://user-images.githubusercontent.com/41116942/111553554-9034b580-877c-11eb-805c-57372080860a.png)

## Input
The first line of the test case gives the value of n (n ≤ 1200) and k, as positive integers. Then, in the following n lines, each point is described by its x and y coordinates as nonnegative reals with 12 digits of precision.
A file with an test case was added to the exercise folder.

## Output
The result will be the maximum area with 12 digits of precision.

## Solution
Bottom-up dynnamic programming algorithm, having in consideration that: P(i,j) is the subproblem of finding a subset of i points from the set pj,...., pn that contains pj and that maximizes the union of the area covered by those points.
