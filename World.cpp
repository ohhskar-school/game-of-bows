#include "World.hpp"
#include <iostream>
#include "Maps/MapFour.hpp"
#include "Maps/MapOne.hpp"
#include "Maps/MapThree.hpp"
#include "Maps/MapTwo.hpp"

World::World(sf::RenderWindow& window, SoundPlayer& sounds)
    : _window(window),
      _worldView(window.getDefaultView()),
      _worldBounds(0.f, 0.f, _worldView.getSize().x, _worldView.getSize().y),
      _spawnPosition1(32.f, 64.f),
      _spawnPosition2(728.f, 64.f),
      _scrollSpeed(-50.f),
      _sceneGraph(),
      _sceneLayers(),
      _textures(),
      _sounds(sounds),
      _player1(nullptr),
      _player2(nullptr),
      _commandQueue(),
      _hasWonDefault(false),
      _hasWonCheck(_hasWonDefault) {
  srand((unsigned)time(0));
  _randValue = rand() % 4;
  switch (_randValue) {
    case 0:
      _mapArray = mapOne;
      break;
    case 1:
      _mapArray = mapTwo;
      break;
    case 2:
      _mapArray = mapThree;
      break;
    case 3:
    default:
      _mapArray = mapFour;
      break;
  }
  _randValue = rand() % 4;
  if (hasWon()) {
    std::cout << "won" << std::endl;
  }
  loadTextures();
  buildScene();
  _worldView.setCenter(_worldView.getSize().x / 2.f, _worldView.getSize().y / 2.f);
}

// Initial Setting Up
void World::loadTextures() {
  // Player Animations
  // Blue
  _textures.load(Textures::ID::BlueRunLeft, "Assets/character/BlueRunLeft.png");
  _textures.load(Textures::ID::BlueIdleLeft, "Assets/character/BlueIdleLeft.png");

  _textures.load(Textures::ID::BlueRunRight, "Assets/character/BlueRunRight.png");
  _textures.load(Textures::ID::BlueIdleRight, "Assets/character/BlueIdleRight.png");

  // Pink
  _textures.load(Textures::ID::PinkRunLeft, "Assets/character/PinkRunLeft.png");
  _textures.load(Textures::ID::PinkIdleLeft, "Assets/character/PinkIdleLeft.png");

  _textures.load(Textures::ID::PinkRunRight, "Assets/character/PinkRunRight.png");
  _textures.load(Textures::ID::PinkIdleRight, "Assets/character/PinkIdleRight.png");

  // Stage
  _textures.load(Textures::ID::PurpleWall, "Assets/background/PurpleWall.png");
  _textures.load(Textures::ID::PurpleBG, "Assets/background/PurpleBG.png");

  _textures.load(Textures::ID::GreenWall, "Assets/background/GreenWall.png");
  _textures.load(Textures::ID::GreenBG, "Assets/background/GreenBG.png");

  _textures.load(Textures::ID::RedWall, "Assets/background/RedWall.png");
  _textures.load(Textures::ID::RedBG, "Assets/background/RedBG.png");

  _textures.load(Textures::ID::OrangeWall, "Assets/background/OrangeWall.png");
  _textures.load(Textures::ID::OrangeBG, "Assets/background/OrangeBG.png");

  // Arrow
  _textures.load(Textures::ID::Arrow, "Assets/arrow/arrow.png");
}

void World::buildScene() {
  // Create main children layers
  for (std::size_t i = 0; i < LayerCount; ++i) {
    SceneNode::NodePtr layer(new SceneNode());
    _sceneLayers[i] = layer.get();
    _sceneGraph.attachChild(std::move(layer));
  }

  Textures::ID bgTexure = Textures::PurpleBG;
  Wall::Set wallSet = Wall::Set::Purple;

  switch (_randValue) {
    case 0:
      bgTexure = Textures::PurpleBG;
      wallSet = Wall::Set::Purple;
      break;
    case 1:
      bgTexure = Textures::GreenBG;
      wallSet = Wall::Set::Green;
      break;
    case 2:
      bgTexure = Textures::RedBG;
      wallSet = Wall::Set::Red;
      break;
    case 3:
    default:
      bgTexure = Textures::OrangeBG;
      wallSet = Wall::Set::Orange;
      break;
  }

  // Setting Background
  sf::Texture& texture = _textures.get(bgTexure);
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
        std::unique_ptr<Wall> wall(new Wall(wallSet, elt, sf::Vector2f(j * 32.f, i * 32.f), _textures));
        wallParent->attachChild(std::move(wall));
      }
      j++;
    }
    i++;
  }

  // Adding Player 1
  std::unique_ptr<Character> player1(new Character(Character::Arch::Archer, 1, _textures));
  _player1 = player1.get();
  _player1->setPosition(_spawnPosition1);
  _player1->setVelocity(0.f, 0.f);
  _sceneLayers[Ground]->attachChild(std::move(player1));

  sf::Texture& arrowTexture = _textures.get(Textures::Arrow);
  std::unique_ptr<VisualArrow> arrowSprite1(new VisualArrow(arrowTexture, 1));
  arrowSprite1->setPosition(-1000.f, -1000.f);
  _player1->attachChild(std::move(arrowSprite1));

  // Adding Player 2
  std::unique_ptr<Character> player2(new Character(Character::Arch::Archer, 2, _textures));
  _player2 = player2.get();
  _player2->setPosition(_spawnPosition2);
  _player2->setVelocity(0.f, 0.f);
  _sceneLayers[Ground]->attachChild(std::move(player2));

  std::unique_ptr<VisualArrow> arrowSprite2(new VisualArrow(arrowTexture, 2));
  arrowSprite2->setPosition(-1000.f, -1000.f);
  _player2->attachChild(std::move(arrowSprite2));

  // Adding Arrow Holder
  std::unique_ptr<ArrowHolder> arrow(new ArrowHolder());
  _sceneLayers[Foreground]->attachChild(std::move(arrow));
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
  hasWonFinder();
  _sceneLayers[Foreground]->removeArrows();
  _sceneGraph.update(dt, _commandQueue);
  updateSounds();
}

void World::updateSounds() {
  // Set listener's position to player position
  // _Sounds.setListenerPosition(mPlayerAircraft->getWorldPosition());

  // Remove unused sounds
  _sounds.removeStoppedSounds();
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
    // Player Collisions
    if (matchesCategories(pair, Category::Player, Category::Wall)) {
      auto& player = static_cast<Character&>(*pair.first);
      auto& wall = static_cast<Wall&>(*pair.second);
      player.handleWallCollision(wall.getBoundRect());
    }

    if (matchesCategories(pair, Category::Player, Category::Arrow)) {
      auto& player = static_cast<Character&>(*pair.first);
      auto& arrow = static_cast<Projectile&>(*pair.second);
      arrow.handlePlayerCollision();
      player.handleArrowCollision(!arrow.getCollidable());
    }

    // Arrow Collisions
    if (matchesCategories(pair, Category::Arrow, Category::Wall)) {
      auto& arrow = static_cast<Projectile&>(*pair.first);
      auto& wall = static_cast<Wall&>(*pair.second);
      arrow.handleWallCollision(wall.getBoundRect());
    }
  }
}

void World::hasWonFinder() { _sceneLayers[Ground]->hasWon(_hasWonCheck); }

bool World::hasWon() { return _hasWonCheck; }
