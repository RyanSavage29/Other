#include <iostream>
#include <string>
#include "AVLNode.h"
using namespace std;

AVLNode::AVLNode(string ss, string na){
    ssn = ss;
    name = na;
    height = 0;
    left = NULL;
    right = NULL;
    parent = NULL;
}
