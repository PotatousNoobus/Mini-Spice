#ifndef CAPACITOR_H
#define CAPACITOR_H

#include "Component.h"

// ============================================
// Capacitor Class
// ============================================
// A capacitor's impedance depends on frequency
// Z_C = 1 / (j * ω * C)  where ω = 2πf
// Which simplifies to: Z_C = -j / (ω * C)
//
// DC (f = 0):  Z = ∞ Ω (open circuit - blocks DC)
// AC (f > 0):  Z = 1/(2πfC) Ω (acts as resistance that decreases with frequency)
//
// Physical insight: Capacitors oppose changes in voltage
// At DC, voltage is constant, so they block current (open circuit)
// At AC, voltage is always changing, so they conduct (lower impedance at higher frequencies)

class Capacitor : public Component {
private:
    double capacitance;  // Value in Farad (F)

public:
    // Constructor: name, nodeA, nodeB, capacitance value
    Capacitor(std::string n, int a, int b, double c) 
        : Component(n, a, b), capacitance(c) {
        if (c <= 0) {
            throw std::invalid_argument("Capacitance must be positive");
        }
    }

    // Capacitor impedance = 1 / (j * ω * C) = -j / (ω * C)
    // Real part = 0
    // Imaginary part = -1 / (2πfC) (negative, decreases in magnitude with frequency)
    std::complex<double> getImpedance(double frequency) const override {
        // Z_C = 1 / (j * ω * C)
        // ω = 2π * f
        // For j in denominator: 1/j = -j
        // So Z_C = -j / (ω * C) = -j / (2πfC)
        
        if (frequency == 0.0) {
            // At DC: capacitor acts as open circuit (infinite impedance)
            // We can't represent infinity, so return a very large value
            // In practice, DC analysis would skip capacitors or handle them specially
            return std::complex<double>(0.0, 1e15);  // Effectively infinite
        }
        
        double omega = 2.0 * M_PI * frequency;
        double imaginaryPart = -1.0 / (omega * capacitance);
        
        return std::complex<double>(0.0, imaginaryPart);
    }

    // Return the capacitance value
    double getValue() const override {
        return capacitance;
    }

    // Identifier for this component type
    std::string getType() const override {
        return "C";
    }
};

#endif // CAPACITOR_H
