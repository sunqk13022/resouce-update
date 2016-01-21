#ifndef RESOURCE_REFRESH_THREAD_H_
#define RESOURCE_REFRESH_THREAD_H_

#include <pthread.h>
#include <tr1/functional>

namespace resrefresh {

class Thread {
 public:
  Thread();
  virtual ~Thread();

  bool Start(const std::tr1::function<void()>& func);
  bool Join();

 private:
  static void* StaticEntry(void* inThread);

 private:
  pthread_t handler_;
  std::tr1::function<void()> func_;
}; // class Thread

} // namespace resrefresh

#endif // RESOURCE_REFRESH_THREAD_H_
