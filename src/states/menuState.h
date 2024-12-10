#ifndef GAME_MENUSCREEN_STATE_H
#define GAME_MENUSCREEN_STATE_H
#include "gameState.h"
#include "../Game.h"
#include <iostream>
class menuState : public gameState {
public:
  void init() override;
  void handleInput(sf::Event *event) override;
  void update(float timeElapsed) override;
  void draw(sf::RenderWindow *window) override;
private:
  sf::Texture _playTexture;
  sf::Sprite _playSprite;
  sf::Texture _exitTexture;
  sf::Sprite _exitSprite;

};
#endif 