#include "Game.hpp"

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game() : _window(sf::VideoMode(768, 576), "World", sf::Style::Close), _world(_window) {}

void Game::run() {
  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;
  while (_window.isOpen()) {
    timeSinceLastUpdate += clock.restart();
    while (timeSinceLastUpdate > TimePerFrame) {
      timeSinceLastUpdate -= TimePerFrame;
      processInput();
      update(TimePerFrame);
    }
    render();
  }
}

// TODO
void Game::processInput() {
  CommandQueue& commands = _world.getCommandQueue();

  sf::Event event;
  while (_window.pollEvent(event)) {
    _player.handleEvent(event, commands);

    if (event.type == sf::Event::Closed) {
      _window.close();
    }
  }
  _player.handleRealtimeInput(commands);
}
void Game::update(sf::Time dt) { _world.update(dt); }

void Game::render() {
  _window.clear();
  _world.draw();
  _window.setView(_window.getDefaultView());
  _window.display();
}