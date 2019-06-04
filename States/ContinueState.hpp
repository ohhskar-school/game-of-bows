#ifndef RC_CONTINUESTATE
#define RC_CONTINUESTATE

#include "State.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class ContinueState : public State {
 public:
  ContinueState(StateStack& stack, Context context);

  virtual void draw();
  virtual bool update(sf::Time dt);
  virtual bool handleEvent(const sf::Event& event);
  void updateOptionText();

 private:
  enum OptionNames {
    Continue,
    Exit,
  };

 private:
  sf::Sprite _BackgroundSprite;
  std::vector<sf::Text> _Options;
  std::size_t _OptionIndex;
};

#endif