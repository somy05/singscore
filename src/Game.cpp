#include "Game.h"

sf::RenderWindow Game::_window;
sf::Clock Game::_clock;
Game::State Game::_state = uninitialised;
std::map<Game::State, gameState *> Game::_stateInstances;

void Game::start() {
    if (_state != uninitialised) return;
    _window.create(sf::VideoMode(Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT, 32), "SingScore", sf::Style::Default);
    _window.setFramerateLimit(60);
    _stateInstances[splashScreen] = new splashState();
    _stateInstances[splashScreen]->init();
    _stateInstances[menu] = new menuState();
    _stateInstances[menu]->init();
    _stateInstances[playing] = new playingState();
    _stateInstances[playing]->init();
    _state = splashScreen;
    gameLoop();
    auto itr = _stateInstances.begin();
    while (itr != _stateInstances.end()) {
        delete itr->second;
        itr++;
    }
    _window.close();
}

void Game::gameLoop() {
    while (_state != exiting) {
        float timeElapsed = _clock.restart().asSeconds();
        _window.clear(sf::Color(255, 255, 255));
        gameState *currentState = _stateInstances[_state];

        // Handle input
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {_state = exiting;}
            currentState->handleInput(&event);
        }

        // Update our entities
        currentState->update(timeElapsed);

        // Draw our new entities
        currentState->draw(&_window);
        _window.display();
    }
    


}

void Game::setState(Game::State s) {_state = s;}
