#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "external/doctest.h"
#include "Point.h"

TEST_CASE("Point tests") {
	SUBCASE("Point inside rectangle") {
		Point p(5, 5);
		CHECK(p.withinRectangle(0, 0, 10, 10));
	}
	SUBCASE("Point outside rectangle") {
		Point p(20, 20);
		CHECK_FALSE(p.withinRectangle(0, 0, 10, 10));
	}
}