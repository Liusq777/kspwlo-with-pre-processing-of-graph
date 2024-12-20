
#ifndef TOOLS_HPP
#define TOOLS_HPP

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <unordered_set>

#include "../model/graph.hpp"

using namespace std;

class Label {
public:
    NodeID node_id;     //节点id
    int length;         //长度
    int lowerBound;     //下界
    Label* previous;    //前驱节点
    
    Label(NodeID node_id, double length) {
        this->node_id = node_id;
        this->length = length;
        this->previous = NULL;
        this->lowerBound = 0;
    };
    
    //================================================================
    //===========三种Label类的对象的构造方法==========================
    Label(NodeID node_id, double length, Label* previous) {
        this->node_id = node_id;
        this->length = length;
        this->previous = previous;
        this->lowerBound = 0;
    };

    Label(NodeID node_id, double length, int lowerBound) {
        this->node_id = node_id;
        this->length = length;
        this->previous = NULL;
        this->lowerBound = lowerBound;
    };

    Label(NodeID node_id, double length, int lowerBound, Label* previous) {
        this->node_id = node_id;
        this->length = length;
        this->previous = previous;
        this->lowerBound = lowerBound;
    };
    //===========三种Label类的对象的构造方法==========================
    //================================================================
};

class MyComparator {
    bool reverse;
public:
    MyComparator(const bool& revparam=false) {
    	reverse=revparam;
    }
    bool operator() (const Label* lhs, const Label* rhs) const {
        return (lhs->length>rhs->length);
    }
};

typedef priority_queue<Label*,std::vector<Label*>,MyComparator> PriorityQueue;

#endif