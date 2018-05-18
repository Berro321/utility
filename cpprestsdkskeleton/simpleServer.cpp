#include "stdafx.h"
#include "simpleServer.h"

using namespace std;

simpleServer::simpleServer(utility::string_t url) : m_listener(url)
{
	m_listener.support(methods::GET, std::bind(&simpleServer::handle_get, this, std::placeholders::_1));
	m_listener.support(methods::POST, std::bind(&simpleServer::handle_post, this, std::placeholders::_1));
	m_listener.support(methods::DEL, std::bind(&simpleServer::handle_delete, this, std::placeholders::_1));
	m_listener.support(methods::PUT, std::bind(&simpleServer::handle_put, this, std::placeholders::_1));
}

void simpleServer::handle_get(web::http::http_request message) {
	ucout << message.to_string() << endl << message.relative_uri().to_string() << endl;
	web::json::value obj = web::json::value::parse(U("{\"a\" : 10}"));
	message.reply(status_codes::OK, obj);
}

//Possibly use post to let server decide the stuff
void simpleServer::handle_post(web::http::http_request message) {
	ucout << message.to_string() << endl;
	web::json::value obj = web::json::value::parse(U("{\"a\" : 10}"));
	message.reply(status_codes::OK, obj); //Send back a json file
}

void simpleServer::handle_put(web::http::http_request message) {
	ucout << message.to_string() << endl;
	message.reply(status_codes::OK);
}

void simpleServer::handle_delete(web::http::http_request message) {
	ucout << message.to_string() << endl;
	message.reply(status_codes::OK);
}