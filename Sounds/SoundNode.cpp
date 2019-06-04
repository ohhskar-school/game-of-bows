#include "SoundNode.hpp"
#include "SoundPlayer.hpp"

SoundNode::SoundNode(SoundPlayer& player) : SceneNode(), _Sounds(player) {}

void SoundNode::playSound(SoundEffect::ID sound, sf::Vector2f position) { _Sounds.play(sound, position); }

unsigned int SoundNode::getCategory() const { return Category::SoundEffect; }