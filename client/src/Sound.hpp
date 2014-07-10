#ifndef SOUND_HPP_
# define SOUND_HPP_

# include <iostream>
# include <string>
# include <map>
# include <SDL2/SDL_mixer.h>

enum type
  {
    MUSIC,
    EFFECT
  };

class	Sound
{
public:
  Sound();
  ~Sound();
  bool	play(const std::string &, int type);
  void	toggle();
  void	set(bool state);

private:
  std::map<std::string, Mix_Music *>	_musicBox;
  std::map<std::string, Mix_Chunk *>	_soundBox;
  bool					_enabled;
};
#endif /* !SOUND_HPP */
