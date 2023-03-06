#pragma once

#include <string>
#include <agda/node.hpp>
#include <agda/request.hpp>

#define ERROR_COLOR "\e[31m"
#define INFO_COLOR "\e[34m"
#define RESET_COLOR "\e[0m"

#define ERROR_MESSAGE "\e[1;31mError: " RESET_COLOR
#define INFO_MESSAGE "\e[1;34mInfo: " RESET_COLOR

#define REQ_COL "\e[1;34m"
#define ARG_COL "\e[0;32m"
#define RES_COL "\e[0m"

namespace view
{
	void print_error(const char *format, ...);
	void print_info(const char *format, ...);
	void print_node_tree(node_t *node, int level = 0);
	void print_node_path(node_t *node);
	void print_node_list(node_t *node);
	void print_help(const request_t &request = request_t{""});
	void print_node_content(node_t *node);
	
	std::string get_request(const std::string &req = "");
	std::string get_string(void);
}
