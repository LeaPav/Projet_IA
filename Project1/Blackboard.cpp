#include"Blackboard.hpp"
void Blackboard::SetValue(const string& key, int value) {
    data[key] = value;
}
int Blackboard::GetValue(const string& key) {
    return data[key];
}