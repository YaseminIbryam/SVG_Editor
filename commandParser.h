#pragma once
#include <sstream>

class commandParser {
private:
	template<typename T>
	static bool extract(std::stringstream& ss, T& val) {
		if (ss >> val) {
			return true;
		}
		ss.clear();
		return false;
	}
	static bool isValidPath(std::string& path);

public:
	static bool isClean(std::stringstream& ss);

	static bool parsePath(std::stringstream& ss, std::string& path,const  std::string& command);

	static bool parseN(std::stringstream& ss, int& n,const std::string& command);

	static bool parseTranslate(std::stringstream& ss, double& horizontal, double& vertical, int& n, bool& hasN);
};