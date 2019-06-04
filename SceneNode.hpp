#ifndef RC_SCENENODE
#define RC_SCENENODE

// C++ Datatypes
#include <memory>
#include <set>
#include <vector>

// Misc. C++ includes
#include <cassert>

// SFML Modules
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>

// User Created
#include "Commands/Command.hpp"
#include "Entities/Categories.hpp"
#include "Commands/CommandQueue.hpp"

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable {
 public:
  // Variable Declarations and Constructor
  typedef std::unique_ptr<SceneNode> NodePtr;
  typedef std::pair<SceneNode*, SceneNode*> CollisionPair;
  SceneNode();

  // Tree Manipulating Functions
  void attachChild(NodePtr);
  NodePtr detachChild(const SceneNode& node);
  void update(sf::Time dt, CommandQueue& commands);

  // For Collision / Getters
  virtual unsigned int getCategory() const;
  virtual sf::FloatRect getBoundRect() const;
  sf::Transform getWorldTransform() const;
  sf::Vector2f getWorldPosition() const;
  unsigned int getCell() const;

  void checkNodeCollision(SceneNode& node, unsigned int cell, unsigned int category, std::set<CollisionPair>& collisionPairs);
  void checkSceneCollision(SceneNode& sceneGraph, std::set<CollisionPair>& collisionPairs);

  // For Control
  void onCommand(const Command& command, sf::Time dt);

  // For Deletion
  virtual bool isDestroyed() const;
  void removeArrows();

  bool hasWon() const;

 private:
  // Variable Declerations
  std::vector<NodePtr> _child;
  SceneNode* _parent;

  // Draw Functions
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

  // Update Functions
  virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
  void updateChildren(sf::Time dt, CommandQueue& commands);
};

bool collision(const SceneNode& lhs, const SceneNode& rhs);

#endif