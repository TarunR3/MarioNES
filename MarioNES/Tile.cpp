#include "Tile.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>

Block::Block(sf::Texture& tileset, sf::IntRect rect, sf::Vector2f position, int type) {
	block_sprite.setTexture(tileset);
	block_sprite.setPosition(position);
	///block_sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	block_sprite.setTextureRect(rect);
	block_sprite.setScale(sf::Vector2f(2.0, 2.0));
}

void Block::Collision(Mario& mario, std::vector<Mushroom>& Mushroom_v, std::vector<Enemy>& Enemy_v) {
	if (mario.small) {
		if (block_sprite.getGlobalBounds().intersects(mario.sprite.getGlobalBounds()) && mario.getPosition().y > block_sprite.getGlobalBounds().top + block_sprite.getGlobalBounds().height + 26 && mario.getPosition().x > block_sprite.getGlobalBounds().left - 10 && mario.getPosition().x < block_sprite.getGlobalBounds().left + block_sprite.getGlobalBounds().width + 10 && mario.velocity.y < 0) {
			hit = true;
			active = true;
		}
		if (hit) {
			if (frameCounter.getElapsedTime().asSeconds() > 0.01f && counter <= 10) {
				block_sprite.setPosition(block_sprite.getPosition().x, block_sprite.getPosition().y - 2);
				counter++;
				active = false;
				frameCounter.restart();
			}
			if (frameCounter.getElapsedTime().asSeconds() > 0.01f && counter <= 21 && counter > 10) {
				block_sprite.setPosition(block_sprite.getPosition().x, block_sprite.getPosition().y + 2);
				counter++;
				frameCounter.restart();
			}
			if (counter == 22) {
				hit = false;
				counter = 0;
			}
		}
	}
	if (!mario.small) {
		if (block_sprite.getGlobalBounds().intersects(mario.sprite.getGlobalBounds()) && mario.getPosition().y > block_sprite.getGlobalBounds().top + block_sprite.getGlobalBounds().height + 26 && mario.getPosition().x > block_sprite.getGlobalBounds().left - 10 && mario.getPosition().x < block_sprite.getGlobalBounds().left + block_sprite.getGlobalBounds().width + 10 && mario.velocity.y < 0) {
			hit = true;
			active = true;
		}
		if (hit) {
			broken = true;
		}
	}
	if (active) {
		for (int i = 0; i < Mushroom_v.size(); i++) {
			if (Mushroom_v[i].Mushroom_sprite.getPosition().y < block_sprite.getGlobalBounds().top && Mushroom_v[i].free && Mushroom_v[i].Mushroom_sprite.getGlobalBounds().intersects(block_sprite.getGlobalBounds())) {
				Mushroom_v[i].velocity.y = -400.0f;
			}
		}
	}
	if (active) {
		for (int i = 0; i < Enemy_v.size(); i++) {
			if (Enemy_v[i].Enemy_sprite.getPosition().y < block_sprite.getGlobalBounds().top && Enemy_v[i].Enemy_sprite.getGlobalBounds().intersects(block_sprite.getGlobalBounds())) {
				Enemy_v[i].type = 1;
				Enemy_v[i].dead = true;
			}
		}
	}
}

CoinBlock::CoinBlock(sf::Texture& tileset, sf::IntRect rect, sf::Vector2f position, int type) {

	Coinblock_sprite.setTexture(tileset);
	Coinblock_sprite.setPosition(position);
	///Coinblock_sprite.setTextureRect(sf::IntRect(759, 0, 32, 32));
	Coinblock_sprite.setTextureRect(rect);
	Coinblock_sprite.setScale(sf::Vector2f(2.0, 2.0));

	if (type == 0) {
		Coin_sprite.setTexture(tileset);
		Coin_sprite.setPosition(sf::Vector2f(position.x + 8, position.y));
		Coin_sprite.setTextureRect(sf::IntRect(759, 33, 32, 32));
		Coin_sprite.setScale(sf::Vector2f(1.5, 1.5));
	}
}

