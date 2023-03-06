#include <agda/request.hpp>
#include <algorithm>

char *get_next_token(std::string *tok, const char *ptr)
{
	// Init
	if(!tok || !ptr)
		return NULL;
	*tok = "";

	// Skip spaces
	while(*ptr && isspace(*ptr))
		ptr++;

	// Read token
	while(*ptr && !isspace(*ptr))
	{
		*tok += *ptr;
		ptr++;
	}

	return (char *)ptr;
}

request_t::request_t(const std::string &request)
{
	const char *cReq = request.c_str();
	std::string temp;

	// Get request type
	cReq = get_next_token(&temp, cReq);
	std::transform(temp.begin(), temp.end(),temp.begin(), ::toupper);
	if (temp == "NEW")
		type = CREATE_NODE;
	else if (temp == "DELETE")
		type = DELETE_NODE;
	else if (temp == "EDIT")
		type = EDIT_NODE;
	else if (temp == "SAVE")
		type = SAVE_NODE;
	else if (temp == "LOAD")
		type = LOAD_NODE;
	else if (temp == "TREE")
		type = PRINT_TREE;
	else if (temp == "PATH")
		type = PRINT_PATH;
	else if (temp == "LIST")
		type = PRINT_LIST;
	else if (temp == "PRINT")
		type = PRINT_NODE;
	else if (temp == "HELP")
		type = PRINT_HELP;
	else if (temp == "QUIT")
		type = QUIT;
	else if (temp == "MOVE")
		type = MOVE;
	else
		type = UNKNOWN;

	// Get args
	while(*cReq)
	{
		cReq = get_next_token(&temp, cReq);
		if(temp.size() >= 1)
			args.push_back(temp);
	}
}

request_t::~request_t()
{
}

bool request_t::is_valid() const
{
	return (type != UNKNOWN);
}

std::string request_t::to_string() const
{
	const std::string requestTypeName[] = {
		[UNKNOWN] = "UNKNOWN",
		[QUIT] = "QUIT",
		[MOVE] = "MOVE",
		[CREATE_NODE] = "CREATE_NODE",
		[DELETE_NODE] = "DELETE_NODE",
		[PRINT_HELP] = "PRINT_HELP",
		[PRINT_PATH] = "PRINT_PATH",
		[PRINT_LIST] = "PRINT_LIST",
		[PRINT_TREE] = "PRINT_TREE"
	};

	std::string output = requestTypeName[type] + " [";
	for (int i = 0; i < args.size(); ++i)
	{
		output += args[i];

		if(i != args.size()-1)
			output += ", ";
	}
	output += "]";

	return output;
}

