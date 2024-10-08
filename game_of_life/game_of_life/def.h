#include<vector>
#include<iostream>
#include<SFML/Graphics.hpp>

namespace def {
	
	/* 
		Underpopulation:
		  If a living cell has fewer than 2 living neighbors, it dies (as if by underpopulation).

		Overcrowding:
		  If a living cell has more than 3 living neighbors, it dies (as if by overpopulation).

		Survival:
		  If a living cell has 2 or 3 living neighbors, it survives to the next generation.

		Reproduction:
		  If a dead cell has exactly 3 living neighbors, it becomes a living cell (as if by reproduction).
	
	*/


}