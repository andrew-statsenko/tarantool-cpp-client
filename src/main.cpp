#include <iostream>
#include <tuple>

#include "box.hpp"


int main(int argc, char* argv[])
{

	std::cout << "starting" << std::endl;

	tarantool::client::box box;

	box.connect("127.0.0.1", 3301);

	// decltype(auto) spaces = box.get_spaces();
	const tarantool::client::api::box::space& space1 = box.get_spaces()[1];
	decltype(auto) space2 = box.get_spaces()["tester2"];

	// std::cout << "space by index #1: index: " << space1.get_index() << " name: " << space1.get_name() << std::endl; 
	//std::cout << "space by name #2: index: " << space2.get_index() << " name: " << space2.get_name() << std::endl; 
	// std::tuple<int, int> ret;
	int ec;
	std::tuple<int, int> ret = space1.get<std::tuple<int, int>>( 12, "test", 3.14, std::string("string"), false);
	std::cout << "return: #0: " << std::get<0>(ret) << ", #1: " << std::get<1>(ret) << std::endl;

	std::cout << "finish" << std::endl;

}
