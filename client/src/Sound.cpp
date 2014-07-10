#include "Sound.hpp"
#include "Exception.hpp"

Sound::Sound()
{
  _enabled = true;
  try
    {
      if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
	throw (Exception("Mix_OpenAudio()"));
      Mix_AllocateChannels(128);
      // _musicBox["intro"] = Mix_LoadMUS("./assets/sounds/intro.ogg");
      //      _musicBox["menu"] = Mix_LoadMUS("./assets/sounds/menu.ogg");
      // _musicBox["game"] = Mix_LoadMUS("./assets/sounds/game.ogg");
      // _soundBox["box"] = Mix_LoadWAV("./assets/sounds/chest.wav");
      // _soundBox["creeper"] = Mix_LoadWAV("./assets/sounds/creeper.wav");
      // _soundBox["eat"] = Mix_LoadWAV("./assets/sounds/eat.wav");
      // _soundBox["explosion"] = Mix_LoadWAV("./assets/sounds/explosion.wav");
      // _soundBox["fuse"] = Mix_LoadWAV("./assets/sounds/fuse.wav");
      // _soundBox["hurt"] = Mix_LoadWAV("./assets/sounds/hurt.wav");
      // _soundBox["pop"] = Mix_LoadWAV("./assets/sounds/pop.wav");
      // _soundBox["orb"] = Mix_LoadWAV("./assets/sounds/orb.wav");
      // _soundBox["click"] = Mix_LoadWAV("./assets/sounds/click.wav");
      // _soundBox["getbomb"] = Mix_LoadWAV("./assets/sounds/getbomb.wav");
      // _soundBox["burp"] = Mix_LoadWAV("./assets/sounds/burp.wav");
      // _soundBox["chickenhurt"] = Mix_LoadWAV("./assets/sounds/chickenhurt.wav");
      // _soundBox["chickenspawn"] = Mix_LoadWAV("./assets/sounds/chickenspawn.wav");
      // _soundBox["endgame"] = Mix_LoadWAV("./assets/sounds/endgame.wav");
      for (std::map<std::string, Mix_Chunk *>::iterator it = _soundBox.begin(); it != _soundBox.end(); ++it)
	if (it->second != NULL)
	  Mix_VolumeChunk(it->second, 32);
    }
  catch (const Exception &e)
    {
      std::cerr << e.what() << std::endl;
      _musicBox["intro"] = NULL;
      _musicBox["menu"] = NULL;
      // _musicBox["game"] = NULL;
      // _soundBox["box"] = NULL;
      // _soundBox["creeper"] = NULL;
      // _soundBox["eat"] = NULL;
      // _soundBox["explosion"] = NULL;
      // _soundBox["fuse"] = NULL;
      // _soundBox["hurt"] = NULL;
      // _soundBox["pop"] = NULL;
      // _soundBox["orb"] = NULL;
      // _soundBox["click"] = NULL;
      // _soundBox["getbomb"] = NULL;
      // _soundBox["burp"] = NULL;
      // _soundBox["chickenhurt"] = NULL;
      // _soundBox["chickenspawn"] = NULL;
      // _soundBox["endgame"] = NULL;
    }
}

Sound::~Sound()
{
  for (std::map<std::string, Mix_Music *>::iterator it = _musicBox.begin(); it != _musicBox.end(); ++it)
    if (it->second != NULL)
      Mix_FreeMusic(it->second);
  for (std::map<std::string, Mix_Chunk *>::iterator it = _soundBox.begin(); it != _soundBox.end(); ++it)
    if (it->second != NULL)
      Mix_FreeChunk(it->second);
  Mix_AllocateChannels(0);
  Mix_Quit();
}

void	Sound::toggle()
{
  int	volume;

  if (_enabled == true)
    {
      volume = 0;
      Mix_VolumeMusic(0);
      _enabled = false;
    }
  else
    {
      volume = 32;
      Mix_VolumeMusic(128);
      _enabled = true;
    }
  for (std::map<std::string, Mix_Chunk *>::iterator it = _soundBox.begin(); it != _soundBox.end(); ++it)
    if (it->second != NULL)
      Mix_VolumeChunk(it->second, volume);
}

bool	Sound::play(const std::string &to_play, int type)
{
  if (type == EFFECT)
    {
      if (_soundBox.find(to_play) != _soundBox.end())
	{
	  Mix_PlayChannel(-1, _soundBox[to_play], 0);
	  return (true);
	}
    }
  else if (type == MUSIC)
    {
      if (_musicBox.find(to_play) != _musicBox.end())
	{
	  Mix_PlayMusic(_musicBox[to_play], -1);
	  return (true);
	}
    }
  return (false);
}

void    Sound::set(bool state)
{
  int	volume;

  if (state == true)
    {
      volume = 32;
      Mix_VolumeMusic(128);
      _enabled = true;
    }
  else
    {
      volume = 0;
      Mix_VolumeMusic(0);
      _enabled = false;
    }
  for (std::map<std::string, Mix_Chunk *>::iterator it = _soundBox.begin(); it != _soundBox.end(); ++it)
    if (it->second != NULL)
      Mix_VolumeChunk(it->second, volume);
}
