#ifndef DCANALYSIS_H
#define DCANALYSIS_H

#include <iostream>
#include "Circuit.h"
#include "SimulationResult.h"
using namespace std;

class DCAnalysis {
public:
    SimulationResult run(const Circuit& circuit) {
        cout << "\n[DCAnalysis] Running DC Analysis (f = 0 Hz)..." << endl;

        SimulationResult result("DC");
        const auto& components = circuit.getComponents();

        for (const auto& comp : components) {
            ComponentResult cr;
            cr.name      = comp->getName();
            cr.type      = comp->getType();
            cr.frequency = 0.0;
            cr.impedance = comp->getImpedance(0.0);

            result.addResult(cr);

            cout << "  " << cr.name << " (" << cr.type << "): ";
            if (cr.type == "R")      cout << "Conducts normally, Z = " << cr.getMagnitude() << " Ω";
            else if (cr.type == "L") cout << "Short circuit, Z = " << cr.getMagnitude() << " Ω";
            else if (cr.type == "C") cout << "Open circuit (blocks DC), Z = ∞";
            else if (cr.type == "V") cout << "Ideal source, Z = " << cr.getMagnitude() << " Ω";
            cout << endl;
        }

        cout << "[DCAnalysis] Done." << endl;
        return result;
    }
};

#endif // DCANALYSIS_H
