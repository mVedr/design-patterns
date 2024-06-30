#include <iostream>
using namespace std;

class Subject
{
public:
    virtual void Request() = 0;
};

class RealSubject : public Subject
{
public:
    void Request()
    {
        cout << "RealSubject: Handling Request\n";
    }
};

class Proxy : public Subject
{
private:
    RealSubject *real_subject_;
    bool CheckAccess()
    {
        cout << "Proxy: Check access prior before real request\n";
        return true;
    }
    void LogAccess()
    {
        cout << "Proxy: Logging time of req\n";
    }

public:
    Proxy(RealSubject *real_subject) : real_subject_(new RealSubject(*real_subject))
    {
    }

    ~Proxy()
    {
        delete real_subject_;
    }
    void Request()
    {
        if (this->CheckAccess())
        {
            this->real_subject_->Request();
            this->LogAccess();
        }
    }
};

void ClientCode(Subject &subject)
{
    // ...
    subject.Request();
    // ...
}

int main()
{
    cout << "Client: Executing the client code with a real subject:\n";
    RealSubject *real_subject = new RealSubject;
    ClientCode(*real_subject);
    cout << "\n";
    cout << "Client: Executing the same client code with a proxy:\n";
    Proxy *proxy = new Proxy(real_subject);
    ClientCode(*proxy);

    delete real_subject;
    delete proxy;
    return 0;
}