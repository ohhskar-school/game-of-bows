#include "MenuState.hpp"
#include "../Utilities/Utilities.hpp"
#include "../ResourceManager.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

MenuState::MenuState(StateStack& stack, Context context) : State(stack, context), _Options(), _OptionIndex(0) {
  sf::Texture& texture = context.textures->get(Textures::TitleScreen);
  sf::Font& font = context.fonts->get(Fonts::Main);

  _BackgroundSprite.setTexture(texture);

  // A simple menu demonstration
  sf::Text playOption;
  playOption.setFont(font);
  playOption.setString("Play");
  centerOrigin(playOption);
  playOption.setCharacterSize(16);
  playOption.setPosition(context.window->getView().getSize() / 2.f + sf::Vector2f(25.f, 130.f));
  _Options.push_back(playOption);

  sf::Text aboutOption;
  aboutOption.setFont(font);
  aboutOption.setString("About");
  centerOrigin(aboutOption);
  aboutOption.setCharacterSize(16);
  aboutOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 30.f));
  _Options.push_back(aboutOption);

  sf::Text creditsOption;
  creditsOption.setFont(font);
  creditsOption.setString("Credits");
  centerOrigin(creditsOption);
  creditsOption.setCharacterSize(16);
  creditsOption.setPosition(aboutOption.getPosition() + sf::Vector2f(0.f, 30.f));
  _Options.push_back(creditsOption);

  sf::Text exitOption;
  exitOption.setFont(font);
  exitOption.setString("Exit");
  centerOrigin(exitOption);
  exitOption.setCharacterSize(16);
  exitOption.setPosition(creditsOption.getPosition() + sf::Vector2f(0.f, 30.f));
  _Options.push_back(exitOption);

  updateOptionText();
}

void MenuState::draw() {
  sf::RenderWindow& window = *getContext().window;

  window.setView(window.getDefaultView());
  window.draw(_BackgroundSprite);

  for (const sf::Text& text : _Options) window.draw(text);
}

bool MenuState::update(sf::Time) { return true; }

bool MenuState::handleEvent(const sf::Event& event) {
  // The demonstration menu logic
  if (event.type != sf::Event::KeyPressed) return false;

  if (event.key.code == sf::Keyboard::Return) {
    if (_OptionIndex == Play) {
      requestStackPop();
      requestStackPush(States::Game);
    } else if (_OptionIndex == About) {
      requestStackPop();
      requestStackPush(States::Game);
    }  else if (_OptionIndex == Credits) {
      requestStackPop();
      requestStackPush(States::Game);
    } else if (_OptionIndex == Exit) {
      // The exit option was chosen, by removing itself, the stack will be empty, and the game will know it is time to
      // close.
      requestStackPop();
    }
  }

  else if (event.key.code == sf::Keyboard::Up) {
    // Decrement and wrap-around
    if (_OptionIndex > 0)
      _OptionIndex--;
    else
      _OptionIndex = _Options.size() - 1;

    updateOptionText();
  }

  else if (event.key.code == sf::Keyboard::Down) {
    // Increment and wrap-around
    if (_OptionIndex < _Options.size() - 1)
      _OptionIndex++;
    else
      _OptionIndex = 0;

    updateOptionText();
  }

  return true;
}

void MenuState::updateOptionText() {
  if (_Options.empty()) return;

  // White all texts
  for (sf::Text& text : _Options) text.setColor(sf::Color::White);

  // Red the selected text
  _Options[_OptionIndex].setColor(sf::Color::Yellow);
}
