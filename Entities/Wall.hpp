#ifndef RC_WALL
#define RC_WALL

#include "../ResourceManager.hpp"
#include "SpriteEntity.hpp"

class Wall : public SpriteEntity {
 public:
  enum Set { Standard };
  explicit Wall(Set spriteSet, Textures::WallSpecific& tile, sf::Vector2f position, const TextureHolder& textures);

  // Draws
  void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

  // For Collision
  unsigned int getCategory() const;
  virtual sf::FloatRect getBoundRect() const;
  unsigned int getCell() const;

 private:
   sf::Sprite _sprite;
  sf::Vector2f _position;

  Textures::ID getSpriteSheet(Wall::Set);
  sf::IntRect getSpriteBounds(Textures::WallSpecific&);
};
#endif