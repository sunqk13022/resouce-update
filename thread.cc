#include "thread.h"

namespace resrefresh {

Thread::Thread() {
}

Thread::~Thread() {
}

bool Thread::Start(const std::tr1::function<void()>& function) {
  func_ = function;
  int err = pthread_create(&handler_, NULL, StaticEntry, this);
  if (err != 0) {
    return false;
  }

  return true;
}

bool Thread::Join() {
  int err = pthread_join(handler_, NULL);
  if ( err != 0) {
    return false;
  }
  return true;
}

void* Thread::StaticEntry(void* param) {
  Thread* base_thread = static_cast<Thread*>(param);
  base_thread->func_();
  return 0;
}

} // namespace resrefresh
