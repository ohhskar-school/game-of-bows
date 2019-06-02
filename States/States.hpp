#ifndef RC_STATES
#define RC_STATES

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

class State {
 public:
  typedef std::unique_ptr<State> Ptr;
  struct Context {
    ...
  };

 public:
  State(StateStack& stack, Context context);
  virtual ~State();
  virtual void draw() = 0;
  virtual bool update(sf::Time dt) = 0;
  virtual bool handleEvent(const sf::Event& event) = 0;

 protected:
  void requestStackPush(States::ID stateID);
  void requestStackPop();
  void requestStateClear();
  Context getContext() const;

 private:
  StateStack* _Stack;
  Context _Context;
};

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
    ... Action action;
    States::ID stateID;
  };

 private:
  std::vector<State::Ptr> _Stack;
  std::vector<PendingChange> _PendingList;
  State::Context _Context;
  std::map<States::ID, std::function<State::Ptr()>> _Factories;
};

struct Context {
  Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Player& player);
  sf::RenderWindow* window;
  TextureHolder* textures;
  FontHolder* fonts;
  Player* player;
};

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
  FOREACH(PendingChange change, _PendingList) {
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

#endif