#include <iostream>
#include <fstream> 
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include "model/graph.hpp"
#include "algorithms/kspwlo.hpp"
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

// 辅助函数：从文件中读取图的边 
void readGraph(const std::string& filename, std::vector<std::vector<std::pair<int, int>>>& graph, int& numNodes, int& numEdges) {
    
    double read_begin = clock();

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    file >> numNodes >> numEdges;
    graph.resize(numNodes);

    int u, v, w, temp;
    while (file >> u >> v >> w >> temp) {
        if (u >= graph.size()) {
            graph.resize(u + 1);
        }
        if (v >= graph.size()) {
            graph.resize(v + 1);
        }
        graph[u].emplace_back(v, w);
    }

    file.close();
    
    double read_end = clock();
    double read_time = (read_end - read_begin) * 1000 / CLOCKS_PER_SEC;

    cout << "[测试] 读图循环操作完成: read_time is "<< read_time << "ms" << endl;
}


void removeDegreeOneNodes(std::vector<std::vector<std::pair<int, int>>>& graph) {
    std::unordered_set<int> nodesToRemove;
    // 找出一度顶点
    for (int u = 0; u < graph.size(); ++u) {
        if (graph[u].size() == 1) {
            nodesToRemove.insert(u);
        }
    }

    // 删除一度顶点指向的边
    std::unordered_map<int, std::vector<int>> edgesToRemove;
    for (int u : nodesToRemove) {
        for (const auto& edge : graph[u]) {
            edgesToRemove[edge.first].push_back(u);
        }
    }

    for (auto& pair : edgesToRemove) {
        for (int u : pair.second) {
            graph[u].erase(std::remove_if(graph[u].begin(), graph[u].end(), [pair](const std::pair<int, int>& edge) {
                return edge.first == pair.first;
                }), graph[u].end());
        }
    }

    // 删除一度顶点
    for (int u : nodesToRemove) {
        graph[u].clear();
    }

    // 重新索引图
    std::vector<int> newNodeIndex(graph.size(), -1);
    std::vector<int> oldNodeIndex(graph.size(), -1);
    int newIdx = 0;
    for (int oldIdx = 0; oldIdx < graph.size(); ++oldIdx) {
        if (nodesToRemove.find(oldIdx) == nodesToRemove.end()) {
            newNodeIndex[oldIdx] = newIdx;
            oldNodeIndex[newIdx] = oldIdx;
            newIdx++;
        }
    }

    std::vector<std::vector<std::pair<int, int>>> newGraph(newIdx);
    for (int oldIdx = 0; oldIdx < graph.size(); ++oldIdx) {
        if (newNodeIndex[oldIdx] != -1) {
            for (const auto& edge : graph[oldIdx]) {
                int newSrc = newNodeIndex[oldIdx];
                int newDest = newNodeIndex[edge.first];
                if (newSrc != -1 && newDest != -1) {
                    newGraph[newSrc].emplace_back(newDest, edge.second);
                }
            }
        }
    }

    graph.swap(newGraph);
}



int main(int argc, char** argv) {
    // 变量定义
    string graphFile = ""; // 图文件的路径
    unsigned int k = 0; // 要计算的路径数量
    double theta = -1; // 路径相似度的阈值（范围：0到1）
    string algo = ""; // 路径计算所使用的算法
    RoadNetwork* rN = 0; // 指向RoadNetwork对象的指针

    NodeID source = 0, target = 100; // 源节点和目标节点

    // 解析命令行参数
    int opt = -1;
    while ((opt = getopt(argc, argv, "f:s:d:k:t:a:")) != -1) {
        switch (opt) {
        case 'f':
            graphFile = string(optarg); // 获取图文件路径
            break;
        case 's':
            source = stoi(string(optarg)); // 获取源节点
            break;
        case 'd':
            target = stoi(string(optarg)); // 获取目标节点
            break;
        case 'k':
            k = stoi(string(optarg)); // 获取k值
            break;
        case 't':
            theta = stof(string(optarg)); // 获取theta值
            break;
        case 'a':
            algo = string(optarg); // 获取算法名称
            break;
        }
    }

    // 输入检查
    if (graphFile == "") {
        cerr << "参数错误。请正确定义图文件。" << endl;
        cerr << "当前 graphFile 的值为: '" << graphFile << "'" << endl;
        exit(1);
    }

    if (k < 1) {
        cerr << "请将k定义为 [1,+inf) 范围内的值" << endl;
        exit(2);
    }

    if (theta < 0 || theta > 1) {
        cerr << "请将theta定义为 [0,1] 范围内的值" << endl;
        exit(3);
    }

    if (source == target) {
        cerr << "源节点和目标节点相同" << endl;
        exit(4);
    }

    // 打印日志信息
    cout << "[日志] 网络文件: " << graphFile << endl;
    cout << "[日志] 源节点: " << source << endl;
    cout << "[日志] 目标节点: " << target << endl;
    cout << "[日志] 路径数量k: " << k << endl;
    cout << "[日志] 相似度阈值theta: " << theta << endl;
    cout << "[日志] 算法: " << algo << endl;

    // 开始计时
    double begin = clock();

    // 开始执行函数
    std::vector<std::vector<std::pair<int, int>>> GRAPH;
    int NodesNum, EdgesNum;

    // 读取原始图
    readGraph(graphFile, GRAPH, NodesNum, EdgesNum);

    // 删除一度顶点
    removeDegreeOneNodes(GRAPH);

    // 加载道路网络，此时应使用修改后的图
    rN = new RoadNetwork(GRAPH); // 使用内存中的图构造 RoadNetwork 对象

    vector<Path> result; // 保存路径结果
    pair<vector<Path>, double> completeResult; // 保存完整结果（路径及额外信息）

    // 根据输入的算法选择合适的路径计算函数
    if (boost::iequals(algo, "svpplus")) {
        result = svp_plus(rN, source, target, k, theta); // 增强版SVP算法 result为vector
    }

    // 结束计时
    double end = clock();
    double total_runtime = (end - begin) * 1000 / CLOCKS_PER_SEC;
    cout << "total_runtime:" << total_runtime << "ms" << endl;

    // 打印结果路径长度
    cout << source << "\t" << target << "\t[" << result[0].length;
    for (unsigned int j = 1; j < result.size(); j++) {
        cout << "," << result[j].length;
    }
    cout << "]" << endl;

    // 释放道路网络资源
    delete rN;
    return 0;
}


