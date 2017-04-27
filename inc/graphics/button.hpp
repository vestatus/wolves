#pragma once
#include <string>
#include <list>
#include <SFML/Graphics.hpp>
#include <functional>

using std::string;
using std::list;

typedef std::function<void ()> Action;

class Button {
protected:
	static list<Button> buttons;
public:
	int x, y, h, w;
	string text;
	Button(int x, int y, int w, int h, string text, Action action);
	Action activate = [](){};
	void save();
	static list<Button>::iterator begin();
	static list<Button>::iterator end();
};