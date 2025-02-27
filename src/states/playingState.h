#ifndef GAME_playing_STATE_H
#define GAME_playing_STATE_H

#include "gameState.h"
#include "../audioInput.h"
#include "../audioOutput.h"



class playingState : public gameState {
public:
  void init() override;
  void handleInput(sf::Event *event) override;
  void update(float timeElapsed) override;
  void draw(sf::RenderWindow *window) override;

public:
  sf::Text text2;
  sf::Font font2;
  audioInput audio;
  audioOutput music;


};





#endif //GAME_playing_STATE_H