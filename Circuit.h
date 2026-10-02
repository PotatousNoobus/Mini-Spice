#ifndef CIRCUIT_H
#define CIRCUIT_H

#include "Component.h"
#include <vector>
#include <memory>
#include <iostream>

// ============================================
// Circuit Class
// ============================================
// A Circuit is a container that:
// - Holds all components
// - Manages nodes (connection points)
// - Provides access to components for simulation
// 
// Think of it like a breadboard where components are placed

class Circuit {
private:
    std::vector<std::unique_ptr<Component>> components;
    int numNodes;      // Total number of nodes in circuit
    int groundNode;    // Reference node (typically node 0)

public:
    // Constructor: specify how many nodes this circuit will have
    // Example: 3 nodes = nodes 0, 1, 2 (node 0 is ground)
    Circuit(int nodes) 
        : numNodes(nodes), groundNode(0) {
        if (nodes < 2) {
            throw std::invalid_argument("Circuit must have at least 2 nodes");
        }
    }

    // Add a component to the circuit
    // The component must connect between valid nodes (0 to numNodes-1)
    void addComponent(std::unique_ptr<Component> comp) {
        // Validate that component connects to valid nodes
        if (comp->getNodeA() < 0 || comp->getNodeA() >= numNodes ||
            comp->getNodeB() < 0 || comp->getNodeB() >= numNodes) {
            throw std::out_of_range("Component nodes out of circuit range");
        }
        
        // Add component to our list
        components.push_back(std::move(comp));
    }

    // Get total number of nodes
    int getNumNodes() const { return numNodes; }

    // Get the ground (reference) node
    int getGroundNode() const { return groundNode; }

    // Get number of components
    int getNumComponents() const { return components.size(); }

    // Get all components (used by simulator)
    const auto& getComponents() const { return components; }

    // Print all components (for debugging)
    void listComponents() const {
        std::cout << "\n=== Circuit Components ===" << std::endl;
        std::cout << "Total nodes: " << numNodes << ", Ground: " << groundNode << std::endl;
        std::cout << "Total components: " << components.size() << "\n" << std::endl;

        for (const auto& comp : components) {
            std::cout << "  " << comp->getName() 
                      << " (" << comp->getType() << ")"
                      << " | Nodes: " << comp->getNodeA() 
                      << " - " << comp->getNodeB()
                      << " | Value: " << comp->getValue() << std::endl;
        }
        std::cout << "\n==========================\n" << std::endl;
    }
};

#endif // CIRCUIT_H
