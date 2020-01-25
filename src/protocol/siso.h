#ifndef SISO_H
#define SISO_H

#include <vector>
#include "mailbox.h"
#include "pack.h"
#include "node.h"

namespace protocol
{
	class Siso : public Node
	{
	private:
		Mailbox _mailbox;
	protected:
		void Process();
		bool Mailbox_Empty() const;
		virtual Pack* Process(Pack* input) const = 0;
	public:
		Siso();
		void Pack_Push(Pack* pack);
	};

	inline bool Siso::Mailbox_Empty() const
	{
		return(this->_mailbox.Empty());
	}
}

#endif
