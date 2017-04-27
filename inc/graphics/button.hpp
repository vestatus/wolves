#pragma once
#include <string>
#include <list>
#include <SFML/Graphics.hpp>

using std::string;
using std::list;

class Button {
protected:
	static list<Button> buttons;
public:
	int x, y, h, w;
	string text;
	Button(int x, int y, int w, int h, string text);
	void save();
	static list<Button>::iterator begin();
	static list<Button>::iterator end();
};