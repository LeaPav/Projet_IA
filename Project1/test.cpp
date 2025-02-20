
//#include <unordered_map>
//#include <string>
//#include <iostream>
//#include <vector>
//#include <memory>
//#include "Enemy.hpp"
//#include "Objet.hpp"
//#include "Player.hpp"
//#include <SFML/Graphics.hpp>
//Player& player;
//Enemy& enemy;
//Objet& objet;
//
//using namespace std;
//
//enum class NodeState { SUCCESS, FAILURE, RUNNING };
//
//class BTNode {
//public:
//    virtual ~BTNode() = default;
//    virtual NodeState execute() = 0;
//};
//
//
//class Blackboard {
//private:
//    std::unordered_map<std::string, sf::Vector2f> data;
//public:
//    void SetValue(const std::string& key, sf::Vector2f value) {
//        data[key] = value;
//    }
//    sf::Vector2f GetValue(const std::string& key) {
//        return data[key];
//    }
//};
//
//class SequenceNode : public BTNode {
//private:
//    std::vector<std::unique_ptr<BTNode>> children;
//public:
//    void AddChild(std::unique_ptr<BTNode> child) {
//        children.push_back(std::move(child));
//    }
//    NodeState execute() override {
//        for (auto& child : children) {
//            if (child->execute() == NodeState::FAILURE) {
//                return NodeState::FAILURE;
//            }
//        }
//        return NodeState::SUCCESS;
//    }
//};
//
//class SelectorNode : public BTNode {
//private:
//    std::vector<std::unique_ptr<BTNode>> children;
//public:
//    void AddChild(std::unique_ptr<BTNode> child) {
//        children.push_back(std::move(child));
//    }
//    NodeState execute() override {
//        for (auto& child : children) {
//            if (child->execute() == NodeState::SUCCESS) {
//                return NodeState::SUCCESS;
//            }
//        }
//        return NodeState::FAILURE;
//    }
//};
//
//class ConditionNode : public BTNode {
//private:
//    Blackboard& blackboard;
//    sf::Vector2f key;
//    sf::Vector2f expectedValue;
//public:
//    ConditionNode(Blackboard& bb, sf::Vector2f k, sf::Vector2f value)
//        : blackboard(bb), key(k), expectedValue(value) {
//    }
//
//    NodeState execute() override {
//        sf::Vector2f posPlayer = blackboard.GetValue("player pos");
//        sf::Vector2f posEnemy = expectedValue;
//
//        float distPlayer = std::hypot(posPlayer.x - objet.shape.getPosition().x,
//            posPlayer.y - objet.shape.getPosition().y);
//        float distEnemy = std::hypot(posEnemy.x - objet.shape.getPosition().x,
//            posEnemy.y - objet.shape.getPosition().y);
//
//        return (distPlayer < distEnemy) ? NodeState::SUCCESS : NodeState::FAILURE;
//    }
//};
//
//class ActionNode1 : public BTNode {
//private:
//    std::string actionName;
//public:
//    ActionNode1(std::string name) : actionName(name) {}
//    NodeState execute() override {
//        enemy.setCurrentState(enemy.PATROL);
//        return NodeState::SUCCESS;
//    }
//};
//class ActionNode2 : public BTNode {
//private:
//    std::string actionName;
//public:
//    ActionNode2(std::string name) : actionName(name) {}
//    NodeState execute() override {
//        enemy.setCurrentState(enemy.PROTECT);
//        return NodeState::SUCCESS;
//    }
//};
//
//
//
//
//
//int main() {
//    Blackboard blackboard;
//    blackboard.SetValue("player pos", player.shape.getPosition());
//
//    auto root = std::make_unique<SelectorNode>();
//    auto sequenceProtect = std::make_unique<SequenceNode>();
//    auto sequencePatrol = std::make_unique<SequenceNode>();
//
//
//    sequenceProtect->AddChild(std::make_unique<ConditionNode>(blackboard, blackboard.GetValue("player pos"), enemy.shape.getPosition()));
//    sequenceProtect->AddChild(std::make_unique<ActionNode1>("Protection de l'item"));
//
//
//    sequencePatrol->AddChild(std::make_unique<ActionNode2>("Patrouiller"));
//
//    root->AddChild(std::move(sequenceProtect));
//    root->AddChild(std::move(sequencePatrol));
//
//    root->execute();
//    return 0;
//}