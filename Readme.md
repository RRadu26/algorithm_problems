walsh - a problem in which we use Walsh Tables. Given x, y - coordonates who
indicated the element found at the line x and column y, what element is there?
1 or 0. 
	Input - walsh.in
		first line : N - Walsh table dimension
		second line: K
		next K lines : x y, which represents lines and columns
	Out - k lines, the result of the problem for each coordinates from walsh.in

statistics - problem: given a list of N encrypted words, what is the maximum 
amout of words from the list which have a dominant letter?
	Input - statistics.in
		first line : N
		next N lines: words
	Output: the result 

fortificatii - given a cost graph who represents a map of cities(nodes) and roads,
in which the cities are controlled by the romans of barbarians, in which we can
choose to build K fortification - which will slow the barbarians, what is the
minimum cost in which a barbarian army can reach the empire capital?
	Input - fortificatii.in
		first line: N - nodes M - connections
		second line: B - barbarian nodes
		next B lines - index of barbarian nodes
		next M lines - X Y Z - X,Y nodes connected, Z - connection cost
	Output - the result

curatare.cpp - given a 2D grid map of a "house", in which a cell can represent: the initial location
of a cleaning robot, nothing, a dirty spot or a wall, what is the minimum time
in which the robots can clean the whole house?
	Input: curatare.in
		first line: N,M - size of the grid
		next N lines : M characters representing the cells, as follows:
		. - free space
		R - starting point for a robot
		S - dirty spot
		X - wall
	Output - the result
