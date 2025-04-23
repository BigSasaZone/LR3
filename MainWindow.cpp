#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    polynomButton = new QPushButton("Polynom", this);
    priorityQueueButton = new QPushButton("Priority Queue", this);
    stackButton = new QPushButton("Stack", this);
    setButton = new QPushButton("Set", this);
    segmentDequeButton = new QPushButton("Segment Deque", this);

    connect(polynomButton, &QPushButton::clicked, this, &MainWindow::openPolynomWidget);
    connect(priorityQueueButton, &QPushButton::clicked, this, &MainWindow::openPriorityQueueWidget);
    connect(stackButton, &QPushButton::clicked, this, &MainWindow::openStackWidget);
    connect(setButton, &QPushButton::clicked, this, &MainWindow::openSetWidget);
    connect(segmentDequeButton, &QPushButton::clicked, this, &MainWindow::openSegmentDequeWidget);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(polynomButton);
    layout->addWidget(priorityQueueButton);
    layout->addWidget(stackButton);
    layout->addWidget(setButton);
    layout->addWidget(segmentDequeButton);

    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow() {}

void MainWindow::openPolynomWidget() {
    PolynomWidget *widget = new PolynomWidget;
    widget->show();
}

void MainWindow::openPriorityQueueWidget() {
    PriorityQueueWidget *widget = new PriorityQueueWidget;
    widget->show();
}

void MainWindow::openStackWidget() {
    StackWidget *widget = new StackWidget;
    widget->show();
}

void MainWindow::openSetWidget() {
    SetWidget *widget = new SetWidget;
    widget->show();
}

void MainWindow::openSegmentDequeWidget() {
    SegmentDequeWidget *widget = new SegmentDequeWidget;
    widget->show();
}

PolynomWidget::PolynomWidget(QWidget *parent)
    : QWidget(parent) {
    powerInput = new QLineEdit;
    coeffInput = new QLineEdit;
    otherPolynomInput = new QLineEdit;
    scalarInput = new QLineEdit;
    pointInput = new QLineEdit;
    exponentInput = new QLineEdit;
    output = new QTextEdit;
    output->setReadOnly(true);

    addTermButton = new QPushButton("Add Term");
    addPolynomButton = new QPushButton("Add Polynom");
    multiplyPolynomButton = new QPushButton("Multiply Polynom");
    subtractPolynomButton = new QPushButton("Subtract Polynom");
    scalarMultiplyButton = new QPushButton("Scalar Multiply");
    evaluatePointButton = new QPushButton("Evaluate at Point");
    superPositionButton = new QPushButton("Superposition");
    powerButton = new QPushButton("Power");
    displayButton = new QPushButton("Display Polynom");

    connect(addTermButton, &QPushButton::clicked, this, &PolynomWidget::addTerm);
    connect(addPolynomButton, &QPushButton::clicked, this, &PolynomWidget::addPolynom);
    connect(multiplyPolynomButton, &QPushButton::clicked, this, &PolynomWidget::multiplyPolynom);
    connect(subtractPolynomButton, &QPushButton::clicked, this, &PolynomWidget::subtractPolynom);
    connect(scalarMultiplyButton, &QPushButton::clicked, this, &PolynomWidget::scalarMultiply);
    connect(evaluatePointButton, &QPushButton::clicked, this, &PolynomWidget::evaluatePoint);
    connect(superPositionButton, &QPushButton::clicked, this, &PolynomWidget::superPosition);
    connect(powerButton, &QPushButton::clicked, this, &PolynomWidget::power);
    connect(displayButton, &QPushButton::clicked, this, &PolynomWidget::displayPolynom);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *termLayout = new QHBoxLayout;
    termLayout->addWidget(new QLabel("Power:"));
    termLayout->addWidget(powerInput);
    termLayout->addWidget(new QLabel("Coefficient:"));
    termLayout->addWidget(coeffInput);
    termLayout->addWidget(addTermButton);

    QHBoxLayout *otherPolynomLayout = new QHBoxLayout;
    otherPolynomLayout->addWidget(new QLabel("Other Polynom (power:coeff,...):"));
    otherPolynomLayout->addWidget(otherPolynomInput);

    QHBoxLayout *scalarLayout = new QHBoxLayout;
    scalarLayout->addWidget(new QLabel("Scalar:"));
    scalarLayout->addWidget(scalarInput);
    scalarLayout->addWidget(scalarMultiplyButton);

    QHBoxLayout *pointLayout = new QHBoxLayout;
    pointLayout->addWidget(new QLabel("Point:"));
    pointLayout->addWidget(pointInput);
    pointLayout->addWidget(evaluatePointButton);

    QHBoxLayout *exponentLayout = new QHBoxLayout;
    exponentLayout->addWidget(new QLabel("Exponent:"));
    exponentLayout->addWidget(exponentInput);
    exponentLayout->addWidget(powerButton);

    mainLayout->addLayout(termLayout);
    mainLayout->addLayout(otherPolynomLayout);
    mainLayout->addWidget(addPolynomButton);
    mainLayout->addWidget(multiplyPolynomButton);
    mainLayout->addWidget(subtractPolynomButton);
    mainLayout->addLayout(scalarLayout);
    mainLayout->addLayout(pointLayout);
    mainLayout->addWidget(superPositionButton);
    mainLayout->addLayout(exponentLayout);
    mainLayout->addWidget(displayButton);
    mainLayout->addWidget(output);

    setLayout(mainLayout);
}

