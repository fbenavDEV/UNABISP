#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <map>
#include <string>
#include <mutex>
#include "defs.h"

namespace protocol
{
	using std::map;
	using std::string;
	using std::mutex;

	class Dictionary
	{
	private:
		map <uint, string> _index;
		mutex _locker;
	public:
		Dictionary();
		virtual ~Dictionary();
		void Add_Word(uint id, const string& index);
		string Pick_Word(uint id) const;
		string Remove_Word(uint id);
	};
}

#endif