#include "NodeState.hpp"
#include <unordered_map>
using namespace std;
class Blackboard {
private:
    unordered_map<std::string, int> data;
public:
    void SetValue(const std::string& key, int value);
    int GetValue(const std::string& key);
};