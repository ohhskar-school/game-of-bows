#include "SceneNode.hpp"

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

void SceneNode::update(sf::Time dt) {
  updateCurrent(dt);
  updateChildren(dt);
}

void SceneNode::updateCurrent(sf::Time dt) {}

void SceneNode::updateChildren(sf::Time dt) {
  for (const NodePtr& child : _child) {
    child->update(dt);
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

unsigned int SceneNode::getCategory() const { return Category::Scene; }

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
