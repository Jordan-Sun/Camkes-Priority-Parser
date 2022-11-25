#include "node.h"
#include <iostream>

using namespace std;

int main()
{
    auto a = make_shared<Node>("a", "box", 10, Protocol::UNSET);
    auto b = make_shared<Node>("b", "box", 20, Protocol::UNSET);
    auto c = make_shared<Node>("c", "box", 30, Protocol::UNSET);
    auto d = make_shared<Node>("d", "box", 40, Protocol::UNSET);
    auto e = make_shared<Node>("e", "circle", NONE, Protocol::PIP);
    auto f = make_shared<Node>("f", "circle", NONE, Protocol::PROP);
    auto g = make_shared<Node>("g", "circle", NONE, Protocol::IPCP);

    assert(e->add_requestor(a));
    assert(!e->add_requestor(a));
    assert(e->add_requestor(b));
    assert(f->add_requestor(c));
    assert(f->add_requestor(d));
    assert(g->add_requestor(e));
    assert(g->add_requestor(f));

    cout << *e << *f << *g;

    return 0;
}