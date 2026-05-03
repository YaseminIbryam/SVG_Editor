/**
* @file main.cpp
* @brief Главен файл, съдържащ главното меню за команди.
*/

#include <iostream>
#include <fstream>
#include <string>


class SvgEditor {
}
void help() {
	std::cout << "The following commands are supported:\n"
		<< "open <file>		opens <file>\n"
		<< "close			closes currently opened file\n"
		<< "save			saves the currently open file\n"
		<< "saveas <file>	saves the currently open file in <file>\n"
		<< "help			prints this information\n"
		<< "exit			exists the program\n";
}

std::string getFilePath() {
	std::string filePath;

	//Изчиства интервалите след командата, за да не влязат в името на файла
	std::getline(std::cin >> std::ws, filePath);

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
	if (filePath.empty()) {
		std::cout << "Грешка! Липсва име на файл!" << std::endl;
		return "";
	}
	if (!filePath.ends_with(".svg")) { //C++20
		std::cout << "Грешка! Програмата поддържа .svg файлов формат!" << std::endl;
		return "";
	}
	return filePath;

}

void openFile(std::string& filePath) {
	filePath = getFilePath();
	if (filePath.empty()) {
		return;
	}
	
	std::ifstream svgFile(filePath);

	std::size_t startIndex = filePath.rfind('\\') + 1; // намира индекса на началото на името на файла
	std::size_t lenFileName = filePath.length() - startIndex;
	std::string fileName = filePath.substr(startIndex, lenFileName);
	if (svgFile.is_open()) {
		std::cout << "Successfully opened " << fileName;
	}
	else {
		/
}

int main() {
	std::string currentFile = "";
	std::string command = "";
	while (std::cin >> command && command != "exit") { 
		if (command == "open") {
			
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
