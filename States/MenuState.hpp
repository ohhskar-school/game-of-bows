#ifndef RC_MENUSTATE
#define RC_MENUSTATE

#include "State.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class MenuState : public State {
 public:
  MenuState(StateStack& stack, Context context);

  virtual void draw();
  virtual bool update(sf::Time dt);
  virtual bool handleEvent(const sf::Event& event);

  void updateOptionText();

 private:
  enum OptionNames {
    Play,
    About,
    Credits,
    Exit,
  };

 private:
  sf::Sprite _BackgroundSprite;

  std::vector<sf::Text> _Options;
  std::size_t _OptionIndex;
};

#endif
