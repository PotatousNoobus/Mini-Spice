#ifndef VOLTAGESOURCE_H
#define VOLTAGESOURCE_H

#include <string>
#include <complex>
#include <stdexcept>
#include "Component.h"
using namespace std;

class VoltageSource : public Component {
private:
    double voltage;
    double frequency;

public:
    VoltageSource(string n, int a, int b, double v, double f = 0.0)
        : Component(n, a, b), voltage(v), frequency(f) {
        if (v <= 0) {
            throw invalid_argument("Voltage must be positive");
        }
    }

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
