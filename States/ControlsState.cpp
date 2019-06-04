#include "ControlsState.hpp"
#include "../ResourceManager.hpp"
#include "../Utilities/Utilities.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

ControlsState::ControlsState(StateStack& stack, Context context)
    : State(stack, context),
      _ControllerTexture(context.textures->get(Textures::Controller)),
      _KeyboardTexture(context.textures->get(Textures::Keyboard)),
      _Options(),
      _OptionIndex(0) {
  sf::Font& font = context.fonts->get(Fonts::Main);

  _BackgroundSprite.setTexture(_KeyboardTexture);

  // A simple menu demonstration
  sf::Text keyboardOption;
  keyboardOption.setFont(font);
  keyboardOption.setString("Player 1");
  centerOrigin(keyboardOption);
  keyboardOption.setCharacterSize(16);
  keyboardOption.setPosition(context.window->getView().getSize() / 2.f + sf::Vector2f(-40.f, 160.f));
  _Options.push_back(keyboardOption);

  sf::Text controllerOption;
  controllerOption.setFont(font);
  controllerOption.setString("Player 2");
  centerOrigin(controllerOption);
  controllerOption.setCharacterSize(16);
  controllerOption.setPosition(keyboardOption.getPosition() + sf::Vector2f(200.f, 0.f));
  _Options.push_back(controllerOption);

  sf::Text backOption;
  backOption.setFont(font);
  backOption.setString("Back");
  centerOrigin(backOption);
  backOption.setCharacterSize(16);
  backOption.setPosition(controllerOption.getPosition() + sf::Vector2f(200.f, 0.f));
  _Options.push_back(backOption);

  updateOptionText();
}

void ControlsState::draw() {
  sf::RenderWindow& window = *getContext().window;

  window.setView(window.getDefaultView());
  window.draw(_BackgroundSprite);

  for (const sf::Text& text : _Options) window.draw(text);
}

bool ControlsState::update(sf::Time) { return true; }

bool ControlsState::handleEvent(const sf::Event& event) {
  // The demonstration menu logic
  if (event.type != sf::Event::KeyPressed) return false;

  if (event.key.code == sf::Keyboard::Return && _OptionIndex == Back) {
      requestStackPop();
      requestStackPush(States::Menu);
  }

  else if (event.key.code == sf::Keyboard::Left) {
    // Decrement and wrap-around
    if (_OptionIndex > 0)
      _OptionIndex--;
    else
      _OptionIndex = _Options.size() - 1;

    updateOptionText();
  }

  else if (event.key.code == sf::Keyboard::Right) {
    // Increment and wrap-around
    if (_OptionIndex < _Options.size() - 1)
      _OptionIndex++;
    else
      _OptionIndex = 0;

    updateOptionText();
  }

  return true;
}

void ControlsState::updateOptionText() {
  if (_Options.empty()) return;

  // White all texts
  for (sf::Text& text : _Options) text.setFillColor(sf::Color::White);

  // Red the selected text
  _Options[_OptionIndex].setFillColor(sf::Color::Yellow);

  if(_OptionIndex == Keyboard) {
      _BackgroundSprite.setTexture(_KeyboardTexture);
  } else if(_OptionIndex == Controller) {
      _BackgroundSprite.setTexture(_ControllerTexture);
  } 
}
