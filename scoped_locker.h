#ifndef RESREFRESH_SCOPED_LOCKER_H_
#define RESREFRESH_SCOPED_LOCKER_H_

template <typename LockType>
class ScopedLocker {
 public:
  explicit ScopedLocker(LockType* lock)
    : m_lock(lock) {
    m_lock->Lock();
  }

  ~ScopedLocker() {
    m_lock->Unlock();
  }
 private:
  LockType* m_lock;
  ScopedLocker(const ScopedLocker* other);
  ScopedLocker& operator = (const ScopedLocker& other);
}; // class ScopedLocker

#endif  // RESREFRESH_SCOPED_LOCKER_H_
