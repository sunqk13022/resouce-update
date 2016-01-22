#ifndef RESREFRESH_I_UPDATE_H_
#define RESREFRESH_I_UPDATE_H_

namespace resrefresh {

class IUpdate {
 public:
  IUpdate(){}
  virtual ~IUpdate() {}

  virtual bool Update() = 0;
}; // class IUpdate

} // namespace resrefresh

#endif // RESREFRESH_I_UPDATE_H_
