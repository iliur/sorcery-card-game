#ifndef _CARD_OBSERVER_H_
#define _CARD_OBSERVER_H_

class Ability;

class CardObserver {
 public:
  virtual ~CardObserver() = default;
  virtual Ability getAbility() const = 0;
  virtual int getId() const = 0;
};

#endif
