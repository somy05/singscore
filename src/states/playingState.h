#ifndef GAME_playing_STATE_H
#define GAME_playing_STATE_H

#include "gameState.h"
#include "../audioInput.h"
#include "../audioOutput.h"
#include "../Game.h"



class playingState : public gameState {
public:
  playingState() 
  : font2(),
   text2(),
   audio(),
   music(),
   gameStarted(false),
   userPitch(0.0),
   targetPitch(0.0),
   score(0)
  {}
  
  void init() override;
  void handleInput(sf::Event *event) override;
  void update(float timeElapsed) override;
  void draw(sf::RenderWindow *window) override;

private:
  sf::Text text2;
  sf::Font font2;
  audioInput audio;
  audioOutput music;
  
  // Game state variables
  bool gameStarted;
  double userPitch;
  double targetPitch;
  int score;
  
  // Helper methods
  void startGame();
  void calculateScore();
  double getPitchAccuracy(double userPitch, double targetPitch);
  std::string getPitchName(double frequency);
};





#endif //GAME_playing_STATE_H