#include "World.hpp"
#include <iostream>
#include "Maps/MapOne.hpp"
World::World(sf::RenderWindow& window)
    : _window(window),
      _worldView(window.getDefaultView()),
      _worldBounds(0.f, 0.f, _worldView.getSize().x, _worldView.getSize().y),
      _spawnPosition(32.f, 64.f),
      _scrollSpeed(-50.f),
      _sceneGraph(),
      _sceneLayers(),
      _textures(),
      _player(nullptr),
      _commandQueue() {
  _mapArray = mapOne;
  loadTextures();
  buildScene();
  _worldView.setCenter(_worldView.getSize().x / 2.f, _worldView.getSize().y / 2.f);
}

// Initial Setting Up
void World::loadTextures() {
  _textures.load(Textures::ID::Player, "Assets/character/player.png");
  _textures.load(Textures::ID::Background, "Assets/background/standardBG.png");
  _textures.load(Textures::ID::WallStandard, "Assets/background/standard.png");
  _textures.load(Textures::ID::Arrow, "Assets/arrow/arrow.png");
}

void World::buildScene() {
  // Create main children layers
  for (std::size_t i = 0; i < LayerCount; ++i) {
    SceneNode::NodePtr layer(new SceneNode());
    _sceneLayers[i] = layer.get();
    _sceneGraph.attachChild(std::move(layer));
  }

  // Setting Background
  sf::Texture& texture = _textures.get(Textures::Background);
  sf::IntRect textureRect(_worldBounds);
  std::unique_ptr<SpriteEntity> backgroundSprite(new SpriteEntity(texture, textureRect));
  backgroundSprite->setPosition(_worldBounds.left, _worldBounds.top);
  _sceneLayers[Background]->attachChild(std::move(backgroundSprite));

  // Adding Level
  SceneNode::NodePtr walls(new SceneNode());
  SceneNode* wallParent = walls.get();
  walls->setPosition(0.f, 0.f);
  _sceneLayers[Ground]->attachChild(std::move(walls));

  int i = 0, j = 0;
  for (auto& row : _mapArray) {
    j = 0;
    for (auto& elt : row) {
      if (elt != Textures::WallSpecific::None) {
        std::unique_ptr<Wall> wall(new Wall(Wall::Set::Standard, elt, sf::Vector2f(j * 32.f, i * 32.f), _textures));
        wallParent->attachChild(std::move(wall));
      }
      j++;
    }
    i++;
  }

  // Adding Player
  std::unique_ptr<Character> player(new Character(Character::Arch::Archer, 1, _textures));
  _player = player.get();
  _player->setPosition(_spawnPosition);
  _player->setVelocity(0.f, 0.f);
  _sceneLayers[Ground]->attachChild(std::move(player));

  sf::Texture& arrowTexture = _textures.get(Textures::Arrow);
  sf::IntRect arrowTextureRect(0.f, 0.f, 32.f, 32.f);
  std::unique_ptr<VisualArrow> arrowSprite(new VisualArrow(arrowTexture, arrowTextureRect));
  _player->attachChild(std::move(arrowSprite));
}

// Functions that update every tick
void World::draw() {
  _window.setView(_worldView);
  _window.draw(_sceneGraph);
}

void World::update(sf::Time dt) {
  while (!_commandQueue.isEmpty()) {
    _sceneGraph.onCommand(_commandQueue.pop(), dt);
  }
  handleCollisions();
  _sceneGraph.update(dt);
}

// Getters
CommandQueue& World::getCommandQueue() { return _commandQueue; }

// Collisions
bool matchesCategories(SceneNode::CollisionPair& colliders, Category::Type type1, Category::Type type2) {
  unsigned int category1 = colliders.first->getCategory();
  unsigned int category2 = colliders.second->getCategory();
  if (type1 & category1 && type2 & category2) {
    return true;
  } else if (type1 & category2 && type2 & category1) {
    std::swap(colliders.first, colliders.second);
    return true;
  } else {
    return false;
  }
}

void World::handleCollisions() {
  std::set<SceneNode::CollisionPair> collisionPairs;
  _sceneGraph.checkSceneCollision(_sceneGraph, collisionPairs);
  for (auto pair : collisionPairs) {
    std::cout << "collisions" << std::endl;
    if (matchesCategories(pair, Category::PlayerOne, Category::Wall)) {
      auto& player = static_cast<Character&>(*pair.first);
      auto& wall = static_cast<Wall&>(*pair.second);
      player.handleWallCollision(wall.getBoundRect());
    }
  }
}