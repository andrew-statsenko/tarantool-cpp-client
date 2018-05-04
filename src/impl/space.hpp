#pragma once

namespace tarantool {
namespace client {

class space_impl : public api::box::space
{
public:

public:
	std::uint32_t get_index() const override
	{
		return _index;
	};

	const std::string& get_name() const override
	{
		return _name;
	};

private:
	std::uint32_t _index;
	std::string _name;

private:
	space_impl() = default;
	space_impl(std::uint32_t index, const std::string& name) :
		_index(index),
		_name(name)
	{
	};

public:
	~space_impl() = default;
	friend class spaces_impl;
};


} // client
} // tarantool
