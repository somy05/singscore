#include "playingState.h"

void playingState::init(){
audio.initPortAudio();

if (!font2.loadFromFile("assets/gamefont.ttf")){
    std::cout << "Error while loading assets " << std::endl;
    return;
}
text2.setCharacterSize(24);
text2.setFillColor(sf::Color::Black);
text2.setStyle(sf::Text::Bold);
text2.setPosition(600,400);
text2.setFont(font2);
text2.setString("Placeholder text");

}
void playingState::handleInput(sf::Event *event) {



}
void playingState::update(float timeElapsed) { 

audio.startRecording();

}
void playingState::draw(sf::RenderWindow *window) { 


window->draw(text2);

};