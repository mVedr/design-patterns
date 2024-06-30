#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class Prototype {
public:
    virtual ~Prototype() {}
    virtual Prototype* clone() const = 0;
    virtual void print() const = 0;
};

class ConcretePrototype1 : public Prototype {
private:
    string name;
    int id;
public:
    ConcretePrototype1(string name, int id) : name(name), id(id) {}

    // Copy constructor
    ConcretePrototype1(const ConcretePrototype1& other) : name(other.name), id(other.id) {}

    Prototype* clone() const override {
        return new ConcretePrototype1(*this);
    }

    void print() const override {
        cout << "ConcretePrototype1: [Name: " << name << ", ID: " << id << "]" << endl;
    }
};

class ConcretePrototype2 : public Prototype {
private:
    string type;
    double value;
public:
    ConcretePrototype2(string type, double value) : type(type), value(value) {}

    // Copy constructor
    ConcretePrototype2(const ConcretePrototype2& other) : type(other.type), value(other.value) {}

    Prototype* clone() const override {
        return new ConcretePrototype2(*this);
    }

    void print() const override {
        cout << "ConcretePrototype2: [Type: " << type << ", Value: " << value << "]" << endl;
    }
};

class PrototypeFactory {
private:
    unordered_map<string, Prototype*> prototypes;
public:
    PrototypeFactory() {
        prototypes["Type1"] = new ConcretePrototype1("Type1", 1);
        prototypes["Type2"] = new ConcretePrototype2("Type2", 2.0);
    }

    ~PrototypeFactory() {
        for (auto pair : prototypes) {
            delete pair.second;
        }
        prototypes.clear();
    }

    Prototype* createPrototype(const string& type) {
        return prototypes[type]->clone();
    }
};

int main() {
    PrototypeFactory* factory = new PrototypeFactory();

    Prototype* prototype1 = factory->createPrototype("Type1");
    prototype1->print();

    Prototype* prototype2 = factory->createPrototype("Type2");
    prototype2->print();

    delete prototype1;
    delete prototype2;
    delete factory;

    return 0;
}