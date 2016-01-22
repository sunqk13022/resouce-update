#include "event.h"
#include "scoped_locker.h"

namespace resrefresh {

AutoResetEvent::AutoResetEvent(bool init_state)
    : m_mutex(),
      m_cond(&m_mutex),
      m_signaled(init_state) {
}

AutoResetEvent::~AutoResetEvent() {
}

void AutoResetEvent::Wait() {
  ScopedLocker<Mutex> locker(&m_mutex);
  while(!m_signaled)
    m_cond.Wait();
  m_signaled = false;
}

bool AutoResetEvent::TimedWait(int64_t timeout) {
  ScopedLocker<Mutex> locker(&m_mutex);
  if (!m_signaled) {
    m_cond.TimedWait(timeout);
  }

  if (!m_signaled) {
    return false;
  }
  m_signaled = false;
  return true;
}

void AutoResetEvent::Set() {
  ScopedLocker<Mutex> locker(&m_mutex);
  m_signaled = true;
  m_cond.Signal();
}

} // namespace resrefresh
