#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using std::vector;
using std::string;

class Logger { // This logger is seen as an alternative to debugging with std::cout and std::printf
			   // Multiple types of loggers may appear over time
protected:
    string fname; // name of the file in the logs folder in which the log will be written
public:
    virtual void log(string text, string tag) = 0;
};

class BufferedLogger : public Logger {
private:
    vector<string> buffer; // this buffer is used to avoid opening a file every time a message needs to be written
public:
    BufferedLogger(){};
    BufferedLogger(string fname);
    ~BufferedLogger(); // makes sure the buffer's contents are saved to disk when the logger is destroyed
    void log(string text, string tag) override;
    void flush(); // save the buffer's contents to the disk
};