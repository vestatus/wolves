#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using std::vector;
using std::string;

class Logger {
protected:
    string fname;
public:
    virtual void log(string text, string tag) = 0;
};

class BufferedLogger : public Logger {
private:
    vector<string> buffer;
public:
    BufferedLogger(){};
    BufferedLogger(string fname);
    ~BufferedLogger();
    void log(string text, string tag) override;
    void flush();
};