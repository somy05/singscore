#include "splashState.h"



void splashState::init(){
    if (!font.openFromFile("assets/gamefont.ttf")){
    std::cout << "Error while loading assets " << std::endl;
    return;
}
text.setFont(font);
text.setString("Volume up!");
text.setCharacterSize(24);
text.setFillColor(sf::Color::Black);
text.setStyle(sf::Text::Bold);
text.setPosition({600,400});



    
}
void splashState::handleInput(sf::Event *event) {

if (event->is<sf::Event::KeyPressed>() || event->is<sf::Event::MouseButtonPressed>()) {
    Game::setState(Game::menu);
}

 }
void splashState::update(float timeElapsed) { 



}
void splashState::draw(sf::RenderWindow *window) { 


window->draw(text);
}