void PolynomWidget::addTerm() {
    bool powerOk, coeffOk;
    size_t power = powerInput->text().toUInt(&powerOk);
    int coeff = coeffInput->text().toInt(&coeffOk);
    if (powerOk && coeffOk) {
        polynom = Polynom<int>(power, coeff) + polynom;
        output->append(QString("Added term: %1x^%2").arg(coeff).arg(power));
    } else {
        output->append("Invalid power or coefficient");
    }
}

void PolynomWidget::addPolynom() {
    Polynom<int> other;
    QStringList terms = otherPolynomInput->text().split(",");
    for (const QString &term : terms) {
        QStringList parts = term.split(":");
        if (parts.size() == 2) {
            bool powerOk, coeffOk;
            size_t power = parts[0].toUInt(&powerOk);
            int coeff = parts[1].toInt(&coeffOk);
            if (powerOk && coeffOk) {
                other = Polynom<int>(power, coeff) + other;
            }
        }
    }
    polynom += other;
    output->append("Added polynom");
}

void PolynomWidget::multiplyPolynom() {
    Polynom<int> other;
    QStringList terms = otherPolynomInput->text().split(",");
    for (const QString &term : terms) {
        QStringList parts = term.split(":");
        if (parts.size() == 2) {
            bool powerOk, coeffOk;
            size_t power = parts[0].toUInt(&powerOk);
            int coeff = parts[1].toInt(&coeffOk);
            if (powerOk && coeffOk) {
                other = Polynom<int>(power, coeff) + other;
            }
        }
    }
    polynom *= other;
    output->append("Multiplied polynom");
}

void PolynomWidget::subtractPolynom() {
    Polynom<int> other;
    QStringList terms = otherPolynomInput->text().split(",");
    for (const QString &term : terms) {
        QStringList parts = term.split(":");
        if (parts.size() == 2) {
            bool powerOk, coeffOk;
            size_t power = parts[0].toUInt(&powerOk);
            int coeff = parts[1].toInt(&coeffOk);
            if (powerOk && coeffOk) {
                other = Polynom<int>(power, coeff) + other;
            }
        }
    }
    polynom -= other;
    output->append("Subtracted polynom");
}

void PolynomWidget::scalarMultiply() {
    bool ok;
    int scalar = scalarInput->text().toInt(&ok);
    if (ok) {
        polynom = polynom.ProdScalar(scalar);
        output->append(QString("Multiplied by scalar: %1").arg(scalar));
    } else {
        output->append("Invalid scalar");
    }
}

