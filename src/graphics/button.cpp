#include "../../inc/graphics/button.hpp"

list<Button> Button::buttons;

Button::Button(int x, int y, int w, int h, string text, std::function<void (Button*)> action) {
	this -> x = x;
	this -> y = y;
	this -> w = w;
	this -> h = h;
	this -> text = text;
	this -> action = action;
}

list<Button>::iterator Button::begin() {
	return buttons.begin();
}

list<Button>::iterator Button::end() {
	return buttons.end();
}

void Button::save() {
	buttons.push_back(*this);
}

void Button::activate() {
	cl -= 70;
	action(this);
}