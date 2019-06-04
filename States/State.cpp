#include "State.hpp"
#include "StateStack.hpp"

State::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Player& player,
                        MusicPlayer& music, SoundPlayer& sounds)
    : window(&window), textures(&textures), fonts(&fonts), player(&player), music(&music), sounds(&sounds) {}

State::State(StateStack& stack, Context context) : _Stack(&stack), _Context(context) {}

State::~State() {}

void State::requestStackPush(States::ID stateID) { _Stack->pushState(stateID); }

void State::requestStackPop() { _Stack->popState(); }

void State::requestStateClear() { _Stack->clearStates(); }

State::Context State::getContext() const { return _Context; }