void PolynomWidget::evaluatePoint() {
    bool ok;
    int point = pointInput->text().toInt(&ok);
    if (ok) {
        int value = polynom.ValueInPoint(point);
        output->append(QString("Value at x=%1: %2").arg(point).arg(value));
    } else {
        output->append("Invalid point");
    }
}

void PolynomWidget::superPosition() {
    Polynom<int> other;
    QStringList terms = otherPolynomInput->text().split(",");
    for (const QString &term : terms) {
        QStringList parts = term.split(":");
        if (parts.size() == 2) {
            bool powerOk, coeffOk;
            size_t power = parts[0].toUInt(&powerOk);
            int coeff = parts[1].toInt(&coeffOk);
            if (powerOk && coeffOk) {
                other = Polynom<int>(power, coeff) + other;
            }
        }
    }
    polynom = polynom.SuperPosition(other);
    output->append("Performed superposition");
}

void PolynomWidget::power() {
    bool ok;
    size_t exponent = exponentInput->text().toUInt(&ok);
    if (ok) {
        polynom = Polynom<int>::Power(polynom, exponent);
        output->append(QString("Raised to power: %1").arg(exponent));
    } else {
        output->append("Invalid exponent");
    }
}

void PolynomWidget::displayPolynom() {
    QString result;
    auto terms = polynom.GetSet().GoForward();
    for (size_t i = 0; i < terms.GetLenght(); ++i) {
        result += QString("%1x^%2").arg(terms[i].k).arg(terms[i].power);
        if (i < terms.GetLenght() - 1) result += " + ";
    }
    output->append("Polynom: " + (result.isEmpty() ? "0" : result));
}

PriorityQueueWidget::PriorityQueueWidget(QWidget *parent)
    : QWidget(parent) {
    valueInput = new QLineEdit;
    otherQueueInput = new QLineEdit;
    output = new QTextEdit;
    output->setReadOnly(true);

    pushButton = new QPushButton("Push");
    popButton = new QPushButton("Pop");
    topButton = new QPushButton("Top");
    sizeButton = new QPushButton("Size");
    isEmptyButton = new QPushButton("Is Empty");
    concatButton = new QPushButton("Concat");
    mapButton = new QPushButton("Map (+1)");
    whereButton = new QPushButton("Where (>0)");

    connect(pushButton, &QPushButton::clicked, this, &PriorityQueueWidget::push);
    connect(popButton, &QPushButton::clicked, this, &PriorityQueueWidget::pop);
    connect(topButton, &QPushButton::clicked, this, &PriorityQueueWidget::top);
    connect(sizeButton, &QPushButton::clicked, this, &PriorityQueueWidget::size);
    connect(isEmptyButton, &QPushButton::clicked, this, &PriorityQueueWidget::isEmpty);
    connect(concatButton, &QPushButton::clicked, this, &PriorityQueueWidget::concat);
    connect(mapButton, &QPushButton::clicked, this, &PriorityQueueWidget::map);
    connect(whereButton, &QPushButton::clicked, this, &PriorityQueueWidget::where);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *valueLayout = new QHBoxLayout;
    valueLayout->addWidget(new QLabel("Value:"));
    valueLayout->addWidget(valueInput);
    valueLayout->addWidget(pushButton);

    QHBoxLayout *otherQueueLayout = new QHBoxLayout;
    otherQueueLayout->addWidget(new QLabel("Other Queue (comma-separated):"));
    otherQueueLayout->addWidget(otherQueueInput);

    mainLayout->addLayout(valueLayout);
    mainLayout->addWidget(popButton);
    mainLayout->addWidget(topButton);
    mainLayout->addWidget(sizeButton);
    mainLayout->addWidget(isEmptyButton);
    mainLayout->addLayout(otherQueueLayout);
    mainLayout->addWidget(concatButton);
    mainLayout->addWidget(mapButton);
    mainLayout->addWidget(whereButton);
    mainLayout->addWidget(output);

    setLayout(mainLayout);
}

