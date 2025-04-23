#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "Polynomial.h"
#include "PriorityQueue.h"
#include "Stack.h"
#include "RedBlackTree.h"
#include "SegmentDeque.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openPolynomWidget();
    void openPriorityQueueWidget();
    void openStackWidget();
    void openSetWidget();
    void openSegmentDequeWidget();

private:
    QPushButton *polynomButton;
    QPushButton *priorityQueueButton;
    QPushButton *stackButton;
    QPushButton *setButton;
    QPushButton *segmentDequeButton;
};

class PolynomWidget : public QWidget {
    Q_OBJECT

public:
    PolynomWidget(QWidget *parent = nullptr);

private slots:
    void addTerm();
    void addPolynom();
    void multiplyPolynom();
    void subtractPolynom();
    void scalarMultiply();
    void evaluatePoint();
    void superPosition();
    void power();
    void displayPolynom();

private:
    Polynom<int> polynom;
    QLineEdit *powerInput;
    QLineEdit *coeffInput;
    QLineEdit *otherPolynomInput;
    QLineEdit *scalarInput;
    QLineEdit *pointInput;
    QLineEdit *exponentInput;
    QTextEdit *output;
    QPushButton *addTermButton;
    QPushButton *addPolynomButton;
    QPushButton *multiplyPolynomButton;
    QPushButton *subtractPolynomButton;
    QPushButton *scalarMultiplyButton;
    QPushButton *evaluatePointButton;
    QPushButton *superPositionButton;
    QPushButton *powerButton;
    QPushButton *displayButton;
};

class PriorityQueueWidget : public QWidget {
    Q_OBJECT

public:
    PriorityQueueWidget(QWidget *parent = nullptr);

private slots:
    void push();
    void pop();
    void top();
    void size();
    void isEmpty();
    void concat();
    void map();
    void where();

private:
    PriorityQueue<int> queue;
    QLineEdit *valueInput;
    QLineEdit *otherQueueInput;
    QTextEdit *output;
    QPushButton *pushButton;
    QPushButton *popButton;
    QPushButton *topButton;
    QPushButton *sizeButton;
    QPushButton *isEmptyButton;
    QPushButton *concatButton;
    QPushButton *mapButton;
    QPushButton *whereButton;
};

class StackWidget : public QWidget {
    Q_OBJECT

public:
    StackWidget(QWidget *parent = nullptr);

private slots:
    void push();
    void pop();
    void top();
    void size();
    void isEmpty();
    void clear();

private:
    Stack<int> stack;
    QLineEdit *valueInput;
    QTextEdit *output;
    QPushButton *pushButton;
    QPushButton *popButton;
    QPushButton *topButton;
    QPushButton *sizeButton;
    QPushButton *isEmptyButton;
    QPushButton *clearButton;
};

class SetWidget : public QWidget {
    Q_OBJECT

public:
    SetWidget(QWidget *parent = nullptr);

private slots:
    void insert();
    void size();
    void find();
    void goForward();
    void read();
    void getSubTree();
    void isSubTree();
    void map();
    void where();
    void reduce();

private:
    Set<int> set;
    QLineEdit *valueInput;
    QLineEdit *otherSetInput;
    QLineEdit *templateInput;
    QTextEdit *output;
    QPushButton *insertButton;
    QPushButton *sizeButton;
    QPushButton *findButton;
    QPushButton *goForwardButton;
    QPushButton *readButton;
    QPushButton *getSubTreeButton;
    QPushButton *isSubTreeButton;
    QPushButton *mapButton;
    QPushButton *whereButton;
    QPushButton *reduceButton;
};

class SegmentDequeWidget : public QWidget {
    Q_OBJECT

public:
    SegmentDequeWidget(QWidget *parent = nullptr);

private slots:
    void pushBack();
    void pushFront();
    void insertAt();
    void getElement();
    void getSize();
    void sort();
    void map();
    void where();
    void takeDeque();
    void concat();

private:
    SegmentDeque<int> deque;
    QLineEdit *valueInput;
    QLineEdit *indexInput;
    QLineEdit *otherDequeInput;
    QLineEdit *rangeInput;
    QTextEdit *output;
    QPushButton *pushBackButton;
    QPushButton *pushFrontButton;
    QPushButton *insertAtButton;
    QPushButton *getElementButton;
    QPushButton *getSizeButton;
    QPushButton *sortButton;
    QPushButton *mapButton;
    QPushButton *whereButton;
    QPushButton *takeDequeButton;
    QPushButton *concatButton;
};

#endif // MAINWINDOW_H