void CoinBlock::Collision(Mario& mario, std::vector<Mushroom>& Mushroom_v, std::vector<Enemy>& Enemy_v) {
	if (!hit) {
		if (frameCounter.getElapsedTime().asSeconds() > wait + static_cast<float> (xFrame == 0) * 0.20f) {
			if (xFrame == 2) xFrame = 0;
			else xFrame++;
			frameCounter.restart();
		}
		Coinblock_sprite.setTextureRect(sf::IntRect(759 + (33 * xFrame), 0, 33, 33));
	}

	if (Coinblock_sprite.getGlobalBounds().intersects(mario.sprite.getGlobalBounds()) && mario.getPosition().y > Coinblock_sprite.getGlobalBounds().top + Coinblock_sprite.getGlobalBounds().height + 26 && mario.getPosition().x > Coinblock_sprite.getGlobalBounds().left - 10 && mario.getPosition().x < Coinblock_sprite.getGlobalBounds().left + Coinblock_sprite.getGlobalBounds().width + 10 && !hit && mario.velocity.y < 0) {
		hit = true;
		activated = true;
	}

	if (hit) {
		Coinblock_sprite.setTextureRect(sf::IntRect(858, 0, 33, 33));
		mario.coin++;

		if (frameCounter.getElapsedTime().asSeconds() > 0.01f && counter <= 10) {
			Coinblock_sprite.setPosition(Coinblock_sprite.getPosition().x, Coinblock_sprite.getPosition().y - 2);
			Coin_sprite.setPosition(Coin_sprite.getPosition().x, Coin_sprite.getPosition().y - 5);
			counter++;
			frameCounter.restart();
			if (counter > 1) {
				activated = false;
			}
		}

		if (frameCounter.getElapsedTime().asSeconds() > 0.01f && counter <= 21 && counter > 10) {
			Coinblock_sprite.setPosition(Coinblock_sprite.getPosition().x, Coinblock_sprite.getPosition().y + 2);
			Coin_sprite.setPosition(Coin_sprite.getPosition().x, Coin_sprite.getPosition().y - 5);
			counter++;
			frameCounter.restart();
		}

		if (frameCounter.getElapsedTime().asSeconds() > 0.01f && coin_counter <= 10) {
			Coin_sprite.setPosition(Coin_sprite.getPosition().x, Coin_sprite.getPosition().y + 5);
			coin_counter++;
			frameCounter.restart();
		}

		if (frameCounter.getElapsedTime().asSeconds() > 0.01f && coin_counter <= 21 && coin_counter > 10) {
			Coin_sprite.setPosition(Coin_sprite.getPosition().x, Coin_sprite.getPosition().y + 5);
			coin_counter++;
			frameCounter.restart();
		}
	}
	if (activated) {
		for (int i = 0; i < Mushroom_v.size(); i++) {
			if (Mushroom_v[i].Mushroom_sprite.getPosition().y < Coinblock_sprite.getGlobalBounds().top && Mushroom_v[i].free && Mushroom_v[i].Mushroom_sprite.getGlobalBounds().intersects(Coinblock_sprite.getGlobalBounds())) {
				Mushroom_v[i].velocity.y = -400.0f;
			}
		}
	}
	if (activated) {
		for (int i = 0; i < Enemy_v.size(); i++) {
			if (Enemy_v[i].Enemy_sprite.getPosition().y < Coinblock_sprite.getGlobalBounds().top && Enemy_v[i].Enemy_sprite.getGlobalBounds().intersects(Coinblock_sprite.getGlobalBounds())) {
				Enemy_v[i].type = 1;
				Enemy_v[i].dead = true;
			}
		}
	}
}


Mushroom::Mushroom(sf::Texture& tileset, sf::IntRect rect, sf::Vector2f position) {
	Mushroom_sprite.setTexture(tileset);
	Mushroom_sprite.setPosition(sf::Vector2f(position.x, position.y));
	Mushroom_sprite.setTextureRect(sf::IntRect(824, 297, 33, 33));
	Mushroom_sprite.setScale(sf::Vector2f(2.0, 2.0));
}

void Mushroom::Logic(Mario& mario) {
	if (!activated) {
		if (Mushroom_sprite.getGlobalBounds().intersects(mario.sprite.getGlobalBounds()) && mario.getPosition().y > Mushroom_sprite.getGlobalBounds().top + Mushroom_sprite.getGlobalBounds().height + 26 && mario.getPosition().x > Mushroom_sprite.getGlobalBounds().left - 10 && mario.getPosition().x < Mushroom_sprite.getGlobalBounds().left + Mushroom_sprite.getGlobalBounds().width + 10 && mario.velocity.y < 0) {
			activated = true;
		}
	}
	if (activated) {
		if (frameCounter.getElapsedTime().asSeconds() > 0.01f && counter <= 22) {
			Mushroom_sprite.setPosition(Mushroom_sprite.getPosition().x, Mushroom_sprite.getPosition().y - 3);
			counter++;
			frameCounter.restart();
		}
		if (counter > 22) {
			free = true;
			if (Mushroom_sprite.getGlobalBounds().intersects(mario.sprite.getGlobalBounds())) {
				if (mario.small) {
					done = true;
					mario.small = false;
					mario.activation = "mushroom";
					mario.pause = true;
					mario.sprite.setOrigin(sf::Vector2f(8.5, 16.5));
				}
				else {
					done = true;
				}
			}
		}
	}
}

