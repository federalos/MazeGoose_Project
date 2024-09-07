#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ostream>
#include <stdlib.h>
#include <cctype>
#include "Game.h"

/*
1. import map of labirinth from txt file
# - wall
F - destination
S - start

2. Draw the labirithm in consle

3. 

3. Route to exit algorithm
*/

/*
# - wall
. - cave
S - start
F - Finish
C - Player
*/
/*
void print_maze(const int& maze) {
	
}
*/

/* to-do
Control on button

Auto maze exit
	time to step
	max stupid AI
		randow choose of route crossroad
	Breadcrumbs

Competitive with AI
	Can you beat the stupid AI

Graphics
	
*/

int main() {
	std::string path_to_maze = "Maze1.txt";
	std::ifstream input(path_to_maze);
	std::vector<std::string> slices;
	std::string slice;

	Position start_pos, exit_pos;
	std::vector<Position> wall_pos, floor_pos;
	int iter_x = 0, iter_y=0;
	while (getline(input, slice)) {
		iter_x = 0;
		for (const auto& symbol : slice) {
			if (symbol == '#') {
				wall_pos.push_back({ iter_x ,iter_y });
			}
			else if (symbol == '.') {
				floor_pos.push_back({ iter_x ,iter_y });
			}
			else if (tolower(symbol) == 's') {
				start_pos = { iter_x ,iter_y };
				floor_pos.push_back({ iter_x ,iter_y });
			}
			else if (tolower(symbol) == 'f') {
				exit_pos = { iter_x ,iter_y };
				floor_pos.push_back({ iter_x ,iter_y });
			}
			iter_x++;
		}
		iter_y++;
	}

	// Init game engine
	Game game;

	game.setExit(exit_pos);
	game.setStart(start_pos);
	game.setWall(wall_pos);
	game.setFloor(floor_pos);

	// Game loop
	while (game.isRunning() && 
		((game.getExitPos().x != game.getPlayerPos().x)||(game.getExitPos().y != game.getPlayerPos().y))) {
		
		// Update
		game.update();
		// Render
		game.render();
	}
	std::cout << " Congratulation!" << "\n";
	return 0;
}