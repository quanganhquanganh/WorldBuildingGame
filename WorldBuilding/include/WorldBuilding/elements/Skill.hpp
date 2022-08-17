#ifndef SKILL_HPP
#define SKILL_HPP

#include <string>

namespace WorldGame {
    /**
     * @brief The Skill class
     *
     * This class is used to store the skills of the game.
     * It is used to store the skills of the player and the opponent.
     */
    class Skill {
    public:
        /**
         * @brief The SkillType enum
         *
         * Skill's type
         */
        enum class SkillType {
            Combat,
            Stealth,
            Luck,
            Null
        };

        Skill();
        Skill(const std::string& name, const std::string& description, SkillType type);
        Skill(const Skill&) noexcept = default;
        Skill& operator=(const Skill&) noexcept = default;
        Skill(Skill&&) noexcept = default;
        Skill& operator=(Skill&&) noexcept = default;
        ~Skill() = default;

        const std::string& get_name() const noexcept { return _name; }
        const std::string& get_description() const noexcept { return _description; }
        const SkillType get_type() const noexcept { return _type; }
        void put_name(const std::string& s) { _name = s; }
        void put_description(const std::string& s) { _description = s; }
        void put_type(const SkillType& s) { _type = s; }

        /**
         * @brief operator==
         *
         * Compares two skills
         *
         * @param other
         * @return true if the skills are equal
         * @return false if the skills are not equal
         */
        bool operator==(const Skill& other) const noexcept;
        /**
         * @brief operator!=
         *
         * Compares two skills
         *
         * @param other
         * @return true if the skills are not equal
         * @return false if the skills are equal
         */
        bool operator!=(const Skill& other) const noexcept;

    private:
        /**
         * @brief _name
         *
         * This is the name of the skill.
         */
        std::string _name;
        /**
         * @brief _description
         *
         * This is the description of the skill.
         */
        std::string _description;
        /**
         * @brief _uses
         *
         * This is the number of uses of the skill.
         */
        SkillType _type;
    };
}

#endif // !SKILL_HPP