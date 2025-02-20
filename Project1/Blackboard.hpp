#pragma once
#include "NodeState.hpp"


class Blackboard {
private:
    unordered_map<string, Vector2f> data;
public:
    void SetValue(const string& key, Vector2f value);
    Vector2f GetValue(const string& key);
};