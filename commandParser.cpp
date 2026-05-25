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

bool commandParser::parsePath(std::stringstream& ss, std::string& path, const std::string& command) {
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

bool commandParser::parseN(std::stringstream& ss, int& n,const std::string& command) {
	if (extract<int>(ss, n)) {
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
		try {
			if (argument.starts_with(arg1)) {
				if (hasVertical) {
					std::cout << "Error: '" << arg1 << "' specified more than once!\n";
					return false;
				}
				vertical = std::stod(argument.substr(arg1.size())); //stod = string to double
				hasVertical = true;
			}
			else if (argument.starts_with(arg2)) {
				if (hasHorizontal) {
					std::cout << "Error: '" << arg2 << "' specified more than once!\n"; 
					return false;
				}
				horizontal = std::stod(argument.substr(arg2.size())); //stod = string to double
				hasHorizontal = true;
			}
			else {
				if (hasN) {
					std::cout << "Too many or wrong arguments!\n";
					return false;
				}
				n = std::stoi(argument); //stoi = string to int
				if (n <= 0) {
					std::cout << "Error: Sequence number must be a positive integer starting from 1.\n";
					return false;
				}
				hasN = true;
				
			}
		}
		catch (...) {
			std::cout << "Error: Invalid argument '" << argument << "'\n";
			hasN = false;
			return false;
		}
	}
	if (!(hasHorizontal && hasVertical)) {
		std::cout << "Error: Missing required arguments ('vertical=' and 'horizontal=').\n";
		return false;
	}
	return true;
}


