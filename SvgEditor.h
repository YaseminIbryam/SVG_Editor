#pragma once
#include <string>
#include "FigureList.h"
#include "external/pugixml/src/pugixml.hpp"

/**
* @brief Главен клас, който управлява работата на приложението.
* @details Този клас осъществява връзката между потребителския вход от конзолата, парсъра за команди и мениджъра на фигурите. Отговаря за цялостния цикъл на програмата, включително отварянето, обработката и запазването на SVG файловете.
*/
class SvgEditor {
private:
	std::string currentFilePath; ///< Пътят до текущо отворения файл. Ако няма такъв е празен стринг
	std::string command; ///< Последната въведена команда
	FigureList figures; ///< Контейнер, съдържащ всички фигури, които са заредени в момента.


	/**
	* @brief Взима само името на файла от целия път.
	* @param path Пълният път.
	* @return Името на файла заедно с разширението.
	*/
	std::string getFileName(const std::string& path) const;

	/**
	* @brief Записва текущите фигури в посочения файл във формат SVG.
	* @param path Пътят до файла за запис.
	* @return true при успешен запис
	* @return false при грешка
	*/
	bool writeToFile(const std::string& path);
	
	/**
	* @brief Извлича цвета за запълване (fill) от даден XML възел.
	* @param tag XML възелът, от който се чете.
	* @param def Цвета за запълване по подразбиране, наследен от обхващаща група (или подадена от главната функция, ако няма група над този таг)
	* @param reserve Краен (Резервен) цвят за запълване по подразбиране.
	* @return Низ, съдържащ цвета за запълване.
	*/
	std::string extractFill(pugi::xml_node tag, const char* def, const char* reserve) const;

	/**
	* @brief Извлича цвета на контура (stroke) от даден XML възел.
	* @param tag XML възелът, от който се чете.
	* @param def Цвета на контура по подразбиране, наследен от обхващаща група (или подадена от главната функция, ако няма група над този таг)
	* @param reserve Краен (Резервен) цвят на контура по подразбиране.
	* @return Низ, съдържащ цвета на контура.
	*/
	std::string extractStroke(pugi::xml_node tag, const char* def, const char* reserve) const;

	/**
	* @brief Извлича дебелината на контура (stroke-width) от даден XML възел.
	* @param tag XML възелът, от който се чете.
	* @param def Дебелина на контура по подразбиране, наследен от обхващаща група. (или подадена от главната функция, ако няма група над този таг)
	* @param reserve Крайна (Резервна) дебелина по подразбиране.
	* @return Дебелината на контура.
	*/
	double extractStrokeWidth(pugi::xml_node tag, const double def, const double reserve) const;

	/**
	* @brief Извлича всички фигури от даден XML възел и ги добавя в контейнера.
	* @param tag Основният XML възел, който се обхожда рекурсивно.
	* @param defaultFill Цвят за запълване по подразбиране от родителски (svg) възел.
	* @param defaultStroke Цвят на контура по подразбиране от родителски (svg) възел.
	* @param defaultStrokeWidth Дебелина на контура по подразбиране от родителски (svg) възел.
	*/
	void extractFigures(pugi::xml_node tag, const char* defaultFill, const char* defaultStroke, double defaultStrokeWidth);

	/**
	* @brief Изгражда вътрешното представяне на фигурите чрез четене от SVG файл.
	* @details Логиката за зареждане и обхождане XML е базирана на примерите от: https://pugixml.org/docs/quickstart.html
	* @param file Пътят до файла за четене.
	* @return true при успешно прочитане
	* @return false при грешка
	*/
	bool getFiguresFromFile(const std::string& file);

	/**
	* @brief Отваря SVG файл въз основа на въведен от потребителя път.
	* @details Ако подаденият файл не съществува, създава нов празен файл.
	* @param filePath Пътят към файла, който трябва да бъде отворен.
	*/
	void open(std::string& filePath);

	/// Затваря текущия файл. Промените не се запазват автоматично.
	void close();

	/// Записва всички промени в текущо отворения файл.
	void save();

	/**
	* @brief Записва текущите данни в напълно нов файл.
	* @details Изисква от потребителя да въведе нов валиден път, където да бъде запазена информацията.
	* @param newPath Пътят към новия файл.
	*/
	void saveAs(const std::string& newPath);

	/// Извежда на екрана списък с всички възможни команди.
	void help();

	/**
	* @brief Обработва командата за създаване на нова фигура, подадена от потребителя.
	* @param ss Потокът, съдържащ аргументите на командата.
	*/
	void handleCreate(std::stringstream& ss);

	/**
	* @brief Обработва командата за намиране на фигури в даден регион.
	* @param ss Потокът, съдържащ аргументите на командата.
	*/
	void handleWithin(std::stringstream& ss);

	/**
	* @brief Обработва командата за транслиране (преместване) на фигури.
	* @param ss Потокът, съдържащ аргументите на командата.
	*/
	void handleTranslate(std::stringstream& ss);
public:
	/**
	* @brief Пуска основния цикъл на програмата.
	* @details Чете и изпълнява команди от конзолата, докато не се въведе "exit".
	*/
	void start();
};