void Mushroom::Collision(std::vector<sf::Sprite>& tiles, sf::Vector2f vel) {
	bool a = false;
	bool right = false;
	bool left = false;

	hitbox.setPosition(Mushroom_sprite.getPosition());
	hitbox.setSize(sf::Vector2f(60, 128));
	hitbox.setOrigin(2, 64);

	for (int i = 0; i < tiles.size(); i++) {
		if (hitbox.getGlobalBounds().intersects(tiles[i].getGlobalBounds())) {
			if (vel.x >= 0 && Mushroom_sprite.getPosition().x < tiles[i].getGlobalBounds().left && Mushroom_sprite.getPosition().y > tiles[i].getGlobalBounds().top && Mushroom_sprite.getPosition().y < tiles[i].getGlobalBounds().top + tiles[i].getGlobalBounds().height + 20) {
				vel.x = 0;
				velocity.x = -150.0f;
				right_collide = true;
				right = true;
			}

			if (vel.x <= 0 && Mushroom_sprite.getPosition().x > tiles[i].getGlobalBounds().left + tiles[i].getGlobalBounds().width && Mushroom_sprite.getPosition().y > tiles[i].getGlobalBounds().top && Mushroom_sprite.getPosition().y < tiles[i].getGlobalBounds().top + tiles[i].getGlobalBounds().height + 20) {
				vel.x = 0;
				velocity.x = 150.0f;
				left_collide = true;
				left = true;
			}

			if (vel.y > 0 && Mushroom_sprite.getPosition().y < tiles[i].getGlobalBounds().top && Mushroom_sprite.getPosition().x > tiles[i].getGlobalBounds().left - 32 && Mushroom_sprite.getPosition().x < tiles[i].getGlobalBounds().left + tiles[i].getGlobalBounds().width + 32) {
				Mushroom_sprite.setPosition(sf::Vector2f(Mushroom_sprite.getPosition().x, tiles[i].getGlobalBounds().top - 64));
				vel.y = 0;
				velocity.y = 0;
				collide = true;
				a = true;
			}
		}
	}

	if (!a) {
		collide = false;
	}
	if (!left) {
		left_collide = false;
	}
	if (!right) {
		right_collide = false;
	}
}


void Mushroom::update(float deltaTime, std::vector<sf::Sprite> tiles) {
	if (free) {
		if (initial == 0) {
			velocity.x = 150.0f;
			initial++;
		}

		velocity.y += 1500.0 * deltaTime;

		if (collide) {
			velocity.y = 0;
		}

		Mushroom_sprite.move(velocity * deltaTime);
		Collision(tiles, velocity);
	}
}


Broken::Broken(sf::Texture& tileset, sf::IntRect rect, sf::Vector2f position) {
	block_sprite1.setTexture(tileset);
	block_sprite1.setPosition(position.x + 12, position.y);
	block_sprite1.setTextureRect(sf::IntRect(66, 0, 32, 32));
	block_sprite1.setScale(sf::Vector2f(0.5, 0.5));
	block_sprite1.rotate(45);

	block_sprite2.setTexture(tileset);
	block_sprite2.setPosition(position.x + 40, position.y + 12);
	block_sprite2.setTextureRect(sf::IntRect(66, 0, 32, 32));
	block_sprite2.setScale(sf::Vector2f(0.5, 0.5));
	block_sprite2.rotate(-45);

	block_sprite3.setTexture(tileset);
	block_sprite3.setPosition(position.x + 12, position.y + 36);
	block_sprite3.setTextureRect(sf::IntRect(66, 0, 32, 32));
	block_sprite3.setScale(sf::Vector2f(0.5, 0.5));
	block_sprite3.rotate(45);

	block_sprite4.setTexture(tileset);
	block_sprite4.setPosition(position.x + 40, position.y + 48);
	block_sprite4.setTextureRect(sf::IntRect(66, 0, 32, 32));
	block_sprite4.setScale(sf::Vector2f(0.5, 0.5));
	block_sprite4.rotate(-45);

	block_sprite5.setTexture(tileset);
	block_sprite5.setPosition(position);
	block_sprite5.setTextureRect(sf::IntRect(66, 0, 32, 32));
	block_sprite5.setScale(sf::Vector2f(2.0, 2.0));
}

