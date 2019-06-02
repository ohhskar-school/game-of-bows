#include "State.hpp"
#include "TitleState.hpp"

TitleState::TitleState(StateStack& stack, Context context)
    : State(stack, context), _Text(), _ShowText(true), _TextEffectTime(sf::Time::Zero) {
  _BackgroundSprite.setTexture(context.textures->get(Textures::TitleScreen));

  _Text.setFont(context.fonts->get(Fonts::Main));
  _Text.setString("Press any key to start");
  centerOrigin(_Text);
  _Text.setCharacterSize(16);
  _Text.setPosition(context.window->getView().getSize() / 2.f + sf::Vector2f(150.f, 130.f));
//   _Text.setPosition(0.f, 0.f);
}

void TitleState::draw() {
  sf::RenderWindow& window = *getContext().window;
  window.draw(_BackgroundSprite);

  if (_ShowText) window.draw(_Text);
}

bool TitleState::update(sf::Time dt) {
  _TextEffectTime += dt;

  if (_TextEffectTime >= sf::seconds(0.5f)) {
    _ShowText = !_ShowText;
    _TextEffectTime = sf::Time::Zero;
  }

  return true;
}

bool TitleState::handleEvent(const sf::Event& event) {
  // If any key is pressed, trigger the next screen
  if (event.type == sf::Event::KeyPressed) {
    requestStackPop();
    requestStackPush(States::Menu);
  }

  return true;
}