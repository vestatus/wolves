#pragma once
#include <string>
#include <SFML/Graphics.hpp>

using std::string;

class Button {
public:
	int x, y, h, w;
	string text;
	Button(int x, int y, int w, int h, string text) {
		this -> x = x;
		this -> y = y;
		this -> w = w;
		this -> h = h;
		this -> text = text;
	}
};