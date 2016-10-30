#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <Box2D/Box2D.h>
#include "game.h"
#include "gameManager.h"

#define SCALE 30 //pass from pixels to box2D positions

void createGround(b2World& World, float X, float Y) {
  b2BodyDef BodyDef;
  BodyDef.position = b2Vec2(X / 30.f, Y / 30.f);
  BodyDef.type = b2_staticBody;
  b2Body* Body = World.CreateBody(&BodyDef);
  b2PolygonShape Shape;
  Shape.SetAsBox((800.f / 2) / SCALE, (16.f / 2) / SCALE); // Creates a box shape. Divide your desired width and height by 2.
  b2FixtureDef FixtureDef;
  FixtureDef.density = 0.f;  // Sets the density of the body
  FixtureDef.shape = &Shape; // Sets the shape
  Body->CreateFixture(&FixtureDef); // Apply the fixture definition
}

void createBox(b2World& World, float mouseX, float mouseY) {
  b2BodyDef BodyDef;
  BodyDef.position = b2Vec2(mouseX / SCALE, mouseY / SCALE);
  BodyDef.type = b2_dynamicBody;
  b2Body* Body = World.CreateBody(&BodyDef);

  b2PolygonShape Shape;
  Shape.SetAsBox((32.f / 2) / SCALE, (32.f / 2) / SCALE);
  b2FixtureDef FixtureDef;
  FixtureDef.density = 1.f;
  FixtureDef.friction = 0.7f;
  FixtureDef.shape = &Shape;
  Body->CreateFixture(&FixtureDef);
}

void Game::start() {
  //createGround(*world, 400.f, 500.f);
  map.setTexture("map.png");
  box.setTexture("box.png");
  player.setTexture("player.png");
  GameManager::addToDraw(&map);
  GameManager::addToDraw(&player);
}

void Game::input() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) player.moveY(-playerSpeed);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) player.moveY(playerSpeed);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) player.moveX(-playerSpeed);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) player.moveX(playerSpeed);
}

void Game::update() {

}

void Game::finish() {

}