#ifndef RC_STATESTACK
#define RC_STATESTACK

#include "../ResourceManager.hpp"
#include "State.hpp"
#include "StateIdentifiers.hpp"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>

#include <functional>
#include <map>
#include <utility>
#include <vector>

namespace sf {
class Event;
class RenderWindow;
}

class StateStack : private sf::NonCopyable {
 public:
  enum Action {
    Push,
    Pop,
    Clear,
  };

 public:
  explicit StateStack(State::Context context);

  template <typename T>
  void registerState(States::ID stateID);

  void update(sf::Time dt);
  void draw();
  void handleEvent(const sf::Event& event);

  void pushState(States::ID stateID);
  void popState();
  void clearStates();

  bool isEmpty() const;

 private:
  State::Ptr createState(States::ID stateID);
  void applyPendingChanges();

 private:
  struct PendingChange {
    explicit PendingChange(Action action, States::ID stateID = States::None);

    Action action;
    States::ID stateID;
  };

 private:
  std::vector<State::Ptr> _Stack;
  std::vector<PendingChange> _PendingList;

  State::Context _Context;
  std::map<States::ID, std::function<State::Ptr()>> _Factories;
};

template <typename T>
void StateStack::registerState(States::ID stateID) {
  _Factories[stateID] = [this]() { return State::Ptr(new T(*this, _Context)); };
}

#endif
