#include "Mutex.hpp"

Mutex::Mutex()
{
  pthread_mutex_init(&_mutex, NULL);
  _isLocked = false;
}

Mutex::~Mutex()
{
  if (_isLocked)
    unlock();
  pthread_mutex_destroy(&_mutex);
}

void		Mutex::lock()
{
  _isLocked = true;
  pthread_mutex_lock(&_mutex);
}

void		Mutex::unlock()
{
  _isLocked = false;
  pthread_mutex_unlock(&_mutex);
}

pthread_mutex_t	*Mutex::getMutexPtr()
{
  return (&_mutex);
}
