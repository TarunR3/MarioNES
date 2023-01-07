#include "Mario.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

Mario::Mario() {
    texture.loadFromFile("Resources/mariosheet.png");
    sprite.setTexture(texture);

    if (small) {
        sprite.setTextureRect(sf::IntRect(29, 0, 17, 17));
        sprite.setOrigin(sf::Vector2f(8.5, 8.5));
    }

    if (!small) {
        sprite.setTextureRect(sf::IntRect(29, 52, 17, 33));
        sprite.setOrigin(sf::Vector2f(8.5, 16.5));
    }

    sprite.setScale(sf::Vector2f(scale, scale));
    sprite.setPosition(sf::Vector2f(100, 0));

    vision.setSize(sf::Vector2f(1024, 968));
}

sf::Vector2f Mario::getPosition()
{
    return sprite.getPosition();
}

bool Mario::rc(sf::Sprite tile)
{
    return velocity.x >= 0 && sprite.getPosition().x < tile.getGlobalBounds().left&& sprite.getPosition().y > tile.getGlobalBounds().top && sprite.getPosition().y < tile.getGlobalBounds().top + tile.getGlobalBounds().height + 20;
}

bool Mario::lc(sf::Sprite tile)
{
    return velocity.x <= 0 && sprite.getPosition().x > tile.getGlobalBounds().left + tile.getGlobalBounds().width && sprite.getPosition().y > tile.getGlobalBounds().top && sprite.getPosition().y < tile.getGlobalBounds().top + tile.getGlobalBounds().height + 20;
}

bool Mario::onTop(sf::Sprite tile)
{
    return velocity.y > 0 && sprite.getPosition().y < tile.getGlobalBounds().top&& sprite.getPosition().x > tile.getGlobalBounds().left - 20 && sprite.getPosition().x < tile.getGlobalBounds().left + tile.getGlobalBounds().width + 20;
}

bool Mario::beneath(sf::Sprite tile)
{
    return velocity.y < 0 && sprite.getPosition().y > tile.getGlobalBounds().top + tile.getGlobalBounds().height && sprite.getPosition().x > tile.getGlobalBounds().left - 20 && sprite.getPosition().x < tile.getGlobalBounds().left + tile.getGlobalBounds().width + 20;
}

void Mario::animate(std::string animation)
{
    if (animation == "idle") {
        if (small) {
            sprite.setTextureRect(sf::IntRect(211, 0, 17, 17));
        }
        if (!small) {
            sprite.setTextureRect(sf::IntRect(209, 52, 17, 33));
        }
    }

    else if (animation == "running") {
        if (small) {
            if (frameCounter.getElapsedTime().asSeconds() > 0.17f) {
                if (xFrame == 3) xFrame = 0;
                else xFrame++;
                frameCounter.restart();
            }
            sprite.setTextureRect(sf::IntRect(89 + (30 * xFrame), 0, 17, 17));
        }
        if (!small) {
            if (frameCounter.getElapsedTime().asSeconds() > 0.17f) {
                if (xFrame == 3) xFrame = 0;
                else xFrame++;
                frameCounter.restart();
            }
            sprite.setTextureRect(sf::IntRect(89 + (30 * xFrame), 52, 17, 33));
        }
    }

    else if (animation == "jumping") {
        if (small) {
            sprite.setTextureRect(sf::IntRect(29, 0, 17, 17));
            if (key == "left") {
                sprite.setScale(sf::Vector2f(scale, scale));
            }
            if (key == "right") {
                sprite.setScale(sf::Vector2f(-scale, scale));
            }
        }
        if (!small) {
            sprite.setTextureRect(sf::IntRect(29, 52, 17, 33));
            if (key == "left") {
                sprite.setScale(sf::Vector2f(scale, scale));
            }
            if (key == "right") {
                sprite.setScale(sf::Vector2f(-scale, scale));
            }
        }
    }
    else if (animation == "mushroom") {
        sprite.setPosition(position);
        if (key == "right") {
            sprite.setScale(sf::Vector2f(scale, scale));
        }

        if (key == "left") {
            sprite.setScale(sf::Vector2f(-scale, scale));
        }
        if (frameCounter.getElapsedTime().asSeconds() > 0.1f) {
            xFrame = mushroom_count % 2;

            sprite.setTextureRect(sf::IntRect(211 - (2 * xFrame), 0 + (52 * xFrame), 17, 17 + (16 * xFrame)));
            sprite.setOrigin(8.5, 8.5 + (8 * xFrame));
            mushroom_count++;

            frameCounter.restart();
        }
        if (mushroom_count > 5) {
            pause = false;
            mushroom_count = 0;
        }
    }
    else if (animation == "hit") {
        sprite.setPosition(position);
        if (key == "right") {
            sprite.setScale(sf::Vector2f(scale, scale));
        }

        if (key == "left") {
            sprite.setScale(sf::Vector2f(-scale, scale));
        }
        if (frameCounter.getElapsedTime().asSeconds() > 0.1f) {
            xFrame = hit_count % 2;

            sprite.setTextureRect(sf::IntRect(211 - (2 * xFrame), 0 + (52 * xFrame), 17, 17 + (16 * xFrame)));
            sprite.setOrigin(8.5, 8.5 + (8 * xFrame));
            hit_count++;

            frameCounter.restart();
        }
        if (hit_count > 6) {
            pause = false;
            hit_count = 0;
        }
    }
    else if (animation == "crouching") {
        sprite.setTextureRect(sf::IntRect(388, 56, 17, 23));
    }
    if (animation == "finish") {
        if (small) {
            velocity.x = 0;
            velocity.y = 0;
            sprite.setTextureRect(sf::IntRect(328, 29, 17, 17));
            sprite.setScale(scale, scale);
            if (finish_counter == 0) {
                sprite.setPosition(sprite.getPosition().x + 2, sprite.getPosition().y);
                finish_counter++;
            }
        }
        else {
            velocity.x = 0;
            velocity.y = 0;
            sprite.setTextureRect(sf::IntRect(389, 87, 17, 32));
            sprite.setScale(scale, scale);
            if (finish_counter == 0) {
                sprite.setPosition(sprite.getPosition().x + 2, sprite.getPosition().y);
                finish_counter++;
            }
        }
    }
}

