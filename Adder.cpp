// Adder.cpp

#include <iostream>
#include "Adder.h"

// -----
// Adder
// -----

Adder::Adder() :
    _value(0) {};

// ---
// add
// ---

void Adder::add(uint32_t x) {
    _value += x;
}

// -----
// clear
// -----

void Adder::clear() {
    _value = 0;
}

// -----------
// print_value
// -----------

void Adder::print_value(std::ostream& out) {
    using namespace std;
    out << "Current value: " << _value << endl;
}
