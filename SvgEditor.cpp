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
		try {
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
					if (commandParser::parsePathOnly(ss, tempPath, command)) {
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
					commandParser::parsePathOnly(ss, tempPath, command);
					saveAs();
				}

				else if (command == "create") {
					//Check for trash
					std::string figure;
					if (!(ss >> figure)) {
						std::cout << "Error: Command 'create' requires a figure type (line, rectangle or circle).\n";
					}
					else if (figure != "rectangle" && figure != "circle" && figure != "line") {
						std::cout << "Error: Figure type can only be line, circle or rectangle.\n";
					}
					else if (figure == "circle") {
						double cx, cy, r;
						if (commandParser::parseCircleGeometry(ss, cx, cy, r)) {
							//............
						}
						else { continue; }
					}
					else if (figure == "rectangle") {
						double x, y, width, height;
						if (commandParser::parseRectangleGeometry(ss, x, y, width, height)) {
							//................
						}
						else { continue; }
					}
					else if (figure == "line") {
						double x1, y1, x2, y2;
						if (commandParser::parseLineGeometry(ss, x1, y1, x2, y2)) {
							//................
						}
						else { continue; }
					}
					if (commandParser::isClean(ss)) {
						//create
					}
					else {
						std::cout << "Error: Error: Too much arguments!\n";
					}
				}
				else if (command == "erase") {
					int n;
					commandParser::parseNOnly(ss, n, command);
					//erase();
				}
				else if (command == "translate") {
					bool isAllFigures = false;
					int n = 0;
					double horizontal = 0;
					double vertical = 0;
					if (commandParser::parseTranslate(ss, horizontal, vertical, n, isAllFigures)) {
						if (isAllFigures) {
							//translate with n
						}
						else {
							//translate
						}
					}
				}
				else if (command == "within") {
					std::string region;
					if (!(ss >> region)) {
						std::cout << "Error: Command 'within' requires a region type (rectangle or circle).\n";
					}
					else if (region != "rectangle" && region != "circle") {
						std::cout << "Error: Region type can only be circle or rectangle.\n";
					}
					else if (region == "circle") {
						double cx, cy, r;
						if (commandParser::parseCircleGeometry(ss, cx, cy, r)) {
							//withincircle
						}
						else { continue; }
					}
					else if (region == "rectangle") {
						double x, y, width, height;
						if (commandParser::parseRectangleGeometry(ss, x, y, width, height)) {
							//withinrectangle
						}
						else { continue; }
					}
					if(commandParser::isClean(ss)) {
						//within
					}
					else {
						std::cout << "Error: Error: Too much arguments!\n";
					}
				}
				else if (command == "open") {
					std::cout << "Error: File " << getFileName(currentFilePath) << " is already open. Please close it first.\n";
				}
				else {
					std::cout << command << " is not recognized." << std::endl;
				}
			}
		}
		catch (const std::invalid_argument&) {
			std::cout << "Error: Invalid number format for '" << command << "'\n";
		}
		catch (const std::out_of_range&) {
			std::cout << "Error: The number is too large or too small for this data type.\n"; //само за сигурност
		}
		
	}
}