#ifndef RC_CATEGORIES
#define RC_CATEGORIES

namespace Category {
enum Type {
  None = 0,
  Scene = 1 << 0,
  Collidable = 1 << 1,
  PlayerOne = 1 << 2,
  PlayerTwo = 1 << 3,
  Arrow = 1 << 4,
  VisualArrow = 1 << 5,
  Wall = 1 << 6,
  IgnoreWallCollide = 1 << 7,
  ArrowHolder = 1 << 8,
  VisualArrowOne = 1 << 9,
  VisualArrowTwo = 1 << 10,
  Dead = 1 << 11,
  Player = PlayerOne | PlayerTwo,
  SoundEffect = 1 << 12,
};
}  // namespace Category

#endif