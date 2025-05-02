#ifndef VIEW_H
#define VIEW_H
#include <QFormLayout>
#include <QWidget>
#include <QGraphicsScene>
#include <QLineEdit>
#include <QPushButton>
#include <QGraphicsEllipseItem>
#include <QComboBox>

class View final : public QWidget {
    Q_OBJECT
public:
    explicit View(QWidget *parent = nullptr);
    QPushButton* getCreateRootButton() const;
    QPushButton* getCreateNodeButton() const;
    QPushButton* getDeleteRootButton() const;
    QPushButton* getDeleteNodeButton() const;
    QPushButton* getBalanceButton() const;
    QPushButton* getInfoButton() const;
    QString getRootValue() const;
    QLineEdit* getParentValue() const;
    QComboBox* getSideValue() const;
    QLineEdit* getValue() const;


    void clearScene() const;
    void drawCircle(int centerX, int centerY, int radius, const QColor &color) const;
    void drawText(int x, int y, const QString &text) const;
    void drawLine(int startX, int startY, int endX, int endY, const QColor &color) const;
    void showMessage(const QString &message);
    void showUserFeedback(const QString &message, bool success);
    bool showConfirmation(const QString &message, const QString &title);
    static bool isValidInput(const QString& text, float& value, QString* errorMessage);

private:
    QGraphicsView *view{};
    QGraphicsScene *scene{};

    QLineEdit *rootInput{};
    QLineEdit *parentInput{};
    QComboBox* sideInput{};
    QLineEdit *valueInput{};

    QPushButton *createRootBtn{};
    QPushButton *createNodeBtn{};
    QPushButton *deleteRootBtn{};
    QPushButton *deleteNodeBtn{};
    QPushButton *balanceBtn{};
    QPushButton *infoBtn{};

    QHBoxLayout *mainLayout{};
    QHBoxLayout *topLayout{};
    QHBoxLayout *balanceLayout{};
    QVBoxLayout *leftLayout{};
    QVBoxLayout *rightLayout{};
    QFormLayout *formLayout{};

    void setupUI();
};

#endif //VIEW_H
