#ifndef RESOURCE_REFRESH_MUTEX_H_
#define RESOURCE_REFRESH_MUTEX_H_

#include <pthread.h>
#include <assert.h>

namespace resrefresh {

class ConditionVariable;

class Mutex {
  friend class ConditionVariable;
 public:
  Mutex();
  virtual ~Mutex();

  void Lock();
  void AssertLocked() const;
  void Unlock();

 private:
  pthread_mutex_t m_mutex;
}; // class Mutex

} // namespace resrefresh

#endif // RESOURCE_REFRESH_MUTEX_H_
