#include "NodeState.hpp"
#include <unordered_map>
#include <string>

class Blackboard {
private:
    unordered_map<string, int> data;
public:
    void SetValue(const string& key, int value);
    int GetValue(const string& key);
};