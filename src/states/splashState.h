#ifndef GAME_SPLASHSCREEN_STATE_H
#define GAME_SPLASHSCREEN_STATE_H
#include "gameState.h"
#include "../Game.h"
#include <iostream>
class splashState : public gameState {
public:
  void init() override;
  void handleInput(sf::Event *event) override;
  void update(float timeElapsed) override;
  void draw(sf::RenderWindow *window) override;

  private:
    sf::Font font;
    sf::Text text;
};
#endif //GAME_SPLASHSCREEN_STATE_H