#pragma once

#include <agda/request.hpp>

namespace proc
{
	enum error_t 
	{
		NO_ERROR = 0,
		BAD_ARGS, PATH_NOT_EXIST, NODE_ALREADY_EXIST,
		NOT_ALREADY_IMPLEMENTED, GENERAL_FAILURE,
		NODE_NOT_EXIST, CANNOT_DELETE_ROOT
	};

	error_t request_create_node(request_t &request);
	error_t request_delete_node(request_t &request);
	error_t request_edit_node(request_t &request);
	error_t request_save_node(request_t &request);
	error_t request_load_node(request_t &request);
	error_t request_move(request_t &request);
	error_t request_print_node(request_t &request);
	error_t request_print_path(request_t &request);
	error_t request_print_list(request_t &request);
	error_t request_print_tree(request_t &request);
	bool handle_request(request_t &req, std::string &sreq);
	void handle_error(request_t &req, proc::error_t err);
	void handle_signal_interrupt(int a);
}
