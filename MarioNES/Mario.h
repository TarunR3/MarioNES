#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

class Mario
{
private:
	sf::Texture texture;
	sf::Vector2f position;
	sf::RectangleShape hitbox;

	sf::Clock frameCounter;
	int mushroom_count = 0;
	int hit_count = 0;
	int finish_counter = 0;

	float scale = 3.5f;
	float xFrame = 0.0f;

	bool a = false;
	bool left = false;
	bool right = false;

	bool collide = false;
	bool right_collide = false;
	bool left_collide = false;

public:
	Mario();
	void animate(std::string animation);
	void update(float deltaTime, std::vector<sf::Sprite> tiles);

	bool rc(sf::Sprite tile);
	bool lc(sf::Sprite tile);
	bool onTop(sf::Sprite tile);
	bool beneath(sf::Sprite tile);

	sf::Vector2f getPosition();

	sf::Sprite sprite;
	sf::Vector2f velocity;
	sf::RectangleShape vision;

	std::string key;

	int coin = 0;

	bool dead = false;

	bool small = true;
	bool finish = false;
	int stage = 0;

	bool pause = false;
	bool can_be_hit = true;
	bool crouching = false;
	int crouch = 0;
	int counter = 0;
	std::string activation = "";

	bool isJumping = true;

	void Collision(std::vector<sf::Sprite>& tiles);
};
