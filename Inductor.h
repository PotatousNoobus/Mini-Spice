#ifndef INDUCTOR_H
#define INDUCTOR_H
using namespace std;
#include "Component.h"

class Inductor : public Component {
private:
    double inductance;  

public:
    Inductor(string n, int a, int b, double l) : Component(n, a, b), inductance(l) {
        if (l <= 0) {
            throw invalid_argument("Inductance must be positive");
        }
    }

    // Inductor impedance = j * ω * L
    // Real part = 0
    // Imaginary part = 2πfL (increases with frequency)
    complex<double> getImpedance(double frequency) const override {
        // Z_L = j * ω * L
        // ω = 2π * f
        // Imaginary part: 2 * π * f * L
        // Real part: 0
        
        if (frequency == 0.0) {
            // At DC: inductor acts as short circuit (0 impedance)
            return complex<double>(0.0, 0.0);
        }
        
        double omega = 2.0 * M_PI * frequency;
        double imaginaryPart = omega * inductance;
        
        return complex<double>(0.0, imaginaryPart);
    }

    // Return the inductance value
    double getValue() const override {
        return inductance;
    }

    // Identifier for this component type
    string getType() const override {
        return "L";
    }
};

#endif 
