#ifndef INSPIRATOR_HPP
#define INSPIRATOR_HPP

#include <vector>
#include <cwchar>
#include <string>
#include <iostream>
#include <functional>
#include <memory>
#include <map>

//Inspirator namespaces declarations-------------------------------------------------------------------------------------------------------
namespace Inspirator {

	//Alias-es for easy use------------------------------------------------------------------------------------------------------------
	using std::string;
	using strvec = std::vector<std::string>;
	//-------------------------------------------------------------------------------------------------------------------------------------
	
	/* Card's interface */
	
	class Card {
		using size_t = std::vector<string>::size_type;
		strvec des; //Descriptions
		strvec ev; //Events
		string n;
		string idea;
		size_t des_sze, ev_sze = 0;
	public:
		Card(const std::string& s = "None", size_t a = 2, size_t b = 2);

		Card(const std::string& s, const strvec& d, const strvec& e); //Card constructor,
													//using vectors of strings

		Card(const Card&) noexcept = default;
		Card& operator=(const Card&) noexcept = default;

		Card(Card&&) noexcept = default;
		Card& operator=(Card&&) noexcept = default;

		~Card() = default;

		size_t des_size() const noexcept { return des_sze; }
		size_t ev_size() const noexcept { return ev_sze; }

		const strvec& get_des() const noexcept { return des; }
		const strvec& get_ev() const noexcept { return ev; }

		string name() noexcept { return n; }
		const string& name() const noexcept { return n; }
		void put_name(const string& s) { n = s; }

		const string& get_idea() const noexcept { return idea; }
		void put_idea(const string& s) { idea = s; }

		void des_add(const string&); //Add string to descriptions
		void ev_add(const string&); //Add string to events

		void refresh() { des.clear(); ev.clear(); idea = "None"; }
	};
	
	class card_randomize {
	public:
		card_randomize(const std::vector<string>&, const std::vector<string>&);
		void operator()(Card&);
	private:
		strvec dL; // Description list
		strvec eL; // Event list
	};

	//iostreams Operators--------------------------------------------------------------------------------------------------------------

	std::istream& operator>>(std::istream& is, Card& card); //Input operator for Card

	std::ostream& operator<<(std::ostream& os, const Card& card); //Output operator for Card

	//---------------------------------------------------------------------------------------------------------------------------------

	/* Deck's interface */

	class Deck {
		using CardPtr = std::shared_ptr<Card>;
		using DeckPtr = std::shared_ptr<Deck>;
		string n;
		std::map<string, CardPtr> cm;
		std::map<string, DeckPtr> dm;
	public:
		Deck(const string& s = "None")
			:n{ s } {}
		
		string name() noexcept { return n; }
		const string& name() const noexcept { return n; }
		void put_name(const string& s) { n = s; }

		Card& get_card(const string& id) { return *cm[id]; }
		const Card& get_card(const string& id) const { return *(cm.find(id)->second); }
		Deck& get_deck(const string& id) { return *dm[id]; }
		const Deck& get_deck(const string& id) const { return *(dm.find(id)->second); }
		
		const auto& cards_map() const noexcept{ return cm; }
		const auto& decks_map() const noexcept{ return dm; }
		
		auto cards_size() const noexcept { return cm.size(); }
		auto decks_size() const noexcept { return dm.size(); }
		
		void add_card(const string& id, const CardPtr& s) { cm.insert(std::make_pair(id, s)); }

		void add_card(const string& id, CardPtr&& s) { cm.insert(std::make_pair(id, std::forward<CardPtr>(s))); }
		
		void add_card(const string& id, Card* p) { cm.insert(std::make_pair(id, CardPtr(p))); }
		
		void add_deck(const string& id, const DeckPtr& s) { dm.insert(std::make_pair(id, s)); }

		void add_deck(const string& id, DeckPtr&& p) { dm.insert(std::make_pair(id, std::forward<DeckPtr>(p))); }
		
		void add_deck(const string& id, Deck* p) { dm.insert(std::make_pair(id, DeckPtr(p))); }
	};

	std::istream& operator>>(std::istream& is, Deck& deck); //Input operator for Deck

	std::ostream& operator<<(std::ostream& os, const Deck& deck); //Output operator for Deck

//-------------------------------------------------------------------------------------------------------------------------------------
}

#endif // !INSPIRATOR_HPP