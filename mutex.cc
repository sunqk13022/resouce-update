#include "mutex.h"

namespace resrefresh {

Mutex::Mutex() {
  pthread_mutexattr_t attr;
  pthread_mutexattr_init(&attr);
  pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_DEFAULT);
  pthread_mutex_init(&m_mutex, &attr);
  pthread_mutexattr_destroy(&attr);
}

Mutex::~Mutex() {
  pthread_mutex_destroy(&m_mutex);
}
void Mutex::Lock() {
  pthread_mutex_lock(&m_mutex);
  AssertLocked();
}

void Mutex::AssertLocked() const {
  assert(m_mutex.__data.__lock > 0);
}

void Mutex::Unlock() {
  AssertLocked();
  pthread_mutex_unlock(&m_mutex);
}


} // namespace resrefresh
