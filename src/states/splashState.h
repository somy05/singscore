#ifndef GAME_SPLASHSCREEN_STATE_H
#define GAME_SPLASHSCREEN_STATE_H
#include "gameState.h"
class SplashscreenState : public gameState {
public:
  void init() override;
  void handleInput(sf::Event *event) override;
  void update(float timeElapsed) override;
  void draw(sf::RenderWindow *window) override;
};
#endif //GAME_SPLASHSCREEN_STATE_H