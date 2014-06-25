#ifndef _SCOPELOCK_H_
#define _SCOPELOCK_H_

template <class Lock>
class Scopelock
{
public:
  Scopelock(Lock &obj);
  ~Scopelock();

private:
  Lock	&_obj;
};

template <typename Lock>
Scopelock<Lock>::Scopelock(Lock &obj) : _obj(obj)
{
  obj.lock();
}

template <typename Lock>
Scopelock<Lock>::~Scopelock()
{
  _obj.unlock();
}

#endif /* _SCOPELOCK_H_ */
