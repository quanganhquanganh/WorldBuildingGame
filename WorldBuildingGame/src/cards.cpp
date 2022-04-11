#include <fstream>
#include "cards.hpp"
#include "tools.hpp"

namespace Inspirator {
	strvec get_list(std::istream& is, const string& identifier) {
		strvec list;
		string s;
		std::getline(is, s);
		if (s != identifier) {
			is.clear(std::ios_base::failbit);
		}
		else {
			string line;
			while (std::getline(is, line) && line != "}") {
				list.push_back(line);
			}
		}
		return list;
	}

//Card member functions implementations------------------------------------------------------------------
	
	Card::Card(const std::string& s, size_t a, size_t b)
		:n{ s },
		des{ strvec(a) }, 
		ev{ strvec(b) },
		des_sze{ a },
		ev_sze{ b }
	{}

	Card::Card(const std::string& s, const strvec& des_list, const strvec& ev_list)//vectors constructor
		:n{ s },
		des{des_list}, 
		ev{ev_list},
		des_sze{ des_list.size() },
		ev_sze{ ev_list.size() }
	{}

	void Card::des_add(const std::string& s) {
		des.push_back(s);
	}

	void Card::ev_add(const std::string& s) {
		ev.push_back(s);
	}

	CardFactory::CardFactory(const std::vector<string>& d, const std::vector<string>& e)
		: dL{ d }, eL{ e } {}
	
	void CardFactory::operator()(Card& c) {
		c.refresh();
		for (size_t i = 0; i < c.des_size(); ++i) {
			c.des_add(rand_element(dL));
		}
		for (size_t i = 0; i < c.ev_size(); ++i) {
			c.ev_add(rand_element(eL));
		}
	}

//io operators implementations-----------------------------------------------------------------

	auto get_id(std::istream& is) {
		std::string s, id;

		std::getline(is, s, ':');
		if (s != "{id") {
			is.clear(std::ios_base::failbit);
			return id;
		}
		std::getline(is, id, ';');
		return id;
	}

	auto get_str_vec(std::istream& is, std::string sig) {
		//get a str vector from is with the format of v_sig{s1;s2;s3;s4;...}
		std::vector<std::string> res;
		std::string v_sig;
		std::getline(is, v_sig, '{');
		if (!is) { return res; }
		if (v_sig != sig) {
			return res;
		}
		std::string str;
		while (getline(is, str, ';')) {
			res.push_back(str);
			if (is.peek() == '}') { break; }
		}
		char c = is.get();
        if (is && (c != '}')) {
            is.clear(std::ios_base::failbit);
            return res;
        }
        return res;
	}

	constexpr char DECK_HEAD[] = "deck";
	constexpr char CARD_HEAD[] = "card";
	constexpr char DES_HEAD[] = "des";
	constexpr char EV_HEAD[] = "ev";

	std::istream& operator>>(std::istream& is, Card& ca) {
		std::string ca_sig;
		char x = 0;
		while (isspace(x = is.get()));
		is.putback(x);

		auto id = get_id(is);
		if (!is) { return is; }
		std::getline(is, ca_sig, '{');
		if (!is) { return is; }
		if (ca_sig != CARD_HEAD) {
			is.clear(std::ios_base::failbit);
			return is;
		}
		std::vector<std::string> des = get_str_vec(is, DES_HEAD);
		char c = is.get();
		if (!is) { return is; }
		if (c != ';') {
			is.clear(std::ios_base::failbit);
			return is;
		}
		std::vector<std::string> ev = get_str_vec(is, EV_HEAD);
		c = is.get();
		if (!is) { return is; }
		if (c != ';') {
			is.clear(std::ios_base::failbit);
			return is;
		}
		std::string idea;
		std::getline(is, idea, '}');
		is >> c;
		if (!is) { return is; }
		if (c != '}') {
			is.clear(std::ios_base::failbit);
			return is;
		}
		Card buff(id, des, ev);
		buff.put_idea(idea);

		ca = std::move(buff);
		
		return is;
	}

	std::ostream& operator<<(std::ostream& os, const Card& ca) {
		auto des = ca.get_des();
		auto ev = ca.get_ev();
		os << "{id:" << ca.name() << ";" << CARD_HEAD << "{";
		os << DES_HEAD << "{";
		for (const auto& s : des) {
			os << s;
			os << ';';
		}
		os << "};" << EV_HEAD << "{";
		for (const auto& s : ev) {
			os << s;
			os << ';';
		}
		os << "};";
		return os << ca.get_idea() << "}}";
	}

	//Deck member functions implementations------------------------------------------------------------------
	Card& Deck::get_card(const string& id) { 
		auto res = cm.find(id);
		if (res == cm.end()) {
			throw std::invalid_argument("No such card in deck");
		}
		return *(res->second); 
	}
	const Card& Deck::get_card(const string& id) const { 
		auto res = cm.find(id);
		if (res == cm.end()) {
			throw std::invalid_argument("No such card in deck");
		}
		return *(res->second);  
	}
	Deck& Deck::get_deck(const string& id) { 
		auto res = dm.find(id);
		if (res == dm.end()) {
			throw std::invalid_argument("No such deck in deck");
		}
		return *(res->second); 
	}
	const Deck& Deck::get_deck(const string& id) const { 
		auto res = dm.find(id);
		if (res == dm.end()) {
			throw std::invalid_argument("No such deck in deck");
		}
		return *(res->second);
	}

	std::istream& operator>>(std::istream& is, Deck& de) {
		std::string de_sig, s;
		auto id = get_id(is);
		if (!is) return is;
		char c;
		Deck buff(id);

		std::getline(is, de_sig, '{');
		if (!is) { return is; }
		if (de_sig != DECK_HEAD) {
			is.clear(std::ios_base::failbit);
			return is;
		}
		std::getline(is, s, ':');
		if (!is) { return is; }
		if (s != "total") {
			is.clear(std::ios_base::failbit);
			return is;
		}
		
		int c_num = 0; is >> c_num;
		if (!is) { return is; }
		for (int i = 0; i < c_num; ++i) {
			auto tmp = std::shared_ptr<Card>(new Card());
			is >> c >> *tmp;
			if (!is) { return is; }
			if (c != ';') {
				is.clear(std::ios_base::failbit);
				return is;
			}
			buff.add_card(tmp->name(), std::move(tmp));
		}

		std::getline(is, s, ':');
		if (!is) { return is; }
		if (s != ";}{total") {
			is.clear(std::ios_base::failbit);
			return is;
		}
		int d_num = 0; is >> d_num;
		if (!is) { return is; }
		for (int i = 0; i < d_num; ++i) {
			auto tmp = std::shared_ptr<Deck>(new Deck());
			is >> c >> *tmp;
			if (!is) { return is; }
			if (c != ';') {
				is.clear(std::ios_base::failbit);
				return is;
			}
			buff.add_deck(tmp->name(), std::move(tmp));
		}
		std::getline(is, s, '}');
		is >> c;
		if (!is) { return is; }
		if (s != ";" && c != '}') {
			is.clear(std::ios_base::failbit);
			return is;
		}
		de = std::move(buff);

		return is;
	}
	
	std::ostream& operator<<(std::ostream& os, const Deck& de) {
		const auto& cm = de.cards_map();
		const auto& dm = de.decks_map();
		os << "{id:" << de.name() << ";" << DECK_HEAD << "{total:" << cm.size() << ";";
		for (const auto& c : cm)
			os << *(c.second) << ";";
		os << "}" << "{total:" << dm.size() << ";";
		for (const auto& d : dm)
			os << *(d.second) << ";";

		return os << "}}";
	}
}
