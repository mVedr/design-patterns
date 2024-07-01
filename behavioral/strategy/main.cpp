#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

class Strategy {
public:
    virtual ~Strategy() {}
    virtual string doAlgorithm(const string& data) const = 0;
};

class Context {
private:
    Strategy* strategy_;
public:
    explicit Context(Strategy* strategy = nullptr) : strategy_(strategy) {}

    void set_strategy(Strategy* strategy) {
        strategy_ = strategy;
    }

    void doSomeBusinessLogic() const {
        if (strategy_) {
            cout << "Context: Sorting data using the strategy (not sure how it'll do it)\n";
            string result = strategy_->doAlgorithm("aecbd");
            cout << result << "\n";
        } else {
            cout << "Context: Strategy isn't set\n";
        }
    }
};

class ConcreteStrategyA : public Strategy {
public:
    string doAlgorithm(const string& data) const {
        string result(data);
        sort(result.begin(), result.end());
        return result;
    }
};

class ConcreteStrategyB : public Strategy {
public:
    string doAlgorithm(const string& data) const {
        string result(data);
        sort(result.begin(), result.end(), greater<char>());
        return result;
    }
};

void clientCode() {
    ConcreteStrategyA strategyA;
    ConcreteStrategyB strategyB;
    
    Context context(&strategyA);
    cout << "Client: Strategy is set to normal sorting.\n";
    context.doSomeBusinessLogic();
    cout << "\n";
    
    cout << "Client: Strategy is set to reverse sorting.\n";
    context.set_strategy(&strategyB);
    context.doSomeBusinessLogic();
}

int main() {
    clientCode();
    return 0;
}
