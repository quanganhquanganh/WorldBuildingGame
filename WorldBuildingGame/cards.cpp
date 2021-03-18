#include <fstream>
#include "cards.h"

namespace Inspirator {
	strVector get_list(std::istream& is, const string& identifier) {
		strVector list;
		string s;
		char c = 0;
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
	
	Card::Card(int a, int b)
		:des{ strVector(a) }, 
		ev{ strVector(b) }
	{}

	Card::Card(const strVector& des_list, const strVector& ev_list)//vectors constructor
		:des{des_list}, 
		ev{ev_list}
	{}

	Card::Card(const Card& c) noexcept
		:des{ c.get_des() },
		ev{ c.get_ev() },
		name{ c.get_name() },
		idea{ c.get_idea() } {}

	Card& Card::operator=(const Card& c) noexcept {
		des = c.get_des();
		ev = c.get_ev();
		name = c.get_name();
		idea = c.get_idea();
	}

	Card::Card(Card&& c) noexcept
		:des{ std::move(c.des) },
		ev{ std::move(c.ev) },
		name{ std::move(c.name) },
		idea{ std::move(c.idea) } {}

	Card& Card::operator=(Card&& c) noexcept {
		des = std::move(c.des);
		ev = std::move(c.ev);
		name = std::move(c.name);
		idea = std::move(c.idea);
	}

	void Card::des_add(const std::string& s) {
		des.push_back(s);
	}

	void Card::ev_add(const std::string& s) {
		ev.push_back(s);
	}


	card_randomize::card_randomize(RandFunc r, const strVector& d, const strVector& e)
		:rand{ r }, dL{ d }, eL{ e } {}

	void card_randomize::operator()(Card& c) {
		c.refresh();
		for (size_t i = 0; i < c.des_size(); ++i) {
			c.des_add(rand(dL));
		}
		for (size_t i = 0; i < c.ev_size(); ++i) {
			c.ev_add(rand(eL));
		}
	}

//ios operators implementations-----------------------------------------------------------------

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
		is.get();
		return res;
	}

	constexpr char CARD_ID[] = "card";
	constexpr char DES_ID[] = "des";
	constexpr char EV_ID[] = "ev";

	std::istream& operator>>(std::istream& is, Card& ca) {
		std::string ca_sig;
		char x = 0;
		while (isspace(x = is.get()));
		is.putback(x);

		std::getline(is, ca_sig, '{');
		if (!is) { return is; }
		if (ca_sig != "card") {
			is.clear(std::ios_base::failbit);
			return is;
		}
		std::vector<std::string> des = get_str_vec(is, "des");
		char c = is.get();
		if (!is) { return is; }
		if (c != ';') {
			is.clear(std::ios_base::failbit);
			return is;
		}
		std::vector<std::string> ev = get_str_vec(is, "ev");
		c = is.get();
		if (!is) { return is; }
		if (c != ';') {
			is.clear(std::ios_base::failbit);
			return is;
		}
		std::string idea;
		std::getline(is, idea, '}');
		if (!is) { return is; }
		Card buff(des, ev);
		buff.put_idea(idea);

		ca = std::move(buff);

		return is;
	}

	std::ostream& operator<<(std::ostream& os, const Card& ca) {
		auto des = ca.get_des();
		auto ev = ca.get_ev();
		os << CARD_ID << "{";
		os << DES_ID << "{";
		for (const auto& s : des) {
			os << s;
			os << ';';
		}
		os << "};" << EV_ID << "{";
		for (const auto& s : ev) {
			os << s;
			os << ';';
		}
		os << "};";
		return os << ca.get_idea() << '}';
	}
}