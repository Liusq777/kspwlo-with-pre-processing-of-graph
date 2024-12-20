// widget.h
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QMessageBox>
#include <iostream>
#include <fstream>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include "model/graph.hpp"
#include "algorithms/kspwlo.hpp"
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <QFile>
#include <QFileDialog>

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    void executeAlgorithm(const QString &graphFile, int source, int target, int k, double theta);

private slots:
    void onRunButtonClicked();

private:
    QLineEdit *graphFileEdit;
    QLineEdit *sourceEdit;
    QLineEdit *targetEdit;
    QLineEdit *kEdit;
    QLineEdit *thetaEdit;
    QPushButton *runButton;
    QTextEdit *resultEdit;
    QVBoxLayout *layout;
};

