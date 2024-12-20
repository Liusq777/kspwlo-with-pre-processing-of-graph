// widget.cpp
#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent) {
    // 设置布局
    layout = new QVBoxLayout(this);

    // 创建控件
    //graphFileEdit = new QLineEdit(this);
    sourceEdit = new QLineEdit(this);
    targetEdit = new QLineEdit(this);
    kEdit = new QLineEdit(this);
    thetaEdit = new QLineEdit(this);
    runButton = new QPushButton("SELECT FILE AND RUN", this);
    resultEdit = new QTextEdit(this);

    // 添加控件到布局
    //layout->addWidget(new QLabel("Graph File:", this));
    //layout->addWidget(graphFileEdit);
    layout->addWidget(new QLabel("Source Node(s):", this));
    layout->addWidget(sourceEdit);
    layout->addWidget(new QLabel("Destination Node(d):", this));
    layout->addWidget(targetEdit);
    layout->addWidget(new QLabel("Path Nums(k):", this));
    layout->addWidget(kEdit);
    layout->addWidget(new QLabel("Similarity Threshold(θ):", this));
    layout->addWidget(thetaEdit);
    layout->addWidget(runButton);
    layout->addWidget(resultEdit);

    // 设置窗口标题和大小
    setWindowTitle("Top-k Solver");
    resize(400, 300);

    // 连接按钮信号
    connect(runButton, &QPushButton::clicked, this, &Widget::onRunButtonClicked);
}

void readGraph(const std::string& filename, std::vector<std::vector<std::pair<int, int>>>& graph, int& numNodes, int& numEdges) {

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
    cout << "[测试] 读图循环操作完成" << endl;
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

void Widget::onRunButtonClicked() {
    QString graphFile = QFileDialog::getOpenFileName(this, tr("Open Graph File"), "/home/ubuntu22/myProject/UI/sample", tr("Graph Files (*.gr)"));
    int source = sourceEdit->text().toInt();
    int target = targetEdit->text().toInt();
    int k = kEdit->text().toInt();
    double theta = thetaEdit->text().toDouble();

    // 参数验证
    if (graphFile.isEmpty()) {
        QMessageBox::critical(this, "Error", "Please define the graph file.");
        return;
    }

    if (k < 1) {
        QMessageBox::critical(this, "Error", "Please define k as a value in [1,+inf) range.");
        return;
    }

    if (theta < 0 || theta > 1) {
        QMessageBox::critical(this, "Error", "Please define theta as a value in [0,1] range.");
        return;
    }

    if (source == target) {
        QMessageBox::critical(this, "Error", "Source and target nodes are the same.");
        return;
    }

    // 执行算法
    executeAlgorithm(graphFile, source, target, k, theta);
}

void Widget::executeAlgorithm(const QString &graphFile, int source, int target, int k, double theta) {
    cout << "[日志] 网络文件: " << graphFile.toStdString() << endl;
    cout << "[日志] 源节点: " << source << endl;
    cout << "[日志] 目标节点: " << target << endl;
    cout << "[日志] 路径数量k: " << k << endl;
    cout << "[日志] 相似度阈值theta: " << theta << endl;

    RoadNetwork* rN = 0; // 指向RoadNetwork对象的指针

    // 开始执行函数
    std::vector<std::vector<std::pair<int, int>>> GRAPH;
    int NodesNum, EdgesNum;


    readGraph(graphFile.toStdString(), GRAPH, NodesNum, EdgesNum);

    // 删除一度顶点
    removeDegreeOneNodes(GRAPH);

    //加载道路网络，此时应使用修改后的图
    rN = new RoadNetwork(GRAPH); // 使用内存中的图构造 RoadNetwork 对象

    vector<Path> result; // 保存路径结果
    pair<vector<Path>, double> completeResult; // 保存完整结果（路径及额外信息）

    result = svp_plus(rN, source, target, k, theta); // result为vector

    cout << source << "\t" << target << "\t[" << result[0].length;
    for (unsigned int j = 1; j < result.size(); j++) {
        cout << "," << result[j].length;
    }
    cout << "]" << endl;

    QString resultStr;
    resultStr = "Solution Completed!  Results as Follows:\n";
    for (unsigned int i = 0; i < result.size (); i++) {
        resultStr += "[top-" + QString::number(i + 1) + "]: " + QString::number(result[i].length) + "\n";
    }

    resultEdit->setText(resultStr);

    delete rN;
}