void Broken::Collision(Mario& mario) {
	if (!mario.small && block_sprite5.getGlobalBounds().intersects(mario.sprite.getGlobalBounds()) && mario.getPosition().y > block_sprite5.getGlobalBounds().top + block_sprite5.getGlobalBounds().height + 26 && mario.getPosition().x > block_sprite5.getGlobalBounds().left - 10 && mario.getPosition().x < block_sprite5.getGlobalBounds().left + block_sprite5.getGlobalBounds().width + 10 && mario.velocity.y < 0) {
		activated = true;
	}
	if (activated) {
		if (frameCounter.getElapsedTime().asSeconds() > 0.008f && counter <= 30) {
			block_sprite1.setPosition(block_sprite1.getPosition().x - 2, block_sprite1.getPosition().y - 3);
			block_sprite2.setPosition(block_sprite2.getPosition().x + 2, block_sprite2.getPosition().y - 3);
			block_sprite3.setPosition(block_sprite3.getPosition().x - 2, block_sprite3.getPosition().y - 3);
			block_sprite4.setPosition(block_sprite4.getPosition().x + 2, block_sprite4.getPosition().y - 3);
			counter++;
			frameCounter.restart();
		}

		if (frameCounter.getElapsedTime().asSeconds() > 0.008f && counter > 30 && counter <= 200) {
			block_sprite1.setPosition(block_sprite1.getPosition().x - 2, block_sprite1.getPosition().y + 5);
			block_sprite2.setPosition(block_sprite2.getPosition().x + 2, block_sprite2.getPosition().y + 5);
			block_sprite3.setPosition(block_sprite3.getPosition().x - 2, block_sprite3.getPosition().y + 5);
			block_sprite4.setPosition(block_sprite4.getPosition().x + 2, block_sprite4.getPosition().y + 5);
			counter++;
			frameCounter.restart();
		}
		if (counter > 200) {
			done = true;
		}
	}
}

Background::Background(sf::Texture& tileset, sf::IntRect rect, sf::Vector2f position) {
	Background_sprite.setTexture(tileset);
	Background_sprite.setPosition(position);
	Background_sprite.setTextureRect(rect);
	Background_sprite.setScale(sf::Vector2f(2.0, 2.0));
}

Finish::Finish(sf::Texture& tileset, sf::IntRect rect, sf::Vector2f position, int type) {
	Finish_sprite.setTexture(tileset);

	kind = type;

	if (type == 0) {
		Finish_sprite.setPosition(position.x, position.y);
	}
	if (type == 1) {
		Finish_sprite.setPosition(position.x + 32, position.y);
	}
	if (type == 2) {
		Finish_sprite.setPosition(position.x + 16, position.y + 36);
	}
	if (type == 3) {
		Finish_sprite.setPosition(position.x - 31, position.y + 68);
	}

	Finish_sprite.setTextureRect(rect);

	if (type == 0) {
		Finish_sprite.setScale(sf::Vector2f(2.0, 2.0));
	}

	if (type == 1) {
		Finish_sprite.setScale(sf::Vector2f(1.0f, 4.3f));
	}
	if (type == 2) {
		Finish_sprite.setScale(sf::Vector2f(2.0, 2.0));
	}
	if (type == 3) {
		Finish_sprite.setScale(sf::Vector2f(2.0, 2.0));
	}
}

void Finish::Collision(Mario& mario) {
	if (Finish_sprite.getGlobalBounds().intersects(mario.sprite.getGlobalBounds())) {
		mario.pause = true;
		mario.activation = "finish";
		stage = 1;
	}
}

Enemy::Enemy(sf::Texture& tileset, sf::IntRect rect, sf::Vector2f position, std::string type) {
	category = type;
	Enemy_sprite.setTexture(tileset);
	Enemy_sprite.setPosition(position);
	Enemy_sprite.setTextureRect(rect);
	Enemy_sprite.setScale(sf::Vector2f(3.2f, 3.2f));
}

