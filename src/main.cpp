#include <iostream>
#include <csignal>
#include <agda/node.hpp>
#include <agda/view.hpp>
#include <agda/request.hpp>
#include <agda/proc.hpp>
#include <agda/global.hpp>

int main(int argc, char const *argv[])
{
	signal(SIGINT, proc::handle_signal_interrupt);

	root = new node_t("::");
	current = root;

	while(true)
	{
		// Get request
		std::string sreq = view::get_request();
		request_t req = request_t(sreq);

		// Process request
		if(!proc::handle_request(req, sreq))
			break;
	}
	
	delete root;
	return 0;
}