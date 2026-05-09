#pragma once

#include <string>

class SvgEditor {
private:
	std::string currentFilePath = "";
	std::string command = "";

	std::string getFilePath();
	std::string getFileName(std::string path) const;
	void open();
	void close();
	void save();
	void saveAs();
	void help();

public:
	void start();
};