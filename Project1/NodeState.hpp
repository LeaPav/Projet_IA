#include <iostream>
#include <vector>
#include <memory>
#include "Enemy.hpp"
using namespace std;

enum class NodeState { SUCCESS, FAILURE, RUNNING };

class NodeS {
public:
    virtual ~NodeS() {}
    virtual bool Execute() = 0;
};