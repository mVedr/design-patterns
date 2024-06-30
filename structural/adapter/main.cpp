#include<iostream>
using namespace std;
// allows objects with incompatible interfaces to collaborate
class RoundPeg
{
    int radius_;

public:
    RoundPeg(){}
    RoundPeg(int r)
    {
        this->radius_ = r;
    }
    int getRadius()
    {
        return radius_;
    }
};

class RoundHole
{
    int radius_;

public:
    RoundHole(){}
    RoundHole(int r)
    {
        this->radius_ = r;
    }
    int getRadius()
    {
        return radius_;
    }
    bool fits(RoundPeg peg)
    {
        return radius_ <= peg.getRadius();
    }
};

class SquarePeg
{
    int width_;

public:
SquarePeg(){}
    SquarePeg(int w)
    {
        this->width_ = w;
    }
    int getWidth()
    {
        return width_;
    }
};

class SquarePegAdapter : public RoundPeg{
    SquarePeg peg_;
    public:
    SquarePegAdapter(){}
    SquarePegAdapter(SquarePeg peg){
        this->peg_ = peg;
    };
    int getRadius(){
        return peg_.getWidth()/2;
    }
};

int main(){
    RoundHole *hole = new RoundHole(5);
    RoundPeg rpeg = RoundPeg(5);
    cout<<hole->fits(rpeg)<<"\n";

    auto small_sqpeg = SquarePeg(5);
    auto large_sqpeg = SquarePeg(10);

    // hole->fits(small_sqpeg); WONT COMPILE obv.

    auto small_sqpeg_adapter = SquarePegAdapter(small_sqpeg);
    auto large_sqpeg_adapter = SquarePegAdapter(large_sqpeg);

    cout<<hole->fits(small_sqpeg_adapter)<<"\n";
    cout<<hole->fits(large_sqpeg_adapter)<<"\n";

    return 0;
}