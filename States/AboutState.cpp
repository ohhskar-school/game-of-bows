#include "AboutState.hpp"
#include "State.hpp"

AboutState::AboutState(StateStack& stack, Context context)
    : State(stack, context), _ShowText(true), _TextEffectTime(sf::Time::Zero) {
  _BackgroundSprite.setTexture(context.textures->get(Textures::MenuScreen));
  sf::Font& font = context.fonts->get(Fonts::Main);

  sf::Text developed;
  developed.setFont(font);
  developed.setString("Developed by");
  developed.setFillColor(sf::Color::Yellow);
  centerOrigin(developed);
  developed.setCharacterSize(24);
  developed.setPosition(context.window->getView().getSize() / 2.f + sf::Vector2f(35.f, -130.f));
  _Text.push_back(developed);

  sf::Text nameOne;
  nameOne.setFont(context.fonts->get(Fonts::Main));
  nameOne.setString("Oscar Vian L. Valles");
  centerOrigin(nameOne);
  nameOne.setCharacterSize(16);
  nameOne.setPosition(developed.getPosition() + sf::Vector2f(100.f, 40.f));
  _Text.push_back(nameOne);

  sf::Text nameTwo;
  nameTwo.setFont(context.fonts->get(Fonts::Main));
  nameTwo.setString("Justin Andre E. Po");
  centerOrigin(nameTwo);
  nameTwo.setCharacterSize(16);
  nameTwo.setPosition(nameOne.getPosition() + sf::Vector2f(-15.f, 30.f));
  _Text.push_back(nameTwo);

  sf::Text nameThree;
  nameThree.setFont(context.fonts->get(Fonts::Main));
  nameThree.setString("Patricia Lexa U. Tumulak");
  centerOrigin(nameThree);
  nameThree.setCharacterSize(16);
  nameThree.setPosition(nameTwo.getPosition() + sf::Vector2f(45.f, 30.f));
  _Text.push_back(nameThree);

  sf::Text produced;
  produced.setFont(context.fonts->get(Fonts::Main));
  produced.setString("Produced By");
  produced.setFillColor(sf::Color::Yellow);
  centerOrigin(produced);
  produced.setCharacterSize(24);
  produced.setPosition(nameThree.getPosition() + sf::Vector2f(-130.f, 50.f));
  _Text.push_back(produced);

  sf::Text nameFour;
  nameFour.setFont(context.fonts->get(Fonts::Main));
  nameFour.setString("Ryan Ciriaco M. Dulaca");
  centerOrigin(nameFour);
  nameFour.setCharacterSize(16);
  nameFour.setPosition(produced.getPosition() + sf::Vector2f(120.f, 40.f));
  _Text.push_back(nameFour);
}

void AboutState::draw() {
  sf::RenderWindow& window = *getContext().window;

  window.setView(window.getDefaultView());
  window.draw(_BackgroundSprite);

  for (const sf::Text& text : _Text) window.draw(text);
}

bool AboutState::update(sf::Time dt) {
  _TextEffectTime += dt;

  if (_TextEffectTime >= sf::seconds(1.f)) {
    _ShowText = !_ShowText;
    _TextEffectTime = sf::Time::Zero;
  }

  return true;
}

bool AboutState::handleEvent(const sf::Event& event) {
  // If any key is pressed, trigger the next screen
  if (event.type == sf::Event::KeyPressed) {
    requestStackPop();
    requestStackPush(States::Menu);
  }

  return true;
}