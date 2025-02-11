#include "cmp_decision_tree.h"
#include <random>
#include <chrono>

using namespace std;

//random decision getBranch
std::shared_ptr<DecisionTreeNode> RandomDecision::getBranch(Entity* owner) {
    static random_device rd;
    static default_random_engine e(rd());
    static uniform_int_distribution<int> dist(0, 1);
    bool choice = dist(e) == 0;
    if (choice)
        return _trueNode;
    else
        return _falseNode;
}

//random multiple decision getBranch
std::shared_ptr<DecisionTreeNode> RandomMultiDecision::getBranch(Entity* owner)
{
    static random_device rd;
    static default_random_engine e(rd());
    static uniform_int_distribution<size_t> dist(0, _childNodes.size());
    return _childNodes[dist(e)];
}

//defining DecisionTreeComponent
DecisionTreeComponent::DecisionTreeComponent(Entity* p, shared_ptr<DecisionTreeNode> decisionTree) : _decisionTree(decisionTree), Component(p) { }

void DecisionTreeComponent::update(double dt) {
    _decisionTree->makeDecision(_parent);
}