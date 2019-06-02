#ifndef RC_STATES
#define RC_STATES

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <algorithm>
#include <cassert>
#include <functional>
#include <map>
#include <vector>

#include "../Commands/Player.hpp"
#include "../ResourceManager.hpp"
#include "../World.hpp"

namespace States {
enum ID { Title, Menu, Game, Over };
};  // namespace States

class State {
 public:
  typedef std::unique_ptr<State> Ptr;
  struct Context {
    //   Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Player& player);
    Context(sf::RenderWindow& window, TextureHolder& textures, Player& player);
    sf::RenderWindow* window;
    TextureHolder* textures;
    //   FontHolder* fonts;
    Player* player;
  };

 public:
  State(StateStack& stack, Context context);
  virtual ~State();
  virtual void draw() = 0;
  virtual bool update(sf::Time dt) = 0;
  virtual bool handleEvent(const sf::Event& event) = 0;
  bool centerOrigin(sf::Text text);

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
    //   ...
    Action action;
    States::ID stateID;
  };

 private:
  std::vector<State::Ptr> _Stack;
  std::vector<PendingChange> _PendingList;
  State::Context _Context;
  std::map<States::ID, std::function<State::Ptr()>> _Factories;
};

class GameState : public State {
 public:
  GameState(StateStack& stack, Context context);
  virtual void draw();
  virtual bool update(sf::Time dt);
  virtual bool handleEvent(const sf::Event& event);

 private:
  World _World;
  Player& _Player;
};

class TitleState : public State {
 public:
  TitleState(StateStack& stack, Context context);
  virtual void draw();
  virtual bool update(sf::Time dt);
  virtual bool handleEvent(const sf::Event& event);

 private:
  sf::Sprite _BackgroundSprite;
  sf::Text _Text;
  bool _ShowText;
  sf::Time _TextEffectTime;
};

class MenuState : public State {
 public:
  MenuState(StateStack& stack, Context context);
  virtual void draw();
  virtual bool update(sf::Time dt);
  virtual bool handleEvent(const sf::Event& event);
  enum OptionNames {
    Play,
    Exit,
  };
  std::vector<sf::Text> _Options;
  std::size_t _OptionIndex;

 private:
  sf::Sprite _BackgroundSprite;
  sf::Text _Text;
  bool _ShowText;
  sf::Time _TextEffectTime;
};

#endif