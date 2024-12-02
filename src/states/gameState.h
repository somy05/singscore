#ifndef GAME_GAMESTATE_H
#define GAME_GAMESTATE_H
#include <SFML/Graphics.hpp>
class gameState {
public:
  virtual ~gameState();
  virtual void init() = 0;
  virtual void handleInput(sf::Event *event) = 0;
  virtual void update(float elapsedTime) = 0;
  virtual void draw(sf::RenderWindow *window) = 0;
};
#endif 