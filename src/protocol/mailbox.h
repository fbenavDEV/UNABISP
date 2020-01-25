#ifndef MAILBOX_H
#define MAILBOX_H

#include <map>
#include <mutex>

#include "defs.h"
#include "pack.h"


namespace protocol
{
	using std::map;
	using std::mutex;

	class Mailbox
	{
	private:
		mutex _mailbox_locker;
		map <uint,Pack*> _received;
	public:
		Mailbox();
		void Pack_Push(Pack* pack);
		Pack* Pack_Pop();
		Pack* Pack_Pop(uint id);
		bool  Pack_Exists(uint id) const;
		bool Empty() const;
		~Mailbox();
	};

	inline bool Mailbox::Empty() const
	{
		return(this->_received.empty());
	}
}

#endif
