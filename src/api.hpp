#pragma once

#include <string>
#include <tuple>

namespace tarantool {
namespace client {
namespace api {

class box
{
public:
	/* \brief Connect to the tarantool server
	 * @param host, tarantool server host
	 * @param port, port which the tarantool server listening
	*/
    virtual void connect(std::string host, std::uint16_t port) = 0;

	/* \brief Disconnect from the tarantool server */
    virtual void disconnect() = 0;

	/* \brief Get user spaces collection
	 * @return spaces, collection wich can be indexed by number or space name
	 */
	class spaces;
	virtual const spaces& get_spaces() const = 0;

	class space;
	class spaces
	{
	public:
		/* \brief Get space object by index
		 * @param index, space index
		 * @return space, space object
		 */
		virtual const box::space& operator[](std::uint32_t index) const = 0;

		/* \brief Get space object by name
		 * @param name, name of the space
		 * @return space, space object
		 */
		virtual const box::space& operator[](const std::string& name) const = 0;

	public:
		virtual ~spaces() = default;
	};

	class space
	{
	public:
		/* \brief Get the space index
		 * @return index of the space
		 */
		virtual std::uint32_t get_index() const = 0;

		/* \brief Get the space name
		 * @return name of the space
		 */
		virtual const std::string& get_name() const = 0;


		/* Operations with tarantool spaces */

		/**
		 * \brief Execute SELECT request for single tuple
		 * @param keys, primary keys of the tuple
		 * @return single tuple with type of  ResultType
		 */
		template <typename ResultType, typename... Keys>
		ResultType get(Keys&&... keys)  const
		{
			std::tuple<const Keys...> pk(std::forward<Keys>(keys)...);
			/*
			std::cout << "key #0: " << std::get<0>(pk) << std::endl;
			std::cout << "key #1: " << std::get<1>(pk) << std::endl;
			std::cout << "key #2: " << std::get<2>(pk) << std::endl;
			std::cout << "key #3: " << std::get<3>(pk) << std::endl;
			std::cout << "key #4: " << std::get<4>(pk) << std::endl;

			ResultType  ret;
			std::get<0>(ret) = 10;
			std::get<1>(ret) = 20;
			return ret;
			*/
		};

	public:
		virtual ~space() = default;
	};

public:
	virtual ~box() = default;
};

} // api
} // client
} // tarantool

#include "impl/space.hpp"
#include "impl/spaces.hpp"
#include "impl/box.hpp"
