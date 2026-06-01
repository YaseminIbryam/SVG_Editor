#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "external/doctest.h"
#include "Point.h"
#include "commandParser.h"
#include "Line.h"
#include "Circle.h"
#include "Rectangle.h"
#include "FigureList.h"

TEST_SUITE("Parser tests") {
	TEST_CASE("parseNOnly") {
		int n = 0;
		SUBCASE("Parses positive integer") {
			std::stringstream ss("42");
			CHECK(commandParser::parseNOnly(ss, n, "erase"));
			CHECK(n == 42);
		}
		SUBCASE("Parses a negative integer") {
			std::stringstream ss("-10");
			CHECK(commandParser::parseNOnly(ss, n, "erase"));
			CHECK(n == -10);
		}
		SUBCASE("Successfully parses zero") {
			std::stringstream ss("0");
			CHECK(commandParser::parseNOnly(ss, n, "erase"));
			CHECK(n == 0);
		}
		SUBCASE("Parses an integer even with whitespaces after the number") {
			std::stringstream ss("77   ");
			CHECK(commandParser::parseNOnly(ss, n, "erase"));
			CHECK(n == 77);
		}
		SUBCASE("Throws invalid_argument when letters are appended") {
			std::stringstream ss("123abc");
			CHECK_THROWS_AS(commandParser::parseNOnly(ss, n, "erase"), std::invalid_argument);
		}
		SUBCASE("Throws invalid_argument when letters come before the integer") {
			std::stringstream ss("abc123");
			CHECK_THROWS_AS(commandParser::parseNOnly(ss, n, "erase"), std::invalid_argument);
		}
		SUBCASE("Throws invalid_argument when a float is provided") {
			std::stringstream ss("3.14");
			CHECK_THROWS_AS(commandParser::parseNOnly(ss, n, "erase"), std::invalid_argument);
		}
		SUBCASE("Fails on an empty stream") {
			std::stringstream ss("");
			CHECK_FALSE(commandParser::parseNOnly(ss, n, "erase"));
		}
		SUBCASE("Throws out_of_range for extremely large numbers") {
			std::stringstream ss("99999999999999999999");
			CHECK_THROWS_AS(commandParser::parseNOnly(ss, n, "erase"), std::out_of_range);
		}
	}
	TEST_CASE("parsePathOnly") {
		std::string path;
		const std::string cmd = "open";

		SUBCASE("parses an unquoted valid path") {
			std::stringstream ss("file.svg");
			CHECK(commandParser::parsePathOnly(ss, path, cmd));
			CHECK(path == "file.svg");
		}

		SUBCASE("parses a quoted path containing spaces") {
			std::stringstream ss("\"my folder/my file.svg\"");
			CHECK(commandParser::parsePathOnly(ss, path, cmd));
			CHECK(path == "my folder/my file.svg");
		}

		SUBCASE("fails when the closing quote is missing") {
			std::stringstream ss("\"broken_file.svg");
			CHECK_FALSE(commandParser::parsePathOnly(ss, path, cmd));
		}

		SUBCASE("fails when the stream is empty or contains only spaces") {
			std::stringstream ss("    ");
			CHECK_FALSE(commandParser::parsePathOnly(ss, path, cmd));
		}

		SUBCASE("fails when there are extra arguments after an unquoted path") {
			std::stringstream ss("file.svg extra_text");
			CHECK_FALSE(commandParser::parsePathOnly(ss, path, cmd));
		}

		SUBCASE("fails when there are extra arguments after a quoted path") {
			std::stringstream ss("\"file.svg\" extra_text");
			CHECK_FALSE(commandParser::parsePathOnly(ss, path, cmd));
		}

		SUBCASE("fails when the file extension is not .svg") {
			std::stringstream ss("document.pdf");
			CHECK_FALSE(commandParser::parsePathOnly(ss, path, cmd));
		}

		SUBCASE("fails when the file extension is not .svg (quoted)") {
			std::stringstream ss("\"image.png\"");
			CHECK_FALSE(commandParser::parsePathOnly(ss, path, cmd));
		}
	}
	TEST_CASE("parseTranslate") {
		double horizontal = 0;
		double vertical = 0;
		int n = 0;
		bool hasN = false;

		SUBCASE("parses valid translation without n") {
			std::stringstream ss("vertical=10 horizontal=20");
			CHECK(commandParser::parseTranslate(ss, horizontal, vertical, n, hasN));
			CHECK(horizontal == doctest::Approx(20));
			CHECK(vertical == doctest::Approx(10));
			CHECK_FALSE(hasN);
		}

		SUBCASE("parses valid translation with reversed order") {
			std::stringstream ss("horizontal=-5.5 vertical=3.14");
			CHECK(commandParser::parseTranslate(ss, horizontal, vertical, n, hasN));
			CHECK(horizontal == doctest::Approx(-5.5));
			CHECK(vertical == doctest::Approx(3.14));
			CHECK_FALSE(hasN);
		}

		SUBCASE("parses valid translation with n at the beginning") {
			std::stringstream ss("5 vertical=10 horizontal=20");
			CHECK(commandParser::parseTranslate(ss, horizontal, vertical, n, hasN));
			CHECK(horizontal == doctest::Approx(20));
			CHECK(vertical == doctest::Approx(10));
			CHECK(hasN);
			CHECK(n == 5);
		}

		SUBCASE("parses valid translation with n in the middle") {
			std::stringstream ss("vertical=10 3 horizontal=20");
			CHECK(commandParser::parseTranslate(ss, horizontal, vertical, n, hasN));
			CHECK(horizontal == doctest::Approx(20));
			CHECK(vertical == doctest::Approx(10));
			CHECK(hasN);
			CHECK(n == 3);
		}

		SUBCASE("fails when vertical is missing") {
			std::stringstream ss("horizontal=10");
			CHECK_FALSE(commandParser::parseTranslate(ss, horizontal, vertical, n, hasN));
		}

		SUBCASE("fails when horizontal is missing") {
			std::stringstream ss("vertical=10");
			CHECK_FALSE(commandParser::parseTranslate(ss, horizontal, vertical, n, hasN));
		}

		SUBCASE("fails when vertical is duplicated") {
			std::stringstream ss("vertical=10 vertical=20 horizontal=5");
			CHECK_FALSE(commandParser::parseTranslate(ss, horizontal, vertical, n, hasN));
		}

		SUBCASE("fails when horizontal is duplicated") {
			std::stringstream ss("horizontal=10 horizontal=20 vertical=5");
			CHECK_FALSE(commandParser::parseTranslate(ss, horizontal, vertical, n, hasN));
		}

		SUBCASE("fails when multiple N values are provided") {
			std::stringstream ss("5 6 vertical=10 horizontal=10");
			CHECK_FALSE(commandParser::parseTranslate(ss, horizontal, vertical, n, hasN));
		}

		SUBCASE("fails when N is zero or negative") {
			std::stringstream ss("0 vertical=10 horizontal=10");
			CHECK_FALSE(commandParser::parseTranslate(ss, horizontal, vertical, n, hasN));
		}

		SUBCASE("throws invalid_argument when vertical value is letters") {
			std::stringstream ss("vertical=abc horizontal=10");
			CHECK_THROWS_AS(commandParser::parseTranslate(ss, horizontal, vertical, n, hasN), std::invalid_argument);
		}

		SUBCASE("throws invalid_argument when N is letters") {
			std::stringstream ss("abc vertical=10 horizontal=10");
			CHECK_THROWS_AS(commandParser::parseTranslate(ss, horizontal, vertical, n, hasN), std::invalid_argument);
		}
	}
	TEST_CASE("parseRectangleGeometry") {
		double x = 0;
		double y = 0;
		double width = 0;
		double height = 0;

		SUBCASE("parses valid rectangle geometry with positive coordinates") {
			std::stringstream ss("10 20 100 50");
			CHECK(commandParser::parseRectangleGeometry(ss, x, y, width, height));
			CHECK(x == doctest::Approx(10));
			CHECK(y == doctest::Approx(20));
			CHECK(width == doctest::Approx(100));
			CHECK(height == doctest::Approx(50));
		}

		SUBCASE("parses valid rectangle geometry with negative coordinates and decimal values") {
			std::stringstream ss("-15.5 -20.5 100.5 50.25");
			CHECK(commandParser::parseRectangleGeometry(ss, x, y, width, height));
			CHECK(x == doctest::Approx(-15.5));
			CHECK(y == doctest::Approx(-20.5));
			CHECK(width == doctest::Approx(100.5));
			CHECK(height == doctest::Approx(50.25));
		}

		SUBCASE("parses valid rectangle geometry with zero width and height") {
			std::stringstream ss("0 0 0 0");
			CHECK(commandParser::parseRectangleGeometry(ss, x, y, width, height));
			CHECK(x == doctest::Approx(0));
			CHECK(y == doctest::Approx(0));
			CHECK(width == doctest::Approx(0));
			CHECK(height == doctest::Approx(0));
		}

		SUBCASE("fails when there are less than 4 arguments") {
			std::stringstream ss("10 20 100");
			CHECK_FALSE(commandParser::parseRectangleGeometry(ss, x, y, width, height));
		}

		SUBCASE("fails when the stream is empty") {
			std::stringstream ss("");
			CHECK_FALSE(commandParser::parseRectangleGeometry(ss, x, y, width, height));
		}

		SUBCASE("fails when width is negative") {
			std::stringstream ss("10 20 -5 50");
			CHECK_FALSE(commandParser::parseRectangleGeometry(ss, x, y, width, height));
		}

		SUBCASE("fails when height is negative") {
			std::stringstream ss("10 20 100 -5");
			CHECK_FALSE(commandParser::parseRectangleGeometry(ss, x, y, width, height));
		}

		SUBCASE("throws invalid_argument when x contains letters") {
			std::stringstream ss("10a 20 100 50");
			CHECK_THROWS_AS(commandParser::parseRectangleGeometry(ss, x, y, width, height), std::invalid_argument);
		}

		SUBCASE("throws invalid_argument when height contains letters") {
			std::stringstream ss("10 20.7 100 50.55x");
			CHECK_THROWS_AS(commandParser::parseRectangleGeometry(ss, x, y, width, height), std::invalid_argument);
		}
	}
	TEST_CASE("parseLineGeometry") {
		double x1 = 0;
		double y1 = 0;
		double x2 = 0;
		double y2 = 0;

		SUBCASE("parses valid line geometry with integers") {
			std::stringstream ss("33 17 89 42");
			CHECK(commandParser::parseLineGeometry(ss, x1, y1, x2, y2));
			CHECK(x1 == doctest::Approx(33));
			CHECK(y1 == doctest::Approx(17));
			CHECK(x2 == doctest::Approx(89));
			CHECK(y2 == doctest::Approx(42));
		}

		SUBCASE("parses valid line geometry with mixed double and negative values") {
			std::stringstream ss("-7.5 44.2 0 105.88");
			CHECK(commandParser::parseLineGeometry(ss, x1, y1, x2, y2));
			CHECK(x1 == doctest::Approx(-7.5));
			CHECK(y1 == doctest::Approx(44.2));
			CHECK(x2 == doctest::Approx(0));
			CHECK(y2 == doctest::Approx(105.88));
		}

		SUBCASE("fails when there are less than 4 arguments") {
			std::stringstream ss("12.4 8.1 9");
			CHECK_FALSE(commandParser::parseLineGeometry(ss, x1, y1, x2, y2));
		}

		SUBCASE("fails when the stream is empty") {
			std::stringstream ss("");
			CHECK_FALSE(commandParser::parseLineGeometry(ss, x1, y1, x2, y2));
		}

		SUBCASE("throws invalid_argument when x1 contains letters") {
			std::stringstream ss("33a 17 89.5 42");
			CHECK_THROWS_AS(commandParser::parseLineGeometry(ss, x1, y1, x2, y2), std::invalid_argument);
		}

		SUBCASE("throws invalid_argument when y2 is replaced by text") {
			std::stringstream ss("33.4 17.1 -5.5 bts");
			CHECK_THROWS_AS(commandParser::parseLineGeometry(ss, x1, y1, x2, y2), std::invalid_argument);
		}
	}
	TEST_CASE("parseAreaStyle") {
		//начални стойности за тестване дали се презаписват правилно
		std::string fill = "none";
		std::string stroke = "none";
		double strokeWidth = 1.0;

		SUBCASE("parses successfully when stream is empty (keeps defaults)") {
			std::stringstream ss("");
			CHECK(commandParser::parseAreaStyle(ss, fill, stroke, strokeWidth));
			CHECK(fill == "none");
			CHECK(stroke == "none");
			CHECK(strokeWidth == doctest::Approx(1.0));
		}

		SUBCASE("parses successfully with only fill color") {
			std::stringstream ss("purple");
			CHECK(commandParser::parseAreaStyle(ss, fill, stroke, strokeWidth));
			CHECK(fill == "purple");
			CHECK(stroke == "none");
			CHECK(strokeWidth == doctest::Approx(1.0));
		}

		SUBCASE("parses successfully with fill and stroke colors") {
			std::stringstream ss("tan maroon");
			CHECK(commandParser::parseAreaStyle(ss, fill, stroke, strokeWidth));
			CHECK(fill == "tan");
			CHECK(stroke == "maroon");
			CHECK(strokeWidth == doctest::Approx(1.0));
		}

		SUBCASE("parses successfully with all three arguments (fill, stroke, stroke-width)") {
			std::stringstream ss("blue green 3.25");
			CHECK(commandParser::parseAreaStyle(ss, fill, stroke, strokeWidth));
			CHECK(fill == "blue");
			CHECK(stroke == "green");
			CHECK(strokeWidth == doctest::Approx(3.25));
		}

		SUBCASE("fails when stroke-width is a negative number") {
			std::stringstream ss("red white -4.8");
			CHECK_FALSE(commandParser::parseAreaStyle(ss, fill, stroke, strokeWidth));
		}

		SUBCASE("throws invalid_argument when stroke-width contains letters") {
			std::stringstream ss("pink black 5px");
			CHECK_THROWS_AS(commandParser::parseAreaStyle(ss, fill, stroke, strokeWidth), std::invalid_argument);
		}
	}
	TEST_CASE("parseLinearStyle") {
		std::string stroke = "none";
		double strokeWidth = 1.0;

		SUBCASE("parses successfully when stream is empty (keeps defaults)") {
			std::stringstream ss("");
			CHECK(commandParser::parseLinearStyle(ss, stroke, strokeWidth));
			CHECK(stroke == "none");
			CHECK(strokeWidth == doctest::Approx(1.0));
		}

		SUBCASE("parses successfully with only stroke color") {
			std::stringstream ss("white");
			CHECK(commandParser::parseLinearStyle(ss, stroke, strokeWidth));
			CHECK(stroke == "white");
			CHECK(strokeWidth == doctest::Approx(1.0));
		}

		SUBCASE("parses successfully with stroke color and stroke-width") {
			std::stringstream ss("orange 2.5");
			CHECK(commandParser::parseLinearStyle(ss, stroke, strokeWidth));
			CHECK(stroke == "orange");
			CHECK(strokeWidth == doctest::Approx(2.5));
		}

		SUBCASE("fails when stroke-width is a negative number") {
			std::stringstream ss("cyan -1.5");
			CHECK_FALSE(commandParser::parseLinearStyle(ss, stroke, strokeWidth));
		}

		SUBCASE("throws invalid_argument when stroke-width contains letters") {
			std::stringstream ss("yellow 3px");
			CHECK_THROWS_AS(commandParser::parseLinearStyle(ss, stroke, strokeWidth), std::invalid_argument);
		}
	}

}
TEST_SUITE("Geometry tests") {

	TEST_CASE("Point") {
		SUBCASE("withinRectangle") {
			Point p(17.7, 42.1);

			SUBCASE("returns true when point is inside the rectangle") {
				// x е в (10.2, 30.5), y е в (30.5, 60.9)
				CHECK(p.withinRectangle(10.2, 30.5, 20.3, 30.4));
			}

			SUBCASE("returns false when point is outside the rectangle") {
				CHECK_FALSE(p.withinRectangle(39.1, 15.8, 11.2, 8.4));
			}

			SUBCASE("returns true when point is exactly on the edge of the rectangle") {
				Point edgePoint(30.5, 42.1);
				// Точката е точно на дясната граница (x = 30.5)
				CHECK(edgePoint.withinRectangle(10.2, 30.5, 20.3, 30.4));
			}

			SUBCASE("works correctly with negative coordinates") {
				Point negPoint(-13.4, -27.9);
				// x е в (-20.1, -4.8), y е в (-40.5, -20.3)
				CHECK(negPoint.withinRectangle(-20.1, -40.5, 15.3, 20.2));
			}
		}

		SUBCASE("withinCircle") {
			Point p(3.3, 4.4);

			SUBCASE("returns true when point is strictly inside the circle") {
				CHECK(p.withinCircle(0.0, 0.0, 7.8));
			}

			SUBCASE("returns false when point is outside the circle") {
				CHECK_FALSE(p.withinCircle(-2.1, 5.4, 3.2));
			}

			SUBCASE("returns true when point is exactly on the contour of the circle") {
				// 3.3^2 + 4.4^2 = 5.5^2
				CHECK(p.withinCircle(0.0, 0.0, 5.5));
			}

			SUBCASE("works correctly with negative coordinates") {
				Point negPoint(-12.7, -9.1);
				CHECK(negPoint.withinCircle(-10.5, -7.2, 5.8));
			}
		}

		SUBCASE("translate") {

			SUBCASE("updates coordinates with mixed positive and negative values") {
				Point p(11.4, -7.9);
				p.translate(-3.2, 14.6);
				CHECK(p.x == doctest::Approx(8.2));
				CHECK(p.y == doctest::Approx(6.7));
			}

			SUBCASE("does nothing when translated by zero") {
				Point p(37.3, 89.1);
				p.translate(0.0, 0.0);
				CHECK(p.x == doctest::Approx(37.3));
				CHECK(p.y == doctest::Approx(89.1));
			}
		}
	}

	TEST_CASE("Line") {
		// линия с начална точка p1 и крайна p2
		Point p1(17.3, -8.1);
		Point p2(-14.6, 33.9);
		Line line(p1, p2, "black", 1.5);

		SUBCASE("withinRectangle") {

			SUBCASE("returns true when both start and end points are inside the rectangle") {
				// Правоъгълник, който обхваща и двете точки
				// x е в (-20.2, 25.2), y е в (-15.5, 44.6)
				CHECK(line.withinRectangle(-20.2, -15.5, 45.4, 60.1));
			}

			SUBCASE("returns false when only one point is inside") {
				// Правоъгълникът покрива само p2, но p1 е извън него по ос Y
				CHECK_FALSE(line.withinRectangle(-20.2, 10.4, 45.4, 60.1));
			}

			SUBCASE("returns false when both points are outside the rectangle") {
				CHECK_FALSE(line.withinRectangle(100.1, 100.2, 50.5, 50.5));
			}

			SUBCASE("returns true for a a point (start == end) inside the rectangle") {
				Line degenerateLine(Point(42.7, 19.3), Point(42.7, 19.3), "red", 2.2);
				CHECK(degenerateLine.withinRectangle(30.1, 10.5, 20.4, 20.8));
			}
		}

		SUBCASE("withinCircle") {

			SUBCASE("returns true when both points are inside the circle") {
				// Център (0.0, 10.5) с голям радиус, който покрива и двете точки
				CHECK(line.withinCircle(0.0, 10.5, 35.7));
			}

			SUBCASE("returns false when only one point is inside the circle") {
				// Радиусът е достатъчен за p1, но не стига до p2
				CHECK_FALSE(line.withinCircle(0.0, 10.5, 26.2));
			}

			SUBCASE("returns false when the line completely surrounds a smaller circle") {
				// Кръгът е между двете точки, но точките са извън него
				CHECK_FALSE(line.withinCircle(1.35, 12.9, 5.4));
			}
		}

		SUBCASE("translate") {

			SUBCASE("correctly updates coordinates of both points") {
				// Местене на линията с -11.2 по X и +5.4 по Y
				line.translate(-11.2, 5.4);

				// Новите координати:
				// p1 (6.1, -2.7)
				// p2 (-25.8, 39.3)

				// тестване с правоъгълник, който обхваща новите координати
				CHECK(line.withinRectangle(-25.9, -2.8, 32.1, 42.2));

				// проверка и със старите координати - там вече не трябва да има нищо
				CHECK_FALSE(line.withinRectangle(17.2, -8.2, 1.0, 1.0));
			}
		}
	}

	TEST_CASE("Rectangle") {
		// тест за създаване на правоъгълник
		Point topLeft(14.3, -5.7);
		class Rectangle rect(topLeft, 22.4, 11.8, "blue", "black", 1.0);

		SUBCASE("withinRectangle") {

			SUBCASE("returns true when fully inside the region") {
				// тест за регион, който обхваща изцяло фигурата
				CHECK(rect.withinRectangle(10.1, -10.5, 30.5, 20.2));
			}

			SUBCASE("returns false for partial overlap") {
				// тест за частично припокриване
				CHECK_FALSE(rect.withinRectangle(20.2, -10.5, 30.5, 20.2));
			}

			SUBCASE("returns false when the rectangle completely swallows the region") {
				// тест за фигура, която е по-голяма от търсения регион
				CHECK_FALSE(rect.withinRectangle(20.1, 0.5, 5.2, 3.4));
			}

			SUBCASE("returns true for a a point rectangle") {
				// тест за правоъгълник с нулева площ
				class Rectangle degenerate(Point(42.7, 19.3), 0.0, 0.0, "red", "none", 0.0);
				CHECK(degenerate.withinRectangle(30.1, 10.5, 20.4, 20.8));
			}
		}

		SUBCASE("withinCircle") {

			SUBCASE("returns true when all 4 corners are inside the circle") {
				// тест за кръг, който обхваща целия правоъгълник
				CHECK(rect.withinCircle(25.5, 0.2, 17.8));
			}

			SUBCASE("returns false when only some corners are inside") {
				// тест за частично припокриване с кръг
				CHECK_FALSE(rect.withinCircle(14.3, -5.7, 10.4));
			}

			SUBCASE("returns false when the rectangle swallows the circle") {
				// тест за кръг, който е по-малък и се намира вътре в правоъгълника
				CHECK_FALSE(rect.withinCircle(25.5, 0.2, 3.1));
			}
		}

		SUBCASE("translate") {

			SUBCASE("correctly updates the starting point of the rectangle") {
				// местене на фигурата
				rect.translate(-4.2, 9.1);

				// тест за новите координати
				CHECK(rect.withinRectangle(10.0, 3.3, 22.6, 12.0));

				// тест за отсъствие на старото място
				CHECK_FALSE(rect.withinRectangle(14.2, -5.8, 22.6, 12.0));
			}
		}
	}

	TEST_CASE("Circle") {
		// тест за създаване на кръг
		Point center(11.5, -3.2);
		Circle c(center, 15.4, "green", "black", 1.0);

		SUBCASE("withinRectangle function") {

			SUBCASE("returns true when fully inside the region") {
				// тест за регион, който обхваща изцяло фигурата
				// граници на кръга по X: (-3.9, 26.9), по Y: (-18.6, 12.2)
				CHECK(c.withinRectangle(-5.1, -19.5, 33.2, 35.8));
			}

			SUBCASE("returns false for partial overlap") {
				// тест за частично припокриване
				CHECK_FALSE(c.withinRectangle(10.1, -5.2, 33.2, 35.8));
			}

			SUBCASE("returns false when the circle completely swallows the region") {
				// тест за фигура, която е по-голяма от търсения регион
				CHECK_FALSE(c.withinRectangle(10.1, -4.2, 2.5, 2.5));
			}
		}

		SUBCASE("withinCircle function") {

			SUBCASE("returns true when fully inside the region circle") {
				// тест за по-голям кръг, който обхваща нашия
				CHECK(c.withinCircle(11.5, -3.2, 20.1));
			}

			SUBCASE("returns false for partial overlap") {
				// тест за частично припокриване с друг кръг
				CHECK_FALSE(c.withinCircle(25.5, -3.2, 25.0));
			}

			SUBCASE("returns false when the circle swallows the region circle") {
				// тест за по-малък кръг, който се намира вътре в нашия
				CHECK_FALSE(c.withinCircle(11.5, -3.2, 5.1));
			}
		}

		SUBCASE("translate function") {

			SUBCASE("correctly updates the center of the circle") {
				// местене на фигурата
				c.translate(-5.3, 8.4);

				// тест за новите координати (центърът вече е на 6.2, 5.2)
				CHECK(c.withinRectangle(-10.1, -11.5, 33.2, 35.8));

				// тест за отсъствие на старото място
				CHECK_FALSE(c.withinRectangle(-5.1, -19.5, 33.2, 35.8));
			}
		}
	}
}
TEST_SUITE("FigureList") {

	TEST_CASE("FigureList") {
		FigureList list;

		SUBCASE("getFigureType") {
			// тест при празен списък
			CHECK(list.getFigureType(1) == "");

			// добавяне на фигура
			list.create(new Circle(Point(14.2, -3.7), 5.1, "red", "none", 0.0));

			// тест за извън граници (0, отрицателен, по-голям от размера)
			CHECK(list.getFigureType(0) == "");
			CHECK(list.getFigureType(-3) == "");
			CHECK(list.getFigureType(2) == "");

			// тест за правилно връщане на типа
			CHECK(list.getFigureType(1) == "circle");
		}

		SUBCASE("erase") {
			// тест при празен списък
			CHECK_FALSE(list.erase(1));

			// добавяне на фигури
			list.create(new Circle(Point(1.1, 2.2), 3.3, "red", "none", 0.0));
			list.create(new class Rectangle(Point(-4.4, 5.5), 6.6, 7.7, "blue", "none", 0.0));
			list.create(new Line(Point(8.8, 9.9), Point(-1.1, -2.2), "green", 1.5));

			// тест за извън граници
			CHECK_FALSE(list.erase(0));
			CHECK_FALSE(list.erase(-5));
			CHECK_FALSE(list.erase(5));

			// тест за изтриване на първата фигура
			CHECK(list.erase(1));

			// тест за изместване - втората фигура вече е първа
			CHECK(list.getFigureType(1) == "rectangle");

			// тест за изтриване на последната фигура (в момента индекс 2)
			CHECK(list.erase(2));
			CHECK(list.getFigureType(2) == "");
		}

		SUBCASE("translate (with n)") {
			// добавяне на фигура
			list.create(new class Rectangle(Point(0.0, 0.0), 10.0, 10.0, "red", "none", 0.0));

			// тест за извън граници
			CHECK_FALSE(list.translate(0, 4.1, -2.2));
			CHECK_FALSE(list.translate(-2, 11.1, 7.2));
			CHECK_FALSE(list.translate(3, 9.3, 4.4));

			// тест за успешно изпълнение при валиден индекс
			CHECK(list.translate(1, 5.5, 3.3));
		}

		SUBCASE("translate (all figures)") {
			// тест при празен списък (трябва да мине без ефект и без да гърми)
			list.translate(17.3, -8.4);

			// добавяне на фигури
			list.create(new Circle(Point(0.0, 0.0), 5.0, "red", "none", 0.0));
			list.create(new Line(Point(0.0, 0.0), Point(1.0, 1.0), "blue", 1.0));

			// тест за общо местене (не връща bool, просто проверяваме дали се изпълнява без грешка)
			list.translate(-5.5, 12.2);
		}
		SUBCASE("create and clear functions") {
			// тест за създаване и правилно връщане на новия размер
			CHECK(list.create(new Circle(Point(1.2, 3.4), 5.6, "red", "none", 0.0)) == 1);
			CHECK(list.create(new Line(Point(0.0, 0.0), Point(1.1, 1.1), "blue", 1.0)) == 2);

			// тест за изчистване
			list.clear();
			CHECK(list.getFigureType(1) == "");
			CHECK_FALSE(list.erase(1)); // списъкът трябва да е напълно празен
		}

		SUBCASE("copy constructor and assignment operator") {
			list.create(new class Rectangle(Point(2.2, 3.3), 10.5, 5.5, "green", "none", 0.0));

			// тест за копиране
			FigureList copyList(list);
			CHECK(copyList.getFigureType(1) == "rectangle");

			// тест за дълбоко копиране (промяната в копието не трябва да засяга оригинала)
			copyList.erase(1);
			CHECK(list.getFigureType(1) == "rectangle");

			// тест за оператор за присвояване
			FigureList assignedList;
			assignedList = list;
			CHECK(assignedList.getFigureType(1) == "rectangle");
		}
	}
}