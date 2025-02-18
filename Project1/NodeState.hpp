#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include "Enemy.hpp"
#include "Objet.hpp"
#include "Player.hpp"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;


enum class NodeState { SUCCESS, FAILURE, RUNNING };
class BTNode {
public:
    
    virtual ~BTNode() = default;
    virtual NodeState execute() = 0;
};