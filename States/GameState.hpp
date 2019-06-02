#ifndef RC_GAMESTATE
#define RC_GAMESTATE

#include "../Commands/Player.hpp"
#include "../States/State.hpp"
#include "../World.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

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

#endif