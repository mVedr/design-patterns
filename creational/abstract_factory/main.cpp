#include <iostream>
using namespace std;

class Button
{
public:
    virtual ~Button() {}
    virtual void paint() = 0;
};

class WinButton : public Button
{
public:
    void paint()
    {
        cout << "Windows button..." << endl;
    }
};

class MacButton : public Button
{
public:
    void paint()
    {
        cout << "Mac button..." << endl;
    }
};

class Checkbox
{
public:
    virtual void paint() = 0;
};

class WinCheckbox : public Checkbox
{
public:
    void paint()
    {
        cout << "Window checkbox..." << endl;
    }
};

class MacCheckbox : public Checkbox
{
public:
    void paint()
    {
        cout << "Mac checkbox..." << endl;
    }
};

class GUIFactory
{
public:
    virtual ~GUIFactory() {}
    virtual Button *createButton() = 0;
    virtual Checkbox *createCheckBox() = 0;
};

class WinFactory : public GUIFactory
{
public:
    Button *createButton()
    {
        return new WinButton();
    }
    Checkbox *createCheckBox()
    {
        return new WinCheckbox();
    }
};

class MacFactory : public GUIFactory
{
public:
    Button *createButton()
    {
        return new MacButton();
    }
    Checkbox *createCheckBox()
    {
        return new MacCheckbox();
    }
};

class Appication
{
private:
    GUIFactory *factory;
    Button *button;
    Checkbox *checkbox;

public:
    Appication(GUIFactory *fac)
    {
        this->factory = fac;
    }
    void createUI()
    {
        this->button = factory->createButton();
        this->checkbox = factory->createCheckBox();
    }
    void paint()
    {
        button->paint();
        checkbox->paint();
    }
};

int main()
{
    string os; cin>>os;
    GUIFactory* factory = nullptr;

    if(os=="win"){
        factory = new WinFactory();
    }else if(os=="mac"){
        factory = new MacFactory();
    }else{
        cout<<"This OS is not supported."<<endl;
        return 0;
    }

    Appication* app = new Appication(factory);
    app->createUI();
    app->paint();
    return 0;
}