#pragma once
#include <sstream>

/**
* @brief Клас за парсване на потребителски команди.
* @details Съдържа само статични методи за извличане и валидация на аргументи от входен поток.
*/
class commandParser {
private:
	/// @brief Преобразува низ в реално число (double). Хвърля изключение при невалидни символи.
	/// @param str Низът за преобразуване.
	/// @param num Референция, в която се записва резултатът.
	static void strToDouble(const std::string& str, double& num);
	
	/// @brief Преобразува низ в цяло число (int). Хвърля изключение при невалидни символи.
	/// @param str Низът за преобразуване.
	/// @param n Референция, в която се записва резултатът.
	static void strToInt(const std::string& str, int& n);

	
public:
	/**
	* @brief Проверява дали входният поток е изчистен от допълнителни аргументи.
	* @param ss Входният поток с командата.
	* @return true Ако до края на потока има само празни пространства (интервали).
	* @return false Ако в потока са останали още непарснати данни.
	*/
	static bool isClean(std::stringstream& ss);

	/**
	* @brief Извлича път до файл от потока, поддържайки пътища с интервали, оградени в кавички.
	* @param ss Входният поток.
	* @param path Референция, в която се записва извлеченият път.
	* @param command Името на текущата команда (за извеждане на точни грешки).
	* @return true При успешно извличане на валиден .svg път.
	* @return false При липсващ път, незатворени кавички или грешно разширение.
	*/
	static bool parsePathOnly(std::stringstream& ss, std::string& path,const  std::string& command);

	/**
	* @brief Извлича точно един пореден номер (цяло число) от потока и проверява дали няма излишни данни след него.
	* @param ss Входният поток.
	* @param n Референция, в която се записва извлеченият номер.
	* @param command Името на текущата команда.
	* @return true При успешно извличане на числото.
	* @return false При липсващ аргумент, невалиден тип или излишни аргументи след числото.
	*/
	static bool parseNOnly(std::stringstream& ss, int& n,const std::string& command);

	/**
	* @brief Извлича аргументите за командата translate (horizontal, vertical и опционален индекс).
	* @param ss Входният поток.
	* @param horizontal Референция за стойността на хоризонталното отместване.
	* @param vertical Референция за стойността на вертикалното отместване.
	* @param n Референция за поредния номер на фигурата (ако е подаден).
	* @param hasN Референция към булева променлива, която става true, ако е подаден индекс.
	* @return true При успешно извличане на всички задължителни параметри.
	* @return false При дублирани, липсващи или невалидни аргументи.
	*/
	static bool parseTranslate(std::stringstream& ss, double& horizontal, double& vertical, int& n, bool& hasN);

	/**
	* @brief Извлича геометричните параметри, нужни за създаване на кръг.
	* @param ss Входният поток.
	* @param cx Референция за X координатата на центъра.
	* @param cy Референция за Y координатата на центъра.
	* @param r Референция за радиуса.
	* @return true При успешно извличане и валидация на радиуса.
	* @return false При недостиг на аргументи или отрицателен радиус.
	*/
	static bool parseCircleGeometry(std::stringstream& ss, double& cx, double& cy, double& r);

	/**
	* @brief Извлича геометричните параметри, нужни за създаване на правоъгълник.
	* @param ss Входният поток.
	* @param x Референция за X координатата на горния ляв ъгъл.
	* @param y Референция за Y координатата на горния ляв ъгъл.
	* @param width Референция за ширината.
	* @param height Референция за височината.
	* @return true При успешно извличане и валидация на размерите.
	* @return false При недостиг на аргументи или отрицателни размери.
	*/
	static bool parseRectangleGeometry(std::stringstream& ss, double& x, double& y, double& width, double& height);

	/**
	* @brief Извлича геометричните параметри, нужни за създаване на линия.
	* @param ss Входният поток.
	* @param x1 Референция за X координатата на началната точка.
	* @param y1 Референция за Y координатата на началната точка.
	* @param x2 Референция за X координатата на крайната точка.
	* @param y2 Референция за Y координатата на крайната точка.
	* @return true При успешно извличане на 4-те координати.
	* @return false При недостиг на аргументи.
	*/
	static bool parseLineGeometry(std::stringstream& ss, double& x1, double& y1, double& x2, double& y2);

	/**
	* @brief Извлича стиловите параметри за площни фигури (кръг и правоъгълник).
	* @param ss Входният поток.
	* @param fill Референция за цвят на запълване.
	* @param stroke Референция за цвят на контура.
	* @param strokeWidth Референция за дебелина на контура.
	* @return true При успешно извличане на опционалните параметри (включително ако липсват).
	* @return false При подадена отрицателна дебелина на контура.
	*/
	static bool parseAreaStyle(std::stringstream& ss, std::string& fill, std::string& stroke, double& strokeWidth);

	/**
	* @brief Извлича стиловите параметри за линейни фигури (линия).
	* @param ss Входният поток.
	* @param stroke Референция за цвят на контура.
	* @param strokeWidth Референция за дебелина на контура.
	* @return true При успешно извличане на опционалните параметри (включително ако липсват).
	* @return false При подадена отрицателна дебелина на контура.
	*/
	static bool parseLinearStyle(std::stringstream& ss, std::string& stroke, double& strokeWidth);
};