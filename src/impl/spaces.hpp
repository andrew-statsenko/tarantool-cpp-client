#pragma once

#include <map>
#include <exception>

namespace tarantool {
namespace client {

class spaces_impl : public api::box::spaces
{
public:
	const api::box::space& operator[](std::uint32_t index) const override
	{
		auto it = _space_by_index.find(index);
		if (it != _space_by_index.end())
		{
			return it->second;
		}
		throw std::runtime_error("space #" + std::to_string(index) + " not found");
	};

	const api::box::space& operator[](const std::string& name) const override
	{
		auto it = _space_by_name.find(name);
		if (it != _space_by_name.end())
		{
			return it->second;
		}
		throw std::runtime_error("space '" + name + "' not found");
	};
private:
	std::map<std::uint32_t, space_impl> _space_by_index;
	std::map<std::string, space_impl> _space_by_name;

public:
	//! Ctors
	spaces_impl(const spaces_impl&) = delete;
	spaces_impl& operator=(const spaces_impl&) = delete;
	~spaces_impl() = default;
private:
	// spaces_impl() = default;

	spaces_impl()
	{
		_space_by_index.emplace(1, space_impl(1, "tester1"));
		_space_by_name.emplace("tester1", space_impl(1, "tester1"));

		_space_by_index.emplace(2, space_impl(2, "tester2"));
		_space_by_name.emplace("tester2", space_impl(2, "tester2"));
	}

public:
	friend class box_impl;
	friend class api_impl;
};


} // client
} // tarantool
