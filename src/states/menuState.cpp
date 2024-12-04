#include "menuState.h"

void menuState::init(){
    if (!_playTexture.loadFromFile("assets/play.png") 
     || !_exitTexture.loadFromFile("assets/exit.png")) {
    std::cout << "Error while loading assets" << std::endl;
    return;
  }
  _playSprite.setTexture(_playTexture);
  _exitSprite.setTexture(_exitTexture);
  _playSprite.setPosition(450, 500);
  _exitSprite.setPosition(450, 600);


}
void menuState::handleInput(sf::Event *event) {
    if (event->type == sf::Event::MouseButtonPressed) {
    int x = event->mouseButton.x;
    int y = event->mouseButton.y;
    if (_playSprite.getGlobalBounds().contains(x, y)) {
      Game::setState(Game::playing);
    } else if (_exitSprite.getGlobalBounds().contains(x, y)) {
      Game::setState(Game::exiting);
    }
  }



}
void menuState::update(float timeElapsed) { 



}
void menuState::draw(sf::RenderWindow *window) { 

window->draw(_playSprite);
window->draw(_exitSprite);


}