#ifndef STORY_HPP
#define STORY_HPP

#include <string>
#include "BaseCard.hpp"

namespace WorldGame {
  constexpr int MAX_USES = 999;
  constexpr int MAX_SKILLS = 3;
  constexpr int MAX_SKILL_PERCENTAGE = 100;
  
  class Story : public BaseCard {
  public:
    Story();
    Story(std::string name, std::string description, int uses, std::vector<std::pair<Skill, int>> skills);
    ~Story() = default;
  };
}

#endif // STORY_HPP