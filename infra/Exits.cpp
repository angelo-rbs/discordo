#ifndef EXITS_CPP
#define EXITS_CPP

#include <exception>

struct quit_exit : public std::exception {
    std::string msg;
    quit_exit(std::string msg) : msg(msg) {}
};

struct early_exit : public std::exception {
    std::string msg;
    early_exit(std::string msg) : msg(msg) {}
};

#endif