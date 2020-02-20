#include <string>
#include <regex>
#include <iostream>
#include <fstream>
#include "parser/node_segmenter.h"

int main()
{
	/**std::string s = "NODE[ASASA9ASA] {sadsadasa dsds} NODE[ssa]{sadsadsadsadsadsa}";
	s.erase(std::remove(s.begin(), s.end(), ' '),s.end());
	std::regex rx("NODE\\[[\\w]{1,}\\]\\{[\\w]{1,}\\}");
	//NODE\\[[\\w]{1,}\\]
	bool y = std::regex_search(s, rx);
	const std::sregex_iterator end;
	for (std::sregex_iterator itr(std::cbegin(s),std::cend(s),rx); itr != end; ++itr)
	{
		std::smatch sm = *itr;		
	}
	std::cout << "Codigo revisado";**/
	std::string s = "0,2,3.5,3.9,4,3";	
	std::regex rx("\\s*,\\s*");
	const std::sregex_iterator end;
	std::sregex_iterator sitr(std::cbegin(s), std::cend(s), rx);
	std::smatch ss = *sitr;
	for (std::sregex_iterator itr(std::cbegin(s), std::cend(s), rx); itr != end; ++itr)
	{
		std::smatch sm = *itr;
		string ss = sm.prefix();
	}
	std::cout << "Codigo revisado";

	std::ifstream test("Language.txt");
	parser::Node_Segmenter ns(test);
	ns.Segment();
}