void Enemy::update(float deltaTime, std::vector<sf::Sprite> tiles, std::vector<Enemy>& Enemy_v) {
	if (initial == 0) {
		velocity.x = -150.0f;
		initial++;
	}

	if (type != 1) {
		velocity.y += 1500.0f * deltaTime;
	}

	if (collide) {
		velocity.y = 0;
	}

	if (!dead && category == "goomba") {
		if (frameCounter.getElapsedTime().asSeconds() > 0.4f) {
			if (xFrame == 1) xFrame = 0;
			else xFrame++;
			frameCounter.restart();
		}
		Enemy_sprite.setTextureRect(sf::IntRect(0 + (29 * xFrame), 3, 17, 23));
	}

	if (dead && type == 0) {
		velocity.x = 0;
		Enemy_sprite.setTextureRect(sf::IntRect(59, 7, 23, 10));
		if (frameCounter.getElapsedTime().asSeconds() > .01f) {
			counter++;
			frameCounter.restart();
		}
		if (counter > 20) {
			done = true;
		}

	}
	if (dead && type == 1) {
		velocity.x = 0;
		if (counter == 0) {
			Enemy_sprite.rotate(180);
			Enemy_sprite.setPosition(Enemy_sprite.getPosition().x + 64, Enemy_sprite.getPosition().y + 44);
			counter++;
		}
		if (frameCounter.getElapsedTime().asSeconds() > 0.013f && counter < 20) {
			counter++;
			Enemy_sprite.setPosition(Enemy_sprite.getPosition().x, Enemy_sprite.getPosition().y - .01f);
			frameCounter.restart();
		}
		if (frameCounter.getElapsedTime().asSeconds() > 0.01f && counter >= 20 && !done) {
			counter++;
			Enemy_sprite.setPosition(Enemy_sprite.getPosition().x, Enemy_sprite.getPosition().y + 5);
			frameCounter.restart();
		}
		if (counter > 200) {
			done = true;
		}
	}

	Enemy_sprite.move(velocity * deltaTime);
	Collision(tiles, velocity, Enemy_v);
}

void Enemy::Logic(Mario& mario) {
	if (mario.small) {
		coll = 90;
	}
	if (mario.crouching) {
		coll = 90;
	}
	else {
		coll = 100;
	}

	if (Enemy_sprite.getGlobalBounds().intersects(mario.sprite.getGlobalBounds()) && mario.getPosition().y < Enemy_sprite.getGlobalBounds().top && mario.velocity.y > 0 && !mario.dead) {
		counter = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			mario.velocity.y = -800.0f;
			counter = 0;
		}
		else {
			mario.velocity.y = -400.0f;
			counter = 0;
		}
		dead = true;
	}

	if (Enemy_sprite.getGlobalBounds().intersects(mario.sprite.getGlobalBounds()) && mario.getPosition().y + coll > Enemy_sprite.getGlobalBounds().top + Enemy_sprite.getGlobalBounds().height) {
		if (mario.can_be_hit && !dead) {
			dmg = true;
			mario.can_be_hit = false;
		}
	}
	else {
		dmg = false;
	}


	if (dmg) {
		if (mario.small) {
			mario.dead = true;
			dmg = false;
		}
		else {
			mario.small = true;
			mario.sprite.setOrigin(sf::Vector2f(8.5, 8.5));
			mario.activation = "hit";
			mario.pause = true;
			dmg = false;
		}
	}

	if (!mario.can_be_hit) {
		if (frameCounter.getElapsedTime().asSeconds() > 0.15f) {
			frameCounter.restart();
			counter++;
		}
		if (counter > 8) {
			mario.can_be_hit = true;
			counter = 0;
		}
	}
}

