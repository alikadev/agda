#include <agda/node.hpp>
#include <agda/global.hpp>

char *get_next_tok(std::string *result, const char *path)
{
	while(*path && *path != '/'){
		*result += *path;
		path++;
	}
	return (char *)path;
}

node_t::node_t(const std::string name)
{
	parent = nullptr;
	childs = std::vector<node_t*>();

	for (int i = 0; i < name.size(); ++i)
	{
		if(name[i] == '/')
		{
			this->name = NODE_NAME_ERROR;
			return;
		}
	}

	this->name = name;
}

node_t::~node_t()
{
	if(current == this)
		current = root;

	while(!childs.empty()) {
		delete *childs.begin();
	} 

	if(!parent)
		return;
	
	parent->remove_child(name);
}

void node_t::add_child(node_t *node)
{
	if(node->name != NODE_NAME_ERROR)
	{
		node->parent = this;
		childs.push_back(node);
	}
}

void node_t::remove_child(const std::string &name)
{
	std::vector<node_t*>::iterator it = get_child_iterator(name);
	if(it == childs.end())
		return;

	childs.erase(it);
}

node_t *node_t::get_child(const std::string &name)
{
	std::vector<node_t*>::iterator it = get_child_iterator(name);

	if(childs.end() == it)
		return nullptr;
	return *it;
}

node_t *node_t::get_child(const size_t idx)
{
	return childs[idx];
}

node_t *node_t::get_by_path(const std::string &path)
{
	const char *cPath = path.c_str();
	std::string item;
	node_t *child;

	// Request get root
	if (cPath[0] == ':' && cPath[1] == ':')
	{
		cPath ++;
		child = root;

	} else if (cPath[0] == '.' && cPath[1] == '.')
	{
		cPath ++;
		if(!parent)
			return nullptr;
		child = parent;

	} else {
		cPath = get_next_tok(&item, cPath);
		if(item.size() == 0)
			return nullptr;

		child = get_child(item);
	}

	if(child && *cPath && cPath[1]) {
		child = child->get_by_path(std::string(cPath+1));
		return child;
	}

	return child;
}

void node_t::set_data(const std::string &data)
{
	this->data = data;
}

std::vector<node_t*>::iterator node_t::get_child_iterator(const std::string &name)
{
	for (std::vector<node_t*>::iterator it = childs.begin(); it != childs.end(); ++it)
	{
		if((*it)->get_name() == name)
		{
			return it;
		}
	}

	return childs.end();
}