void PriorityQueueWidget::push() {
    bool ok;
    int value = valueInput->text().toInt(&ok);
    if (ok) {
        queue.Push(value);
        output->append(QString("Pushed: %1").arg(value));
    } else {
        output->append("Invalid value");
    }
}

void PriorityQueueWidget::pop() {
    if (!queue.IsEmpty()) {
        queue.Pop();
        output->append("Popped");
    } else {
        output->append("Queue is empty");
    }
}

void PriorityQueueWidget::top() {
    if (!queue.IsEmpty()) {
        int value = queue.Top();
        output->append(QString("Top: %1").arg(value));
    } else {
        output->append("Queue is empty");
    }
}

void PriorityQueueWidget::size() {
    output->append(QString("Size: %1").arg(queue.Size()));
}

void PriorityQueueWidget::isEmpty() {
    output->append(queue.IsEmpty() ? "Queue is empty" : "Queue is not empty");
}

void PriorityQueueWidget::concat() {
    PriorityQueue<int> other;
    QStringList values = otherQueueInput->text().split(",");
    for (const QString &value : values) {
        bool ok;
        int val = value.toInt(&ok);
        if (ok) {
            other.Push(val);
        }
    }
    queue = queue.Concat(other);
    output->append("Concatenated queue");
}

void PriorityQueueWidget::map() {
    queue = queue.Map([](int x) { return x + 1; });
    output->append("Mapped: added 1 to each element");
}

void PriorityQueueWidget::where() {
    queue = queue.Where([](int x) { return x > 0; });
    output->append("Filtered: kept elements > 0");
}

StackWidget::StackWidget(QWidget *parent)
    : QWidget(parent) {
    valueInput = new QLineEdit;
    output = new QTextEdit;
    output->setReadOnly(true);

    pushButton = new QPushButton("Push");
    popButton = new QPushButton("Pop");
    topButton = new QPushButton("Top");
    sizeButton = new QPushButton("Size");
    isEmptyButton = new QPushButton("Is Empty");
    clearButton = new QPushButton("Clear");

    connect(pushButton, &QPushButton::clicked, this, &StackWidget::push);
    connect(popButton, &QPushButton::clicked, this, &StackWidget::pop);
    connect(topButton, &QPushButton::clicked, this, &StackWidget::top);
    connect(sizeButton, &QPushButton::clicked, this, &StackWidget::size);
    connect(isEmptyButton, &QPushButton::clicked, this, &StackWidget::isEmpty);
    connect(clearButton, &QPushButton::clicked, this, &StackWidget::clear);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *valueLayout = new QHBoxLayout;
    valueLayout->addWidget(new QLabel("Value:"));
    valueLayout->addWidget(valueInput);
    valueLayout->addWidget(pushButton);

    mainLayout->addLayout(valueLayout);
    mainLayout->addWidget(popButton);
    mainLayout->addWidget(topButton);
    mainLayout->addWidget(sizeButton);
    mainLayout->addWidget(isEmptyButton);
    mainLayout->addWidget(clearButton);
    mainLayout->addWidget(output);

    setLayout(mainLayout);
}

void StackWidget::push() {
    bool ok;
    int value = valueInput->text().toInt(&ok);
    if (ok) {
        stack.Push(value);
        output->append(QString("Pushed: %1").arg(value));
    } else {
        output->append("Invalid value");
    }
}

void StackWidget::pop() {
    try {
        int value = stack.Pop();
        output->append(QString("Popped: %1").arg(value));
    } catch (const std::out_of_range &e) {
        output->append("Stack is empty");
    }
}

void StackWidget::top() {
    try {
        int value = stack.Top();
        output->append(QString("Top: %1").arg(value));
    } catch (const std::out_of_range &e) {
        output->append("Stack is empty");
    }
}

void StackWidget::size() {
    output->append(QString("Size: %1").arg(stack.Size()));
}

void StackWidget::isEmpty() {
    output->append(stack.Empty() ? "Stack is empty" : "Stack is not empty");
}

void StackWidget::clear() {
    stack.Clear();
    output->append("Stack cleared");
}

