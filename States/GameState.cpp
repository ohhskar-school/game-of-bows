#include "GameState.hpp"
#include "../Sounds/MusicPlayer.hpp"

GameState::GameState(StateStack& stack, Context context)
    : State(stack, context), _World(*context.window, *context.sounds), _Player(*context.player) {
  srand((unsigned)time(0));
  _randValue = rand() % 5 + 1;
  switch(_randValue) {
    case 1:
      context.music->play(Music::GameThemeOne);
      break;
    case 2:
      context.music->play(Music::GameThemeTwo);
      break;
    case 3:
      context.music->play(Music::GameThemeThree);
      break;
    case 4:
      context.music->play(Music::GameThemeFour);
      break;
    case 5:
      context.music->play(Music::GameThemeFive);
      break;
  }
}

void GameState::draw() { _World.draw(); }

bool GameState::update(sf::Time dt) {
  _World.update(dt);

  if (_World.hasWon()) {
    requestStackPush(States::Continue);
  }

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