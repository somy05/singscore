#ifndef GAME_playing_STATE_H
#define GAME_playing_STATE_H

#include "gameState.h"
class playingState : public gameState {
public:
  void init() override;
  void handleInput(sf::Event *event) override;
  void update(float timeElapsed) override;
  void draw(sf::RenderWindow *window) override;
};







#endif //GAME_playing_STATE_H