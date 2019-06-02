#include "States.hpp"

template <typename T>
void StateStack::registerState(States::ID stateID) {
  _Factories[stateID] = [this]() { return State::Ptr(new T(*this, _Context)); };
}

State::Ptr StateStack::createState(States::ID stateID) {
  auto found = _Factories.find(stateID);
  assert(found != _Factories.end());
  return found->second();
}

void StateStack::handleEvent(const sf::Event& event) {
  for (auto itr = _Stack.rbegin(); itr != _Stack.rend(); ++itr) {
    if (!(*itr)->handleEvent(event)) return;
  }
  applyPendingChanges();
}

void StateStack::applyPendingChanges() {
  for (PendingChange change : _PendingList) {
    switch (change.action) {
      case Push:
        _Stack.push_back(createState(change.stateID));
        break;
      case Pop:
        _Stack.pop_back();
        break;
      case Clear:
        _Stack.clear();
        break;
    }
  }
  _PendingList.clear();
}

bool TitleState::handleEvent(const sf::Event& event) {
  if (event.type == sf::Event::KeyPressed) {
    requestStackPop();
    requestStackPush(States::Menu);
  }
  return true;
}

bool TitleState::update(sf::Time dt) {
  _TextEffectTime += dt;
  if (_TextEffectTime >= sf::seconds(0.5f)) {
    _ShowText = !_ShowText;
    _TextEffectTime = sf::Time::Zero;
  }
  return true;
}

MenuState::MenuState(StateStack& stack, Context context) {
    sf::Text playOption;
    playOption.setFont(font);
    playOption.setString("Play");
    centerOrigin(playOption);
    playOption.setPosition(context.window->getView().getSize() / 2.f);
    mOptions.push_back(playOption);
    return true;
}