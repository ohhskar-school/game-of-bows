#include "ControlsState.hpp"
#include "../ResourceManager.hpp"
#include "../Utilities/Utilities.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

ControlsState::ControlsState(StateStack& stack, Context context)
    : State(stack, context),
      _KeyboardTexture(context.textures->get(Textures::Keyboard)),
      _ControllerTexture(context.textures->get(Textures::Controller)),
      _Options(),
      _OptionIndex(0) {
  sf::Font& font = context.fonts->get(Fonts::Main);

  _BackgroundSprite.setTexture(_KeyboardTexture);

  // A simple menu demonstration
  sf::Text keyboardOption;
  keyboardOption.setFont(font);
  keyboardOption.setString("Keyboard");
  centerOrigin(keyboardOption);
  keyboardOption.setCharacterSize(16);
  keyboardOption.setPosition(context.window->getView().getSize() / 2.f + sf::Vector2f(25.f, 130.f));
  _Options.push_back(keyboardOption);

  sf::Text controllerOption;
  controllerOption.setFont(font);
  controllerOption.setString("Controller");
  centerOrigin(controllerOption);
  controllerOption.setCharacterSize(16);
  controllerOption.setPosition(keyboardOption.getPosition() + sf::Vector2f(25.f, 30.f));
  _Options.push_back(controllerOption);

  sf::Text backOption;
  backOption.setFont(font);
  backOption.setString("Back");
  centerOrigin(backOption);
  backOption.setCharacterSize(16);
  backOption.setPosition(controllerOption.getPosition() + sf::Vector2f(25.f, 30.f));
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

  if (event.key.code == sf::Keyboard::Return) {
    // if (_OptionIndex == Keyboard) {
    //   _BackgroundSprite.setTexture(_KeyboardTexture);
    // } else if (_OptionIndex == Controller) {
    //   _BackgroundSprite.setTexture(_ControllerTexture);
    // } 
    if (_OptionIndex == Back) {
      requestStackPush(States::Menu);
    }
  }

  else if (event.key.code == sf::Keyboard::Left) {
    // Decrement and wrap-around
    if (_OptionIndex > 0)
      _OptionIndex--;
    else
      _OptionIndex = _Options.size() - 1;

    updateOptionText();
    updateOptionBackground();
  }

  else if (event.key.code == sf::Keyboard::Right) {
    // Increment and wrap-around
    if (_OptionIndex < _Options.size() - 1)
      _OptionIndex++;
    else
      _OptionIndex = 0;

    updateOptionText();
    updateOptionBackground();
  }

  return true;
}

void ControlsState::updateOptionText() {
  if (_Options.empty()) return;

  // White all texts
  for (sf::Text& text : _Options) text.setColor(sf::Color::White);

  // Red the selected text
  _Options[_OptionIndex].setColor(sf::Color::Yellow);
}

void ControlsState::updateOptionBackground() {
  if(_OptionIndex == Keyboard) {
      _BackgroundSprite.setTexture(_KeyboardTexture);
  } else if(_OptionIndex == Controller) {
      _BackgroundSprite.setTexture(_ControllerTexture);
  } 
}
