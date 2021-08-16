#include "../include/Card.hpp"

Card::Card()
: number(0), color("BLACK"), function("NONE")
{}
Card::Card(int number, std::string color)
: number(number), color(color), function("NONE")
{}
Card::Card(std::string function, std::string color)
: number(-1), color(color), function(function)
{}
