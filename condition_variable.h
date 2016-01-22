#ifndef RESOURCE_REFRESH_CONDITION_VARIABLE_H_
#define RESOURCE_REFRESH_CONDITION_VARIABLE_H_

#include <pthread.h>
#include <stdint.h>

namespace resrefresh {

class Mutex;

class ConditionVariable {
 public:
  explicit ConditionVariable(Mutex* mutex);
  virtual ~ConditionVariable();

  void Signal();
  void Wait();
  bool TimedWait(int64_t timeout_in_ms);

 private:
  Mutex* m_mutex;
  pthread_cond_t m_cond;
}; // class ConditionVariable

} // namespace resrefresh

#endif // RESOURCE_REFRESH_CONDITION_VARIABLE_H_
