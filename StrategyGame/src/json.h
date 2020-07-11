#pragma once
#include <iostream>

class Json {
public:
	static inline std::string Jsonify(std::string key, std::string value) {
		return " \"" + key + "\": \"" + value + "\"";
	}
	static inline std::string Jsonify(std::string key, int value) {
		return " \"" + key + "\": \"" + std::to_string(value) + "\"";
	}

};
