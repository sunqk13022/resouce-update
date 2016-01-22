#include "condition_variable.h"
#include "mutex.h"
#include <sys/time.h>

namespace resrefresh {

ConditionVariable::ConditionVariable(Mutex* mutex) {
  pthread_cond_init(&m_cond, NULL);
  m_mutex = mutex;
}

ConditionVariable::~ConditionVariable() {
  pthread_cond_destroy(&m_cond);
  m_mutex = NULL;
}

void ConditionVariable::Signal() {
  pthread_cond_signal(&m_cond);
}

void ConditionVariable::Wait() {
  pthread_cond_wait(&m_cond, &m_mutex->m_mutex);
}

bool ConditionVariable::TimedWait(int64_t timeout_in_ms) {
  struct timeval tv;
  gettimeofday(&tv, NULL);

  timespec ts;
  int64_t usec = tv.tv_usec + timeout_in_ms * 1000LL;
  ts.tv_sec = tv.tv_sec + usec / 1000000;
  ts.tv_nsec = (usec % 1000000) * 1000;
  pthread_cond_timedwait(&m_cond, &m_mutex->m_mutex, &ts);
  return true;
}

} // namespace resrefresh
