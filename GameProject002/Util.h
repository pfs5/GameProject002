#pragma once

#include <string>
#include <iostream>

namespace Util {
	const bool DEBUG_MODE = true;

	inline void printMessage(const std::string& _s) {
		if (DEBUG_MODE)
			std::cerr << _s << std::endl;
	}
}