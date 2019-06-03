#ifndef RC_CREDITSSTATE
#define RC_CREDITSSTATE

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include "../ResourceManager.hpp"
#include "../Utilities/Utilities.hpp"
#include "State.hpp"
#include "StateIdentifiers.hpp"
#include "StateStack.hpp"

class CreditsState : public State {
 public:
  CreditsState(StateStack& stack, Context context);
  virtual void draw();
  virtual bool update(sf::Time dt);
  virtual bool handleEvent(const sf::Event& event);

  enum AboutText {
    titleOne,
    creditOne,
    creditTwo,
    creditThree,
    creditFour,
    creditFive,
    titleTwo,
    creditSix,
    creditSeven,
    creditEight,
    creditNine,
    creditTen,
    creditEleven,
  };

 private:
  sf::Sprite _BackgroundSprite;
  bool _ShowText;
  std::vector<sf::Text> _Text;
  sf::Time _TextEffectTime;
};

#endif