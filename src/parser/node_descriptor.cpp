#include <regex>
#include "defs.h"
#include "node_descriptor.h"


namespace parser
{
	NodeDescriptor::NodeDescriptor(const string& text)
	{
		this->_text = text;
	}

	void NodeDescriptor::Parse_Node_Type()
	{
		if (this->_text.find("NODE["))
		{
			uint nb = (uint)this->_text.find("[");
			uint ne = (uint)this->_text.find("]");
			this->_tag = this->_text.substr((size_t)(nb+1), (size_t)(ne-nb));
			this->_text = this->_text.substr((size_t)ne, this->_text.length());
			this->_text = std::regex_replace(this->_text, std::regex("{"), "");
			this->_text = std::regex_replace(this->_text, std::regex("}"), "");
		}
	}

	void NodeDescriptor::Process_Line(const string& line)
	{
		uint ne = line.find("=");
		string prop = line.substr(0, ne);
		string data = line.substr(ne + 1, line.length());
	}

	void NodeDescriptor::Parse_Properties()
	{
		if (!this->_text.find("NODE["))
		{
			uint nb = 0;
			while (nb != std::string::npos)
			{
				nb = (uint)this->_text.find("[");
				uint ne = (uint)this->_text.find("]");
				if (nb != std::string::npos)
				{
					string line_prop = this->_text.substr((size_t)(nb + 1), (ne - nb));
					this->Process_Line(line_prop);
				}
			}
		}
	}

	void NodeDescriptor::Parse()
	{
		this->Parse_Node_Type();
		this->Parse_Properties();
	}
	
	NodeDescriptor::~NodeDescriptor()
	{
	}
}