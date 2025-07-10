#include "menuState.h"

void menuState::init(){
    if (!_playTexture.loadFromFile("assets/play.png") 
     || !_exitTexture.loadFromFile("assets/exit.png")) {
    std::cout << "Error while loading assets" << std::endl;
    return;
  }
  _playSprite.setTexture(_playTexture);
  _exitSprite.setTexture(_exitTexture);
  _playSprite.setPosition({450, 500});
  _exitSprite.setPosition({450, 600});
  std::cout << "Menu state initialized" << std::endl;


}
void menuState::handleInput(sf::Event* event) {
  if (event->type == sf::Event::MouseButtonPressed) {
    sf::Vector2f mousePos = {static_cast<float>(event->mouseButton.x), static_cast<float>(event->mouseButton.y)};

      if (_playSprite.getGlobalBounds().contains(mousePos)) {
          Game::setState(Game::playing);
      } else if (_exitSprite.getGlobalBounds().contains(mousePos)) {
          Game::setState(Game::exiting);
      }
  }
}

void menuState::update(float timeElapsed) { 



}
void menuState::draw(sf::RenderWindow *window) { 

window->draw(_playSprite);
std::cout << "Drawing play sprite" << std::endl;
window->draw(_exitSprite);
std::cout << "Drawing exit sprite" << std::endl;


}