#include "menuState.h"

void menuState::init(){
    
      if (!_playTexture.loadFromFile("assets/play.png")) {
        std::cout << "Error loading play.png" << std::endl;
    }
    if (!_exitTexture.loadFromFile("assets/exit.png")) {
        std::cout << "Error loading exit.png" << std::endl;
    }
   
    //ADD TRUE PARAMETER TO .setTexture
    _playSprite.setTexture(_playTexture, true);
    _exitSprite.setTexture(_exitTexture, true);

    _playSprite.setPosition({600, 400});
    _exitSprite.setPosition({600, 200});
    std::cout << "Menu state initialized" << std::endl;
  
    return;
  }



void menuState::handleInput(sf::Event* event) {
  if (const auto* mouseclick = event->getIf<sf::Event::MouseButtonPressed>()) {
    sf::Vector2f mousePos = {static_cast<float>(mouseclick->position.x), static_cast<float>(mouseclick->position.y)};

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

window->draw(_exitSprite);



}