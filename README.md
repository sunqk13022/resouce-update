# resouce-update
资源定期更新的一个通用的库

C++实现的，有一个后台线程定期更新资源，双buffer机制。资源可以是REDIS、FILE等等比较耗时的东东。
```c++
#include "res_refresh.h"
#include "i_update.h"
#include <string>

class TestRes: public resrefresh::IUpdate {
public:
  TestRes() {
  }

  ~TestRes() {
  }

  bool Update() {
     //这是在单独的线程中运行的
    //printf("Update=%s\n", value.c_str());
    static int i = 0;
    i++;
    if (i % 2 == 0) {
      value = "2345";
    } else {
      value = "1234";
    }   
    return true;
  }

  std::string value;
};

int main() {
  resrefresh::ResRefresh<TestRes> resourse;
  resourse.set_time_interval(1);
  TestRes* p1 = NULL;
  resourse.StartUpdate();
  for (int i = 0; i < 10; i++) {
    resourse.GetValue(&p1);
    printf("the value=%s\n", p1->value.c_str());
    sleep(1);
  }
  return 0;
}
```
