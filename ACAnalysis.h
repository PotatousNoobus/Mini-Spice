#ifndef ACANALYSIS_H
#define ACANALYSIS_H

#include "Circuit.h"
#include "SimulationResult.h"
#include <vector>
#include <cmath>
#include <iostream>

// ============================================
// ACAnalysis Class
// ============================================
// Sweeps through a range of frequencies
// and records each component's impedance at each point
//
// This shows how the circuit behaves across the frequency spectrum
// e.g. at what frequency does a capacitor start conducting?

class ACAnalysis {
private:
    double startFreq;   // Starting frequency (Hz)
    double endFreq;     // Ending frequency (Hz)
    int numPoints;      // How many frequency points to sample

public:
    // Constructor
    ACAnalysis(double start, double end, int points = 10)
        : startFreq(start), endFreq(end), numPoints(points) {
        if (start <= 0 || end <= start) {
            throw invalid_argument("Invalid frequency range");
        }
    }

    // Generate logarithmically spaced frequency points
    // Log spacing is standard in electronics (decades: 1, 10, 100, 1k, 10k...)
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

    // Run AC sweep on circuit
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
