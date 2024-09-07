#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ostream>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <cctype>

//int main()
//{
//	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
//	sf::CircleShape shape(20.f);
//	shape.setFillColor(sf::Color::Green);
//
//	while (window.isOpen())
//	{
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//				window.close();
//		}
//
//		window.clear();
//		window.draw(shape);
//		window.display();
//	}
//
//	return 0;
//}
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

const int Height = 20;
const int Width = 20;

struct Position
{
	int x;
	int y;
};

class Maze
{
public:
	Maze(const std::vector<std::string> slices) {
		boundary.x = slices[0].size();
		boundary.y = slices.size();
		
		for (int iter_y = 0; iter_y < boundary.y; iter_y++){
			for (int iter_x = 0; iter_x < boundary.x; iter_x++) {
				if (slices[iter_y][iter_x] == 'S') {
					walls[iter_y][iter_x] = true;
					start.x = iter_x;
					start.y = iter_y;
					player.x = start.x;
					player.y = start.y;
				}
				else if (slices[iter_y][iter_x] == 'F'){
					walls[iter_y][iter_x] = true;
					finish.x = iter_x;
					finish.y = iter_y;
				}
				else if (slices[iter_y][iter_x] == '.'){
					walls[iter_y][iter_x] = true;
				} else{
					walls[iter_y][iter_x] = false;
				}
			}
		}
	}
	void print() const {
		for (int iter_y = 0; iter_y < boundary.y; iter_y++) {
			for (int iter_x = 0; iter_x < boundary.x; iter_x++) {
				if (walls[iter_y][iter_x]) {
					if ((iter_x == player.x) && (iter_y == player.y)) {
						std::cout << "X";
					}
					else if ((iter_x == start.x) && (iter_y == start.y)) {
						std::cout << "A";
					}
					else if ((iter_x == finish.x) && (iter_y == finish.y)) {
						std::cout << "O";
					}
					else {
						std::cout << " ";
					}
				}
				else {
					std::cout << "#";
				}
			}
			std::cout << std::endl;
		}
	}
	
	void movement(const char& command) {
		if (tolower(command) == 's') {
			if (colisionCheck({ player.x, (player.y + 1) })) {
				player.y++;
			}
		}
		else if (tolower(command) == 'a') {
			if (colisionCheck({ (player.x - 1), player.y })) {
				player.x--;
			}
		}
		else if (tolower(command) == 'w') {
			if (colisionCheck({ player.x, (player.y - 1) })) {
				player.y--;
			}
		}
		else if (tolower(command) == 'd') {
			if (colisionCheck({ (player.x + 1), player.y })) {
				player.x++;
			}
		}
	}
	
	Position getPlayer() const {
		return player;
	}
	Position getStart() const {
		return start;
	}
	Position getFinish() const {
		return finish;
	}


private:
	bool colisionCheck(const Position& pos) {
		if (!(walls[pos.y][pos.x]) ||
			(pos.x > boundary.x) || (pos.y > boundary.y)||
			(pos.x < 0) || (pos.y < 0)) {
			return false;
		}
		return true;
	}
	
	Position player;
	Position start;
	Position finish;
	bool walls[Height][Width]{false};
	Position boundary;
};

std::vector<std::string> ParseTXT(const std::string& path) {
	
	std::ifstream input(path);
	std::vector<std::string> slices;
	std::string slice;
	if (input) {
		while (getline(input, slice)) {
			slices.push_back(slice);
		}
	}
	return slices;
}

bool operator==(const Position& lhs, const Position& rhs) {
	return ((lhs.x == rhs.x)&&(lhs.y==rhs.y));
}

bool operator!=(const Position& lhs, const Position& rhs) {
	return ((lhs.x != rhs.x) || (lhs.y != rhs.y));
}

int main() {
	std::string path_to_maze = "Maze1.txt";
	std::vector<std::string> ReadedMaze = ParseTXT(path_to_maze);
	
	Maze maze(ReadedMaze);

	char command;
	while (maze.getPlayer() != maze.getFinish()){
		system("CLS");
		std::cout << "X - you are here" << std::endl
			<< "O - exit from the Maze" << std::endl
			<< "A - enter to the Maze" << std::endl
			<< "# - wall" << std::endl << std::endl
			<< "AAAVVV_THE MAZE_VVVAAA" << std::endl << std::endl;

		maze.print();


		std::cout << std::endl << std::endl
			<< "/|\\|//|\\|//|\\|//|\\|/" << std::endl 
			<<" _CONTROL_" << std::endl
			<< "w - go up" << std::endl
			<< "s - go down" << std::endl
			<< "a - go left" << std::endl
			<< "d - go right" << std::endl
			<< "WHAT IS YOUR NEX MOVE< ADVENTURE? ";
		std::cin >> command;
		maze.movement(command);
	}

	
	return 0;
}