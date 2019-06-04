#include "ContinueState.hpp"
#include "../ResourceManager.hpp"
#include "../Utilities/Utilities.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

ContinueState::ContinueState(StateStack& stack, Context context)
    : State(stack, context), _BackgroundSprite(), _Options(), _OptionIndex(0) {
  sf::Font& font = context.fonts->get(Fonts::Main);
  sf::Vector2f viewSize = context.window->getView().getSize();

  sf::Text winner;
  winner.setFont(font);
  winner.setString("Player has won!");
  winner.setCharacterSize(16);
  centerOrigin(winner);
  winner.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);

  sf::Text continueOption;
  continueOption.setFont(font);
  continueOption.setString("Continue");
  centerOrigin(continueOption);
  continueOption.setPosition(winner.getPosition() + sf::Vector2f(-40.f, 50.f));

  sf::Text exitOption;
  exitOption.setFont(font);
  exitOption.setString("Exit");
  centerOrigin(exitOption);
  exitOption.setPosition(continueOption.getPosition() + sf::Vector2f(50.f, 0.f));
}

void ContinueState::draw() {
  sf::RenderWindow& window = *getContext().window;
  window.setView(window.getDefaultView());

  sf::RectangleShape backgroundShape;
  backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
  backgroundShape.setSize(window.getView().getSize());

  window.draw(backgroundShape);
  for (const sf::Text& text : _Options) window.draw(text);
}

bool ContinueState::update(sf::Time) { return false; }

bool ContinueState::handleEvent(const sf::Event& event) {
  // The demonstration menu logic
  if (event.type != sf::Event::KeyPressed) return false;

  if (event.key.code == sf::Keyboard::Return) {
    if (_OptionIndex == Continue) {
      requestStateClear();
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

void ContinueState::updateOptionText() {
  if (_Options.empty()) return;

  // White all texts
  for (sf::Text& text : _Options) text.setFillColor(sf::Color::White);

  // Red the selected text
  _Options[_OptionIndex].setFillColor(sf::Color::Yellow);
}