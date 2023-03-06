#include <iostream>
#include <agda/view.hpp>
#include <agda/request.hpp>

using std::cin;
using std::cout;
using std::endl;
using std::flush;

#define request(name,args,text) << REQ_COL << "  " << name << " " << ARG_COL << args << RES_COL << " | " << text << endl
#define argument(name,text) << ARG_COL << "  <" << name << ">" << RES_COL << " | " << text << endl
#define argument_comment(text) << RES_COL << "         | " << text << endl

void print_new_message()
{
	cout
	<< "Command " << REQ_COL << "NEW" << RES_COL << endl
	request ("NEW", "<name>       ", "Create a subnode with name <name>")
	request ("NEW", "<name> <path>", "Create a subnode in node at <path> with name <name>")
	<< endl
	<< "Arguments" << endl
	argument ("name", "The name of the new node")
	argument ("path", "The path of the supernode (relative or absolute)");
}

void print_delete_message()
{
	cout
	<< "Command " << REQ_COL << "DELETE" << RES_COL << endl
	request ("DELETE", "<path>", "Delete a node and all it subnodes")
	<< endl
	<< "Arguments" << endl
	argument ("path", "The path of the node (relative or absolute)");
}

void print_tree_message()
{
	cout
	<< "Command TREE" << endl
	request ("TREE", "      ", "Print the node hierarchie")
	request ("TREE", "<path>", "Print the node hierarchie from the node at <path>")
	<< endl
	<< "Arguments" << endl
	argument ("path", "The path of the node (relative or absolute");
}

void print_path_message()
{
	cout
	<< "Command PATH" << endl
	request("PATH","","Print the current node path");
}

void print_list_message()
{
	cout
	<< "Command LIST" << endl
	request("LIST", "      ", "Print the subnode of the current node")
	request("LIST", "<path>", "Print the subnode of the node at <path>")
	<< endl
	<< "Arguments" << endl
	argument("path", "The path of the node (relative or absolute)");
}

void print_help_message()
{
	cout 
	<< "Command list" << endl
	request("NEW", "<name [<path>]", "Create a node")
	request("DELETE", "<path>     ", "Delete a node (and subnodes)")
	request("MOVE", "<path>       ", "Change the current node cursor")
	request("TREE", "[<path>]     ", "Print the node hierarchie")
	request("PATH", "             ", "Print the current node path")
	request("LIST", "[<path>]     ", "Print the subnodes")
	request("QUIT", "             ", "Quit the application")
	request("HELP", "[<comm>]     ", "Print help message for a command")
	<< endl
	<< "Arguments" << endl
	argument("[..]", "The argument '...' is not needed")
	argument("name", "The name of the node")
	argument("path", "The path of the node. It can be relative")
	argument_comment("  ('example/other') or absolute ('::/example/other'")
	argument("comm", "The name of a command");

	cout << endl;
	view::print_info("No HELPER for request: SAVE [<node>]");
	view::print_info("No HELPER for request: LOAD [<node>]");
	view::print_info("No HELPER for request: EDIT [<node>]");
	cout << endl;
	view::print_info("No DETAIL for request: SAVE [<node>]");
	view::print_info("No DETAIL for request: LOAD [<node>]");
	view::print_info("No DETAIL for request: EDIT [<node>]");
	view::print_info("No DETAIL for request: MOVE <node>");
	view::print_info("No DETAIL for request: QUIT");
}

void view::print_help(const request_t &req)
{
	if(req.get_type() != request_t::PRINT_HELP)
		return;

	if(req.get_args().size() == 0)
	{
		print_help_message();
		return;
	}

	request_t argreq = request_t(req.get_args()[0]);
	if(argreq.get_type() == request_t::CREATE_NODE)
		print_new_message();

	else if(argreq.get_type() == request_t::DELETE_NODE)
		print_delete_message();

	else if(argreq.get_type() == request_t::PRINT_TREE)
		print_tree_message();

	else if(argreq.get_type() == request_t::PRINT_PATH)
		print_path_message();

	else if(argreq.get_type() == request_t::PRINT_LIST)
		print_list_message();

	else if(argreq.get_type() == request_t::PRINT_HELP)
		print_help_message();

	else
		print_error("Unknown request: %s", req.get_args()[0].c_str());
}