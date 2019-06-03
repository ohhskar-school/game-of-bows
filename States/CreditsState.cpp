#include "CreditsState.hpp"
#include "State.hpp"

CreditsState::CreditsState(StateStack& stack, Context context)
    : State(stack, context), _ShowText(true), _TextEffectTime(sf::Time::Zero) {
  _BackgroundSprite.setTexture(context.textures->get(Textures::MenuScreen));
  sf::Font& font = context.fonts->get(Fonts::Main);

  sf::Text titleOne;
  titleOne.setFont(font);
  titleOne.setString("Art:");
  titleOne.setFillColor(sf::Color::Yellow);
  titleOne.setCharacterSize(24);
  titleOne.setPosition(sf::Vector2f(50.f, 50.f));
  _Text.push_back(titleOne);

  sf::Text creditOne;
  creditOne.setFont(context.fonts->get(Fonts::Main));
  creditOne.setString("Adventurer Animation Pack by FinalGateStudios");
  creditOne.setCharacterSize(13);
  creditOne.setPosition(titleOne.getPosition() + sf::Vector2f(0.f, 50.f));
  _Text.push_back(creditOne);

  sf::Text creditTwo;
  creditTwo.setFont(context.fonts->get(Fonts::Main));
  creditTwo.setString("Generic DUNGEON pack by Estudio Vaca Roxa");
  creditTwo.setCharacterSize(13);
  creditTwo.setPosition(creditOne.getPosition() + sf::Vector2f(0.f, 30.f));
  _Text.push_back(creditTwo);

  sf::Text creditThree;
  creditThree.setFont(context.fonts->get(Fonts::Main));
  creditThree.setString("Green Pixel Art Background by Fez Escalante");
  creditThree.setCharacterSize(13);
  creditThree.setPosition(creditTwo.getPosition() + sf::Vector2f(0.f, 30.f));
  _Text.push_back(creditThree);

  sf::Text creditFour;
  creditFour.setFont(context.fonts->get(Fonts::Main));
  creditFour.setString("Lava Cave from Dinocide");
  creditFour.setCharacterSize(13);
  creditFour.setPosition(creditThree.getPosition() + sf::Vector2f(0.f, 30.f));
  _Text.push_back(creditFour);

  sf::Text creditFive;
  creditFive.setFont(context.fonts->get(Fonts::Main));
  creditFive.setString("Desert Background by blank_canvas");
  creditFive.setCharacterSize(13);
  creditFive.setPosition(creditFour.getPosition() + sf::Vector2f(0.f, 30.f));
  _Text.push_back(creditFive);

  sf::Text titleTwo;
  titleTwo.setFont(font);
  titleTwo.setString("Music:");
  titleTwo.setFillColor(sf::Color::Yellow);
  titleTwo.setCharacterSize(24);
  titleTwo.setPosition(creditFive.getPosition() + sf::Vector2f(0.f, 70.f));
  _Text.push_back(titleTwo);

  sf::Text creditSix;
  creditSix.setFont(font);
  creditSix.setString("SFX - Towerfall Ascension");
  creditSix.setCharacterSize(13);
  creditSix.setPosition(titleTwo.getPosition() + sf::Vector2f(0.f, 50.f));
  _Text.push_back(creditSix);

  sf::Text creditSeven;
  creditSeven.setFont(font);
  creditSeven.setString("Reincarnated Soul Part 2 - Castlevania: Bloodlines");
  creditSeven.setCharacterSize(13);
  creditSeven.setPosition(creditSix.getPosition() + sf::Vector2f(0.f, 30.f));
  _Text.push_back(creditSeven);

  sf::Text creditEight;
  creditEight.setFont(font);
  creditEight.setString("Sky Tower - Kirby’s Return to Dream Land");
  creditEight.setCharacterSize(13);
  creditEight.setPosition(creditSeven.getPosition() + sf::Vector2f(0.f, 30.f));
  _Text.push_back(creditEight);

  sf::Text creditNine;
  creditNine.setFont(font);
  creditNine.setString("The Raising Fighting Spirit - Naruto");
  creditNine.setCharacterSize(13);
  creditNine.setPosition(creditEight.getPosition() + sf::Vector2f(0.f, 30.f));
  _Text.push_back(creditNine);

  sf::Text creditTen;
  creditTen.setFont(font);
  creditTen.setString("Song of the Ancients - NieR: Automata");
  creditTen.setCharacterSize(13);
  creditTen.setPosition(creditNine.getPosition() + sf::Vector2f(0.f, 30.f));
  _Text.push_back(creditTen);

  sf::Text creditEleven;
  creditEleven.setFont(font);
  creditEleven.setString("Dating Fight! - UNDERTALE");
  creditEleven.setCharacterSize(13);
  creditEleven.setPosition(creditTen.getPosition() + sf::Vector2f(0.f, 30.f));
  _Text.push_back(creditEleven);
}

void CreditsState::draw() {
  sf::RenderWindow& window = *getContext().window;

  window.setView(window.getDefaultView());
  window.draw(_BackgroundSprite);

  for (const sf::Text& text : _Text) window.draw(text);
}

bool CreditsState::update(sf::Time dt) {
  _TextEffectTime += dt;

  if (_TextEffectTime >= sf::seconds(1.f)) {
    _ShowText = !_ShowText;
    _TextEffectTime = sf::Time::Zero;
  }

  return true;
}

bool CreditsState::handleEvent(const sf::Event& event) {
  // If any key is pressed, trigger the next screen
  if (event.type == sf::Event::KeyPressed) {
    requestStackPop();
    requestStackPush(States::Menu);
  }

  return true;
}