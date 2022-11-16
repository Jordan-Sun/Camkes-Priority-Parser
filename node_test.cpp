#include "node.h"
#include <iostream>

using namespace std;

int main()
{
    Node a("a", 10);
    Node b("b", 20);
    Node c("c", 30);
    Node d("d", 40);
    Node e("e");
    Node f("f");
    Node g("g");

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