#include "Skill.h"

namespace WorldGame {
    Skill::Skill()
    : _name(""), _description(""), _type(SkillType::Null)
    {}

    Skill::Skill(const std::string& name, const std::string& description, SkillType type)
    : _name(name), _description(description), _type(type)
    {}

    bool Skill::operator==(const Skill& other) const noexcept {
        return _name == other._name && _description == other._description && _type == other._type;
    }
    bool Skill::operator!=(const Skill& other) const noexcept {
        return !(*this == other);
    }
}