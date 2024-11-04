#include <iostream>
#include <vector>
#include <memory>

using namespace std;

struct Input {
    int value;

private:
    explicit Input(int val) : value(val) {}

public:
    static Input& getTrue() {
        static Input trueInstance(1);
        return trueInstance;
    }

    static Input& getFalse() {
        static Input falseInstance(0);
        return falseInstance;
    }
};


class Gate {
public:
    virtual int Evaluate(int a, int b) const = 0;
    virtual ~Gate() {}
};

class ANDGate : public Gate {
public:
    int Evaluate(int a, int b) const override {
        return a & b;
    }
};

class ORGate : public Gate {
public:
    int Evaluate(int a, int b) const override {
        return a | b;
    }
};

class XORGate : public Gate {
public:
    int Evaluate(int a, int b) const override {
        return a ^ b;
    }
};

class XNORGate : public Gate {
public:
    int Evaluate(int a, int b) const override {
        return !(a ^ b);
    }
};

class NORGate : public Gate {
public:
    int Evaluate(int a, int b) const override {
        return !(a | b);
    }
};

class NANDGate : public Gate {
public:
    int Evaluate(int a, int b) const override {
        return !(a & b);
    }
};


class Circuit {
private:
    vector<shared_ptr<Gate> > gates;

public:
    
    void addGate(shared_ptr<Gate> gate) {
        gates.push_back(gate);
    }

    
    int Evaluate(const vector<Input>& inputs) const {
        if (gates.empty() || inputs.size() < 2) {
            cerr << "Error: Insufficient gates or inputs provided." << endl;
            return -1;  
        }

        
        int result = inputs[0].value;

        for (size_t i = 0; i < gates.size() && i + 1 < inputs.size(); ++i) {
            result = gates[i]->Evaluate(result, inputs[i + 1].value);
        }

        return result;
    }
};


int main() {
    
    Input& T = Input::getTrue();
    Input& F = Input::getFalse();

    
    Circuit circuit;
    circuit.addGate(make_shared<ANDGate>());
    circuit.addGate(make_shared<ORGate>());
    circuit.addGate(make_shared<XORGate>());

    vector<Input> inputs1 = {T, T, F, T};
    int output1 = circuit.Evaluate(inputs1);
    cout << "Output of the circuit with inputs [T, T, F, T] and gates [AND, OR, XOR]: " << output1 << endl;

    Circuit circuit2;
    circuit2.addGate(make_shared<NANDGate>());
    circuit2.addGate(make_shared<NORGate>());
    circuit2.addGate(make_shared<XNORGate>());

    vector<Input> inputs2 = {F, T, T, F};
    int output2 = circuit2.Evaluate(inputs2);
    cout << "Output of the circuit with inputs [F, T, T, F] and gates [NAND, NOR, XNOR]: " << output2 << endl;

    Circuit circuit3;
    circuit3.addGate(make_shared<ANDGate>());
    circuit3.addGate(make_shared<NANDGate>());
    circuit3.addGate(make_shared<ORGate>());

    vector<Input> inputs3 = {T, F, T, T};
    int output3 = circuit3.Evaluate(inputs3);
    cout << "Output of the circuit with inputs [T, F, T, T] and gates [AND, NAND, OR]: " << output3 << endl;

    return 0;
}