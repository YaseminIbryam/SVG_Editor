#pragma once
#include "Figure.h"
#include "Point.h"

/**
* @brief Клас за фигурата кръг.
* Наследява базовия клас Figure и имплементира функциите за кръг.
*/
class Circle : public Figure {
private:
	Point center; ///< Точка на центъра на кръга
	double radius; ///< Дължина на радиуса на кръга
public:
	/** 
	* @brief Конструктор за създаване на кръг.
	* @param center Центърът на кръга.
	* @param radius Радиусът на кръга.
	* @param fill Цвят на запълването на кръга. Черен по подразбиране.
	* @param stroke Цвят на контура на кръга. По подразбиране е "none".
	* @param strokeWidth Дебелина на контура на кръга. По подразбиране е 1.0.
	*/
	Circle(Point center, double radius, std::string fill = "black", std::string stroke = "none", double strokeWidth = 1.0);
	
	/**
	* @brief Създава дълбоко копие на кръга.
	* @return Circle* Указател към новосъздаденото копие на текущия кръг.
	*/
	Circle* clone() const final;

	/**
	* @brief Записва кръга в изходен поток във формат SVG.
	* @param out Изходният поток, в който ще се записват данните.
	*/
	void save(std::ostream& out) const final;

	/**
	 * @brief Връща типа на фигурата.
	 * @return std::string Низа на типа "circle".
	 */
	std::string getType() const final;

	/// Извежда кръга на екрана.
	void print() const final;

	/// Измества кръга спрямо текущото му местоположение.
	void translate(double horizontal, double vertical) final;

	/// Проверява дали кръгът се съдържа изцяло в правоъгълен регион.
	bool withinRectangle(double x, double y, double width, double height) const final;

	/// Проверява дали кръгът се съдържа изцяло в кръгов регион.
	bool withinCircle(double cx, double cy, double r) const final;
};