#ifndef VIEW_H
#define VIEW_H
#include <QFormLayout>
#include <QGraphicsScene>
#include <QLineEdit>
#include <QPushButton>
#include <QGraphicsEllipseItem>
#include <QComboBox>

class View final : public QWidget {
    Q_OBJECT
private:
    QGraphicsView *view{};
    QGraphicsScene *scene{};

    QLineEdit *rootInput{};
    QLineEdit *parentInput{};
    QComboBox *sideInput{};
    QLineEdit *nodeInput{};

    QPushButton *addRootBtn{};
    QPushButton *addNodeBtn{};
    QPushButton *removeRootBtn{};
    QPushButton *removeNodeBtn{};
    QPushButton *balanceBtn{};
    QPushButton *removeTreeBtn{};
    QPushButton *infoBtn{};
    QPushButton *exportImageBtn{};

    QHBoxLayout *mainLayout{};
    QHBoxLayout *upperLeftLayout{};
    QHBoxLayout *upperRightLayout{};
    QHBoxLayout *rightBottomLayout{};
    QVBoxLayout *leftLayout{};
    QVBoxLayout *rightLayout{};
    QFormLayout *formLayout{};

    void setupUI();
    void setUpConnections();

public:
    explicit View(QWidget *parent = nullptr);
    
    void clearScene() const;
    void drawCircle(int centerX, int centerY, int radius, const QColor &color) const;
    void drawText(int x, int y, const QString &text) const;
    void drawLine(int startX, int startY, int endX, int endY, const QColor &color) const;
    void showMessage(const QString &message);
    void showUserFeedback(const QString &message, bool success);
    bool showConfirmation(const QString &message, const QString &title);
    static bool isValidInput(const QString& text, float& value, QString* errorMessage);
    void render(QImage& image) const;

signals:
    void onAddRootRequested(const QString &value);
    void onAddNodeRequested(const QString &parent, const QString &value);
    void onRemoveNodeRequested(const QString &parent, const QString &value);
    void onRemoveRootRequested();
    void onInfoRequested();
    void onBalanceRequested();
    void onRemoveTreeRequested();
    void onExportRequested();
};

#endif //VIEW_H
