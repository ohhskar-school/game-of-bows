#ifndef RC_RESOURCE
#define RC_RESOURCE

#include <SFML/Graphics.hpp>
#include <cassert>
#include <map>
#include <memory>

// Resource Tables
namespace Textures {
enum ID { Player, Background, WallStandard, Arrow, TitleScreen };
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

namespace Fonts {
enum ID {
  Main
};
}; // namespace Font

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

template class ResourceHolder<sf::Font, Fonts::ID>;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;

#endif