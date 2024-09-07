#include "Game.h"
// Constructor
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initPlayer();
	this->initEnter();
	this->initExit();
	this->initfloor();
	this->initWall();
}
// Destructor
Game::~Game()
{
	delete this->window;
}
// Accessors
const bool Game::isRunning() const
{
	return this->window->isOpen();
}

const Position Game::getPlayerPos() const
{
	return player_pos;
}

const Position Game::getExitPos() const
{
	return exit_pos;
}



// Setters
void Game::setStart(const Position& pos)
{
	start_pos = pos;
	player_pos = start_pos;
}

void Game::setExit(const Position& pos)
{
	exit_pos = pos;
}

void Game::setFloor(const std::vector<Position>& pos)
{
	floor_pos = pos;
}

void Game::setWall(const std::vector<Position>& pos)
{
	wall_pos = pos;
}

// Public functions


// Game logic update
void Game::update()
{
	this->updateEvents();
}
// Visualisation: slice of game world
void Game::render()
{
	this->window->clear(); // Clear frame

	// Draw game objects
	for (const auto& item : wall_pos) {
		wall_sp.setPosition(item.x*40, item.y*40);
		this->window->draw(this->wall_sp);
	}
	for (const auto& item : floor_pos) {
		floor_sp.setPosition(item.x * 40, item.y * 40);
		this->window->draw(this->floor_sp);
	}
	enter_sp.setPosition(start_pos.x*40, start_pos.y*40);
	this->window->draw(this->enter_sp);
	exit_sp.setPosition(exit_pos.x*40, exit_pos.y*40);
	this->window->draw(this->exit_sp);
	player_sp.setPosition(player_pos.x*40, player_pos.y*40);
	this->window->draw(this->player_sp);
	

	
	this->window->display(); // Point where drawing is stoped
}

void Game::updateEvents()
{
	while (this->window->pollEvent(this->event)) {
		switch (this->event.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->event.key.code == sf::Keyboard::Escape){
				this->window->close();
				break;
			}
			else if (this->event.key.code == sf::Keyboard::Up) {
				playerMove({0,-step_y});
			}
			else if (this->event.key.code == sf::Keyboard::Down) {
				playerMove({ 0,+step_y });
			}
			else if (this->event.key.code == sf::Keyboard::Left) {
				playerMove({ -step_x,0 });
			}
			else if (this->event.key.code == sf::Keyboard::Right) {
				playerMove({ +step_x,0 });
			}
		}
	}
}


// Private functions
void Game::initVariables()
{
	this->window = nullptr;

	step_x = 1;
	step_y = 1;

}

void Game::initWindow()
{
	this->videoMode.height = 900;
	this->videoMode.width = 1600;
	this->window = new sf::RenderWindow(this->videoMode, "Goose Maze");

	this->window->setFramerateLimit(60);
}

void Game::initPlayer()
{
	// Create a texure
	//sf::Texture texture_name;
	// Load a texture
	//texture_name.loadFromFile(path to file);
	// Create a sprite
	//sf::Sprite Sprite_name;
	// Set the texture of sprite as loaded one
	//Sprite_name.setTexture(texture_name);
	this->player_tx.loadFromFile("images/goose_left.png", sf::IntRect(0,0,40,40));
	this->player_sp.setTexture(player_tx);
}

void Game::initExit()
{
	// Placeholder
	this->exit_tx.loadFromFile("images/exit.png", sf::IntRect(0, 0, 40, 40));
	this->exit_sp.setTexture(exit_tx);
}

void Game::initEnter()
{
	// Placeholder
	this->enter_tx.loadFromFile("images/enter.png", sf::IntRect(0, 0, 40, 40));
	this->enter_sp.setTexture(enter_tx);
}

void Game::initWall()
{
	this->wall_tx.loadFromFile("images/wall.png", sf::IntRect(0, 0, 40, 40));
	this->wall_sp.setTexture(wall_tx);
}

void Game::initfloor()
{
	this->floor_tx.loadFromFile("images/green_camo.png", sf::IntRect(0, 0, 40, 40));
	this->floor_sp.setTexture(floor_tx);
}

void Game::playerMove(const Position& shift)
{
	if (IsCollisionWall({player_pos.x+shift.x,player_pos.y + shift.y })) {
		player_pos.x += shift.x;
		player_pos.y += shift.y;
	}
}

bool Game::IsCollisionWall(const Position& pos)
{
	for (const auto& item : floor_pos) {
		if (pos.x == item.x) {
			if (pos.y == item.y){
				return true;
			}
		}
	}
	return false;
}
