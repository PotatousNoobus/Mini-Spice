#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <complex>
#include <cmath>

// ============================================
// Component Base Class
// ============================================
// A Component is ANY electrical element that:
// - Has a name (for identification)
// - Connects between two nodes (nodeA and nodeB)
// - Can calculate its impedance at a given frequency

class Component {
protected:
    std::string name;
    int nodeA, nodeB;  // The two nodes this component connects

public:
    // Constructor: every component needs a name and two connection points
    Component(std::string n, int a, int b) 
        : name(n), nodeA(a), nodeB(b) {}
    
    // Virtual destructor for proper cleanup of derived classes
    virtual ~Component() = default;

    // CORE METHOD: Calculate impedance at a frequency
    // DC (freq=0): R stays R, L becomes 0, C becomes infinite
    // AC (freq>0): R stays R, L becomes jwL, C becomes 1/jwC
    virtual std::complex<double> getImpedance(double frequency) const = 0;

    // Return the component's base value (R in Ohms, L in Henry, C in Farad)
    virtual double getValue() const = 0;

    // Return component type as a string ("R", "L", "C", etc.)
    virtual std::string getType() const = 0;

    // Getters for node information
    int getNodeA() const { return nodeA; }
    int getNodeB() const { return nodeB; }
    std::string getName() const { return name; }
};

#endif // COMPONENT_H