SetWidget::SetWidget(QWidget *parent)
    : QWidget(parent) {
    valueInput = new QLineEdit;
    otherSetInput = new QLineEdit;
    templateInput = new QLineEdit;
    output = new QTextEdit;
    output->setReadOnly(true);

    insertButton = new QPushButton("Insert");
    sizeButton = new QPushButton("Size");
    findButton = new QPushButton("Find");
    goForwardButton = new QPushButton("Go Forward");
    readButton = new QPushButton("Read");
    getSubTreeButton = new QPushButton("Get SubTree");
    isSubTreeButton = new QPushButton("Is SubTree");
    mapButton = new QPushButton("Map (+1)");
    whereButton = new QPushButton("Where (>0)");
    reduceButton = new QPushButton("Reduce (Sum)");

    connect(insertButton, &QPushButton::clicked, this, &SetWidget::insert);
    connect(sizeButton, &QPushButton::clicked, this, &SetWidget::size);
    connect(findButton, &QPushButton::clicked, this, &SetWidget::find);
    connect(goForwardButton, &QPushButton::clicked, this, &SetWidget::goForward);
    connect(readButton, &QPushButton::clicked, this, &SetWidget::read);
    connect(getSubTreeButton, &QPushButton::clicked, this, &SetWidget::getSubTree);
    connect(isSubTreeButton, &QPushButton::clicked, this, &SetWidget::isSubTree);
    connect(mapButton, &QPushButton::clicked, this, &SetWidget::map);
    connect(whereButton, &QPushButton::clicked, this, &SetWidget::where);
    connect(reduceButton, &QPushButton::clicked, this, &SetWidget::reduce);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *valueLayout = new QHBoxLayout;
    valueLayout->addWidget(new QLabel("Value:"));
    valueLayout->addWidget(valueInput);
    valueLayout->addWidget(insertButton);

    QHBoxLayout *otherSetLayout = new QHBoxLayout;
    otherSetLayout->addWidget(new QLabel("Other Set (comma-separated):"));
    otherSetLayout->addWidget(otherSetInput);

    QHBoxLayout *templateLayout = new QHBoxLayout;
    templateLayout->addWidget(new QLabel("Template (e.g., {LCR}):"));
    templateLayout->addWidget(templateInput);

    mainLayout->addLayout(valueLayout);
    mainLayout->addWidget(sizeButton);
    mainLayout->addWidget(findButton);
    mainLayout->addWidget(goForwardButton);
    mainLayout->addLayout(templateLayout);
    mainLayout->addWidget(readButton);
    mainLayout->addLayout(otherSetLayout);
    mainLayout->addWidget(getSubTreeButton);
    mainLayout->addWidget(isSubTreeButton);
    mainLayout->addWidget(mapButton);
    mainLayout->addWidget(whereButton);
    mainLayout->addWidget(reduceButton);
    mainLayout->addWidget(output);

    setLayout(mainLayout);
}

void SetWidget::insert() {
    bool ok;
    int value = valueInput->text().toInt(&ok);
    if (ok) {
        set.Insert(value);
        output->append(QString("Inserted: %1").arg(value));
    } else {
        output->append("Invalid value");
    }
}

void SetWidget::size() {
    output->append(QString("Size: %1").arg(set.Size()));
}

void SetWidget::find() {
    bool ok;
    int value = valueInput->text().toInt(&ok);
    if (ok) {
        auto iter = set.Find(value);
        output->append(iter != set.end() ? QString("Found: %1").arg(value) : "Not found");
    } else {
        output->append("Invalid value");
    }
}

void SetWidget::goForward() {
    QString result;
    auto array = set.GoForward();
    for (size_t i = 0; i < array.GetLenght(); ++i) {
        result += QString::number(array[i]) + " ";
    }
    output->append("Elements: " + (result.isEmpty() ? "None" : result));
}

