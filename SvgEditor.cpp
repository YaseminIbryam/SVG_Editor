#include <iostream>
#include <fstream>
#include "commandParser.h"
#include "SvgEditor.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Line.h"


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

bool SvgEditor::writeToFile(const std::string& path) {
	std::ofstream file(path);
	if (!file.is_open()) {
		std::cout << "Error: Could not open file " << path << " for writing." << std::endl;
		return false;
	}
	file << "<?xml version=\"1.0\" standalone=\"no\"?>\n<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n<svg>\n";
	figures.save(file);
	file << "</svg>\n";
	file.close();
	return true;
}

void SvgEditor::open(std::string& filePath) {
	std::ifstream file(filePath); // опитва да отвари файла за четене
	if (!file.is_open()) {
		std::ofstream createFile(filePath); // отваря за писане (създава го)
		createFile.close();
		file.clear();
		file.open(filePath); // пак опитва да отвари файла за четене 
		if (!file.is_open()) { // При случай, че пътят е невалиден
			std::cout << "Error: Invalid path.";
			return;
		}
	}
	//TO DO: GET THE INFO FROM THE FILE AND STORE IT
	currentFilePath = filePath;
	file.close();
	std::cout << "Successfully opened " << getFileName(currentFilePath) << std::endl;
}

void SvgEditor::save() {
	if (writeToFile(currentFilePath)) {
		std::cout << "Successfully saved the changes to " << getFileName(currentFilePath) << std::endl;
	}
}

void SvgEditor::saveAs(const std::string& newPath) {
	if (writeToFile(newPath)) {
		std::cout << "Successfully saved another " << getFileName(newPath) << std::endl;
		currentFilePath = newPath;
	}
}

void SvgEditor::close() {
	figures.clear();
	currentFilePath.clear();
	std::cout << "Successfully closed " << getFileName(currentFilePath) << std::endl;
	
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

void SvgEditor::handleCreate(std::stringstream& ss) {
	std::string figure;
	std::string fill = "none";
	std::string stroke = "none";
	double strokeWidth = 1.0;
	if (!(ss >> figure)) {
		std::cout << "Error: Command 'create' requires a figure type (line, rectangle or circle).\n";
	}
	else if (figure != "rectangle" && figure != "circle" && figure != "line") {
		std::cout << "Error: Figure type can only be line, circle or rectangle.\n";
	}
	else if (figure == "circle") {
		double cx, cy, r;
		if (commandParser::parseCircleGeometry(ss, cx, cy, r) && commandParser::parseAreaStyle(ss, fill, stroke, strokeWidth)) {
			if (commandParser::isClean(ss)) {
				figures.create(new Circle(Point(cx, cy), r, fill, stroke, strokeWidth));
			}
			else {
				std::cout << "Error: Error: Too much arguments!\n";
			}
		}
	}
	else if (figure == "rectangle") {
		double x, y, width, height;
		if (commandParser::parseRectangleGeometry(ss, x, y, width, height) && commandParser::parseAreaStyle(ss, fill, stroke, strokeWidth)) {
			if (commandParser::isClean(ss)) {

				figures.create(new Rectangle(Point(x, y), width, height, fill, stroke, strokeWidth));
			}
			else {
				std::cout << "Error: Error: Too much arguments!\n";
			}
		}
	}
	else if (figure == "line") {
		double x1, y1, x2, y2;
		if (commandParser::parseLineGeometry(ss, x1, y1, x2, y2) && commandParser::parseLinearStyle(ss, stroke, strokeWidth)) {
			if (commandParser::isClean(ss)) {
				figures.create(new Line(Point(x1, y1), Point(x2, y2), stroke, strokeWidth));
			}
			else {
				std::cout << "Error: Error: Too much arguments!\n";
			}
		}
	}

}

void SvgEditor::handleWithin(std::stringstream& ss) {
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
			if (commandParser::isClean(ss)) {
				figures.withinCircle(cx, cy, r);
			}
			else {
				std::cout << "Error: Error: Too much arguments!\n";
			}
		}
	}
	else if (region == "rectangle") {
		double x, y, width, height;
		if (commandParser::parseRectangleGeometry(ss, x, y, width, height)) {
			if (commandParser::isClean(ss)) {
				figures.withinRectangle(x, y, width, height);
			}
			else {
				std::cout << "Error: Error: Too much arguments!\n";
			}
		}
	}
}

void SvgEditor::handleTranslate(std::stringstream& ss) {
	bool isAllFigures = false;
	int n = 0;
	double horizontal = 0;
	double vertical = 0;
	if (commandParser::parseTranslate(ss, horizontal, vertical, n, isAllFigures)) {
		if (isAllFigures) {
			figures.translate(horizontal, vertical);
		}
		else {
			figures.translate(n, horizontal, vertical);
		}
	}
}

void SvgEditor::start() {
	bool isRunning = true;
	std::string line;
	while (std::getline(std::cin, line) && isRunning) {
		try {
			std::stringstream ss(line); //Създава поток с реда
			ss >> command; //Извлича първата дума (командата)

			if (command == "exit") { //Програма ще приключи без значение какво селдва след командата exit
				std::cout << "Exit\n";
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
						figures.print();
					}
					else {
						std::cout << "Error: Command 'print' does not accept arguments!";
					}
				}
				else if (command == "saveas") {
					std::string tempPath;
					if (commandParser::parsePathOnly(ss, tempPath, command)) {
						saveAs(tempPath);
					}
				}

				else if (command == "create") {
					handleCreate(ss);
					
				}
				else if (command == "erase") {
					int n;
					if (commandParser::parseNOnly(ss, n, command)) {
						figures.erase(n);
					}
				}
				else if (command == "translate") {
					handleTranslate(ss);
				}
				else if (command == "within") {
					handleWithin(ss);
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