#pragma once

#include "box.hpp"
#include "spaces.hpp"
#include "space.hpp"

namespace tarantool {
namespace client {

class api_impl : public box_impl, public spaces_impl
{
public:
	api_impl() = default;
};


} // client
} // tarantool
