#ifndef VOLTAGESOURCE_H
#define VOLTAGESOURCE_H
using namespace std;
#include "Component.h"

// ============================================
// VoltageSource Class
// ============================================
// An ideal voltage source has zero internal impedance
// It maintains a fixed voltage regardless of current
//
// DC Source (frequency = 0): e.g. a battery
// AC Source (frequency > 0): e.g. a signal generator
//
// Z = 0 always (ideal source assumption)

class VoltageSource : public Component {
private:
    double voltage;    // Voltage in Volts (V)
    double frequency;  // 0 for DC, >0 for AC

public:
    VoltageSource(string n, int a, int b, double v, double f = 0.0)
        : Component(n, a, b), voltage(v), frequency(f) {
        if (v <= 0) {
            throw invalid_argument("Voltage must be positive");
        }
    }

    // Ideal voltage source: Z = 0 always
    // It enforces voltage, not impedance
    complex<double> getImpedance(double freq) const override {
        return complex<double>(0.0, 0.0);
    }

    double getValue() const override {
        return voltage;
    }

    double getFrequency() const {
        return frequency;
    }

    bool isDC() const {
        return frequency == 0.0;
    }

    string getType() const override {
        return "V";
    }
};

#endif // VOLTAGESOURCE_H
