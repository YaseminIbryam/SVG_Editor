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

std::string SvgEditor::extractFill(pugi::xml_node tag, const char* def, const char* reserve) const {
	std::string fill;
	const pugi::xml_attribute fillAttribute = tag.attribute("fill");
	const char* value;
	if (*def != '\0') {
		value = def;
	}
	else {
		value = reserve;
	}
	fill = fillAttribute.as_string(value);
	return fill;
}
std::string SvgEditor::extractStroke(pugi::xml_node tag, const char* def, const char* reserve) const {
	std::string stroke;
	const pugi::xml_attribute strokeAttribute = tag.attribute("stroke");
	const char* value;
	if (*def != '\0') {
		value = def;
	}
	else {
		value = reserve;
	}
	stroke = strokeAttribute.as_string(value);
	return stroke;
}
double SvgEditor::extractStrokeWidth(pugi::xml_node tag, const double def, const double reserve) const {
	double strokeWidth;
	const pugi::xml_attribute strokeWidthAttribute = tag.attribute("stroke-width");
	double value;
	if (def >= 0.0) {
		value = def;
	}
	else {
		value =  reserve;
	}
	strokeWidth = strokeWidthAttribute.as_double(value);
	return strokeWidth;
}

void SvgEditor::extractFigures(pugi::xml_node tag, const char* defaultFill, const char* defaultStroke, double defaultStrokeWidth) {
	for (pugi::xml_node childTag : tag.children()) {
		if (std::string(childTag.name()) == "g") {
			const char* tempDefaultFill = defaultFill;
			const char* tempDefaultStroke = defaultStroke;
			double tempDefaultStrokeWidth = defaultStrokeWidth;
			pugi::xml_attribute fillAttribute = childTag.attribute("fill");
			if (fillAttribute) {
				tempDefaultFill = fillAttribute.as_string();
			}
			pugi::xml_attribute strokeAttribute = childTag.attribute("stroke");
			if (strokeAttribute) {
				tempDefaultStroke = strokeAttribute.as_string();
			}
			pugi::xml_attribute strokeWidthAttribute = childTag.attribute("stroke-width");
			if (strokeWidthAttribute) {
				tempDefaultStrokeWidth = strokeWidthAttribute.as_double();
			}
			extractFigures(childTag, tempDefaultFill, tempDefaultStroke, tempDefaultStrokeWidth);	
		}
		else if (std::string(childTag.name()) == "circle") {
			const Point center(childTag.attribute("cx").as_double(0.0), childTag.attribute("cy").as_double(0.0));
			const double r = childTag.attribute("r").as_double(0.0);
			const std::string fill = extractFill(childTag, defaultFill, "black");
			const std::string stroke = extractStroke(childTag, defaultStroke, "none");
			const double strokeWidth = extractStrokeWidth(childTag, defaultStrokeWidth, 1.0);
			figures.create(new Circle(center, r, fill, stroke, strokeWidth));
		}
		else if (std::string(childTag.name()) == "rect") {
			Point upperLeft(childTag.attribute("x").as_double(0.0), childTag.attribute("y").as_double(0.0));
			const double width = childTag.attribute("width").as_double(0.0);
			const double height = childTag.attribute("height").as_double(0.0);
			const std::string fill = extractFill(childTag, defaultFill, "black");
			const std::string stroke = extractStroke(childTag, defaultStroke, "none");
			const double strokeWidth = extractStrokeWidth(childTag, defaultStrokeWidth, 1.0);
			figures.create(new Rectangle(upperLeft, width, height, fill, stroke, strokeWidth));
		}
		else if (std::string(childTag.name()) == "line") {
			const Point start(childTag.attribute("x1").as_double(0.0), childTag.attribute("y1").as_double(0.0));
			const Point end(childTag.attribute("x2").as_double(0.0), childTag.attribute("y2").as_double(0.0));
			const std::string stroke = extractStroke(childTag, defaultStroke, "black");
			const double strokeWidth = extractStrokeWidth(childTag, defaultStrokeWidth, 1.0);
			figures.create(new Line(start, end, stroke, strokeWidth));
		}
	}
	return;
}


//Част от функцията е базирана на примерите от https://pugixml.org/docs/quickstart.html
bool SvgEditor::getFiguresFromFile(const std::string& file) {
	pugi::xml_document doc;
	const pugi::xml_parse_result result = doc.load_file(file.c_str()); //c_str: std::string -> const char*
	if (!result)
	{
		std::cout << "Error: " << result.description() << "\n";
		return false;
	}
	const pugi::xml_node node = doc.child("svg");
	if (!node) {
		std::cout << "Error: Missing <svg> in " << getFileName(file) << std::endl;
		return false;
	}
	extractFigures(node, "", "", -1.0);
	return true;
}

