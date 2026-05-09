#include <iostream>
#include <fstream>
#include "SvgEditor.h"


std::string SvgEditor::getFilePath() {
	std::string filePath;
	//Изчиства интервалите след командата, за да не влязат в името на файла
	std::getline(std::cin >> std::ws, filePath);
	if (filePath.empty()) {
		std::cout << "Грешка! Липсва име на файл!" << std::endl;
		return "";
	}
	//Изчиства интервалите след името на файла, ако има такива
	while (!filePath.empty() && filePath.back() == ' ') {
		filePath.pop_back();
	}
	//Премахва кавичките от началото и края, ако има такива
	if (filePath.size() >= 2 && filePath.front() == '"' && filePath.back() == '"') {
		filePath.pop_back();
		filePath.erase(0, 1);
	}
	else if (filePath.front() == '"' || filePath.back() == '"') { // при " или несъответствие в кавичките
		std::cout << "Грешка! Грешен формат на името на файла!" << std::endl;
		return "";
	}
	if (!filePath.ends_with(".svg")) { //C++20
		std::cout << "Грешка! Програмата поддържа .svg файлов формат!" << std::endl;
		return "";
	}
	return filePath;
}

std::string SvgEditor::getFileName(std::string path) const{
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

void SvgEditor::open() {
	std::string filePath = getFilePath();
	if (filePath.empty()) {
		return;
	}
	std::ifstream svgFile(filePath);
	if (!svgFile.is_open()) {
		std::ofstream svgFile(filePath);
	}
	currentFilePath = filePath;
	svgFile.close();
	std::cout << "Successfully opened " << getFileName(filePath);
}

void SvgEditor::close() {

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
	while (std::cin >> command && command != "exit") {
		if (command == "open") {
			open();
		}
		else if (command == "close") {
		}
		else if (command == "save") {
		}
		else if (command == "saveas") {
		}
		else if (command == "help") {
			help();
		}
	}
}