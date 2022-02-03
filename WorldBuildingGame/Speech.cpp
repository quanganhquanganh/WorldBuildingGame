#include "Speech.h"
#include "tools.hpp"

namespace WorldGame {
    Speech::Speech()
    : Card()
    {
        _type = Normal;
        _skills = std::vector<std::pair<Skill, int>>();
        _is_unique = false;
        _is_collectible = false;
    }

    Speech::Speech(std::string name, SpeechType type, std::string description, int uses, std::vector<std::pair<Skill, int>> skills)
    : Card(description)
    {
        _type = type;
        _skills = skills;
        _is_unique = false;
        _is_collectible = false;
    }

    SpeechFactory::SpeechFactory(const std::vector<std::string>& descriptions, const std::vector<std::string>& events, const std::vector<Skill>& skills)
        : _descriptions(descriptions), _events(events), _skills(skills) {
            for (auto& skill : _skills) {
                if (skill.get_type() == Skill::SkillType::Social) {
                    _social_skills.push_back(skill);
            }
        }
    }

    void SpeechFactory::operator()(Speech& speech) {
        auto rand_type = static_cast<Speech::SpeechType>(basic_random::get((int)Speech::Null - 1));
        speech.put_type(rand_type);
        speech.put_uses(basic_random::get(1, MAX_USES));

        std::vector<Skill> rand_skills;
        rand_skills.push_back(rand_element(_social_skills));
        for(int i = 0; i < basic_random::get(1, MAX_SKILLS - 1); ++i) {
            auto& s = rand_element(_skills);
            if(rand_skills[0] != s) {
                rand_skills.push_back(s);
            }
        }
        std::vector<std::pair<Skill, int>> rand_skill_percentages;
        auto curr_max_per = MAX_SKILL_PERCENTAGE;
        for(auto& skill : _skills) {
            rand_skill_percentages.push_back(std::make_pair(skill, basic_random::get(30, curr_max_per)));
            curr_max_per = curr_max_per - rand_skill_percentages.back().second;
        }
        speech.put_skills(rand_skill_percentages);
        Inspirator::CardFactory card_factory(_descriptions, _events);
        card_factory(speech);
    }

    Speech SpeechFactory::operator()() {
        Speech speech;
        (*this)(speech);
        return speech;
    }
}