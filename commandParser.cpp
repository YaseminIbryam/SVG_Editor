#include "commandParser.h"
#include <string>
#include <iostream>

bool commandParser::isClean(std::stringstream& ss) {
	while (std::isspace(ss.peek())) {
		ss.get();
	}
	return ss.eof();
}

bool commandParser::isValidPath(std::string& path) {
	//Премахва кавичките от началото и края, ако има такива
	if (path.size() >= 2 && path.front() == '"' && path.back() == '"') {
		path.pop_back();
		path.erase(0, 1);
	}
	else if (path.front() == '"' || path.back() == '"') { // при " или несъответствие в кавичките
		std::cout << "Error! Wrong file name format!" << std::endl;
		return false;
	}
	if (!path.ends_with(".svg")) { //C++20
		std::cout << "Error! The program supports the .svg file format!" << std::endl;
		return false;
	}
	return true;
}

bool commandParser::parsePathOnly(std::stringstream& ss, std::string& path, const std::string& command) {
	if (ss >> path) {
		if (isValidPath(path)) {
			if (isClean(ss)) {
				return true;
			}
			std::cout << "Error: Too many arguments for '" << command << "'\n";
		}
	}
	else {
		std::cout << "Error: Missing file path for command '" << command << "'\n";
	}
	return false;
}


void commandParser::strToDouble(const std::string& str, double& num) {
	std::size_t charNum = 0;
	num = std::stod(str, &charNum); //stod = string to double
	if (charNum < str.size()) {
		throw std::invalid_argument("");
	}
}

void commandParser::strToInt(const std::string& str, int& n) {
	std::size_t charNum = 0;
	n = std::stoi(str, &charNum); //stoi = string to int
	if (charNum < str.size()) {
		throw std::invalid_argument("");
	}
}

bool commandParser::parseNOnly(std::stringstream& ss, int& n,const std::string& command) {
	std::string strN;
	if (ss >> strN) {
		strToInt(strN, n);
		if (isClean(ss)) {
			return true;
		}
		std::cout << "Error: Too many arguments for '" << command << "'\n";
	}
	else {
		std::cout << "Error: Missing or invalid argument for command '" << command << "' (Int expected)\n";
	}
	return false;
}


bool commandParser::parseTranslate(std::stringstream& ss, double& horizontal, double& vertical, int& n, bool& hasN) {
	bool hasVertical = false;
	bool hasHorizontal = false;
	std::string arg1 = "vertical=";
	std::string arg2 = "horizontal=";
	std::string argument;
	while (ss >> argument) {

		if (argument.starts_with(arg1)) {
			if (hasVertical) {
				std::cout << "Error: '" << arg1 << "' specified more than once!\n";
				return false;
			}
			std::string verticalstr = argument.substr(arg1.size());
			strToDouble(verticalstr, vertical);
			hasVertical = true;
		}
		else if (argument.starts_with(arg2)) {
			if (hasHorizontal) {
				std::cout << "Error: '" << arg2 << "' specified more than once!\n"; 
				return false;
			}
			std::string horizontalstr = argument.substr(arg2.size());
			strToDouble(horizontalstr, horizontal);
			hasHorizontal = true;
		}
		else {
			if (hasN) {
				std::cout << "Too many or wrong arguments!\n";
				return false;
			}
			strToInt(argument, n);
			if (n <= 0) {
				std::cout << "Error: Sequence number must be a positive integer starting from 1.\n";
				return false;
			}
			hasN = true;
		}
	}
	if (!(hasHorizontal && hasVertical)) {
		std::cout << "Error: Missing required arguments ('vertical=' and 'horizontal=').\n";
		return false;
	}
	return true;
}

bool commandParser::parseRectangleGeometry(std::stringstream& ss, double& x, double& y, double& width, double& height) {
	std::string arg1, arg2, arg3, arg4;
	if (!(ss >> arg1 && ss >> arg2 && ss >> arg3 && ss >> arg4)) {
		std::cout << "Error: A rectangle requires at least 4 double values (x, y, width, height)";
		return false;
	}
	strToDouble(arg1, x);
	strToDouble(arg2, y);
	strToDouble(arg3, width);
	strToDouble(arg4, height);
	if (width < 0 || height < 0) {
		std::cout << "Error: Width and height can't be negative numbers.\n";
		return false;
	}
	return true;
}

bool commandParser::parseCircleGeometry(std::stringstream& ss, double& cx, double& cy, double& r) {
	std::string arg1, arg2, arg3;
	if (!(ss >> arg1 && ss >> arg2 && ss >> arg3)) {
		std::cout << "Error: A circle requires at least 3 double values (cx, cy, radius)";
		return false;
	}
	strToDouble(arg1, cx);
	strToDouble(arg2, cy);
	strToDouble(arg3, r);
	if (r < 0) {
		std::cout << "Error: Radius can't be a negative number.\n";
		return false;
	}
	return true;
}

bool commandParser::parseLineGeometry(std::stringstream& ss, double& x1, double& y1, double& x2, double& y2) {
	std::string arg1, arg2, arg3, arg4;
	if (!(ss >> arg1 && ss >> arg2 && ss >> arg3 && ss >> arg4)) {
		std::cout << "Error: A line requires at least 4 double values (x1, y1, x2, y2)";
		return false;
	}
	strToDouble(arg1, x1);
	strToDouble(arg2, y1);
	strToDouble(arg3, x2);
	strToDouble(arg4, y2);
	return true;
}

bool commandParser::parseAreaStyle(std::stringstream& ss) {

}
bool commandParser::parseLinearStyle(std::stringstream& ss) {

}