#pragma once

#include <iostream>
#include <boost/asio.hpp>

#include "msgpack.hpp"
#include "tarantool_consts.hpp"


namespace tarantool {
namespace client {

class box_impl : public api::box
{
public:
	box_impl() :
		_io_context{},
		_socket{_io_context},
		_connected{false},
		_operational{false}
	{
		using namespace tarantool::protocol::consts;

		_tarantool_server_version.resize(greeting_server_version_len),
		_tarantool_greeting_salt.resize(greeting_server_salt_len);
	};

	void connect(std::string host, std::uint16_t port) override
	{
		boost::asio::ip::tcp::resolver resolver{_io_context};
		boost::asio::ip::tcp::resolver::query query(host, std::to_string(port));
		boost::asio::ip::tcp::resolver::iterator iter = resolver.resolve(query);
		boost::asio::ip::tcp::endpoint endpoint = *iter;

		_socket.connect(endpoint);

		read_greeting();
	};

	void disconnect() override
	{
		_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
		_socket.close();
		_connected = false;
	};

	const api::box::spaces& get_spaces() const override
	{
		return _spaces_impl;
	};

private:
	void read_greeting()
	{
		using namespace tarantool::protocol::consts;

		std::size_t readed = 0;

		readed += _socket.read_some(boost::asio::buffer(_tarantool_server_version));
		readed += _socket.read_some(boost::asio::buffer(_tarantool_greeting_salt));
		std::array<char, greeting_server_rest_len> rest;
		readed += _socket.read_some(boost::asio::buffer(rest));
		// TODO: check read length
		std::cout << "Tarantool: " << _tarantool_server_version << std::endl;
		std::cout << "Salt: " << _tarantool_greeting_salt << std::endl;
	};

private:
	spaces_impl _spaces_impl;

private:
	boost::asio::io_context _io_context;
	boost::asio::ip::tcp::socket _socket;

	bool _connected;
	bool _operational;

private:
	 std::string _tarantool_server_version;
	 std::string _tarantool_greeting_salt;
};


} // client
} // tarantool
