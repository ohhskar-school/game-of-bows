#ifndef RC_WORLD
#define RC_WORLD

// For Random
#include <cstdlib>
#include <ctime>
// SFML Modules
#include <SFML/System/NonCopyable.hpp>

// User Defined

// Entities
#include "Entities/ArrowHolder.hpp"
#include "Entities/Character.hpp"
#include "Entities/SpriteEntity.hpp"
#include "Entities/VisualArrow.hpp"
#include "Entities/Wall.hpp"

// Commands
#include "Commands/Command.hpp"
#include "Commands/CommandQueue.hpp"

// Everything Else
#include "ResourceManager.hpp"
#include "SceneNode.hpp"

class World : private sf::NonCopyable {
 public:
  // Constructors
  explicit World(sf::RenderWindow&);

  // Update and Draw Functions
  void update(sf::Time);
  void draw();

  void handleCollisions();
  bool hasWon();
  void hasWonFinder();

  // Getters
  CommandQueue& getCommandQueue();

 private:
  // Enums and Variables
  enum Layer { Background, Ground, Foreground, HUD, LayerCount };

  // World Settings
  sf::RenderWindow& _window;
  sf::View _worldView;
  sf::FloatRect _worldBounds;
  sf::Vector2f _spawnPosition1;
  sf::Vector2f _spawnPosition2;
  float _scrollSpeed;

  // Scenes
  SceneNode _sceneGraph;
  std::array<SceneNode*, LayerCount> _sceneLayers;

  // Textures
  TextureHolder _textures;
  std::array<std::array<Textures::WallSpecific, 24>, 18> _mapArray;

  Character* _player1;
  Character* _player2;

  // commands
  CommandQueue _commandQueue;

  //hasWon
  bool _hasWonDefault;
  bool& _hasWonCheck;
  unsigned int _randValue;

  void loadTextures();
  void buildScene();
};

bool matchesCategories(SceneNode::CollisionPair& colliders, Category::Type type1, Category::Type type2);

#endif