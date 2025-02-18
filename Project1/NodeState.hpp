#pragma once
#include <iostream>
#include <vector>
#include <memory>
using namespace std;



class NodeS {
public:
    NodeS(){}
    virtual ~NodeS() {}
    virtual bool Execute() = 0;
};