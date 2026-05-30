#include "FigureList.h"
#include <iostream>

void FigureList::swap(FigureList& other) {
	std::swap(list, other.list);
}

FigureList::FigureList() = default;

FigureList::~FigureList() {
	for (Figure* figure : list) {
		delete figure;
	}
}

FigureList::FigureList(const FigureList& other) {
	for (Figure* figure : other.list) {
		list.push_back(figure->clone());
	}
}

FigureList& FigureList::operator=(const FigureList& other) {
	FigureList copy(other);
	swap(copy);
	return *this;
}

void FigureList::clear() {
	for (Figure* figure : list) {
		delete figure;
	}
	list.clear();
}

void FigureList::save(std::ostream& out) const {
	for (Figure* figure : list) {
		figure->save(out);
	}
}

std::string FigureList::getFigureType(int n) const {
	if (n <= 0 || n > list.size()) {
		return "";
	}
	return list[n - 1]->getType();
}

void FigureList::print() const {
	int n = 0;
	for(const Figure* figure : list) {
		std::cout << ++n << ". ";
		figure->print();
		std::cout << std::endl;
	}
	
}

std::size_t FigureList::create(Figure* newFigure) {
	list.push_back(newFigure);
	return list.size();
}

bool FigureList::erase(int n) {
	if (n <= 0 || n > list.size()) {
		return false;
	}
	std::size_t i = n - 1;
	delete list[i];
	list.erase(list.begin() + i);
	return true;

}

bool FigureList::translate(int n, double horizontal, double vertical) {
	if (n <= 0 || n > list.size()) {
		return false;
	}
	list[n - 1]->translate(horizontal, vertical);
	return true;
}

void FigureList::translate(double horizontal, double vertical) {
	for (Figure* figure : list) {
		figure->translate(horizontal, vertical);
	}
}

void FigureList::withinRectangle(double x, double y, double width, double height) {
	std::size_t n = 0;
	for (Figure* figure : list) {
		if (figure->withinRectangle(x, y, width, height)) {
			std::cout << ++n << ". ";
			figure->print();
			std::cout << std::endl;
		}
	}
	if (!n) {
		std::cout << "No figures are located within rectangle " << x << ' ' << y << ' ' << width << ' ' << height << std::endl;
	}
}

void FigureList::withinCircle(double cx, double cy, double r) {
	std::size_t n = 0;
	for (Figure* figure : list) {
		if (figure->withinCircle(cx, cy, r)) {
			std::cout << ++n << ". ";
			figure->print();
			std::cout << std::endl;
		}
	}
	if (!n) {
		std::cout << "No figures are located within circle " << cx << ' ' << cy << ' ' << r << std::endl;
	}
}