#include <iostream>
#include <fstream>
#include "commandParser.h"
#include "SvgEditor.h"


std::string SvgEditor::getFileName(const std::string& path) const{
	//std::size_t lastBackslashIndex = filePath.rfind('\\'); // връща std::string::npos ако няма съвпадение
	//if (lastBackslashIndex == std::string::npos) {  //std::string::npos = -1 - константа за най-голямата възможна стойност на size_t
	//	std::string fileName = filePath;
	//}
	//else {
	//	std::string fileName = filePath.substr(lastBackslashIndex + 1);
	//}
	std::size_t startIndex = path.rfind('\\') + 1; // намира индекса на началото на името на файла
	std::string name = path.substr(startIndex);
	return name;
}

void SvgEditor::open(std::string& filePath) {
	std::ifstream svgFile(filePath);
	if (!svgFile.is_open()) {
		std::ofstream svgFile(filePath); //???
		//TO DO: GET THE INFO FROM THE FILE AND STORE IT
	}
	currentFilePath = filePath;
	svgFile.close();
	std::cout << "Successfully opened " << getFileName(filePath) << std::endl;
}

void SvgEditor::close() {
	// Actually delete the data
	std::cout << "Successfully closed " << getFileName(currentFilePath) << std::endl;
	currentFilePath = "";
}
void SvgEditor::help() {
	std::cout << "The following commands are supported:\n"
		<< "open <file>		opens <file>\n"
		<< "close			closes currently opened file\n"
		<< "save			saves the currently open file\n"
		<< "saveas <file>		saves the currently open file in <file>\n"
		<< "help			prints this information\n"
		<< "exit			exists the program\n";
}

void SvgEditor::start() {
	bool isRunning = true;
	std::string line;
	while (std::getline(std::cin, line) && isRunning) {
		std::stringstream ss(line); //Създава поток с реда
		ss >> command; //Извлича първата дума (командата)

		if (command == "exit") { //Програма ще приключи без значение какво селдва след командата exit
			isRunning = false;
		}
		else if (command == "help") {
			if (commandParser::isClean(ss)) {
				help();
			}
			else {
				std::cout << "Error: Command 'help' does not accept arguments!";
			}
		}
		else if (currentFilePath.empty()) {
			if (command == "open") {
				std::string tempPath;
				if (commandParser::parsePath(ss, tempPath, command)) {
					open(tempPath);
				}
			}
			else { 
				std::cout << "No file is currently open." << std::endl;
			}
		}
		else {
			if (command == "close") {
				if (commandParser::isClean(ss)) {
					close();
				}
				else {
					std::cout << "Error: Command 'close' does not accept arguments!";
				}
			}
			else if (command == "save") {
				if (commandParser::isClean(ss)) {
					save();
				}
				else {
					std::cout << "Error: Command 'save' does not accept arguments!";
				}
			}
			else if (command == "print") {
				if (commandParser::isClean(ss)) {
					//print();
				}
				else {
					std::cout << "Error: Command 'print' does not accept arguments!";
				}
			}
			else if (command == "saveas") {
				std::string tempPath;
				commandParser::parsePath(ss, tempPath, command);
				saveAs();
			}
			
			else if (command == "create") {
				//Check for trash
			}
			else if (command == "erase") {
				int n;
				commandParser::parseN(ss, n, command);
				//erase();
			}
			else if (command == "translate") {
				bool isAllFigures = false;
				int n = 0;
				double horizontal = 0;
				double vertical = 0;
				if (commandParser::parseTranslate(ss, horizontal, vertical, n, isAllFigures)) {

				}
			}
			else if (command == "within") {
				//Check for trash
			}
			else if (command == "open") {
				std::cout << "Error: File " << getFileName(currentFilePath) << " is already open. Please close it first.";
			}
			else {
				std::cout << command << " is not recognized." << std::endl;
			}
		}
	}
}