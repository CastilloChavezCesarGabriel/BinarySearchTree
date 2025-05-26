#include "View.h"
#include <QGraphicsView>
#include <QMessageBox>

View::View(QWidget *parent) : QWidget(parent) {
    setupUI();
}

void View::setupUI() {
    setWindowTitle("Binary Search Tree");
    resize(650, 370);
    constexpr QSize btnSize(100, 30);

    scene = new QGraphicsScene(this);
    scene->setBackgroundBrush(Qt::white);
    view = new QGraphicsView(scene);

    rootInput = new QLineEdit;
    addRootBtn = new QPushButton("Insert");
    addRootBtn->setFixedSize(btnSize);
    removeRootBtn = new QPushButton("Remove");
    removeRootBtn->setFixedSize(btnSize);

    parentInput = new QLineEdit;
    nodeInput = new QLineEdit;
    addNodeBtn = new QPushButton("Insert");
    addNodeBtn->setFixedSize(btnSize);
    removeNodeBtn = new QPushButton("Remove");
    removeNodeBtn->setFixedSize(btnSize);

    balanceBtn = new QPushButton("Balance Tree");
    removeTreeBtn = new QPushButton("Delete Tree");
    infoBtn = new QPushButton("Show Info");
    exportImageBtn = new QPushButton("Export BST");

    upperLeftLayout = new QHBoxLayout;
    upperLeftLayout->addWidget(rootInput);

    upperRightLayout = new QHBoxLayout;
    upperRightLayout->addWidget(infoBtn);
    upperRightLayout->addWidget(exportImageBtn);

    rightBottomLayout = new QHBoxLayout();
    rightBottomLayout->addWidget(balanceBtn);
    rightBottomLayout->addWidget(removeTreeBtn);

    formLayout = new QFormLayout;
    formLayout->addRow("Root Value:", upperLeftLayout);
    formLayout->addWidget(addRootBtn);
    formLayout->addWidget(removeRootBtn);
    formLayout->addRow("Parent Value:", parentInput);
    formLayout->addRow("Node Value:", nodeInput);
    formLayout->addWidget(addNodeBtn);
    formLayout->addWidget(removeNodeBtn);

    leftLayout = new QVBoxLayout;
    leftLayout->addLayout(formLayout);
    leftLayout->setAlignment(Qt::AlignCenter);

    rightLayout = new QVBoxLayout;
    rightLayout->addLayout(upperRightLayout);
    rightLayout->addWidget(view, 1);
    rightLayout->addLayout(rightBottomLayout);

    mainLayout = new QHBoxLayout(this);
    mainLayout->addLayout(leftLayout, 1);
    mainLayout->addLayout(rightLayout, 3);

    setLayout(mainLayout);
    setUpConnections();
}

void View::setUpConnections() {
    auto addRoot = [this]() {
        emit onAddRootRequested(rootInput->text());
    };

    auto addNode = [this]() {
        emit onAddNodeRequested(parentInput->text(), nodeInput->text());
    };

    auto removeNode = [this]() {
        emit onRemoveNodeRequested(parentInput->text(), nodeInput->text());
    };

    connect(addRootBtn, &QPushButton::clicked, this, addRoot);
    connect(addNodeBtn, &QPushButton::clicked, this, addNode);
    connect(removeRootBtn, &QPushButton::clicked, this, &View::onRemoveRootRequested);
    connect(removeNodeBtn, &QPushButton::clicked, this, removeNode);
    connect(infoBtn, &QPushButton::clicked, this, &View::onInfoRequested);
    connect(balanceBtn, &QPushButton::clicked, this, &View::onBalanceRequested);
    connect(removeTreeBtn, &QPushButton::clicked, this, &View::onRemoveTreeRequested);
    connect(exportImageBtn, &QPushButton::clicked, this, &View::onExportRequested);
}

void View::clearScene() const {
    scene->clear();
}

void View::drawCircle(const int centerX, const int centerY, const int radius, const QColor &color) const {
    const QPen pen(color);
    scene->addEllipse(centerX - radius, centerY - radius, radius * 2, radius * 2, pen);
}

void View::drawText(const int x, const int y, const QString &text) const {
    QGraphicsTextItem* label = scene->addText(text);
    label->setDefaultTextColor(Qt::black);
    label->setPos(x, y);
}

void View::drawLine(const int startX, const int startY, const int endX, const int endY, const QColor &color) const {
    const QPen pen(color);
    scene->addLine(startX, startY, endX, endY,pen);
}

void View::showMessage(const QString &message) {
    QMessageBox::information(this, "Tree Info", message);
}

void View::showUserFeedback(const QString &message, const bool success) {
    QMessageBox::information(this, success ? "Success" : "Oops", message);
}

bool View::showConfirmation(const QString &message) {
    const QMessageBox::StandardButton reply = QMessageBox::question(this, "", message,
                                                              QMessageBox::Yes | QMessageBox::No);
    return reply == QMessageBox::Yes;
}

void View::render(QImage& image) const {
    if (!scene || scene->items().isEmpty()) return;

    constexpr qreal scaleFactor = 3.0;
    const QRectF bounds = scene->itemsBoundingRect();
    image = QImage((bounds.size() * scaleFactor).toSize(), QImage::Format_ARGB32);
    image.fill(Qt::white);

    QPainter painter(&image);
    scene->render(&painter, QRectF(), bounds);
    painter.end();
}
