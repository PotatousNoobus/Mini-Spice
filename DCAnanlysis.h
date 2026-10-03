#ifndef DCANALYSIS_H
#define DCANALYSIS_H

#include "Circuit.h"
#include "SimulationResult.h"
#include <iostream>

// ============================================
// DCAnalysis Class
// ============================================
// Runs analysis at frequency = 0 (DC)
//
// At DC:
//   Resistor  → Z = R       (conducts normally)
//   Inductor  → Z = 0       (short circuit)
//   Capacitor → Z = ∞       (open circuit, blocks DC)
//   VSource   → Z = 0       (ideal source)

class DCAnalysis {
public:
    // Run DC analysis on a circuit
    // Returns a SimulationResult with all component impedances at f=0
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

            // Human readable DC behavior
            cout << "  " << cr.name << " (" << cr.type << "): ";
            if (cr.type == "R") cout << "Conducts normally, Z = " << cr.getMagnitude() << " Ω";
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
