#include <agda/view.hpp>
#include <cstdarg>
#include <iostream>
#include <agda/request.hpp>

using std::cin;
using std::cout;
using std::endl;
using std::flush;

void view::print_error(const char *format, ...)
{
	cout << ERROR_MESSAGE << ERROR_COLOR;

	std::va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);

	cout << RESET_COLOR << endl;
}

void view::print_info(const char *format, ...)
{
	cout << INFO_MESSAGE << INFO_COLOR;

	std::va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);

	cout << RESET_COLOR << endl;
}

std::string view::get_request(const std::string &req)
{
	if(req != "")
		cout << req << endl;
	cout << ">" << flush;
	std::string input;
	std::getline(cin, input);
	return input;
}

void view::print_node_content(node_t *node)
{
	cout << node->get_data() << endl;
}

std::string view::get_string()
{
	cout << "Enter an empty new line to quit" << endl;
	std::string input;
	while(true)
	{
		std::string temp;
		std::getline(cin, temp);
		if(temp.size() == 0)
			break;
		input += temp + "\n";
	}
	return input;
}

void view::print_node_tree(node_t *node, int level)
{

	if(level == 0)
	{
		// Print node path
		print_node_path(node);

	} else {
		// Add spaces
		for (int i = 0; i < level-1; ++i)
		{
			cout << "  ";
		}

		// Print node
		cout << "- ";
		cout << node->get_name() << endl;
	}

	// Print subnodes
	for (int i = 0; i < node->size(); ++i)
	{
		print_node_tree(node->get_child(i), level+1);
	}
}

void print_node_subpath(node_t *node)
{
	// Check node exist
	if(!node)
		return;

	// Print parent node
	if(node->get_parent())
		print_node_subpath(node->get_parent());

	// Print node + new line
	cout << node->get_name() << "/";
}

void view::print_node_path(node_t *node)
{
	if(!node) return;
	
	print_node_subpath(node->get_parent());
	cout << node->get_name();
	cout << endl;
}

void view::print_node_list(node_t *node)
{
	if(!node) return;

	cout << node->get_name() << endl;
	for (int i = 0; i < node->size(); ++i)
	{
		if(i == node->size() - 1)
			cout << " └─ ";
		else
			cout << " ├─ ";
		cout << node->get_child(i)->get_name() << endl;
	}
}

