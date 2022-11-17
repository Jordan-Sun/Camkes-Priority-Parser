/*
 *  node.cpp
 *  implementation file for the node class
 *  author: jordan sun
 */ 

#include "node.h"

using namespace std;

Node::Node(string name, string shape, int priority)
: name(name), shape(shape), priority(priority), last(nullptr)
{
}

// add a requestor to the node, return true if successful
bool Node::add_requestor(Node *requestor)
{
    return immed_requestors.insert(requestor).second;
}

// check if the node has the given requestor
bool Node::has_requestor(Node *requestor) const
{
    return immed_requestors.find(requestor) != immed_requestors.end();
}

set<const Node *> Node::get_requestors() const
{
    set<const Node *> requestors;
    for (const Node *requestor : immed_requestors)
    {
        // add the requestor if it is a true requestor
        if (requestor->priority != NONE)
        {
            requestors.insert(requestor);
        }
        // add the requestors of the requestor
        set<const Node *> requestors_of_requestor = requestor->get_requestors();
        requestors.insert(requestors_of_requestor.begin(), requestors_of_requestor.end());
    }
    return requestors;
}

// returns the number of requestors of the node
int Node::get_num_requestors() const
{
    return get_requestors().size();
}

// returns the maximum priority of the node and its requestors
pair<const Node *, int> Node::get_max_priority() const
{
    int max_priority = priority;
    const Node* max_priority_node = this;
    for (auto requestor : get_requestors())
    {
        if (requestor->priority > max_priority)
        {
            max_priority = requestor->priority;
            max_priority_node = requestor;
        }
    }
    return make_pair(max_priority_node, max_priority);
}

// operators
bool Node::operator==(const Node& rhs) const
{
    return name == rhs.name;
}

ostream& operator<<(ostream& os, const Node& node)
{
    auto max_priority = node.get_max_priority();
    os << node.name << " has " << node.get_num_requestors() << " requestors, with a max priority of " << max_priority.second << " from " << max_priority.first->name << endl;
    return os;
}