#include <iostream>
#include <memory>
#include "Circuit.h"
#include "Resistor.h"
#include "Inductor.h"
#include "Capacitor.h"
#include "VoltageSource.h"
#include "DCAnalysis.h"
#include "ACAnalysis.h"
#include "SimulationResult.h"

int main() {
    try {
        std::cout << "========================================" << std::endl;
        std::cout << "        MiniSPICE - Full Demo           " << std::endl;
        std::cout << "========================================" << std::endl;

        // Build the Circuit
        // Simple RLC circuit:
        //   V1 (5V DC source) between node 1 and ground
        //   R1 (1kΩ)          between node 1 and node 2
        //   L1 (10mH)         between node 2 and node 3
        //   C1 (1µF)          between node 3 and ground

        Circuit myCircuit(4);  // 4 nodes: 0(ground), 1, 2, 3

        myCircuit.addComponent(std::make_unique<VoltageSource>("V1", 1, 0, 5.0));
        myCircuit.addComponent(std::make_unique<Resistor>("R1", 1, 2, 1000.0));
        myCircuit.addComponent(std::make_unique<Inductor>("L1", 2, 3, 0.01));
        myCircuit.addComponent(std::make_unique<Capacitor>("C1", 3, 0, 1e-6));

        myCircuit.listComponents();

        // DC Analysis
        DCAnalysis dc;
        SimulationResult dcResult = dc.run(myCircuit);
        dcResult.printResults();

        // AC Analysis (1Hz to 100kHz, 20 points)
        ACAnalysis ac(1.0, 100000.0, 20);
        SimulationResult acResult = ac.run(myCircuit);
        acResult.printResults();

    } catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
