#pragma once

#include <string>
#include <vector>
#include <map>

class request_t
{
public:
	enum type
	{
		UNKNOWN, QUIT,
		CREATE_NODE, DELETE_NODE, EDIT_NODE,
		MOVE, SAVE_NODE, LOAD_NODE,
		PRINT_NODE, PRINT_TREE, PRINT_PATH, 
		PRINT_LIST, PRINT_HELP
	};

	request_t(const std::string &request);
	~request_t();

	bool is_valid() const ;
	request_t::type get_type() const { return type; }
	std::vector<std::string> get_args() const { return args; }

	std::string to_string() const;

private:
	request_t::type type;
	std::vector<std::string> args;
};