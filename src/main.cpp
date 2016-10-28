#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "assets.h"
#include "window.h"

#define SCALE 30 //pass from pixels to box2D positions

struct Data {
  Window window;
  sf::Texture BoxTexture;
  sf::Texture GroundTexture;
  sf::Texture playerTexture;
  sf::Sprite GroundSprite;
  sf::Sprite PlayerSprite;
  float playerSpeed = 1.8f;;
  //b2World world;
} data;
//
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

void init() {
  data.window.createWindow(960, 704, "Multiplayer");
  
  //preparing world
  b2Vec2 gravity(0.0f, 9.8f);
  b2World world(gravity);
  //data.world = &world;
  
  data.BoxTexture.loadFromFile(ASSETS::ImagePath("box.png"));
  data.playerTexture.loadFromFile(ASSETS::ImagePath("player.png"));
  
  //createGround(*data.world, 400.f, 500.f);
  
  //Background
  data.GroundTexture.loadFromFile(ASSETS::ImagePath("map.png"));
  data.GroundSprite.setTexture(data.GroundTexture);
  data.GroundSprite.setOrigin(0.0f, 0.0f);
  data.GroundSprite.setPosition(0.0f, 0.0f);
  
  //Player
  data.PlayerSprite.setTexture(data.playerTexture);
  data.PlayerSprite.setOrigin(0.0f, 0.0f);
  data.PlayerSprite.setPosition(0.0f, 0.0f);
  
  data.window.addToDraw(&data.GroundSprite);
  data.window.addToDraw(&data.PlayerSprite);
}

void input() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
    data.PlayerSprite.setPosition(data.PlayerSprite.getPosition().x, data.PlayerSprite.getPosition().y - data.playerSpeed);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
    data.PlayerSprite.setPosition(data.PlayerSprite.getPosition().x, data.PlayerSprite.getPosition().y + data.playerSpeed);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
    data.PlayerSprite.setPosition(data.PlayerSprite.getPosition().x - data.playerSpeed, data.PlayerSprite.getPosition().y);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
    data.PlayerSprite.setPosition(data.PlayerSprite.getPosition().x + data.playerSpeed, data.PlayerSprite.getPosition().y);
  }
}

int main() {
  init();
  
  while (data.window.isOpen() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
    /** Simulate the world */
    //data.world->Step(1 / 60.f, 8, 3);
    input();
    
    data.window.draw();
  }
  return EXIT_SUCCESS;
}