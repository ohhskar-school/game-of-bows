#ifndef RC_SCENENODE
#define RC_SCENENODE

// C++ Datatypes
#include <memory>
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
#include "Entities/Categories.hpp"

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable {
 public:
  // Variable Declarations and Constructor
  typedef std::unique_ptr<SceneNode> NodePtr;
  typedef std::pair<SceneNode*, SceneNode*> CollisionPair;
  SceneNode();

  // Tree Manipulating Functions
  void attachChild(NodePtr);
  NodePtr detachChild(const SceneNode& node);
  void update(sf::Time dt);

  // For Collision / Getters
  unsigned int getCategory() const;
  virtual sf::FloatRect getBoundRect() const;
  sf::Transform getWorldTransform() const;
  sf::Vector2f getWorldPosition() const;

 private:
  // Variable Declerations
  std::vector<NodePtr> _child;
  SceneNode* _parent;

  // Draw Functions
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

  //Update Functions
  virtual void updateCurrent(sf::Time dt);
  void updateChildren(sf::Time dt);
};

#endif