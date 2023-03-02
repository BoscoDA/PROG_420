#include <string>
#include <iostream>
#include <vector>

struct Point{
private:
    int x, y;
public:
    Point(int x, int y){
        this->x = x;
        this->y = y;
    }

    Point(const Point &p1){
        this->x = p1.x;
        this->y = p1.y;
        std::cout << "COPIED" << std::endl;
    }

    void print(){
        std::cout<<this->x<< "x" << this-> y << std::endl;
    }
};

void foo(std::string s){
    s.append("OOOPS");
}

void bar(Point& p){
    //do something with p
}

int main(){
//    auto origin = std::string("Hello World");
//    std::cout << origin << std::endl;
//    foo(origin);
//    foo(origin);
//    foo(origin);
//    std::cout << origin << std::endl;

    Point p = Point(1,2);

    std::cout << sizeof(p) << std::endl;
    std::cout << sizeof(long) << std::endl;
    std::cout << sizeof(&p) << std::endl;

    std::vector<Point *> points;
    points.push_back(new Point(1,2));
    points.push_back(new Point(1,2));
    points.push_back(new Point(1,2));
    points.push_back(new Point(1,2));
    points.push_back(new Point(1,2));
    points.push_back(new Point(1,2));
    points.push_back(new Point(1,2));
    points.push_back(new Point(1,2));

    for(auto a : points){
        a->print();
    }
    bar(p);
    return 0;
}