void Enemy::Collision(std::vector<sf::Sprite>& tiles, sf::Vector2f vel, std::vector<Enemy>& Enemy_v) {
	bool a = false;
	bool right = false;
	bool left = false;

	hitbox.setPosition(Enemy_sprite.getPosition());
	hitbox.setSize(sf::Vector2f(50, 128));
	hitbox.setOrigin(2, 64);

	for (int tile = 0; tile < tiles.size(); tile++) {
		if (hitbox.getGlobalBounds().intersects(tiles[tile].getGlobalBounds())) {
			if (!dead) {
				if (vel.x >= 0 && Enemy_sprite.getPosition().x < tiles[tile].getGlobalBounds().left && Enemy_sprite.getPosition().y > tiles[tile].getGlobalBounds().top && Enemy_sprite.getPosition().y < tiles[tile].getGlobalBounds().top + tiles[tile].getGlobalBounds().height + 20) {
					vel.x = 0;
					velocity.x = -150.0f;
					right_collide = true;
					right = true;
				}

				if (vel.x <= 0 && Enemy_sprite.getPosition().x > tiles[tile].getGlobalBounds().left + tiles[tile].getGlobalBounds().width && Enemy_sprite.getPosition().y > tiles[tile].getGlobalBounds().top && Enemy_sprite.getPosition().y < tiles[tile].getGlobalBounds().top + tiles[tile].getGlobalBounds().height + 20) {
					vel.x = 0;
					velocity.x = 150.0f;
					left_collide = true;
					left = true;
				}
			}

			if (vel.y > 0 && Enemy_sprite.getPosition().y < tiles[tile].getGlobalBounds().top && Enemy_sprite.getPosition().x > tiles[tile].getGlobalBounds().left - 32 && Enemy_sprite.getPosition().x < tiles[tile].getGlobalBounds().left + tiles[tile].getGlobalBounds().width + 32) {
				if (!dead) {
					Enemy_sprite.setPosition(sf::Vector2f(Enemy_sprite.getPosition().x, tiles[tile].getGlobalBounds().top - 54));
				}
				if (dead && type == 0) {
					Enemy_sprite.setPosition(sf::Vector2f(Enemy_sprite.getPosition().x, tiles[tile].getGlobalBounds().top - 30));
				}
				if (!dead) {
					vel.y = 0;
					velocity.y = 0;
					collide = true;
					a = true;
				}
			}
		}
		for (int tile = 0; tile < Enemy_v.size(); tile++) {
			if (hitbox.getGlobalBounds().intersects(Enemy_v[tile].Enemy_sprite.getGlobalBounds())) {
				if (!dead) {
					if (Enemy_sprite.getGlobalBounds().intersects(Enemy_v[tile].Enemy_sprite.getGlobalBounds()) && Enemy_v[tile].Enemy_sprite.getPosition() != Enemy_sprite.getPosition() && !Enemy_v[tile].dead) {
						if (velocity.x > 0) {
							velocity.x = -150.0f;
						}
						if (velocity.x < 0) {
							velocity.x = 150.0f;
						}
					}
				}
			}
		}
	}

	if (!a) {
		collide = false;
	}
	if (!left) {
		left_collide = false;
	}
	if (!right) {
		right_collide = false;
	}
}

void Entity::createBlock(sf::Texture& tileset, sf::Vector2f pos, sf::IntRect rect, int type) {
	Block Block(tileset, rect, pos, type);
	Block_v.push_back(Block);
	Sprite_v.push_back(Block.block_sprite);
}

void Entity::createCoinBlock(sf::Texture& tileset, sf::Vector2f pos, sf::IntRect rect, int type) {
	CoinBlock CoinBlock(tileset, rect, pos, type);
	CoinBlock_v.push_back(CoinBlock);
	Sprite_v.push_back(CoinBlock.Coinblock_sprite);
}

void Entity::createMushroom(sf::Texture& tileset, sf::Vector2f pos, sf::IntRect rect) {
	Mushroom Mushroom(tileset, rect, pos);
	Mushroom_v.push_back(Mushroom);
}

void Entity::createBroken(sf::Texture& tileset, sf::Vector2f pos, sf::IntRect rect) {
	Broken Broken(tileset, rect, pos);
	Broken_v.push_back(Broken);
}

void Entity::createBackground(sf::Texture& tileset, sf::Vector2f pos, sf::IntRect rect) {
	Background Background(tileset, rect, pos);
	Background_v.push_back(Background);
}

void Entity::createEnemy(sf::Texture& tileset, sf::Vector2f pos, sf::IntRect rect, std::string type) {
	Enemy Enemy(tileset, rect, pos, type);
	Enemy_v.push_back(Enemy);
}

void Entity::createFinish(sf::Texture& tileset, sf::Vector2f pos, sf::IntRect rect, int type) {
	Finish Finish(tileset, rect, pos, type);
	Finish_v.push_back(Finish);
}

void Entity::destroyBlock(sf::Vector2f pos) {
	for (int o = 0; o < Block_v.size(); o++) {
		if (pos == Block_v[o].block_sprite.getPosition()) {
			Block_v.erase(Block_v.begin() + o);
			break;
		}
	}
	for (int o = 0; o < Sprite_v.size(); o++) {
		if (pos == Sprite_v[o].getPosition()) {
			Sprite_v.erase(Sprite_v.begin() + o);
			break;
		}
	}
}

