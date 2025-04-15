#include <iostream>
#include <cmath>

// Constants
const double EPSILON_0 = 8.85e-12; // Vacuum permittivity
const double MU_0 = 4 * M_PI * 1e-7; // Vacuum permeability

// Base class for field vectors
class Field {
protected:
    double value[3]; // x, y, z components

public:
    Field() { value[0] = value[1] = value[2] = 0.0; }
    Field(double x, double y, double z) {
        value[0] = x;
        value[1] = y;
        value[2] = z;
    }

    void printMagnitude() const {
        std::cout << "Components: (" << value[0] << ", " << value[1] << ", " << value[2] << ")\n";
    }
};

// Electric field class derived from Field
class ElectricField : public Field {
private:
    double calculatedE; // Holds computed electric field

public:
    ElectricField() : Field(), calculatedE(0.0) {}
    ElectricField(double x, double y, double z) : Field(x, y, z), calculatedE(0.0) {}
    ElectricField(const ElectricField &e) : Field(e), calculatedE(e.calculatedE) {}

    void calculateElectricField(double Q, double r) {
        calculatedE = Q / (4 * M_PI * r * r * EPSILON_0);
    }

    ElectricField operator+(const ElectricField& other) {
        return ElectricField(value[0] + other.value[0], value[1] + other.value[1], value[2] + other.value[2]);
    }

    friend std::ostream& operator<<(std::ostream& out, const ElectricField& e) {
        out << "E-Field: (" << e.value[0] << ", " << e.value[1] << ", " << e.value[2] << ")";
        return out;
    }
};

// Magnetic field class derived from Field
class MagneticField : public Field {
private:
    double calculatedB; // Holds computed magnetic field

public:
    MagneticField() : Field(), calculatedB(0.0) {}
    MagneticField(double x, double y, double z) : Field(x, y, z), calculatedB(0.0) {}
    MagneticField(const MagneticField &b) : Field(b), calculatedB(b.calculatedB) {}

    void calculateMagneticField(double I, double r) {
        calculatedB = (MU_0 * I) / (2 * M_PI * r);
    }

    MagneticField operator+(const MagneticField& other) {
        return MagneticField(value[0] + other.value[0], value[1] + other.value[1], value[2] + other.value[2]);
    }

    friend std::ostream& operator<<(std::ostream& out, const MagneticField& b) {
        out << "B-Field: (" << b.value[0] << ", " << b.value[1] << ", " << b.value[2] << ")";
        return out;
    }
};

int main() {
    // Initial electric and magnetic fields
    ElectricField e1(0, 1e5, 1e3), e2(1e4, 2e5, 3e3);
    MagneticField b1(0, 2, 1), b2(3, 1, 4);

    std::cout << "Initial Fields:\n";
    e1.printMagnitude();
    b1.printMagnitude();

    // Calculate E using Gauss' Law
    double Q = 1e-6; // charge in Coulombs
    double r = 0.1;  // distance in meters
    e1.calculateElectricField(Q, r);
    std::cout << "\nE at r = " << r << ": " << e1 << "\n";

    // Calculate B using Ampere's Law
    double I = 10; // current in Amperes
    b1.calculateMagneticField(I, r);
    std::cout << "B at r = " << r << ": " << b1 << "\n";

    // Demonstrate operator overload
    ElectricField e3 = e1 + e2;
    MagneticField b3 = b1 + b2;

    std::cout << "\nSummed Fields:\n";
    std::cout << e3 << "\n";
    std::cout << b3 << "\n";

    return 0;
}
