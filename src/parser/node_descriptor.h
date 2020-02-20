#ifndef NODE_DESCRIPTOR_H
#define NODE_DESCRIPTOR_H

#include <string>
#include <map>
#include <vector>
#include <sstream>

using std::string;
using std::map;
using std::vector;
using std::stringstream;

namespace parser
{
	union Data
	{	
		float _numeric;
		char _alpha[4];
	};

	enum DataType
	{
		Integer = 0,
		Float = 1,
		Character = 2
	};

	struct ParsedData
	{
		DataType _dtype;
		vector<Data> _values;
	};

	class NodeDescriptor
	{
	private:
		string _tag;
		string _text;
		map<string, ParsedData> _values;
		stringstream _log;
		void Parse_Node_Type();
		void Parse_Properties();
		void Process_Line(const string& line);
	public:
		NodeDescriptor(const string& text);
		void Parse();
		~NodeDescriptor();
	};
}

#endif
