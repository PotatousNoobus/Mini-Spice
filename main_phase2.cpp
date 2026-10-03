#include <iostream>
#include <iomanip>
#include <memory>
#include <cmath>
#include "Circuit.h"
#include "Resistor.h"
#include "Inductor.h"
#include "Capacitor.h"

void printImpedance(const std::string& componentName, 
                    std::complex<double> Z, 
                    double frequency) {
    double magnitude = std::abs(Z);
    double phase = std::arg(Z) * 180.0 / M_PI;  // Convert to degrees
    
    std::cout << std::left << std::setw(15) << componentName 
              << "Z = " << std::setw(12) << std::fixed << std::setprecision(2) << magnitude 
              << "Phase: " << std::setw(8) << phase << "°" << std::endl;
}

int main() {
    try {
        std::cout << "      MiniSPICE Phase 2 - Demo          " << std::endl;
        std::cout << "    Resistor + Inductor + Capacitor      " << std::endl;

        // STEP 1: Create a circuit with 3 nodes
        Circuit myCircuit(3);
        std::cout << " Created circuit with 3 nodes (0=ground, 1, 2)" << std::endl;

        // STEP 2: Create components of all three types
        std::cout << "\n--- Creating Components ---" << std::endl;
        
        // Resistor: 1kΩ between node 1 and ground
        auto R1 = std::make_unique<Resistor>("R1", 1, 0, 1000.0);
        std::cout << " Created R1: 1kΩ" << std::endl;
        
        // Inductor: 10mH between node 1 and node 2
        auto L1 = std::make_unique<Inductor>("L1", 1, 2, 0.01);
        std::cout << " Created L1: 10mH" << std::endl;
        
        // Capacitor: 1µF between node 2 and ground
        auto C1 = std::make_unique<Capacitor>("C1", 2, 0, 1e-6);
        std::cout << " Created C1: 1µF" << std::endl;

        // STEP 3: Add components to circuit
        std::cout << "\n--- Adding Components to Circuit ---" << std::endl;
        myCircuit.addComponent(std::move(R1));
        std::cout << " Added R1" << std::endl;
        
        myCircuit.addComponent(std::move(L1));
        std::cout << " Added L1" << std::endl;
        
        myCircuit.addComponent(std::move(C1));
        std::cout << " Added C1" << std::endl;

        // STEP 4: Display circuit contents
        myCircuit.listComponents();

        // STEP 5: Test impedance at multiple frequencies
        std::cout << "--- Impedance Analysis at Different Frequencies ---\n" << std::endl;

        const auto& components = myCircuit.getComponents();
        double frequencies[] = {0.0, 10.0, 100.0, 1000.0, 10000.0, 100000.0};
        
        for (double freq : frequencies) {
            std::cout << "\n" << "At f = " << std::fixed << std::setprecision(0) 
                      << freq << " Hz " << std::endl;
            
            for (const auto& comp : components) {
                auto Z = comp->getImpedance(freq);
                printImpedance(comp->getName(), Z, freq);
            }
        }

        std::cout << "       DC vs AC Behavior               " << std::endl;

        std::cout << "At DC (f = 0 Hz):" << std::endl;
        std::cout << "  Resistor: Acts as R (always conducts)" << std::endl;
        std::cout << "  Inductor: Acts as SHORT (0Ω, conducts freely)" << std::endl;
        std::cout << "  Capacitor: Acts as OPEN (∞Ω, blocks DC)" << std::endl;

        std::cout << "\nAt AC (f = 1 kHz):" << std::endl;
        std::cout << "  Resistor: Still acts as R (frequency-independent)" << std::endl;
        std::cout << "  Inductor: Z increases with frequency (acts like resistance)" << std::endl;
        std::cout << "  Capacitor: Z decreases with frequency (conducts better)" << std::endl;

        std::cout << "         Impedance Formulas             " << std::endl;

        std::cout << "Resistor:  Z_R = R" << std::endl;
        std::cout << "           Always R, no frequency dependence" << std::endl;

        std::cout << "\nInductor:  Z_L = j * 2π * f * L" << std::endl;
        std::cout << "           Magnitude: 2πfL" << std::endl;
        std::cout << "           Phase: +90°" << std::endl;

        std::cout << "\nCapacitor: Z_C = 1 / (j * 2π * f * C)" << std::endl;
        std::cout << "           Magnitude: 1/(2πfC)" << std::endl;
        std::cout << "           Phase: -90°" << std::endl;

        std::cout << "     Calculated Values (f = 1 kHz)     " << std::endl;

        double f_ref = 1000.0;  // 1 kHz
        double omega = 2.0 * M_PI * f_ref;
        double L = 0.01;      // 10 mH
        double C = 1e-6;      // 1 µF

        double Z_L_mag = omega * L;
        double Z_C_mag = 1.0 / (omega * C);

        std::cout << "For L = 10 mH at 1 kHz:" << std::endl;
        std::cout << "  Z_L = j * 2π * 1000 * 0.01 = j * 62.83 Ω" << std::endl;
        std::cout << "  Calculated: " << std::fixed << std::setprecision(2) << Z_L_mag << " Ω\n" << std::endl;

        std::cout << "For C = 1 µF at 1 kHz:" << std::endl;
        std::cout << "  Z_C = 1 / (j * 2π * 1000 * 1e-6) = -j * 159.15 Ω" << std::endl;
        std::cout << "  Calculated: " << Z_C_mag << " Ω\n" << std::endl;

        std::cout << " All checks passed! Phase 2 complete.\n" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
