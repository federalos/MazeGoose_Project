#pragma once

#include <SFML/Graphics.hpp>

/*
	Simple game engine
*/
struct Position
{
	int x;
	int y;
};


class Game
{
public:
	// Constructors
	Game();
	// Destructors
	~Game();
	// Accessors
	const bool isRunning() const;
	const Position getPlayerPos() const;
	const Position getExitPos() const;
	
	// Setters
	void setStart(const Position& pos);
	void setExit(const Position& pos);
	void setFloor(const std::vector<Position>& pos);
	void setWall(const std::vector<Position>& pos);

	// Function
	void update();

	void render();

	void updateEvents();

private:
	// Window and Variables
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;
	
	// Game objects
	sf::Texture player_tx;
	sf::Sprite player_sp;

	sf::Texture exit_tx;
	sf::Sprite exit_sp;

	sf::Texture enter_tx;
	sf::Sprite enter_sp;

	sf::Texture wall_tx;
	sf::Sprite wall_sp;

	sf::Texture floor_tx;
	sf::Sprite floor_sp;

	// Game logic
	Position start_pos;
	Position player_pos;
	Position exit_pos;
	std::vector<Position> wall_pos;
	std::vector<Position> floor_pos;
	int step_x;
	int step_y;

	// Private functions
	void initVariables();
	void initWindow();
	void initPlayer();
	void initExit();
	void initEnter();
	void initWall();
	void initfloor();

	void playerMove(const Position& shift);

	bool IsCollisionWall(const Position& pos);
};

