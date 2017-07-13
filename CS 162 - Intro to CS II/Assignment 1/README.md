Conway's Game of Life:
 - creates a 40 x 20 matrix of cells
 - each generation, the value of each vell may change based upon its neighbors
 - rules:
	- if an occupied cell has 0 or 1 neighbor, it dies of loneliness
	- if an occupied cell has more than 3 neighbors, it dies of overcrowding
	- if an empty vell has exactly 3 occupied neighbors, there is a birth of a new cell to replace the empty cell
	- births and deaths are instantaneous and occue at the changes of generation