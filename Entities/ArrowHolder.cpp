#include "ArrowHolder.hpp"

unsigned int ArrowHolder::getCategory() const {
  return Category::Scene | Category::ArrowHolder | Category::Collidable;
}