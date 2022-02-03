#ifndef WEAPON_H
#define WEAPON_H

#include "cards.hpp"
#include "Skill.h"
#include <vector>
#include <string>

namespace WordGame {
    class Weapon : public Inspirator::Card {
    public:
        enum WeaponType {
            Melee,
            Ranged,
            Null
        };
        Weapon();
        Weapon(std::string name, WeaponType type, std::string description, int damage, std::vector<std::pair<Skill, int>> skills);
        const std::string& get_name() const noexcept { return _name; }
        const std::string& get_description() const noexcept { return idea; }
        const std::vector<std::pair<Skill, int>>& get_skills() const noexcept { return _skills; }
        const int get_damage() const noexcept { return _damage; }
        const WeaponType get_type() const noexcept { return _type; }
        void put_name(const std::string& s) { _name = s; }
        void put_description(const std::string& s) { idea = s; }
        void put_damage(const int& s) { _damage = s; }
        void put_type(const WeaponType& s) { _type = s; }
        void put_skills(const std::vector<std::pair<Skill, int>>& s) { _skills = s; };
}

#endif // !WEAPON_H