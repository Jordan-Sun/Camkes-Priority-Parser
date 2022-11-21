#include "node.h"
#include <iostream>

using namespace std;

int main()
{
    auto a = make_shared<Node>("a", "box", 10);
    auto b = make_shared<Node>("b", "box", 20);
    auto c = make_shared<Node>("c", "box", 30);
    auto d = make_shared<Node>("d", "box", 40);
    auto e = make_shared<Node>("e", "circle");
    auto f = make_shared<Node>("f", "circle");
    auto g = make_shared<Node>("g", "circle");

    assert(e->add_requestor(a));
    assert(!e->add_requestor(a));
    assert(e->add_requestor(b));
    assert(f->add_requestor(c));
    assert(f->add_requestor(d));
    assert(g->add_requestor(e));
    assert(g->add_requestor(f));

    cout << a << b << c << d << e << f << g;

    return 0;
}