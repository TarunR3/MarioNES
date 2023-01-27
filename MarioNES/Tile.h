#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Mario.h"
#include <vector>

class Mushroom {
public:
	sf::Sprite Mushroom_sprite;
	Mushroom(sf::Texture& tileset, sf::IntRect rect, sf::Vector2f position);
	void Logic(Mario& mario);
	void Collision(std::vector<sf::Sprite>& tiles, sf::Vector2f vel);

	void update(float deltaTime, std::vector<sf::Sprite> tiles);

	bool activated = false;
	bool done = false;
	bool free = false;
	sf::Vector2f velocity;

private:
	sf::Clock frameCounter;
	int counter = 0;
	sf::Vector2f position;
	sf::RectangleShape hitbox;
	bool right_collide = false;
	bool left_collide = false;
	bool collide = true;
	int initial = 0;
};


class Enemy {
public:
	sf::Sprite Enemy_sprite;
	Enemy(sf::Texture& tileset, sf::IntRect rect, sf::Vector2f position, std::string type);
	void Collision(std::vector<sf::Sprite>& tiles, sf::Vector2f vel, std::vector<Enemy>& Enemy_v);
	void Logic(Mario& mario);
	void update(float deltaTime, std::vector<sf::Sprite> tiles, std::vector<Enemy>& Enemy_v);
	bool dead = false;
	int type = 0;
	bool done = false;
	bool canDestroy;

private:
	sf::Clock frameCounter;
	int counter = 0;
	sf::Vector2f velocity;
	sf::Vector2f position;
	sf::RectangleShape hitbox;
	bool right_collide = false;
	bool left_collide = false;
	bool collide = true;
	bool dmg = true;
	int initial = 0;
	int xFrame = 0;
	std::string category;
	bool can = false;
	int coll = 0;
};

class Block {
public:
	sf::Sprite block_sprite;

	bool hit = false;
	bool active = false;
	bool broken = false;
	Block(sf::Texture& tileset, sf::IntRect rect, sf::Vector2f position, int type);
	void Collision(Mario& mario, std::vector<Mushroom>& Mushroom_v, std::vector<Enemy>& Enemy_v);

private:
	sf::Clock frameCounter;
	int counter = 0;
};

class Background {
public:
	sf::Sprite Background_sprite;
	Background(sf::Texture& tileset, sf::IntRect rect, sf::Vector2f position);
};

class Finish {
public:
	sf::Sprite Finish_sprite;
	Finish(sf::Texture& tileset, sf::IntRect rect, sf::Vector2f position, int type);
	void Collision(Mario& mario);
	int kind = 0;
	int stage = 0;
	sf::Vector2f velocity;
};

class Broken {
public:
	sf::Sprite block_sprite1;
	sf::Sprite block_sprite2;
	sf::Sprite block_sprite3;
	sf::Sprite block_sprite4;
	sf::Sprite block_sprite5;

	Broken(sf::Texture& tileset, sf::IntRect rect, sf::Vector2f position);
	void Collision(Mario& mario);

	bool activated = false;
	bool done = false;

private:
	sf::Clock frameCounter;
	int counter = 0;
};

class CoinBlock {
public:
	sf::Sprite Coinblock_sprite;
	sf::Sprite Coin_sprite;
	sf::Sprite Mushroom_sprite;
	bool hit = false;
	bool activated = false;
	CoinBlock(sf::Texture& tileset, sf::IntRect rect, sf::Vector2f position, int type);
	void Collision(Mario& mario, std::vector<Mushroom>& Mushroom_v, std::vector<Enemy>& Enemy_v);

	sf::Clock frameCounter;
	float xFrame = 0.0f;
	float wait = 0.15f;
	int counter = 0;
	int coin_counter = 0;
	int type = 0;
};

class Entity
{
public:
	std::vector<Block> Block_v;
	std::vector<CoinBlock> CoinBlock_v;
	std::vector<Mushroom> Mushroom_v;
	std::vector<Broken> Broken_v;
	std::vector<Background> Background_v;
	std::vector<Enemy> Enemy_v;
	std::vector<Finish> Finish_v;
	std::vector<sf::Sprite> Sprite_v;

	bool finish = false;
	bool done = false;

	void createBlock(sf::Texture& tileset, sf::Vector2f pos, sf::IntRect rect, int type);
	void createCoinBlock(sf::Texture& tileset, sf::Vector2f pos, sf::IntRect rect, int type);
	void createMushroom(sf::Texture& tileset, sf::Vector2f pos, sf::IntRect rect);
	void createBroken(sf::Texture& tileset, sf::Vector2f pos, sf::IntRect rect);
	void createBackground(sf::Texture& tileset, sf::Vector2f pos, sf::IntRect rect);
	void createFinish(sf::Texture& tileset, sf::Vector2f pos, sf::IntRect rect, int type);
	void createEnemy(sf::Texture& tileset, sf::Vector2f pos, sf::IntRect rect, std::string type);

	void destroyBlock(sf::Vector2f pos);
	void destroyMushroom(sf::Vector2f pos);
	void destroyBroken(sf::Vector2f pos);
	void destroyEnemy(sf::Vector2f pos);

	void DrawToScreen(sf::RenderWindow& window, Mario& mario, float deltaTime, std::vector<sf::Sprite> tiles);
	void LoadFromFile(std::string FileName, sf::Color backgroundColor, Mario& mario, Entity& EntityList, sf::Texture& tileset, sf::Texture& enemyset);
};
