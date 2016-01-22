#ifndef RESOURCE_REFRESH_EVENT_H_
#define RESOURCE_REFRESH_EVENT_H_

#include "mutex.h"
#include "condition_variable.h"

namespace resrefresh {


class AutoResetEvent {
 public:
  explicit AutoResetEvent(bool init_state = false);
  virtual ~AutoResetEvent();

  void Wait();
  bool TimedWait(int64_t timeout);
  void Set();
 private:
  Mutex m_mutex;
  ConditionVariable m_cond;
  bool m_signaled;
}; // class AutoResetEvent

} // namespace resrefresh

#endif // RESOURCE_REFRESH_EVENT_H_
