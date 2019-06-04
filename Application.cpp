#include "Application.hpp"
#include "States/GameState.hpp"
#include "States/MenuState.hpp"
#include "States/State.hpp"
#include "States/StateIdentifiers.hpp"
#include "States/TitleState.hpp"
#include "States/ControlsState.hpp"
#include "States/AboutState.hpp"
#include "States/CreditsState.hpp"
#include "States/ContinueState.hpp"
#include "Utilities/Utilities.hpp"

const sf::Time Application::TimePerFrame = sf::seconds(1.f / 60.f);

Application::Application()
    : _Window(sf::VideoMode(768, 576), "States", sf::Style::Close),
      _Textures(),
      _Fonts(),
      _Player(),
      _StateStack(State::Context(_Window, _Textures, _Fonts, _Player)),
      _StatisticsText(),
      _StatisticsUpdateTime(),
      _StatisticsNumFrames(0) {
  _Window.setKeyRepeatEnabled(false);

  _Fonts.load(Fonts::Main, "Assets/fonts/prstartk.ttf");
  _Textures.load(Textures::TitleScreen, "Assets/background/titleBG.png");
  _Textures.load(Textures::MenuScreen, "Assets/background/menuBG.png");
  _Textures.load(Textures::Controller, "Assets/background/controllerBG.png");
  _Textures.load(Textures::Keyboard, "Assets/background/keyboardBG.png");

  _StatisticsText.setFont(_Fonts.get(Fonts::Main));
  _StatisticsText.setPosition(5.f, 5.f);
  _StatisticsText.setCharacterSize(10u);

  registerStates();
  _StateStack.pushState(States::Title);
}

void Application::run() {
  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;

  while (_Window.isOpen()) {
    sf::Time dt = clock.restart();
    timeSinceLastUpdate += dt;
    while (timeSinceLastUpdate > TimePerFrame) {
      timeSinceLastUpdate -= TimePerFrame;

      processInput();
      update(TimePerFrame);

      // Check inside this loop, because stack might be empty before update() call
      if (_StateStack.isEmpty()) _Window.close();
    }

    updateStatistics(dt);
    render();
  }
}

void Application::processInput() {
  sf::Event event;
  while (_Window.pollEvent(event)) {
    _StateStack.handleEvent(event);

    if (event.type == sf::Event::Closed) _Window.close();
  }
}

void Application::update(sf::Time dt) { _StateStack.update(dt); }

void Application::render() {
  _Window.clear();

  _StateStack.draw();

  _Window.setView(_Window.getDefaultView());
  _Window.draw(_StatisticsText);

  _Window.display();
}

void Application::updateStatistics(sf::Time dt) {
  _StatisticsUpdateTime += dt;
  _StatisticsNumFrames += 1;
  if (_StatisticsUpdateTime >= sf::seconds(1.0f)) {
    _StatisticsUpdateTime -= sf::seconds(1.0f);
    _StatisticsNumFrames = 0;
  }
}

void Application::registerStates() {
  _StateStack.registerState<TitleState>(States::Title);
  _StateStack.registerState<MenuState>(States::Menu);
  _StateStack.registerState<ControlsState>(States::Controls);
  _StateStack.registerState<AboutState>(States::About);
  _StateStack.registerState<CreditsState>(States::Credits);
  _StateStack.registerState<GameState>(States::Game);
  _StateStack.registerState<ContinueState>(States::Continue);
}
