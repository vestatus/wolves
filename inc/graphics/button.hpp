#pragma once
#include <string>
#include <list>
#include <SFML/Graphics.hpp>
#include <functional>

using std::string;
using std::list;

class Button {
protected:
	static list<Button> buttons;
	std::function<void (Button*)> action = [](Button* btn){};
public:
	int x, y, h, w;
	string text;
	Button(int x, int y, int w, int h, string text, std::function<void (Button*)> action);
	void save();
	void activate();
	static list<Button>::iterator begin();
	static list<Button>::iterator end();
};