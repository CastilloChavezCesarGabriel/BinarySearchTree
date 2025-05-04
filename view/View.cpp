#include "View.h"
#include <QFormLayout>
#include <QPushButton>
#include <QGraphicsEllipseItem>
#include <QGraphicsView>
#include <QMessageBox>

View::View(QWidget *parent) : QWidget(parent) {
    setupUI();
}

void View::setupUI() {
    setWindowTitle("Binary Search Tree");
    resize(650, 350);

    scene = new QGraphicsScene(this);
    scene->setBackgroundBrush(Qt::white);
    view = new QGraphicsView(scene);

    rootInput = new QLineEdit;
    createRootBtn = new QPushButton("Create Root");
    deleteRootBtn = new QPushButton("Delete Root");

    parentInput = new QLineEdit;

    sideInput = new QComboBox();
    sideInput->addItem("left");
    sideInput->addItem("right");

    valueInput = new QLineEdit;
    createNodeBtn = new QPushButton("Create Node");
    deleteNodeBtn = new QPushButton("Delete Node");

    balanceBtn = new QPushButton("Balance Tree");
    balanceLayout = new QHBoxLayout();
    balanceLayout->addWidget(balanceBtn);

    infoBtn = new QPushButton("Show Info");
    exportImageBtn = new QPushButton("Export BST");

    mainLayout = new QHBoxLayout(this);
    leftLayout = new QVBoxLayout;

    topLeftLayout = new QHBoxLayout;
    topLeftLayout->addWidget(rootInput);

    topRightLayout = new QHBoxLayout;
    topRightLayout->addWidget(infoBtn);
    topRightLayout->addWidget(exportImageBtn);

    formLayout = new QFormLayout;
    formLayout->addRow("Root Value:", topLeftLayout);
    formLayout->addWidget(createRootBtn);
    formLayout->addWidget(deleteRootBtn);
    formLayout->addRow("Parent Value:", parentInput);
    formLayout->addRow("Side:", sideInput);
    formLayout->addRow("New Node Value:", valueInput);
    formLayout->addWidget(createNodeBtn);
    formLayout->addWidget(deleteNodeBtn);
    formLayout->addRow(balanceLayout);

    leftLayout->addLayout(formLayout);
    leftLayout->setAlignment(Qt::AlignVCenter);

    rightLayout = new QVBoxLayout;
    rightLayout->addLayout(topRightLayout);
    rightLayout->addWidget(view, 1);

    mainLayout->addLayout(leftLayout, 1);
    mainLayout->addLayout(rightLayout, 3);

    setLayout(mainLayout);
}

QPushButton* View::getCreateRootButton() const {
    return createRootBtn;
}

QPushButton* View::getCreateNodeButton() const {
    return createNodeBtn;
}

QPushButton* View::getDeleteRootButton() const {
    return deleteRootBtn;
}

QPushButton* View::getDeleteNodeButton() const {
    return deleteNodeBtn;
}

QPushButton* View::getBalanceButton() const {
    return balanceBtn;
}

QPushButton* View::getInfoButton() const {
    return infoBtn;
}

QPushButton* View::getExportButton() const {
    return exportImageBtn;
}

QString View::getRootValue() const {
    return rootInput->text();
}

QLineEdit* View::getParentValue() const {
    return parentInput;
}

QComboBox* View::getSideValue() const {
    return sideInput;
}

QLineEdit* View::getValue() const {
    return valueInput;
}

QGraphicsScene* View::getScene() const {
    return scene;
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

bool View::showConfirmation(const QString &message, const QString &title) {
    const QMessageBox::StandardButton reply = QMessageBox::question(this, title, message,
                                                              QMessageBox::Yes | QMessageBox::No);
    return reply == QMessageBox::Yes;
}

bool View::isValidInput(const QString& text, float& value, QString* errorMessage) {
    bool ok;
    value = text.toFloat(&ok);
    if (!ok && errorMessage) {
        *errorMessage = "Invalid float input!";
    }
    return ok;
}