#include <iostream>
#include <mutex>
#include <thread>
using namespace std;

class Singleton{
    protected:
    static mutex mutex_;
    static Singleton* singleton_;

    string value_;

    Singleton(string value){
        this->value_ = value;
    }

    ~Singleton() {}
    
    public:
    //Should not be cloneable
    Singleton(Singleton &other) = delete;
    //Should not be assignable
    void operator=(const Singleton &) = delete;

    static Singleton* GetInstance(string value);

    string value() const{
        return value_;
    }

};

Singleton* Singleton::singleton_ = nullptr;
mutex Singleton::mutex_;

Singleton* Singleton::GetInstance(string value){
    lock_guard<mutex> lock(mutex_);
    if(singleton_==nullptr){
        singleton_ = new Singleton(value);
    }
    return singleton_;
}

void ThreadFoo(){
    this_thread::sleep_for(chrono::milliseconds(1000));
    Singleton* singleton =  Singleton::GetInstance("Foo");
    cout<<singleton->value()<<"\n";
}

void ThreadBar(){
    this_thread::sleep_for(chrono::milliseconds(1000));
    Singleton* singleton =  Singleton::GetInstance("Bar");
    cout<<singleton->value()<<"\n";
}

int main(){
    thread t1(ThreadFoo);
    thread t2(ThreadBar);
    t1.join();
    t2.join();
    return 0;
}