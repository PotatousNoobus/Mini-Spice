#ifndef COMPONENT_H
#define COMPONENT_H
using namespace std;

#include <string>
#include <complex>
#include <cmath>

class Component {
protected:
    string name;
    int nodeA, nodeB;  

public:
    Component(string n, int a, int b) 
        : name(n), nodeA(a), nodeB(b) {}
    
    virtual ~Component() = default;

    // CORE METHOD: Calculate impedance at a frequency
    // DC (freq=0): R stays R, L becomes 0, C becomes infinite
    // AC (freq>0): R stays R, L becomes jwL, C becomes 1/jwC
    virtual complex<double> getImpedance(double frequency) const = 0;

    virtual double getValue() const = 0;

    virtual string getType() const = 0;

    int getNodeA() const { return nodeA; }
    int getNodeB() const { return nodeB; }
    string getName() const { return name; }
};

#endif 
