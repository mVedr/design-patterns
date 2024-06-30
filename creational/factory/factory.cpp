#include <iostream>
using namespace std;

class Vehicle {
public:
    virtual ~Vehicle() {}

    virtual string Travel() = 0;
};

class Car : public Vehicle {
public:
    string Travel() {
        return "Car travels on road";
    }
};

class Boat : public Vehicle {
public:
    string Travel() {
        return "Boat travels on water";  
    }
};

class VehicleFactory {
public:
    virtual ~VehicleFactory() {}
    virtual Vehicle* ProduceVehicle() const = 0;

    void Info(){
        Vehicle* product = this->ProduceVehicle();
        cout<<"This factory created: "<<product->Travel().substr(0,4)<<endl;
        delete product;
    }
};

class CarFactory : public VehicleFactory {
public:
    Vehicle* ProduceVehicle() const {  
        return new Car();
    }
};

class BoatFactory : public VehicleFactory {
public:
    Vehicle* ProduceVehicle() const {
        return new Boat();
    }
};

int main() {
    VehicleFactory* carFactory = new CarFactory();
    carFactory->Info();
    Vehicle* car = carFactory->ProduceVehicle();
    cout << car->Travel() << endl;
    delete car;
    delete carFactory;

    VehicleFactory* boatFactory = new BoatFactory();
    boatFactory->Info();
    Vehicle* boat = boatFactory->ProduceVehicle();
    cout << boat->Travel() << endl;
    delete boat;
    delete boatFactory;

    return 0;
}
