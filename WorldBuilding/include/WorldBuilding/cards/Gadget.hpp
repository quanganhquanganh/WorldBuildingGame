#ifndef GADGET_HPP
#define GADGET_HPP

#include <string>
#include "BaseCard.hpp"

namespace WorldGame {
  constexpr int MAX_USES = 10;
  constexpr int MAX_TIME = 10;
  
  class Gadget : public BaseCard {
  public:
    enum GadgetType {
      Distraction,
      Teleport,
      Stun,
      Kill,
      Null,
    };
    Gadget();
    Gadget(std::string name, std::string description, int uses, GadgetType type);
    ~Gadget() = default;
    
    int get_time() const noexcept { return _time; }
    void put_time(const int& t) { _time = t; }

    void generate();
    void use_card();
    void use_card(const int& i);
  private:
    GadgetType _type;
    int _time;
  };
}

#endif // !GADGET_HPP