void SetWidget::read() {
    QString templateStr = templateInput->text();
    if (templateStr.size() >= 9) {
        QString result = QString::fromStdString(set.Read(templateStr.toStdString()));
        output->append("Read: " + result);
    } else {
        output->append("Invalid template");
    }
}

void SetWidget::getSubTree() {
    bool ok;
    int key = valueInput->text().toInt(&ok);
    if (ok) {
        Set<int> subTree = set.GetSubTree(key);
        QString result;
        auto array = subTree.GoForward();
        for (size_t i = 0; i < array.GetLenght(); ++i) {
            result += QString::number(array[i]) + " ";
        }
        output->append("SubTree: " + (result.isEmpty() ? "None" : result));
    } else {
        output->append("Invalid key");
    }
}

void SetWidget::isSubTree() {
    Set<int> other;
    QStringList values = otherSetInput->text().split(",");
    for (const QString &value : values) {
        bool ok;
        int val = value.toInt(&ok);
        if (ok) {
            other.Insert(val);
        }
    }
    output->append(set.IsSubTree(other) ? "Is SubTree: Yes" : "Is SubTree: No");
}

void SetWidget::map() {
    set = set.Map([](int x) { return x + 1; });
    output->append("Mapped: added 1 to each element");
}

void SetWidget::where() {
    set = set.Where([](int x) { return x > 0; });
    output->append("Filtered: kept elements > 0");
}

void SetWidget::reduce() {
    int sum = set.Reduce([](int x, int y) { return x + y; }, 0);
    output->append(QString("Sum: %1").arg(sum));
}

SegmentDequeWidget::SegmentDequeWidget(QWidget *parent)
    : QWidget(parent) {
    valueInput = new QLineEdit;
    indexInput = new QLineEdit;
    otherDequeInput = new QLineEdit;
    rangeInput = new QLineEdit;
    output = new QTextEdit;
    output->setReadOnly(true);

    pushBackButton = new QPushButton("Push Back");
    pushFrontButton = new QPushButton("Push Front");
    insertAtButton = new QPushButton("Insert At");
    getElementButton = new QPushButton("Get Element");
    getSizeButton = new QPushButton("Get Size");
    sortButton = new QPushButton("Sort");
    mapButton = new QPushButton("Map (+1)");
    whereButton = new QPushButton("Where (>0)");
    takeDequeButton = new QPushButton("Take Deque");
    concatButton = new QPushButton("Concat");

    connect(pushBackButton, &QPushButton::clicked, this, &SegmentDequeWidget::pushBack);
    connect(pushFrontButton, &QPushButton::clicked, this, &SegmentDequeWidget::pushFront);
    connect(insertAtButton, &QPushButton::clicked, this, &SegmentDequeWidget::insertAt);
    connect(getElementButton, &QPushButton::clicked, this, &SegmentDequeWidget::getElement);
    connect(getSizeButton, &QPushButton::clicked, this, &SegmentDequeWidget::getSize);
    connect(sortButton, &QPushButton::clicked, this, &SegmentDequeWidget::sort);
    connect(mapButton, &QPushButton::clicked, this, &SegmentDequeWidget::map);
    connect(whereButton, &QPushButton::clicked, this, &SegmentDequeWidget::where);
    connect(takeDequeButton, &QPushButton::clicked, this, &SegmentDequeWidget::takeDeque);
    connect(concatButton, &QPushButton::clicked, this, &SegmentDequeWidget::concat);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *valueLayout = new QHBoxLayout;
    valueLayout->addWidget(new QLabel("Value:"));
    valueLayout->addWidget(valueInput);
    valueLayout->addWidget(pushBackButton);
    valueLayout->addWidget(pushFrontButton);

    QHBoxLayout *indexLayout = new QHBoxLayout;
    indexLayout->addWidget(new QLabel("Index:"));
    indexLayout->addWidget(indexInput);
    indexLayout->addWidget(insertAtButton);
    indexLayout->addWidget(getElementButton);

    QHBoxLayout *otherDequeLayout = new QHBoxLayout;
    otherDequeLayout->addWidget(new QLabel("Other Deque (comma-separated):"));
    otherDequeLayout->addWidget(otherDequeInput);

    QHBoxLayout *rangeLayout = new QHBoxLayout;
    rangeLayout->addWidget(new QLabel("Range (begin:end):"));
    rangeLayout->addWidget(rangeInput);

    mainLayout->addLayout(valueLayout);
    mainLayout->addLayout(indexLayout);
    mainLayout->addWidget(getSizeButton);
    mainLayout->addWidget(sortButton);
    mainLayout->addWidget(mapButton);
    mainLayout->addWidget(whereButton);
    mainLayout->addLayout(rangeLayout);
    mainLayout->addWidget(takeDequeButton);
    mainLayout->addLayout(otherDequeLayout);
    mainLayout->addWidget(concatButton);
    mainLayout->addWidget(output);

    setLayout(mainLayout);
}

