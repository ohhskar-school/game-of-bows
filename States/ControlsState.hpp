#ifndef RC_CONTROLSSTATE
#define RC_CONTROLSSTATE

#include "State.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class ControlsState : public State {
 public:
  ControlsState(StateStack& stack, Context context);

  virtual void draw();
  virtual bool update(sf::Time dt);
  virtual bool handleEvent(const sf::Event& event);

  void updateOptionText();
  void updateOptionBackground();

 private:
  enum OptionNames {
    Controller,
    Keyboard,
    Back
  };

 private:
  sf::Sprite _BackgroundSprite;
  sf::Texture& _ControllerTexture;
  sf::Texture& _KeyboardTexture;
  std::vector<sf::Text> _Options;
  std::size_t _OptionIndex;
};

#endif
