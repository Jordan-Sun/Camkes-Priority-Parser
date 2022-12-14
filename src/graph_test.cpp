#include "graph.h"
#include <iostream>
#include <cassert>

using namespace std;

int main()
{
    Graph p;

    auto a = make_shared<Node>("a", "box", false, 10);
    auto b = make_shared<Node>("b", "box", false, 20);
    auto c = make_shared<Node>("c", "box", false, 30);
    auto d = make_shared<Node>("d", "box", false, 40);
    auto e = make_shared<Node>("e", "circle", false);
    auto f = make_shared<Node>("f", "circle", false);
    auto g = make_shared<Node>("g", "circle", false);

    assert(p.add_node(a));
    assert(p.add_node(b));
    assert(p.add_node(c));
    assert(p.add_node(d));
    assert(p.add_node(e));
    assert(p.add_node(f));
    assert(p.add_node(g));

    assert(p.add_edge("a", "e"));
    assert(p.add_edge("b", "e"));
    assert(p.add_edge("c", "f"));
    assert(p.add_edge("d", "f"));
    assert(p.add_edge("e", "g"));
    assert(p.add_edge("f", "g"));

    assert(!p.add_node(a));

    assert(!p.add_edge("a", "not a node"));
    assert(!p.add_edge("not a node", "a"));
    assert(!p.add_edge("a", "a"));
    assert(!p.add_edge("a", "e"));
    assert(!p.add_edge("g", "a"));

    cout << p;

    return 0;
}