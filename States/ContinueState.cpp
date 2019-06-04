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

  _continueText.setFont(font);
  _continueText.setString("CONTINUE?");
  _continueText.setCharacterSize(40);
  centerOrigin(_continueText);
  _continueText.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);

  sf::Text continueOption;
  continueOption.setFont(font);
  continueOption.setString("Yes");
  centerOrigin(continueOption);
  continueOption.setCharacterSize(16);
  continueOption.setPosition(_continueText.getPosition() + sf::Vector2f(-40.f, 50.f));
  _Options.push_back(continueOption);

  sf::Text exitOption;
  exitOption.setFont(font);
  exitOption.setString("No");
  centerOrigin(exitOption);
  exitOption.setCharacterSize(16);
  exitOption.setPosition(continueOption.getPosition() + sf::Vector2f(50.f, 0.f));
  _Options.push_back(exitOption);

  updateOptionText();
}

void ContinueState::draw() {
  sf::RenderWindow& window = *getContext().window;
  window.setView(window.getDefaultView());

  sf::RectangleShape backgroundShape;
  backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
  backgroundShape.setSize(window.getView().getSize());

  window.draw(backgroundShape);
  window.draw(_continueText);
  for (const sf::Text& text : _Options) window.draw(text);
}

bool ContinueState::update(sf::Time) { return false; }

bool ContinueState::handleEvent(const sf::Event& event) {
  // The demonstration menu logic
  if (event.type != sf::Event::KeyPressed) return false;

  if (event.key.code == sf::Keyboard::Return) {
    if (_OptionIndex == Continue) {
      requestStackPush(States::Game);
    } else {
      requestStateClear();
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
  }

  else if (event.key.code == sf::Keyboard::Right) {
    // Increment and wrap-around
    if (_OptionIndex < _Options.size() - 1)
      _OptionIndex++;
    else
      _OptionIndex = 0;

    updateOptionText();
  }

  return false;
}

void ContinueState::updateOptionText() {
  if (_Options.empty()) return;

  // White all texts
  for (sf::Text& text : _Options) text.setFillColor(sf::Color::White);

  // Red the selected text
  _Options[_OptionIndex].setFillColor(sf::Color::Yellow);
}