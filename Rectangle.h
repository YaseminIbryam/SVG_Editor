#pragma once
#include "Figure.h"
#include "Point.h"


/**
* @brief Клас за фигурата правоъгълник.
* Наследява базовия клас Figure и имплементира функциите за правоъгълник.
*/
class Rectangle : public Figure {
private:
	Point upperLeft; ///< Точка на началото на горния ляв ъгъл на правоъгълника
	double width; ///< Ширина на правоъгълника
	double height; ///< Височина на правоъгълника
public:
	/**
	* @brief Конструктор за правоъгълник.
	* @param upperLeft Точката на началото на горния ляв ъгъл на правоъгълника.
	* @param width Ширина на правоъгълника.
	* @param height Височината на правоъгълника.
	* @param fill Цвят за запълване на правоъгълника. Черен по подразбиране.
	* @param stroke Цвят на контура на правоъгълника. По подразбиране е "none".
	* @param strokeWidth Дебелина на контура на правоъгълника. По подразбиране е 1.0.
	*/
	Rectangle(Point upperLeft, double width, double height, std::string fill = "black", std::string stroke = "none", double strokeWidth = 1.0);

	/**
	* @brief Създава дълбоко копие на правоъгълника.
	* @return Rectangle* Указател към новосъздаденото копие на текущия правоъгълник.
	*/
	Rectangle* clone() const final;

	/**
	* @brief Записва правоъгълника в изходен поток във формат SVG.
	* @param out Изходният поток, в който ще се записват данните.
	*/
	void save(std::ostream& out) const final;

	/**
	 * @brief Връща типа на фигурата.
	 * @return std::string Низа на типа "rectangle".
	 */
	std::string getType() const final;

	/// Извежда правоъгълника на екрана.
	void print() const final;

	/// Измества правоъгълника по двете оси спрямо текущото му местоположение.
	void translate(double horizontal, double vertical) final;

	/// Проверява дали правоъгълникът се съдържа изцяло в правоъгълен регион.
	bool withinRectangle(double x, double y, double width, double height) const final;

	/// Проверява дали правоъгълникът се съдържа изцяло в кръгов регион.
	bool withinCircle(double cx, double cy, double r) const final;
};