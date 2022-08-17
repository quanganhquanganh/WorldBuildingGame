#include "WorldBuilding/cards/BaseCard.hpp"

using namespace WorldGame;

BaseCard::BaseCard() : _name(""), _uses(0), _skills({}) {
  _card = nullptr;
}
BaseCard::BaseCard(std::string name, std::string description, int uses, std::vector<std::pair<Skill, int>> skills)
  : _name(name), _uses(uses), _skills(skills) {
  _card = std::make_shared<Inspirator::Card>(description);
  _deck.add_card(name, _card);
}

void BaseCard::generate() {
  if (_card == nullptr) {
    _card = std::make_shared<Inspirator::Card>();
  }
  _card_factory(*_card);
}

void BaseCard::put_name(const std::string& s) {
  _deck.remove_card(_name);
  _name = s;
  _deck.add_card(s, _card);
}

void BaseCard::use_card() {
  _uses--;
}

void BaseCard::use_card(const int& i) {
  _uses -= i;
}

void BaseCard::reverse_skill(const Skill& s) {
  for (auto& skill : _skills) {
    if (skill.first == s) {
      skill.second = -skill.second;
    }
  }
}
