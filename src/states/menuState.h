#ifndef GAME_MENUSCREEN_STATE_H
#define GAME_MENUSCREEN_STATE_H
#include "gameState.h"
class MENUSCREENState : public gameState {
public:
  void init() override;
  void handleInput(sf::Event *event) override;
  void update(float timeElapsed) override;
  void draw(sf::RenderWindow *window) override;
};
#endif //GAME_MENUSCREEN_STATE_H