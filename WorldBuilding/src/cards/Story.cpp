#include "Story.hpp"

using namespace WorldGame;

Story::Story() : BaseCard() {}

Story::Story(std::string name, std::string description, int uses, std::vector<std::pair<Skill, int>> skills)
  : BaseCard(name, description, uses, skills) {}