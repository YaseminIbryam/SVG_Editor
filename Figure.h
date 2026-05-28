#pragma once
#include <string>
#include <ostream>

/*
* @brief Абстрактен базов клас за фигурите.
* Обединява общите характеристики на фигурите.
*/
class Figure {
protected:
	std::string fill; ///< Цвят за запълване
	std::string stroke; ///< Цвят на контура
	double strokeWidth; ///< Дебелина на контура

public:
	/*
	* @brief Конструктор на базовия клас за инициализиране на общите SVG атрибути.
	* @param fill Цвят за запълване
	* @param stroke Цвят на контура
	* @param strokeWidth Дебелина на контура
	*/
	Figure(std::string fill, std::string stroke, double strokeWidth) : fill(fill), stroke(stroke), strokeWidth(strokeWidth) {}

	/// @brief Виртуален деструктор за управление на паметта при наследниците.
	virtual ~Figure() = default;

	/**
	* @brief Създава дълбоко копие на текущата фигура.
	* @return Figure* Указател към новосъздаденото копие на фигурата.
	*/
	virtual Figure* clone() const = 0;

	virtual void save(std::ostream& out) const = 0;

	/// @brief Извежда фигурата на екрана.
	virtual void print() const = 0;

	/**
	* @brief Измества фигурата по двете оси спрямо текущото и местоположение.
	* @param horizontal Промяна по абсциса. Положителна стойност мести надясно, отрицателна - наляво.
	* @param vertical Промяна по ордината. Положителна стойност мести надолу, отрицателна - нагоре.
	*/
	virtual void translate(double horizontal, double vertical) = 0;

	/**
	* @brief Проверява дали фигурата се съдържа изцяло в правоъгълен регион.
	* @param x Абсциса на горния ляв ъгъл на правоъгълника.
	* @param y Ордината на горния ляв ъгъл на правоъгълника.
	* @param width Ширина на правоъгълника.
	* @param height Височина на правоъгълника.
	* @return true Ако фигурата е изцяло вътре в правоъгълника.
	* @return false Ако фигурата излиза извън правоъгълника.
	*/
	virtual bool withinRectangle(double x, double y, double width, double height) const = 0;

	/**
	* @brief Проверява дали фигурата се съдържа изцяло в кръгов регион.
	* @param cx Абсциса на центъра на кръга.
	* @param cy Ордината на центъра на кръга.
	* @param r Дължина на радиуса на кръга
	* @return true Ако фигурата е изцяло вътре в кръга.
	* @return false Ако фигурата излиза извън кръга.
	*/
	virtual bool withinCircle(double cx, double cy, double r) const = 0;
};