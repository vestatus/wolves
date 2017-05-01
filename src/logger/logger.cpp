#include "../../inc/logger/logger.hpp"

BufferedLogger::BufferedLogger(string fname) {
    this->fname = fname;
    std::fstream stream;
    stream.open("logs/" + fname, std::ios_base::out);
    stream.close();
}

BufferedLogger::~BufferedLogger() {
    flush();
}

void BufferedLogger::log(string text, string tag) {
    buffer.push_back("[ " + tag + " ]: " + text);
    flush();
}


void BufferedLogger::flush() {
    std::fstream stream;
    stream.open("logs/" + fname, std::ios_base::out | std::fstream::app);

    for(vector<string>::iterator it=buffer.begin(); it != buffer.end(); it++) {
        stream << *it << "\n";
    }
    stream.close();
    buffer.clear();
}