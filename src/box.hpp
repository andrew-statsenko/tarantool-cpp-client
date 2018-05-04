#pragma once

#include "api.hpp"
#include "impl/api.hpp"

namespace tarantool {
namespace client {

class box : public api_impl
{
public:
	box() = default;
	~box() = default;
	box(const box&) = delete;
	box& operator= (const box&) = delete;
};

} // client
} // tarantool

