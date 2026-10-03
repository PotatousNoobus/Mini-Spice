#ifndef SIMULATIONRESULT_H
#define SIMULATIONRESULT_H

#include <vector>
#include <string>
#include <complex>
#include <iostream>
#include <iomanip>

// ============================================
// SimulationResult Class
// ============================================
// Stores the result of one frequency point analysis
// Each result holds:
//   - The frequency
//   - Component name
//   - Its impedance at that frequency (magnitude + phase)

struct ComponentResult {
    string name;
    string type;
    double frequency;
    complex<double> impedance;

    double getMagnitude() const {
        return abs(impedance);
    }

    double getPhase() const {
        return arg(impedance) * 180.0 / M_PI;  // in degrees
    }
};

// ============================================
// SimulationResult Class
// ============================================
// Holds ALL results across ALL frequencies
// for a complete analysis run

class SimulationResult {
private:
    vector<ComponentResult> results;
    string analysisType;  // "DC" or "AC"

public:
    SimulationResult(string type) : analysisType(type) {}

    void addResult(ComponentResult r) {
        results.push_back(r);
    }

    const vector<ComponentResult>& getResults() const {
        return results;
    }

    string getAnalysisType() const {
        return analysisType;
    }

    // Print results to console in a clean table
    void printResults() const {
        cout << "\n========================================" << endl;
        cout << "   " << analysisType << " Analysis Results" << endl;
        cout << "========================================" << endl;
        cout << left
             << setw(10) << "Component"
             << setw(8)  << "Type"
             << setw(14) << "Freq (Hz)"
             << setw(16) << "Magnitude (Ω)"
             << setw(12) << "Phase (°)"
             << endl;
        cout << string(60, '-') << endl;

        for (const auto& r : results) {
            cout << left
                 << setw(10) << r.name
                 << setw(8)  << r.type
                 << setw(14) << fixed << setprecision(2) << r.frequency
                 << setw(16) << r.getMagnitude()
                 << setw(12) << r.getPhase()
                 << endl;
        }
        cout << "========================================\n" << endl;
    }
};

#endif // SIMULATIONRESULT_H
