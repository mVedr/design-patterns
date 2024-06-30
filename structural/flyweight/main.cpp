#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

// Shared (Intrinsic) State
class TreeType {
public:
    string name_;
    string color_;
    string texture_;

    TreeType(const string &name, const string &color, const string &texture)
        : name_(name), color_(color), texture_(texture) {}

    void Display() const {
        cout << "TreeType: " << name_ << ", Color: " << color_ << ", Texture: " << texture_ << endl;
    }
};

// Unique (Extrinsic) State
class Tree {
private:
    TreeType *type_;
    int x_;
    int y_;

public:
    Tree(int x, int y, TreeType *type) : x_(x), y_(y), type_(type) {}

    void Display() const {
        cout << "Tree at (" << x_ << ", " << y_ << ") with ";
        type_->Display();
    }
};

// Flyweight Factory
class TreeFactory {
private:
    unordered_map<string, TreeType *> treeTypes_;

    string GetKey(const string &name, const string &color, const string &texture) {
        return name + "_" + color + "_" + texture;
    }

public:
    TreeType *GetTreeType(const string &name, const string &color, const string &texture) {
        string key = GetKey(name, color, texture);
        if (treeTypes_.find(key) == treeTypes_.end()) {
            cout << "Creating new tree type: " << key << endl;
            treeTypes_[key] = new TreeType(name, color, texture);
        } else {
            cout << "Reusing existing tree type: " << key << endl;
        }
        return treeTypes_[key];
    }

    ~TreeFactory() {
        for (auto pair : treeTypes_) {
            delete pair.second;
        }
    }
};

int main() {
    TreeFactory *factory = new TreeFactory();

    Tree *tree1 = new Tree(10, 20, factory->GetTreeType("Oak", "Green", "Rough"));
    Tree *tree2 = new Tree(30, 40, factory->GetTreeType("Pine", "Green", "Smooth"));
    Tree *tree3 = new Tree(50, 60, factory->GetTreeType("Oak", "Green", "Rough"));
    Tree *tree4 = new Tree(70, 80, factory->GetTreeType("Birch", "White", "Smooth"));

    tree1->Display();
    tree2->Display();
    tree3->Display();
    tree4->Display();

    delete tree1;
    delete tree2;
    delete tree3;
    delete tree4;
    delete factory;

    return 0;
}
