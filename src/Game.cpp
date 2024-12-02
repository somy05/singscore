#include "Game.h"

sf::RenderWindow Game::_window;
sf::Clock Game::_clock;

void Game::start() {
    if (_window.isOpen()) return;

    _window.create(sf::VideoMode(Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT, 32), "Game");
    _window.setFramerateLimit(60);

    gameLoop();
}

void Game::gameLoop() {
    while (_window.isOpen()) {
        float timeElapsed = _clock.restart().asSeconds();
        _window.clear(sf::Color(255, 255, 255));

        // Handle input
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) { _window.close(); }
            // else handle controls input
        }

        // Update our entities

        // Draw our new entities

        _window.display();
    }
}