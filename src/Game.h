#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

class Game {
public:
    const static int SCREEN_WIDTH = 2048;
    const static int SCREEN_HEIGHT = 1536;
    static void start();
    static void gameLoop();
    enum State {
      uninititalised, splashScreen, menu, playing, exiting
    };



private:
    static sf::RenderWindow _window;
    static sf::Clock _clock;
    static State _state;
};

#endif 