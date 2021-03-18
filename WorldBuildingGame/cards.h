#include <vector>
#include <cwchar>
#include <string>
#include <unordered_map>
#include <iostream>

//Inspirator namespaces declarations-------------------------------------------------------------------------------------------------------
namespace Inspirator {
	//Alias-es for easy reading------------------------------------------------------------------------------
	using std::string;
	using strVector = std::vector<std::string>;
	//-------------------------------------------------------------------------------------------------------

	class Card {
		using size_t = std::vector<string>::size_type;
		strVector des; //Descriptions
		strVector ev; //Events
		string name;
		string idea;
	public:
		Card(int a = 2, int b = 2);

		Card(const strVector& d, const strVector& e); //Card constructor,
													//using vectors of strings

		Card(const Card&) noexcept;
		Card& operator=(const Card&) noexcept;

		Card(Card&&) noexcept;
		Card& operator=(Card&&) noexcept;

		size_t des_size() const noexcept { return des.size(); }
		size_t ev_size() const noexcept { return ev.size(); }

		const strVector& get_des() const noexcept { return des; }
		const strVector& get_ev() const noexcept { return ev; }

		const string& get_name() const noexcept { return name; }
		void put_name(const string& s) { name = s; }

		const string& get_idea() const noexcept { return idea; }
		void put_idea(const string& s) { idea = s; }

		void des_add(const string&); //Add string to descriptions
		void ev_add(const string&); //Add string to events

		void refresh() { des = ev = {}; name = idea = "None"; }
	};

	class card_randomize {
		using RandFunc = std::string(*)(const std::vector<std::string>&);
	public:
		card_randomize(RandFunc, const strVector&, const strVector&);
		void operator()(Card&);
	private:
		RandFunc rand; //Function for getting a randomize string from 2 vectors
		const strVector& dL; // Description list
		const strVector& eL; // Event list
	};

	//<iostream> Operators------------------------------------------------------------------------------------------------

	std::istream& operator>>(std::istream& is, Card& card); //Input operator for Card

	std::ostream& operator<<(std::ostream& os, const Card& card); //Output operator for Card

//-------------------------------------------------------------------------------------------------------------------------------------
}