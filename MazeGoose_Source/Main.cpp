#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ostream>
#include <stdlib.h>

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

	if (input) {
		while (getline(input, slice)) {
			slices.push_back(slice);
		}
	}
	
	int rows = slices.size();
	int columns = slices[0].size();

	std::cout << "Amount of rows: " << rows << std::endl
			  << "Amount of columns: " << columns << std::endl;

	int Maze_int[20][20] { 0 };

	int Finish_x, Finish_y; 
	int Start_x, Start_y;

	for (int iter_row = 0; iter_row < rows; iter_row++) {
		for (int iter_col = 0; iter_col < columns; iter_col++) {
			if (slices[iter_row][iter_col] == '.') {
				Maze_int[iter_row][iter_col] = 1;
			}
			else if (slices[iter_row][iter_col] == 'S') {
				Maze_int[iter_row][iter_col] = 2;
				Start_x = iter_col;
				Start_y = iter_row;
			}
			else if (slices[iter_row][iter_col] == 'F') {
				Maze_int[iter_row][iter_col] = 3;
				Finish_x = iter_col;
				Finish_y = iter_row;
			}
		}
	}
	std::cout << "Text maze:" << std::endl;
	for (const auto& item : slices) {
		std::cout << item << std::endl;
	}

	std::cout << std::endl;
	std::cout << "Initializations of maze \n0 = wall \n1=cave \n2 = start \n3= finish" << std::endl;

	for (int iter_y = 0; iter_y < rows; iter_y++) {
		for (int iter_x = 0; iter_x < columns; iter_x++) {
			std::cout << Maze_int[iter_y][iter_x];
		}
		std::cout << std::endl;
	}

	int Player_x = Start_x;
	int Player_y = Start_y;

	std::string operation;

	while ((Player_x != Finish_x) || (Player_y != Finish_y)) {
		system("CLS");
		std::cout << std::flush;
		for (int iter_y = 0; iter_y < rows; iter_y++) {
			for (int iter_x = 0; iter_x < columns; iter_x++) {
				if ((Player_x == iter_x) && (Player_y == iter_y)) {
					std::cout << 'P';
				} else{
					if (Maze_int[iter_y][iter_x] == 0) {
						std::cout << "+";
					}
					else if (Maze_int[iter_y][iter_x] == 2){
						std::cout << "A";
					}
					else if (Maze_int[iter_y][iter_x] == 1) {
						std::cout << " ";
					}
					else if (Maze_int[iter_y][iter_x] == 3) {
						std::cout << "U";
					}
					
				}
			}
			std::cout << std::endl;
		}
		std::cin >> operation;
		if (operation == "s") {
			if ((Player_y + 1 >= 0) && (Player_y + 1 <= rows) && (Maze_int[Player_y + 1][Player_x] != 0)){
				Player_y++;
			}
		}else if (operation == "a") {
			if ((Player_x - 1 >= 0) && (Player_x - 1 <= rows) && (Maze_int[Player_y][Player_x - 1] != 0)) {
				Player_x--;
			}
		}else if (operation == "d") {
			if ((Player_x + 1 >= 0) && (Player_x + 1 <= rows) && (Maze_int[Player_y][Player_x + 1] != 0)) {
				Player_x++;
			}
		}else if (operation == "w") {
			if ((Player_y - 1 >= 0) && (Player_y - 1 <= rows) && (Maze_int[Player_y - 1][Player_x] != 0)) {
				Player_y--;
			}
		}
	}


	return 0;
}