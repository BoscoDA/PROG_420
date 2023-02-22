#include "Include/ll.h"

//debug with: g++ -I Include/ main.cpp -g -fsanitize=address  -o app

int main()
{
    Node<int> *head = new Node<int>(1);
    append(&head, 2);
    append(&head, 3);
    append(&head, 4);

    ///A LOT OF STUFF HAPPENS HERE

    //if you just delete you will leave a dangling pointer DANGEROUS
    delete head;
    // to avoid dangling pointer...
    head = nullptr;

    // A LOT MORE HAPPENS

    print(&head);
}
