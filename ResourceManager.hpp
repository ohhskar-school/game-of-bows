#ifndef RC_RESOURCE
#define RC_RESOURCE

#include <SFML/Graphics.hpp>
#include <cassert>
#include <map>
#include <memory>

// Resource Tables
namespace Textures {
enum ID {
  //Blue Player Animations
  BlueRun,
  BlueIdle,
  BlueJump,
  BlueDeath,

  //Pink Player Animations
  PinkRun,
  PinkIdle,
  PinkJump,
  PinkDeath,

  //Wall Textures
  PurpleWall,
  PurpleBG,

  GreenWall,
  GreenBG,

  RedWall,
  RedBG,

  OrangeWall,
  OrangeBG,
  
  Arrow
};
enum WallSpecific {
  None,
  Air,
  Solid,
  Brick,
  Floor,
  Cracked,
  ChunkOne,
  ChunkTwo,
  ChunkThree,
  ChunkFour,
  ChunkFive,
  ChunkSix,
  ChunkSeven,
  ChunkEight,
  ChunkNine,
  ChunkTen,
  ChunkEleven,
  ChunkTwelve,
  ChunkThirteen,
  ChunkFourteen,
  ChunkFifteen,
  ChunkSixteen,
};
}  // namespace Textures

template <typename Resource, typename Identifier>
class ResourceHolder {
 public:
  void load(Identifier, const std::string&);
  Resource& get(Identifier);
  const Resource& get(Identifier) const;

 private:
  std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};

// Explicitly create a TextureHolder class for compilation
template class ResourceHolder<sf::Texture, Textures::ID>;
typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;

#endif