void Entity::destroyMushroom(sf::Vector2f pos) {
	for (int o = 0; o < Mushroom_v.size(); o++) {
		if (pos == Mushroom_v[o].Mushroom_sprite.getPosition()) {
			Mushroom_v.erase(Mushroom_v.begin() + o);
			break;
		}
	}
}

void Entity::destroyEnemy(sf::Vector2f pos) {
	for (int o = 0; o < Enemy_v.size(); o++) {
		if (pos == Enemy_v[o].Enemy_sprite.getPosition()) {
			Enemy_v.erase(Enemy_v.begin() + o);
			break;
		}
	}
}

void Entity::destroyBroken(sf::Vector2f pos) {
	for (int o = 0; o < Broken_v.size(); o++) {
		if (pos == Broken_v[o].block_sprite5.getPosition()) {
			Broken_v.erase(Broken_v.begin() + o);
			break;
		}
	}
}

void Entity::DrawToScreen(sf::RenderWindow& window, Mario& mario, float deltaTime, std::vector<sf::Sprite> tiles) {
	for (int i = 0; i < Background_v.size(); i++) {
		if (mario.vision.getGlobalBounds().intersects(Background_v[i].Background_sprite.getGlobalBounds())) {
			window.draw(Background_v[i].Background_sprite);
		}
	}

	for (int i = 0; i < Finish_v.size(); i++) {
		if (mario.vision.getGlobalBounds().intersects(Finish_v[i].Finish_sprite.getGlobalBounds())) {
			window.draw(Finish_v[i].Finish_sprite);
			if (Finish_v[i].kind == 1) {
				Finish_v[i].Collision(mario);
			}
			if (Finish_v[i].stage == 1) {
				finish = true;
			}
			if (finish) {
				if (Finish_v[i].kind == 3) {
					if (Finish_v[i].Finish_sprite.getPosition().y < 640) {
						Finish_v[i].velocity.y = 300.0f;
						Finish_v[i].Finish_sprite.move(Finish_v[i].velocity * deltaTime);
					}
					if (Finish_v[i].Finish_sprite.getPosition().y > 640 && !done) {
						Finish_v[i].velocity.y = 0;
						mario.stage = 3;
						done = true;
					}
				}
			}
		}
	}

	for (int i = 0; i < Mushroom_v.size(); i++) {
		if (mario.small) {
			Mushroom_v[i].Logic(mario);
			window.draw(Mushroom_v[i].Mushroom_sprite);
			Mushroom_v[i].update(deltaTime, tiles);

			if (Mushroom_v[i].done) {
				destroyMushroom(Mushroom_v[i].Mushroom_sprite.getPosition());
			}
		}
	}


	for (int i = 0; i < Enemy_v.size(); i++) {
		if (mario.vision.getGlobalBounds().intersects(Enemy_v[i].Enemy_sprite.getGlobalBounds())) {
			Enemy_v[i].Logic(mario);
			window.draw(Enemy_v[i].Enemy_sprite);
			Enemy_v[i].update(deltaTime, tiles, Enemy_v);
		}
		if (!Enemy_v[i].done) {
			if (Enemy_v[i].Enemy_sprite.getPosition().x < mario.getPosition().x - 1200) {
				destroyEnemy(Enemy_v[i].Enemy_sprite.getPosition());
				break;
			}
		}
		if (Enemy_v[i].done) {
			destroyEnemy(Enemy_v[i].Enemy_sprite.getPosition());
		}
	}

	for (int i = 0; i < Broken_v.size(); i++) {
		Broken_v[i].Collision(mario);
		if (Broken_v[i].activated) {
			window.draw(Broken_v[i].block_sprite1);
			window.draw(Broken_v[i].block_sprite2);
			window.draw(Broken_v[i].block_sprite3);
			window.draw(Broken_v[i].block_sprite4);
		}
		if (Broken_v[i].done) {
			destroyBroken(Broken_v[i].block_sprite5.getPosition());
		}
	}

	for (int i = 0; i < Block_v.size(); i++) {
		if (mario.vision.getGlobalBounds().intersects(Block_v[i].block_sprite.getGlobalBounds())) {
			Block_v[i].Collision(mario, Mushroom_v, Enemy_v);
			window.draw(Block_v[i].block_sprite);
			if (Block_v[i].broken) {
				mario.velocity.y = 10.0f;
				destroyBlock(Block_v[i].block_sprite.getPosition());
			}
		}
	}

	for (int i = 0; i < CoinBlock_v.size(); i++) {
		CoinBlock_v[i].Collision(mario, Mushroom_v, Enemy_v);
		window.draw(CoinBlock_v[i].Coin_sprite);
		window.draw(CoinBlock_v[i].Coinblock_sprite);
	}

	if (mario.stage != 4) {
		window.draw(mario.sprite);
	}
}

