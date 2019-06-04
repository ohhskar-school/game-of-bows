#include "MusicPlayer.hpp"

MusicPlayer::MusicPlayer() : _Music(), _Filenames(), _Volume(100.f) {
  _Filenames[Music::MenuTheme] = "Assets/music/Castlevania.ogg";
  _Filenames[Music::GameThemeOne] = "Assets/music/Undertale.ogg";
  _Filenames[Music::GameThemeTwo] = "Assets/music/Towerfall.ogg";
  _Filenames[Music::GameThemeThree] = "Assets/music/Naruto.ogg";
  _Filenames[Music::GameThemeFour] = "Assets/music/Nier.ogg";
  _Filenames[Music::GameThemeFive] = "Assets/music/Kirby.ogg";
}

void MusicPlayer::play(Music::ID theme) {
  std::string filename = _Filenames[theme];

  if (!_Music.openFromFile(filename)) throw std::runtime_error("Music " + filename + " could not be loaded.");

  _Music.setVolume(_Volume);
  _Music.setLoop(true);
  _Music.play();
}

void MusicPlayer::stop() { _Music.stop(); }

void MusicPlayer::setVolume(float volume) { _Volume = volume; }

void MusicPlayer::setPaused(bool paused) {
  if (paused)
    _Music.pause();
  else
    _Music.play();
}
