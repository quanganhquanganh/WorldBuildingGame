#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <vector>
#include <string>
#include "BaseCard.hpp"

namespace WorldGame {
  constexpr int MAX_USES = 10;
  constexpr int MAX_SKILLS = 3;
  constexpr int MAX_SKILL_PERCENTAGE = 100;

  class Weapon : public BaseCard {
  public:
    enum WeaponType {
        Normal,
        Secret,
        Null,
    };
    Weapon();
    Weapon(std::string name, std::string description, int uses, std::vector<std::pair<Skill, int>> skills, WeaponType type);
    ~Weapon() = default;

    WeaponType get_type() const noexcept { return _type; }
    void put_type(const WeaponType& type) { _type = type; }

    void generate();
  private:
    WeaponType _type;
  };
}

#endif // !WEAPON_HPP