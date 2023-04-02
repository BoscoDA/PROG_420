#include<vector>
#include<iostream>
#include <algorithm>

//Test

// template<class T>
// struct Node{
//     T data;
//     Node* next;

//     Node(T data){
//         this->data = data;
//         this->next = nullptr;
//     }
    
//     Node * append(T data){
//         Node *node = new Node<T>(data);
//         this->next = node;
//         return node;
//     }

//     Node operator+(Node<T>& next){
//         this->next = *next;
//         return next;
//     }
// };
template<class T>
bool greater_than(const T& lhs, const T& rhs){
    return lhs > rhs;
}

struct Foo {
    int x;

    Foo(int x){this -> x = x;}

    bool operator >(const Foo& rhs){return this->x > rhs.x;}
    bool operator <(const Foo& rhs){return this->x < rhs.x;}
    bool operator ==(const Foo& rhs){return this->x == rhs.x;}

};

int main(){
    // Node * node = new Node<int>(1);

    // node->append(2)->append(3)->append(4);

    // (*node)+ *(new Node<int>(1));

    std::vector<Foo> foos = {Foo(1),Foo(2),Foo(3)};

    auto r = greater_than<Foo>(Foo(1), Foo(2));

    //with operator overload with can omit the lamda function
    //std::sort(foos.begin(), foos.end(), [](const Foo& lhs, const Foo& rhs) => bool { return lhs.x > rhs.x});
    auto x = Foo(1);
    auto y = Foo(2);

    if(x>y){

    }
    std::sort(foos.begin(), foos.end());
}