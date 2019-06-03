#include "GameState.hpp"

GameState::GameState(StateStack& stack, Context context)
    : State(stack, context), _World(*context.window), _Player(*context.player) {}

void GameState::draw() { _World.draw(); }

bool GameState::update(sf::Time dt) {
  _World.update(dt);

  // if(_World.hasWon()) {
  //   requestStackPush(States::Continue);
  // }

  CommandQueue& commands = _World.getCommandQueue();
  _Player.handleRealtimeInput(commands);

  return true;
}

bool GameState::handleEvent(const sf::Event& event) {
  // Game input handling
  CommandQueue& commands = _World.getCommandQueue();
  _Player.handleEvent(event, commands);
  
  return true;
}