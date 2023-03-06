#include <agda/proc.hpp>
#include <agda/view.hpp>
#include <agda/global.hpp>

static proc::error_t err;

void proc::handle_signal_interrupt(int a)
{
	if(root != nullptr)
		delete root;
	exit(0);
}

void proc::handle_error(request_t &req, proc::error_t err)
{
	if(err == proc::NO_ERROR)
		return;

	std::string temp = "";
	switch (err)
	{
	case proc::NO_ERROR:
		return;

	case proc::BAD_ARGS:
		view::print_error("Bad arguments for request: %s\n", req.to_string().c_str());
		view::print_help(request_t("HELP NEW"));
		break;

	case proc::PATH_NOT_EXIST:
		if(req.get_type() == request_t::CREATE_NODE)
			temp = req.get_args()[1];
		else
			temp = req.get_args()[0];
		view::print_error("Path %s does not exist!", temp.c_str());
		break;

	case proc::GENERAL_FAILURE:
		view::print_error("General failure: Fail to execute %s", req.to_string().c_str());
		break;

	case proc::NOT_ALREADY_IMPLEMENTED:
		view::print_error("This request is not already implemented");
		break;

	case proc::NODE_ALREADY_EXIST:
		view::print_error("Node with name %s already exist", req.get_args()[0].c_str());
		break;

	case proc::NODE_NOT_EXIST:
		view::print_info("Node at path %s do not exist", req.get_args()[0].c_str());
		break;

	case proc::CANNOT_DELETE_ROOT:
		view::print_error("Cannot delete root node!");

	default:
		view::print_error("Unknown error type. Request is %s", req.to_string().c_str());
		break;
	}
}

bool proc::handle_request(request_t &req, std::string &sreq)
{
	if(sreq == "")
		return true;
	
	switch(req.get_type())
	{
	case request_t::QUIT:
		return false;
	
	case request_t::UNKNOWN:
		view::print_error("Unknown request: '%s'", sreq.c_str());
	
	case request_t::PRINT_HELP:
		view::print_help(req);
		break;

	case request_t::PRINT_LIST:
		err = proc::request_print_list(req);
		handle_error(req, err);
		break;

	case request_t::PRINT_PATH:
		err = proc::request_print_path(req);
		handle_error(req, err);
		break;

	case request_t::PRINT_TREE:
		err = proc::request_print_tree(req);
		handle_error(req, err);
		break;

	case request_t::PRINT_NODE:
		err = proc::request_print_node(req);
		handle_error(req, err);
		break;

	case request_t::CREATE_NODE:
		err = proc::request_create_node(req);
		handle_error(req, err);
		break;

	case request_t::DELETE_NODE:
		err = proc::request_delete_node(req);
		handle_error(req, err);
		break;

	case request_t::EDIT_NODE:
		err = proc::request_edit_node(req);
		handle_error(req, err);
		break;

	case request_t::MOVE:
		err = proc::request_move(req);
		handle_error(req, err);
		break;

	case request_t::SAVE_NODE:
		err = proc::request_save_node(req);
		handle_error(req, NOT_ALREADY_IMPLEMENTED);
		break;

	case request_t::LOAD_NODE:
		err = proc::request_load_node(req);
		handle_error(req, NOT_ALREADY_IMPLEMENTED);
		break;
	}
	return true;
}