void Mario::Collision(std::vector<sf::Sprite>& tiles) {
    a = false;
    left = false;
    right = false;

    hitbox.setPosition(sprite.getPosition());

    if (small || crouching) {
        hitbox.setSize(sf::Vector2f(52, 52));
        hitbox.setOrigin(26, 26);

        for (int i = 0; i < tiles.size(); i++) {
            if (hitbox.getGlobalBounds().intersects(tiles[i].getGlobalBounds())) {
                if (rc(tiles[i])) {
                    velocity.x = 0;
                    right_collide = true;
                    right = true;
                }

                if (lc(tiles[i])) {
                    velocity.x = 0;
                    left_collide = true;
                    left = true;
                }

                if (onTop(tiles[i])) {
                    if (crouching) {
                        sprite.setPosition(sf::Vector2f(sprite.getPosition().x, tiles[i].getGlobalBounds().top - 23));
                    }
                    else {
                        sprite.setPosition(sf::Vector2f(sprite.getPosition().x, tiles[i].getGlobalBounds().top - 26));
                    }
                    velocity.y = 0;
                    isJumping = false;
                    collide = true;
                    a = true;
                }

                if (beneath(tiles[i])) {
                    sprite.setPosition(sf::Vector2f(sprite.getPosition().x, tiles[i].getGlobalBounds().top + tiles[i].getGlobalBounds().height + 26));
                    velocity.y = 10;
                }
            }
        }
    }

    if (!small && !crouching) {
        hitbox.setSize(sf::Vector2f(52, 104));
        hitbox.setOrigin(26, 52);

        for (int i = 0; i < tiles.size(); i++) {
            if (hitbox.getGlobalBounds().intersects(tiles[i].getGlobalBounds())) {
                if (rc(tiles[i])) {
                    velocity.x = 0;
                    right_collide = true;
                    right = true;
                }

                if (lc(tiles[i])) {
                    velocity.x = 0;
                    left_collide = true;
                    left = true;
                }

                if (onTop(tiles[i])) {
                    sprite.setPosition(sf::Vector2f(sprite.getPosition().x, tiles[i].getGlobalBounds().top - 52));
                    velocity.y = 0;
                    isJumping = false;
                    collide = true;
                    a = true;
                }

                if (beneath(tiles[i])) {
                    sprite.setPosition(sf::Vector2f(sprite.getPosition().x, tiles[i].getGlobalBounds().top + tiles[i].getGlobalBounds().height + 52));
                    velocity.y = 10;
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


void Mario::update(float deltaTime, std::vector<sf::Sprite> tiles)
{
    if (finish) {
        if (stage == 0) {
            velocity.y = 300.0f;
        }
        sprite.move(velocity * deltaTime);
        Collision(tiles);
        if (collide && stage == 0) {
            stage = 1;
            finish_counter = 0;
        }
        if (stage == 1) {
            sprite.setScale(-scale, scale);
            if (finish_counter < 4) {
                sprite.setPosition(sprite.getPosition().x + 16, sprite.getPosition().y);
                finish_counter++;
            }
            if (finish_counter == 4) {
                stage = 2;
            }
        }
        if (stage == 3) {
            animate("running");
            velocity.x = 150.0f;
            velocity.y += 1500.0f;
            if (getPosition().x > 13094) {
                velocity.x = 0;
                stage = 4;
            }
        }
        if (stage == 4) {
            animate("idle");
            sprite.setScale(scale, scale);
            velocity.y = 0;
        }
    }

    if (dead) {
        sprite.setTextureRect(sf::IntRect(389, 15, 17, 17));
        if (frameCounter.getElapsedTime().asSeconds() > 0.01f && counter <= 40) {
            sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y - 3);
            counter++;
            frameCounter.restart();
        }
        if (frameCounter.getElapsedTime().asSeconds() > 0.01f && counter > 40 && counter <= 200) {
            sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + 4);
            counter++;
            frameCounter.restart();
        }
    }

    if (!dead)
    {
        if (!pause)
        {

            if (velocity.x != 0 && !crouching) {
                if (velocity.x > 0) {
                    velocity.x -= 2.0f;
                    if (velocity.x < 0) {
                        velocity.x = 0;
                    }
                }
                if (velocity.x < 0) {
                    velocity.x += 2.0f;
                    if (velocity.x > 0) {
                        velocity.x = 0;
                    }
                }
            }

            velocity.y += 1500.0 * deltaTime;

            position = sprite.getPosition();

            if (position.y > 1000) {
                dead = true;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !isJumping && !small) {
                animate("crouching");
                crouching = true;

                if (crouch < 4) {
                    sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + 7);
                    crouch++;
                }

                if (key == "right") {
                    sprite.setScale(sf::Vector2f(scale, scale));
                }

                if (key == "left") {
                    sprite.setScale(sf::Vector2f(-scale, scale));
                }

                if (velocity.x != 0) {
                    if (velocity.x > 0) {
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                            velocity.x -= 0.5f;
                        }
                        else {
                            velocity.x -= 1.0f;
                        }
                    }
                    if (velocity.x < 0) {
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                            velocity.x += 0.5f;
                        }
                        else {
                            velocity.x += 1.0f;
                        }
                    }
                }
            }

            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                crouching = false;
                crouch = 0;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !crouching)
            {
                if (!isJumping && !right_collide) {
                    animate("running");
                    sprite.setScale(sf::Vector2f(-scale, scale));
                    key = "right";
                }
                if (!right_collide) {
                    if (velocity.x < 500.0f) {
                        velocity.x += 3.00f;
                    }
                    else {
                        velocity.x = 500.0f;
                    }
                }
            }

            else if (position.x >= 17 && sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !crouching)
            {
                if (!isJumping && !left_collide) {
                    animate("running");
                    sprite.setScale(sf::Vector2f(scale, scale));
                    key = "left";
                }
                if (!left_collide) {
                    if (velocity.x > -500.0f) {
                        velocity.x -= 3.00f;
                    }
                    else {
                        velocity.x = -500.0f;
                    }
                }
            }
            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !crouching && !isJumping) {
                animate("idle");

                if (key == "right") {
                    sprite.setScale(sf::Vector2f(scale, scale));
                }
                if (key == "left") {
                    sprite.setScale(sf::Vector2f(-scale, scale));
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !isJumping)
            {
                if (!crouching) {
                    animate("jumping");
                }
                isJumping = true;
                velocity.y = -880.0f;
            }

            if (collide && !crouching)
            {
                isJumping = false;

                if (velocity.x == 0) {
                    animate("idle");

                    if (key == "right") {
                        sprite.setScale(sf::Vector2f(scale, scale));
                    }
                    if (key == "left") {
                        sprite.setScale(sf::Vector2f(-scale, scale));
                    }
                }
                if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !isJumping) velocity.y = 0;
            }
            sprite.move(velocity * deltaTime);
            Collision(tiles);
        }

        if (pause) {
            if (activation == "mushroom") {
                animate("mushroom");
            }

            if (activation == "hit") {
                animate("hit");
            }
            if (activation == "finish") {
                if (stage == 0) {
                    animate("finish");
                }
                finish = true;
            }
        }
    }
}