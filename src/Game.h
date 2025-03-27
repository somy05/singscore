#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "states/gameState.h"
#include "states/playingState.h"
#include "states/menuState.h"
#include "states/splashState.h"
#include <map>


class Game {
public:
    const static int SCREEN_WIDTH = 1200;
    const static int SCREEN_HEIGHT = 900;
    static void start();
    static void gameLoop();
    enum State {
      uninitialised, splashScreen, menu, playing, exiting
    };
    static void setState(State s);



private:
    static sf::RenderWindow _window;
    static sf::Clock _clock;
    static State _state;
    static std::map<State, gameState*> _stateInstances;
};

#endif 