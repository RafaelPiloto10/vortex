#include "nlohmann/json.hpp"
#include "src/common/common.h"
#include <iostream>

using json = nlohmann::json;

int main() {
  for (std::string line; std::getline(std::cin, line);) {
	if (json::accept(line)) {
		json j = json::parse(line);
		Context::Message msg;
		Context::from_json(j, msg);
		json reply;
		Context::to_json(reply, msg);
	} else {
		std::cerr << "unable to parse invalid json" << std::endl;
	}
  }
  return 0;
}
