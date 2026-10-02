#ifndef RESISTOR_H
#define RESISTOR_H

#include "Component.h"

class Resistor : public Component {
private:
    double resistance;  // Value in Ohms

public:
    Resistor(std::string n, int a, int b, double r) 
        : Component(n, a, b), resistance(r) {
        if (r <= 0) {
            throw std::invalid_argument("Resistance must be positive");
        }
    }

    std::complex<double> getImpedance(double frequency) const override {
        return std::complex<double>(resistance, 0.0);
    }

    double getValue() const override {
        return resistance;
    }

    std::string getType() const override {
        return "R";
    }
};

#endif // RESISTOR_H
