#ifndef RC_RESOURCE
#define RC_RESOURCE

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics.hpp>
#include <cassert>
#include <map>
#include <memory>

// Resource Tables
namespace Textures {
enum ID {
  // Blue Player Animations
  BlueRunRight,
  BlueIdleRight,
  BlueRunLeft,
  BlueIdleLeft,

  // Pink Player Animations
  PinkRunRight,
  PinkIdleRight,
  PinkRunLeft,
  PinkIdleLeft,

  // Wall Textures
  PurpleWall,
  PurpleBG,

  GreenWall,
  GreenBG,

  RedWall,
  RedBG,

  OrangeWall,
  OrangeBG,

  Arrow,
  TitleScreen,
  MenuScreen,
  Controller,
  Keyboard
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

namespace Fonts {
enum ID { Main };
};  // namespace Fonts

namespace SoundEffect {
enum ID { MenuStart, ArrowRecover, ArrowFire, PlayerDeath, PlayerJump, PlayerLand, PlayerReady };
}  // namespace SoundEffect

namespace Music {
enum ID {
  MenuTheme,
  GameThemeOne,
  GameThemeTwo,
  GameThemeThree,
  GameThemeFour,
  GameThemeFive,
};
}  // namespace Music

template <typename Resource, typename Identifier>
class ResourceHolder {
 public:
  void load(Identifier, const std::string&);
  Resource& get(Identifier);
  const Resource& get(Identifier) const;

  template <typename Parameter>
  void load(Identifier id, const std::string& filename, const Parameter& secondParam);

 private:
  std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};

// Explicitly create a TextureHolder class for compilation
template class ResourceHolder<sf::Texture, Textures::ID>;
typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;

template class ResourceHolder<sf::Font, Fonts::ID>;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;

template class ResourceHolder<sf::SoundBuffer, SoundEffect::ID>;
typedef ResourceHolder<sf::SoundBuffer, SoundEffect::ID> SoundBufferHolder;

#endif