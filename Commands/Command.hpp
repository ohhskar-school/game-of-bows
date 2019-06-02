#ifndef RC_COMMAND
#define RC_COMMAND

#include <SFML/System/Time.hpp>

#include <cassert>
#include <functional>
#include "../Entities/Categories.hpp"

class SceneNode;

struct Command {
  Command();
  std::function<void(SceneNode&, sf::Time)> action;
  unsigned int category;
};

template <typename GameObject, typename Function>
std::function<void(SceneNode&, sf::Time)> derivedAction(Function fn) {
  return [=](SceneNode& node, sf::Time dt) {
    assert(dynamic_cast<GameObject*>(&node) != nullptr);
    fn(static_cast<GameObject&>(node), dt);
  };
}

#endif