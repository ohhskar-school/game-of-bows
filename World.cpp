#include "World.hpp"

World::World(sf::RenderWindow& window)
    : _window(window),
      _worldView(window.getDefaultView()),
      _worldBounds(0.f, 0.f, _worldView.getSize().x, _worldView.getSize().y),
      _spawnPosition(32.f, 64.f),
      _scrollSpeed(-50.f),
      _sceneGraph(),
      _sceneLayers(),
      _textures(),
      _player(nullptr) {
  loadTextures();
  buildScene();
  _worldView.setCenter(_worldView.getSize().x / 2.f, _worldBounds.height - _worldView.getSize().y / 2.f);
}

void World::loadTextures() {
  _textures.load(Textures::ID::Player, "assets/character/player.png");
  _textures.load(Textures::ID::Background, "assets/background/standardBG.png");
  _textures.load(Textures::ID::WallStandard, "assets/background/standard.png");
  _textures.load(Textures::ID::Arrow, "assets/arrow/arrow.png");
}

// ToDO
void World::buildScene() {}

void World::draw() {
  _window.setView(_worldView);
  _window.draw(_sceneGraph);
}

void World::update(sf::Time dt) {
  // while (!mCommandQueue.isEmpty()) {
  //   mSceneGraph.onCommand(mCommandQueue.pop(), dt);
  // }
  // handleCollisions();
  _sceneGraph.update(dt);
}
