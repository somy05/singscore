#ifndef GAME_playing_STATE_H
#define GAME_playing_STATE_H

#include "gameState.h"
#include "../audioInput.h"
#include "../audioOutput.h"
#include "../Game.h"



class playingState : public gameState {
public:
  playingState() 
  : text2(font2),
   font2(),
   audio(),
   music()
  {}
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