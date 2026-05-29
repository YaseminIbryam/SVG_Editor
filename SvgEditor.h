#pragma once
#include <string>
#include "FigureList.h"

class SvgEditor {
private:
	std::string currentFilePath; ///< Пътят до текущо отворения файл. Ако няма такъв е празен стринг
	std::string command; ///< Последната въведена команда
	FigureList figures;


	/**
	 * @brief Взима само името на файла от целия път.
	 * @param path Пълният път.
	 * @return Името на файла заедно с разширението.
	 */
	std::string getFileName(const std::string& filePath) const;

	bool writeToFile(const std::string& path);
	
	std::string extractFill(pugi::xml_node tag, const char* def, const char* reserve) const;

	std::string extractStroke(pugi::xml_node tag, const char* def, const char* reserve) const;

	double extractStrokeWidth(pugi::xml_node tag, const double def, const double reserve) const;

	void extractFigures(pugi::xml_node tag, const char* defaultFill, const char* defaultStroke, double defaultStrokeWidth);

	bool getFiguresFromFile(const std::string& file);

	/**
	 * @brief Отваря SVG файл въз основа на въведен от потребителя път.
	 * @details Ако подаденият файл не съществува, създава нов празен файл.
	 * 
	 */
	//CHANGE HAPPENED
	void open(std::string& path);

	/// Затваря текущия файл. Промените не се запазват автоматично.
	void close();

	/// Записва всички промени в текущо отворения файл.
	void save();

	/**
	 * @brief Записва текущите данни в напълно нов файл.
	 * @details Изисква от потребителя да въведе нов валиден път, където да бъде запазена информацията.
	 */
	void saveAs(const std::string& newPath);

	/// Извежда на екрана списък с всички възможни команди.
	void help();

	void handleCreate(std::stringstream& ss);

	void handleWithin(std::stringstream& ss);

	void handleTranslate(std::stringstream& ss);
public:
	/**
	 * @brief Пуска основния цикъл на програмата.
	 * @details Чете и изпълнява команди от конзолата, докато не се въведе "exit".
	 */
	void start();
};