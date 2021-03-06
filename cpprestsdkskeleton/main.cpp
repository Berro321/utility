// cpptest2.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include "simpleServer.h"
#include <cpprest\http_listener.h>
#include <cpprest\http_client.h>

using namespace std;
using namespace web::http::experimental;

std::unique_ptr<simpleServer> server;

void on_initialize(const utility::string_t& address) {
	uri_builder uri(address);
	uri.append_path(U("simpleServer/"));

	auto addr = uri.to_uri().to_string();
	server = std::unique_ptr<simpleServer>(new simpleServer(addr));
	server->open().wait();

	ucout << utility::string_t(U("Listening for requests at : ")) << addr << endl;

	return;
}

void on_shutdown()
{
	server->close().wait();
	return;
}

int main(int argc, wchar_t *argv[])
{
	utility::string_t addre = U("http://localhost:3000");
	on_initialize(addre);
	std::cout << "Press enter to exit" << endl;

	string l;
	getline(cin, l);
	on_shutdown();
	return 0;

}
