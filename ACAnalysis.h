#ifndef ACANALYSIS_H
#define ACANALYSIS_H

#include <vector>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include "Circuit.h"
#include "SimulationResult.h"
using namespace std;

class ACAnalysis {
private:
    double startFreq;
    double endFreq;
    int numPoints;

public:
    ACAnalysis(double start, double end, int points = 10)
        : startFreq(start), endFreq(end), numPoints(points) {
        if (start <= 0 || end <= start) {
            throw invalid_argument("Invalid frequency range");
        }
    }

    vector<double> getFrequencyPoints() const {
        vector<double> freqs;
        double logStart = log10(startFreq);
        double logEnd   = log10(endFreq);
        double step     = (logEnd - logStart) / (numPoints - 1);

        for (int i = 0; i < numPoints; i++) {
            freqs.push_back(pow(10.0, logStart + i * step));
        }
        return freqs;
    }

    SimulationResult run(const Circuit& circuit) {
        cout << "\n[ACAnalysis] Running AC Sweep..." << endl;
        cout << "  Frequency range: " << startFreq << " Hz to "
             << endFreq << " Hz (" << numPoints << " points)" << endl;

        SimulationResult result("AC");
        const auto& components = circuit.getComponents();
        vector<double> freqs = getFrequencyPoints();

        for (double freq : freqs) {
            for (const auto& comp : components) {
                ComponentResult cr;
                cr.name      = comp->getName();
                cr.type      = comp->getType();
                cr.frequency = freq;
                cr.impedance = comp->getImpedance(freq);
                result.addResult(cr);
            }
        }

        cout << "[ACAnalysis] Done. "
             << freqs.size() << " frequency points analyzed." << endl;
        return result;
    }
};

#endif // ACANALYSIS_H
