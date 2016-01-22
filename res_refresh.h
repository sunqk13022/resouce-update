#ifndef RESOURCE_REFRESH_RES_REFRESH_H_
#define RESOURCE_REFRESH_RES_REFRESH_H_

#include "thread.h"
#include "event.h"
#include "i_update.h"

namespace resrefresh {

template <typename UpdateType>
class ResRefresh {

 enum { BUFFSIZE = 2 };

 public:
  ResRefresh();
  ~ResRefresh();

  void StartUpdate();

  void set_time_interval(uint64_t time_interval) {
    time_interval_ = time_interval;
  }

  bool GetValue(UpdateType** pValue);

 private:
  void UpdateInternal();
  void Update();

 private:
  UpdateType buff_[BUFFSIZE];
  Thread* thread_;
  int64_t time_interval_;
  int cur_index_;
  volatile bool thread_exit_;
  AutoResetEvent time_event_;
}; // class ResRefresh

template <typename UpdateType>
ResRefresh<UpdateType>::ResRefresh()
  : thread_(NULL),
    time_interval_(60),
    cur_index_(-1),
    thread_exit_(false) {
}

template <typename UpdateType>
ResRefresh<UpdateType>::~ResRefresh() {
  if (thread_ != NULL) {
    thread_exit_ = true;
    time_event_.Set();
    thread_->Join();
    delete thread_;
    thread_ = NULL;
  }
}

template <typename UpdateType>
void ResRefresh<UpdateType>::UpdateInternal() {
  int index = (cur_index_ + 1) % BUFFSIZE;
  if (buff_[index].Update()) {
    cur_index_ = index;
  }
}

template <typename UpdateType>
bool ResRefresh<UpdateType>::GetValue(UpdateType** pValue) {
  if (cur_index_ < 0) {
    return false;
  }
  *pValue = &buff_[cur_index_];
  return true;
}

template <typename UpdateType>
void ResRefresh<UpdateType>::StartUpdate() {
  UpdateInternal();
  thread_ = new Thread();
  thread_->Start(std::tr1::bind(&ResRefresh::Update, this));
}

template <typename UpdateType>
void ResRefresh<UpdateType>::Update() {
  while(!thread_exit_) {
    time_event_.TimedWait(time_interval_*1000);
    UpdateInternal();
  }
}
} // namespace resrefresh

#endif // RESOURCE_REFRESH_RES_REFRESH_H_