void Entity::LoadFromFile(std::string FileName, sf::Color backgroundColor, Mario& mario, Entity& EntityList, sf::Texture& tileset, sf::Texture& enemyset) {
	EntityList.Block_v.clear();
	EntityList.CoinBlock_v.clear();
	EntityList.Mushroom_v.clear();
	EntityList.Broken_v.clear();
	EntityList.Background_v.clear();
	EntityList.Enemy_v.clear();

	std::ifstream File(FileName);
	std::string line;
	if (File.is_open()) {
		while (getline(File, line)) {
			if (line.substr(0, 5) == "Block") {
				std::vector<std::string> properties = { "","","","","","" };
				int index = 0;
				for (int i = 6; i < line.length(); i++) {
					if (line.at(i) == ',') {
						index += 1;
					}
					else {
						properties[index] += line.at(i);
					}
				}
				sf::Vector2f pos(stoi(properties[0]), stoi(properties[1]));
				sf::IntRect rect(stoi(properties[2]), stoi(properties[3]), stoi(properties[4]), stoi(properties[5]));
				int type = 0;
				if (stoi(properties[2]) == 33 && stoi(properties[3]) == 0) {
					createBroken(tileset, pos, rect);
				}
				createBlock(tileset, pos, rect, type);
			}
			else if (line.substr(0, 9) == "CoinBlock") {
				std::vector<std::string> properties = { "","","","","","","" };
				int index = 0;
				for (int i = 10; i < line.length(); i++) {
					if (line.at(i) == ',') {
						index += 1;
					}
					else {
						properties[index] += line.at(i);
					}
				}
				sf::Vector2f pos(stoi(properties[0]), stoi(properties[1]));
				sf::IntRect rect(stoi(properties[2]), stoi(properties[3]), stoi(properties[4]), stoi(properties[5]));
				int type = stoi(properties[6]);
				createCoinBlock(tileset, pos, rect, type);
				if (type == 1) {
					createMushroom(tileset, pos, rect);
				}
			}
			else if (line.substr(0, 10) == "Background") {
				std::vector<std::string> properties = { "","","","","","" };
				int index = 0;
				for (int i = 11; i < line.length(); i++) {
					if (line.at(i) == ',') {
						index += 1;
					}
					else {
						properties[index] += line.at(i);
					}
				}
				sf::Vector2f pos(stoi(properties[0]), stoi(properties[1]));
				sf::IntRect rect(stoi(properties[2]), stoi(properties[3]), stoi(properties[4]), stoi(properties[5]));
				createBackground(tileset, pos, rect);
			}
			else if (line.substr(0, 5) == "Enemy") {
				std::vector<std::string> properties = { "","","","","","" };
				int index = 0;
				for (int i = 6; i < line.length(); i++) {
					if (line.at(i) == ',') {
						index += 1;
					}
					else {
						properties[index] += line.at(i);
					}
				}

				sf::Vector2f pos(stoi(properties[0]), stoi(properties[1]));
				sf::IntRect rect(stoi(properties[2]), stoi(properties[3]), stoi(properties[4]), stoi(properties[5]));

				std::string type = "";

				if (stoi(properties[2]) == 0 && stoi(properties[3]) == 3) {
					type = "goomba";
				}

				createEnemy(enemyset, pos, rect, type);
			}

			else if (line.substr(0, 6) == "Finish") {
				std::vector<std::string> properties = { "","","","","","","" };
				int index = 0;
				for (int i = 7; i < line.length(); i++) {
					if (line.at(i) == ',') {
						index += 1;
					}
					else {
						properties[index] += line.at(i);
					}
				}

				sf::Vector2f pos(stoi(properties[0]), stoi(properties[1]));
				sf::IntRect rect(stoi(properties[2]), stoi(properties[3]), stoi(properties[4]), stoi(properties[5]));

				int type = 0;
				type = stoi(properties[6]);

				createFinish(tileset, pos, rect, type);
			}
		}
	}
}
