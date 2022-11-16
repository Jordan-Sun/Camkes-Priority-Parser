#include "graph.h"
#include <iostream>

using namespace std;

int main()
{
    Graph p;
    Node a("a", 10);
    Node b("b", 20);
    Node c("c", 30);
    Node d("d", 40);
    Node e("e");
    Node f("f");
    Node g("g");

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