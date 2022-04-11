#ifndef SPEECH_H
#define SPEECH_H

#include "Fighter.h"
#include "cards.hpp"
#include "Skill.h"
#include <vector>
#include <string>

namespace WorldGame {
    constexpr int MAX_USES = 10;
    constexpr int MAX_SKILLS = 3;
    constexpr int MAX_SKILL_PERCENTAGE = 100;

    /**
     * @brief The Speech class
     *
     * This class is used to store the stories/speeches of the game.
     * It is used to store the speech of the player and the opponent.
     * Kinda similar to weapons in the game.
     * Inherited from Inspirator::Card
     */
    class Speech : public Inspirator::Card {
    public:
        /**
         * @brief SpeechType
         * This enum is used to store the type of speech.
         */
        enum SpeechType {
            Normal,
            Taunt,
            DeathRattle,
            BattleCry,
            Secret,
            Null,
        };
        /**
         * @brief Speech constructors.
         * Sets the name of the speech to "Speech"
         * Sets the type of the speech to SpeechType::Normal
         * Sets the description of the speech to "Speech"
         * Sets the uses of the speech to 0
         * Sets the skills of the speech to be empty
         * Sets the damage of the speech to 0
         */
        Speech();
        Speech(std::string name, SpeechType type, std::string description, int uses, std::vector<std::pair<Skill, int>> skills);

        const std::string& get_name() const noexcept { return _name; }
        const std::string& get_description() const noexcept { return idea; }
        const std::vector<std::pair<Skill, int>>& get_skills() const noexcept { return _skills; }
        const int get_uses() const noexcept { return _uses; }
        const SpeechType get_type() const noexcept { return _type; }
        void put_name(const std::string& s) { _name = s; }
        void put_description(const std::string& s) { idea = s; }
        void put_uses(const int& s) { _uses = s; }
        void put_type(const SpeechType& s) { _type = s; }
        void put_skills(const std::vector<std::pair<Skill, int>>& s) { _skills = s; };
        void add_speech(const Speech& s);

    private:
        /**
         * @brief _name
         *
         * This is the name of the speech.
         */
        std::string _name;
        /**
         * @brief _type
         * This is the type of the speech.
         */
        SpeechType _type;
        /**
         * @brief _uses
         * This is the number of uses of the speech.
         */
        int _uses;
        /**
         * @brief _skills
         * The list of skills and their percentages.
         */
        std::vector<std::pair<Skill, int>> _skills;
        /**
         * @brief _is_unique
         */
        bool _is_unique;
        /**
         * @brief _is_collectible
         */
        bool _is_collectible;
    };

    /**
     * @brief The SpeechFactory class
     * This class is used to create speeches.
     * It is used to randomly generate speeches of the player and the opponent.
    */
    class SpeechFactory {
    public:
        /**
         * @brief SpeechFactory
         * @param descriptions
         * @param events
         * @param skills
         */
        SpeechFactory(const std::vector<std::string>& descriptions, const std::vector<std::string>& events, const std::vector<Skill>& skills);
        /**
         * @brief operator ()
         * @param speech
         */
        Speech operator()();
        void operator()(Speech& speech);

    private:
        /**
         * @brief _descriptions
         * The list of descriptions
         */
        std::vector<std::string> _descriptions;
        /**
         * @brief _events
         * The list of events
         */
        std::vector<std::string> _events;
        /**
         * @brief _skills
         * The list of skills of speeches.
         */
        std::vector<Skill> _skills;
        /**
         * @brief _social_skills
         * The list of social skills of speeches.
         */
        std::vector<Skill> _social_skills;
    };

    class SpeechDeck : public Inspirator::Deck {
    private:
        using CharPtr = std::shared_ptr<Fighter>;
        using SpeechPtr = std::shared_ptr<Speech>;
        CharPtr _owner;
    public:
        /**
         * @brief SpeechDeck
         * @param owner
        */
        SpeechDeck(const CharPtr& owner);
        
        Speech& get_speech(const std::string& id) { return (Speech&) Inspirator::Deck::get_card(id); }
        const Speech& get_speech(const std::string& id) const noexcept { return (Speech&) Inspirator::Deck::get_card(id); }
        const auto& speeches_map() const noexcept { return Inspirator::Deck::cards_map(); }

        auto size() const noexcept { return Inspirator::Deck::cards_size(); }
        void add_speech(const std::string& id, const SpeechPtr& s);
		void add_speech(const std::string& id, SpeechPtr&& s);
		void add_speech(const std::string& id, Speech* p);
    };
}

#endif // !SPEECH_H