#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QActionGroup>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void showGreeting();
    void setCompactSize();
    void setFullSize();

private:
    void createActions();
    void createMenus();
    void createToolBar();
    QAction *createColorAction(const QString &text, const QColor &color, Qt::Key key);
    void setLabelColor(const QColor &color);

    QLabel *m_label = nullptr;

    QAction *m_greetingAction = nullptr;
    QAction *m_exitAction = nullptr;
    QAction *m_compactAction = nullptr;
    QAction *m_fullSizeAction = nullptr;

    QActionGroup *m_colorGroup = nullptr;
    QList<QAction *> m_colorActions;
};
#endif // MAINWINDOW_H
