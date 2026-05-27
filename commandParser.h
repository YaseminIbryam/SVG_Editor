#pragma once
#include <sstream>

class commandParser {
private:
	static bool isValidPath(std::string& path);

	static void strToDouble(const std::string& str, double& num);
	
	static void strToInt(const std::string& str, int& n);

	
public:
	static bool isClean(std::stringstream& ss);

	static bool parsePathOnly(std::stringstream& ss, std::string& path,const  std::string& command);

	static bool parseNOnly(std::stringstream& ss, int& n,const std::string& command);

	static bool parseTranslate(std::stringstream& ss, double& horizontal, double& vertical, int& n, bool& hasN);

	static bool parseCircleGeometry(std::stringstream& ss, double& cx, double& cy, double& r);

	static bool parseRectangleGeometry(std::stringstream& ss, double& x, double& y, double& width, double& height);

	static bool parseLineGeometry(std::stringstream& ss, double& x1, double& y1, double& x2, double& y2);

	static bool parseAreaStyle(std::stringstream& ss, std::string& fill, std::string& stroke, double& strokeWidth);

	static bool parseLinearStyle(std::stringstream& ss, std::string& stroke, double& strokeWidth);
};