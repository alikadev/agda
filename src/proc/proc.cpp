#include <agda/proc.hpp>
#include <agda/node.hpp>
#include <agda/view.hpp>
#include <agda/global.hpp>

std::string node2agda(node_t *node)
{
}

proc::error_t proc::request_save_node(request_t &request)
{
	// Check args
	if(request.get_args().size() > 1)
		return proc::BAD_ARGS;

	// Init
	node_t *node = root;
	std::string agda;
	
	// Get node
	if(request.get_args().size() == 1)
	{
		node = current->get_by_path(request.get_args()[1]);
		if(!node)
			return proc::PATH_NOT_EXIST;
	}

	// Process
	agda = node2agda(node);

	return NOT_ALREADY_IMPLEMENTED;
}

proc::error_t proc::request_load_node(request_t &request)
{
	return NOT_ALREADY_IMPLEMENTED;
}

proc::error_t proc::request_create_node(request_t &request)
{
	// Check args
	if(request.get_args().size() > 2 || request.get_args().size() == 0)
		return proc::BAD_ARGS;

	// Init
	std::string name;
	node_t *node = current;

	// Analyse request
	name = request.get_args()[0];
	
	if(request.get_args().size() == 2)
	{
		node = current->get_by_path(request.get_args()[1]);
		if(!node)
			return proc::PATH_NOT_EXIST;
	}

	// Check node already exist
	if(node->get_child(name))
		return proc::NODE_ALREADY_EXIST;

	// Process
	node->add_child(new node_t(name));

	// Check
	if(!node->get_child(name))
		return proc::GENERAL_FAILURE;

	return proc::NO_ERROR;
}

proc::error_t proc::request_delete_node(request_t &request)
{
	// Check args
	if(request.get_args().size() != 1)
		return proc::BAD_ARGS;

	// Init
	node_t *node;

	// Get node
	node = current->get_by_path(request.get_args()[0]);
	if(!node)
		return proc::PATH_NOT_EXIST;

	// Check node already exist
	if(!node)
		return proc::NODE_NOT_EXIST;

	// Check if node is root
	if(node == root)
		return proc::CANNOT_DELETE_ROOT;

	// Delete node
	delete node;

	return proc::NO_ERROR;
}

proc::error_t proc::request_print_path(request_t &request)
{
	// Check args
	if(request.get_args().size() != 0)
		return proc::BAD_ARGS;

	// Print path
	view::print_node_path(current);
	return proc::NO_ERROR;
}

proc::error_t proc::request_print_list(request_t &request)
{
	// Check args
	if(request.get_args().size() > 1)
		return proc::BAD_ARGS;

	// Init
	node_t *node = current;

	// Get node
	if(request.get_args().size() == 1)
	{
		node = current->get_by_path(request.get_args()[0]);
		if(!node)
			return proc::PATH_NOT_EXIST;
	}

	// Process
	view::print_node_list(node);

	return proc::NO_ERROR;
}

proc::error_t proc::request_move(request_t &request)
{
	// Check args
	if(request.get_args().size() != 1)
		return BAD_ARGS;

	// Init
	node_t *node;

	// Process
	node = current->get_by_path(request.get_args()[0]);

	// Check
	if(!node)
		return PATH_NOT_EXIST;
	current = node;
	
	return proc::NO_ERROR;
}

proc::error_t proc::request_print_tree(request_t &request)
{
	// Check args
	if(request.get_args().size() > 1)
		return proc::BAD_ARGS;

	// Init
	node_t *node = current;

	// Get node 
	if(request.get_args().size() == 1)
	{
		node = current->get_by_path(request.get_args()[0]);
		if(!node)
			return proc::PATH_NOT_EXIST;
	}

	// Process
	view::print_node_tree(node);

	return proc::NO_ERROR;
}

proc::error_t proc::request_edit_node(request_t &request)
{
	// Check args
	if(request.get_args().size() > 1)
		return proc::BAD_ARGS;

	// Init
	node_t *node = current;
	std::string text;

	// Get node 
	if(request.get_args().size() == 1)
	{
		node = current->get_by_path(request.get_args()[0]);
		if(!node)
			return proc::PATH_NOT_EXIST;
	}

	// Process
	text = view::get_string();
	node->set_data(text);

	return NO_ERROR;
}

proc::error_t proc::request_print_node(request_t &request)
{
	// Check args
	if(request.get_args().size() > 1)
		return proc::BAD_ARGS;

	// Init
	node_t *node = current;

	// Get node 
	if(request.get_args().size() == 1)
	{
		node = current->get_by_path(request.get_args()[0]);
		if(!node)
			return proc::PATH_NOT_EXIST;
	}

	view::print_node_content(node);

	return NO_ERROR;
}
