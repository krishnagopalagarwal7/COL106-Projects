#include "node.h"
#include <iostream>
#include <stdexcept>
using namespace std;
Node(bool sentinel=true);
Node(int v, Node* nxt, Node* prv);
bool is_sentinel_node();
int get_value();