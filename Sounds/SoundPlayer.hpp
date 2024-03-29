#ifndef RC_SOUNDPLAYER
#define RC_SOUNDPLAYER

#include "../ResourceManager.hpp"

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Vector2.hpp>


#include <SFML/Audio/Listener.hpp>
#include <cmath>

#include <list>

class SoundPlayer : private sf::NonCopyable {
 public:
  SoundPlayer();

  void play(SoundEffect::ID effect);
  void play(SoundEffect::ID effect, sf::Vector2f position);

  void removeStoppedSounds();
  void setListenerPosition(sf::Vector2f position);
  sf::Vector2f getListenerPosition() const;

 private:
  SoundBufferHolder _SoundBuffers;
  std::list<sf::Sound> _Sounds;
};

#endif
