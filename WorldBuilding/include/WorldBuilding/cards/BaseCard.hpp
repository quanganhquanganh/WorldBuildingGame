#ifndef WORLDGAME_BASECARD_HPP
#define WORLDGAME_BASECARD_HPP

#include <string>
#include <vector>
#include "../inspirator.hpp"

namespace WorldGame {
  // Skill class foward decl
  class Skill;
  /**
   * @brief Base card class
   * This class is a base class for all inherited element classes.
   * It is used to store the name, description, uses and skills of the card.
   */
  class BaseCard {
  public:
    /**
     * @brief BaseCard constructors.
     * Sets the name of the card to "Card"
     * Sets the description of the card to "Card"
     * Sets the uses of the card to 0
     * Sets the skills of the card to be empty
     */
    BaseCard();
    BaseCard(std::string name, std::string description, int uses, std::vector<std::pair<Skill, int>> skills);

    const std::string& get_name() const noexcept { return _name; }
    const std::string& get_details() const noexcept { return _card->get_idea(); }
    const std::vector<std::string>& get_descriptions() { return _card->get_des(); }
    const std::vector<std::string>& get_events() { return _card->get_ev(); }
    const std::vector<std::pair<Skill, int>>& get_skills() const noexcept { return _skills; }
    const int get_uses() const noexcept { return _uses; }
    void put_name(const std::string& s);
    void put_details(const std::string& s) { return _card->put_idea(s); }
    void put_uses(const int& s) { _uses = s; }
    void put_skills(const std::vector<std::pair<Skill, int>>& s) { _skills = s; };
    
    virtual double get_damage();
    virtual void reverse_skill(const Skill& s);
    virtual void use_card();
    virtual void use_card(const int& i);

    virtual void generate();
    virtual ~BaseCard() = default;

  protected:
    /**
     * @brief _name
     *
     * This is the name of the card.
     */
    std::string _name;
    /**
     * @brief _uses
     * This is the number of uses of the card.
     */
    int _uses;
    /**
     * @brief _card
     * Inspirator::Card
     */
    std::shared_ptr<Inspirator::Card> _card;
    /**
     * @brief _skills
     * The list of skills and their percentages.
     */
    std::vector<std::pair<Skill, int>> _skills;
    /**
     * @brief _deck
     * Static shared pointer to the deck.
     */
    static Inspirator::Deck& _deck;
    /**
     * @brief Static card factory
     */
    static Inspirator::CardFactory& _card_factory;
  };
}

#endif //WORLDGAME_BASECARD_HPP