void SvgEditor::open(std::string& filePath) {
	std::ifstream file(filePath); // опитва да отвари файла за четене
	if (file.is_open()) {
		file.close();
	}
	else {
		std::ofstream file(filePath); // отваря за писане (създава го)
		if (!file.is_open()) { // При случай, че пътят е невалиден
			std::cout << "Error: Invalid path.";
			return;
		}
		file << "<svg>\n</svg>";
		file.close();
	}
	if (getFiguresFromFile(filePath)) {
		currentFilePath = filePath;
		std::cout << "Successfully opened " << getFileName(currentFilePath) << std::endl;
	}
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
	std::cout << "Successfully closed " << getFileName(currentFilePath) << std::endl;
	currentFilePath.clear();
	
	
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
	if (!(ss >> figure)) {
		std::cout << "Error: Command 'create' requires a figure type (line, rectangle or circle).\n";
		return;
	}
	if (figure != "rectangle" && figure != "circle" && figure != "line") {
		std::cout << "Error: Figure type can only be line, circle or rectangle.\n";
		return;
	}
	std::string fill = "none";
	std::string stroke = "none";
	double strokeWidth = 1.0;
	std::size_t n;
	if (figure == "circle") {
		double cx, cy, r;
		if (commandParser::parseCircleGeometry(ss, cx, cy, r) && commandParser::parseAreaStyle(ss, fill, stroke, strokeWidth)) {
			if (commandParser::isClean(ss)) {
				n = figures.create(new Circle(Point(cx, cy), r, fill, stroke, strokeWidth));
			}
			else {
				std::cout << "Error: Too many arguments!\n";
				return;
			}
		}
		else { return; }
	}
	else if (figure == "rectangle") {
		double x, y, width, height;
		if (commandParser::parseRectangleGeometry(ss, x, y, width, height) && commandParser::parseAreaStyle(ss, fill, stroke, strokeWidth)) {
			if (commandParser::isClean(ss)) {
				n = figures.create(new Rectangle(Point(x, y), width, height, fill, stroke, strokeWidth));
			}
			else {
				std::cout << "Error: Too many arguments!\n";
				return;
			}
		}
		else { return; }
	}
	else if (figure == "line") {
		double x1, y1, x2, y2;
		if (commandParser::parseLineGeometry(ss, x1, y1, x2, y2) && commandParser::parseLinearStyle(ss, stroke, strokeWidth)) {
			if (commandParser::isClean(ss)) {
				n = figures.create(new Line(Point(x1, y1), Point(x2, y2), stroke, strokeWidth));
			}
			else {
				std::cout << "Error: Too many arguments!\n";
				return;
			}
		}
		else { return; }
	}
	std::cout << "Successfully created " << figure << " (" << n << ")\n";
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
				std::cout << "Error: Too many arguments!\n";
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
				std::cout << "Error: Too many arguments!\n";
			}
		}
	}
}

void SvgEditor::handleTranslate(std::stringstream& ss) {
	bool hasN = false;
	int n = 0;
	double horizontal = 0;
	double vertical = 0;
	if (commandParser::parseTranslate(ss, horizontal, vertical, n, hasN)) {
		if (hasN) {
			if (figures.translate(n, horizontal, vertical)) {

				std::cout << "Translated a " << figures.getFigureType(n) << " (" << n << ")\n";
			}
			else {
				std::cout << "There is no figure number " << n << "!\n";

			}
		}
		else {
			
			figures.translate(horizontal, vertical);
			std::cout << "Translated all figures\n";
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
					std::cout << "Error: Command 'help' does not accept arguments!" << std::endl;
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
						std::cout << "Error: Command 'close' does not accept arguments!" << std::endl;
					}
				}
				else if (command == "save") {
					if (commandParser::isClean(ss)) {
						save();
					}
					else {
						std::cout << "Error: Command 'save' does not accept arguments!" << std::endl;
					}
				}
				else if (command == "print") {
					if (commandParser::isClean(ss)) {
						figures.print();
					}
					else {
						std::cout << "Error: Command 'print' does not accept arguments!" << std::endl;
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
						std::string type = figures.getFigureType(n);
						if (figures.erase(n)) {
							std::cout << "Erased a " << type << " (" << n << ")\n";
						}
						else {
							std::cout << "There is no figure number " << n << "!\n";
						}
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