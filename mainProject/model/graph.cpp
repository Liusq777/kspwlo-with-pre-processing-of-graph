#include "graph.hpp" 

RoadNetwork::RoadNetwork(const std::vector<std::vector<std::pair<int, int>>>& graph) {
        this->numNodes = graph.size(); 
        this->numEdges = 0; 
        this->adjListOut = vector<EdgeList>(this->numNodes); 
        this->adjListInc = vector<EdgeList>(this->numNodes); 

        for (int u = 0; u < graph.size(); ++u) {
            for (const auto& edge : graph[u]) {
                int v = edge.first;  
                int w = edge.second; 
                this->adjListOut[u].insert(make_pair(v, w)); 
                this->adjListInc[v].insert(make_pair(u, w)); 
                this->numEdges++; 
            }
        }
    }


//test
/*int count_deletetimes = 6666;
void RoadNetwork::removeDegreeOneNodes()
{
    count_deletetimes=1000;
    for (NodeID i = 1; i < this->numNodes - 1; ++i) {
        if (this->adjListOut[i].size() == 1 && this->adjListInc[i].size() == 1) {
            count_deletetimes++;
            NodeID neighbor = this->adjListOut[i].begin()->first; 
            this->adjListOut[i].clear(); 
            this->adjListInc[neighbor].erase(i); 
        }
    }
}*/


int RoadNetwork::getEdgeWeight(NodeID lnode, NodeID rnode) {
    return this->adjListOut[lnode][rnode]; 
}

RoadNetwork::~RoadNetwork() {
    this->adjListOut.clear(); 
    this->adjListInc.clear(); 
}

bool operator==(const Edge& le, const Edge& re) {
    return (le.first == re.first && le.second == re.second) || (le.second == re.first && le.first == re.second);
}

bool Path::containsEdge(Edge e) {
    bool res = false;

    for (unsigned int i = 0;i < this->nodes.size() - 1;i++) {
        if (this->nodes[i] == e.first && this->nodes[i + 1] == e.second) {
            res = true;
            break;
        }
    }

    return res;
}

double Path::overlap_ratio(RoadNetwork* rN, Path& path2) {
    double sharedLength = 0;

    for (unsigned int i = 0;i < path2.nodes.size() - 1;i++) {
        Edge e = make_pair(path2.nodes[i], path2.nodes[i + 1]);
        if (this->containsEdge(e))
            sharedLength += rN->getEdgeWeight(path2.nodes[i], path2.nodes[i + 1]);
    }

    return sharedLength / path2.length;
}

bool operator==(const Path& lp, const Path& rp) {
    if (lp.length != rp.length || lp.nodes.size() != rp.nodes.size())
        return false;
    for (int i = 0;i < lp.nodes.size();i++) {
        if (lp.nodes[i] != rp.nodes[i])
            return false;
    }
    return true;
}