void SegmentDequeWidget::pushBack() {
    bool ok;
    int value = valueInput->text().toInt(&ok);
    if (ok) {
        deque.PushBack(value);
        output->append(QString("Pushed back: %1").arg(value));
    } else {
        output->append("Invalid value");
    }
}

void SegmentDequeWidget::pushFront() {
    bool ok;
    int value = valueInput->text().toInt(&ok);
    if (ok) {
        deque.PushFront(value);
        output->append(QString("Pushed front: %1").arg(value));
    } else {
        output->append("Invalid value");
    }
}

void SegmentDequeWidget::insertAt() {
    bool valueOk, indexOk;
    int value = valueInput->text().toInt(&valueOk);
    size_t index = indexInput->text().toUInt(&indexOk);
    if (valueOk && indexOk) {
        try {
            deque.InsertAt(value, index);
            output->append(QString("Inserted %1 at index %2").arg(value).arg(index));
        } catch (const std::out_of_range &e) {
            output->append("Index out of range");
        }
    } else {
        output->append("Invalid value or index");
    }
}

void SegmentDequeWidget::getElement() {
    bool ok;
    size_t index = indexInput->text().toUInt(&ok);
    if (ok) {
        try {
            int value = deque[index];
            output->append(QString("Element at %1: %2").arg(index).arg(value));
        } catch (const std::out_of_range &e) {
            output->append("Index out of range");
        }
    } else {
        output->append("Invalid index");
    }
}

void SegmentDequeWidget::getSize() {
    output->append(QString("Size: %1").arg(deque.GetSize()));
}

void SegmentDequeWidget::sort() {
    deque.Sort(std::less<int>());
    output->append("Sorted deque");
}

void SegmentDequeWidget::map() {
    deque = deque.Map([](int x) { return x + 1; });
    output->append("Mapped: added 1 to each element");
}

void SegmentDequeWidget::where() {
    deque = deque.Where([](int x) { return x > 0; });
    output->append("Filtered: kept elements > 0");
}

void SegmentDequeWidget::takeDeque() {
    QStringList range = rangeInput->text().split(":");
    if (range.size() == 2) {
        bool beginOk, endOk;
        size_t begin = range[0].toUInt(&beginOk);
        size_t end = range[1].toUInt(&endOk);
        if (beginOk && endOk) {
            try {
                SegmentDeque<int> subDeque = deque.TakeDeque(begin, end);
                QString result;
                for (size_t i = 0; i < subDeque.GetSize(); ++i) {
                    result += QString::number(subDeque[i]) + " ";
                }
                output->append("SubDeque: " + (result.isEmpty() ? "None" : result));
            } catch (const std::out_of_range &e) {
                output->append("Invalid range");
            }
        } else {
            output->append("Invalid range format");
        }
    } else {
        output->append("Invalid range format");
    }
}

void SegmentDequeWidget::concat() {
    SegmentDeque<int> other;
    QStringList values = otherDequeInput->text().split(",");
    for (const QString &value : values) {
        bool ok;
        int val = value.toInt(&ok);
        if (ok) {
            other.PushBack(val);
        }
    }
    deque = deque.Concat(other);
    output->append("Concatenated deque");
}
