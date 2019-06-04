#include "SceneNode.hpp"
#include <iostream>
SceneNode::SceneNode() : _parent(nullptr){};

void SceneNode::attachChild(NodePtr child) {
  child->_parent = this;

  // Gives ownership of the child to the parent
  _child.push_back(std::move(child));
}

SceneNode::NodePtr SceneNode::detachChild(const SceneNode& node) {
  // Finds the node using the reference
  auto found = std::find_if(_child.begin(), _child.end(), [&](NodePtr& p) -> bool { return p.get() == &node; });

  // Error Checking
  assert(found != _child.end());

  // Cleanup and Detachment from the Tree
  NodePtr result = std::move(*found);
  result->_parent = nullptr;
  return result;
}

// Update Functions

void SceneNode::update(sf::Time dt, CommandQueue& commands) {
  updateCurrent(dt, commands);
  updateChildren(dt, commands);
}

void SceneNode::updateCurrent(sf::Time dt, CommandQueue& commands) {}

void SceneNode::updateChildren(sf::Time dt, CommandQueue& commands) {
  for (const NodePtr& child : _child) {
    child->update(dt, commands);
  }
}

// Draw Functions

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  // Modifies the relative transform to make it global
  states.transform *= getTransform();

  drawCurrent(target, states);

  // Iterates through the child to draw them all
  for (const NodePtr& child : _child) {
    child->draw(target, states);
  }
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {}

// Getter Funcitions

unsigned int SceneNode::getCategory() const { return Category::Scene | Category::Collidable; }

sf::FloatRect SceneNode::getBoundRect() const { return sf::FloatRect(); }

sf::Transform SceneNode::getWorldTransform() const {
  sf::Transform transform = sf::Transform::Identity;
  // Traverses from current node to parent, adds the transform of all nodes directly above the current node
  for (const SceneNode* node = this; node != nullptr; node = node->_parent)
    transform = node->getTransform() * transform;
  return transform;
}

sf::Vector2f SceneNode::getWorldPosition() const {
  // Converts the transform into positions
  return getWorldTransform() * sf::Vector2f();
}

unsigned int SceneNode::getCell() const {
  sf::Vector2f position = getWorldPosition();
  unsigned int cell = 0;
  if (position.x <= 768 / 2) {
    cell = cell | 1 << 1;
  }

  if (position.y <= 576 / 2) {
    cell = cell | 1 << 0;
  }

  return cell;
}

// Control Functions

void SceneNode::onCommand(const Command& command, sf::Time dt) {
  if ((command.category & getCategory()) == command.category) {
    command.action(*this, dt);
  }

  for (const NodePtr& child : _child) {
    child->onCommand(command, dt);
  }
}

// Collision Functions
bool collision(const SceneNode& lhs, const SceneNode& rhs) { return lhs.getBoundRect().intersects(rhs.getBoundRect()); }

void SceneNode::checkNodeCollision(SceneNode& node, unsigned int cell, unsigned int category,
                                   std::set<CollisionPair>& collisionPairs) {
  unsigned int thisCategory = this->getCategory();
  if (
      // Checks if both nodes are collidable
      (thisCategory & Category::Collidable) == Category::Collidable &&

      // Checks if one of the node is a wall and the main node ignores wall collisions
      !(((thisCategory & Category::Wall) == Category::Wall) &&
        (category & Category::IgnoreWallCollide) == Category::IgnoreWallCollide) &&

      // Checks if both nodes are arrows and if both nodes ignore wall collisions. If they ignore wall collisions, then
      // that means they are attached to a wall, they don't nteed to check if they collide with each other
      !(((thisCategory & (Category::Arrow | Category::IgnoreWallCollide)) ==
         (Category::Arrow | Category::IgnoreWallCollide)) &&
        (category & (Category::Arrow | Category::IgnoreWallCollide)) ==
            (Category::Arrow | Category::IgnoreWallCollide))) {
    // Since both objects are collidables,check if they collide and insert into the collision pair set
    if (this != &node && collision(*this, node)) {
      collisionPairs.insert(std::minmax(this, &node));
    };

    // Iterate to the next child
    for (NodePtr& child : _child) {
      child->checkNodeCollision(node, cell, category, collisionPairs);
    };
  }
}

void SceneNode::checkSceneCollision(SceneNode& sceneGraph, std::set<CollisionPair>& collisionPairs) {
  // Gets the Category of the scene
  unsigned int sceneCategory = sceneGraph.getCategory();
  unsigned int sceneCell = sceneGraph.getCell();

  // checks if the current node is a scene (i.e. it is one of the main nodes such as the root node or layer node). if it
  // is then there is no need to check for collisions as by definition nothing should collide with it

  bool checkNode = (sceneCategory & Category::Scene) == Category::Scene ? false : true;

  // Only runs the collision check on the current node and its child nodes if it is collidable. Does not run a collision
  // check if the current node is a wall as the other entities will check if they collide with the wall, lessening the
  // amount of collisions to be checked
  if ((sceneCategory & Category::Collidable) == Category::Collidable &&
      (sceneCategory & Category::Wall) != Category::Wall) {
    if (checkNode) {
      checkNodeCollision(sceneGraph, sceneCell, sceneCategory, collisionPairs);
    }

    for (NodePtr& child : sceneGraph._child) {
      checkSceneCollision(*child, collisionPairs);
    }
  }
}

// Deletion Functions
bool SceneNode::isDestroyed() const { return false; }

void SceneNode::removeArrows() {
  auto wreckfieldBegin = std::remove_if(_child.begin(), _child.end(), std::mem_fn(&SceneNode::isDestroyed));
  _child.erase(wreckfieldBegin, _child.end());
  std::for_each(_child.begin(), _child.end(), std::mem_fn(&SceneNode::removeArrows));
}

bool SceneNode::hasWon() const {
  std::cout << getCategory() << std::endl;

  if ((getCategory() & Category::Dead) == Category::Dead) {
    return true;
  } else {
    for (const NodePtr& child : _child) {
      return child->hasWon();
    }
  }
}