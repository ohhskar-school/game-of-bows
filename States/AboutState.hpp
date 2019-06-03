#ifndef RC_ABOUTSTATE
#define RC_ABOUTSTATE

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include "../ResourceManager.hpp"
#include "../Utilities/Utilities.hpp"
#include "State.hpp"
#include "StateIdentifiers.hpp"
#include "StateStack.hpp"

class AboutState : public State {
 public:
  AboutState(StateStack& stack, Context context);
  virtual void draw();
  virtual bool update(sf::Time dt);
  virtual bool handleEvent(const sf::Event& event);

  enum AboutText {
    developed,
    nameOne,
    nameTwo,
    nameThree,
    produced,
    nameFour
  };

 private:
  sf::Sprite _BackgroundSprite;
  bool _ShowText;
  std::vector<sf::Text> _Text;
  sf::Time _TextEffectTime;
};

#endif