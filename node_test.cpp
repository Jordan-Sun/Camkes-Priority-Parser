#include "node.h"
#include <iostream>

using namespace std;

int main()
{
    Node a("a", "box", 10);
    Node b("b", "box", 20);
    Node c("c", "box", 30);
    Node d("d", "box", 40);
    Node e("e", "circle");
    Node f("f", "circle");
    Node g("g", "circle");

    assert(e.add_requestor(&a));
    assert(!e.add_requestor(&a));
    assert(e.add_requestor(&b));
    assert(f.add_requestor(&c));
    assert(f.add_requestor(&d));
    assert(g.add_requestor(&e));
    assert(g.add_requestor(&f));

    cout << a << b << c << d << e << f << g;

    return 0;
}