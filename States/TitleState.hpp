#ifndef RC_TITLESTATE
#define RC_TITLESTATE

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include "../ResourceManager.hpp"
#include "State.hpp"
#include "StateIdentifiers.hpp"
#include "StateStack.hpp"
#include "../Utilities/Utilities.hpp"

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

#endif