#include "Blackboard.hpp"
void Blackboard::SetValue(const string& key, Vector2f value) {
    data[key] = value;
}
sf::Vector2f Blackboard::GetValue(const string& key) {
    return data[key];
}