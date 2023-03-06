#pragma once

#include <string>
#include <vector>

#define NODE_NAME_ERROR "$:noname"

class node_t
{
public:
	node_t(const std::string name);
	~node_t();

	void add_child(node_t *node);
	void remove_child(const std::string &name);

	node_t *get_child(const std::string &name);
	node_t *get_child(const size_t idx);

	node_t *get_by_path(const std::string &path);

	node_t *get_parent()   { return parent; }
	std::string get_name() { return name; }
	std::string get_data() { return data; }
	
	void set_data(const std::string &data);

	size_t size() { return childs.size(); }

private:
	std::vector<node_t*>::iterator get_child_iterator(const std::string &name);

	std::string name;
	std::vector<node_t*> childs;
	node_t *parent;
	std::string data;
};
