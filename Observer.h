#ifndef _OBSERVER_H_
#define _OBSERVER_H_

class Observer {
 public:
  virtual ~Observer() = default;
  virtual void notify(int boardX, int boardY, bool dead, int currPlayer) = 0;
};

#endif
