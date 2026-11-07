#include "mainwindow.h"

#include <QAction>
#include <QActionGroup>
#include <QColor>
#include <QIcon>
#include <QLabel>
#include <QMenuBar>
#include <QMessageBox>
#include <QPainter>
#include <QPalette>
#include <QPixmap>
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Пример меню Qt");

    m_label = new QLabel("Пример текста", this);
    m_label->setAlignment(Qt::AlignCenter);
    QFont font = m_label->font();
    font.setPointSize(24);
    m_label->setFont(font);
    setCentralWidget(m_label);

    createActions();
    createMenus();
    createToolBar();

    // Начальное состояние: чёрный цвет надписи, компактный размер окна.
    m_colorActions.first()->trigger();
    resize(800, 600);
}

MainWindow::~MainWindow() = default;

void MainWindow::createActions()
{
    // Главное
    m_greetingAction = new QAction(QIcon(":/img/img/greeting.png"), "Приветствие", this);
    m_greetingAction->setShortcut(Qt::CTRL | Qt::Key_G);
    connect(m_greetingAction, &QAction::triggered, this, &MainWindow::showGreeting);

    m_exitAction = new QAction(QIcon(":/img/img/exit.png"), QStringLiteral("Выход"), this);
    m_exitAction->setShortcut(Qt::CTRL | Qt::Key_Q);
    connect(m_exitAction, &QAction::triggered, this, &QWidget::close);

    // Цвет (переключатели)
    m_colorGroup = new QActionGroup(this);
    m_colorGroup->setExclusive(true);
    m_colorActions = {
        createColorAction("чёрный", Qt::black, Qt::Key_1),
        createColorAction("зелёный", QColor(0, 160, 0), Qt::Key_2),
        createColorAction("красный", Qt::red, Qt::Key_3),
        createColorAction("синий", Qt::blue, Qt::Key_4),
    };

    // Вид
    m_compactAction = new QAction(QIcon(":/img/img/small_size.png"), "компактно", this);
    m_compactAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_E));
    connect(m_compactAction, &QAction::triggered, this, &MainWindow::setCompactSize);

    m_fullSizeAction = new QAction(QIcon(":/img/img/full_size.png"), "полный размер", this);
    m_fullSizeAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_W));
    connect(m_fullSizeAction, &QAction::triggered, this, &MainWindow::setFullSize);
}

QAction *MainWindow::createColorAction(const QString &text, const QColor &color, Qt::Key key)
{
    QPixmap pixmap(16, 16);
    pixmap.fill(Qt::transparent);
    {
        QPainter painter(&pixmap);
        painter.setPen(Qt::gray);
        painter.setBrush(color);
        painter.drawRect(0, 0, 15, 15);
    }

    auto *action = new QAction(QIcon(pixmap), text, m_colorGroup);
    action->setCheckable(true);
    action->setShortcut(QKeySequence(Qt::CTRL | key));
    connect(action, &QAction::triggered, this, [this, color] { setLabelColor(color); });
    return action;
}

void MainWindow::createMenus()
{
    QMenu *mainMenu = menuBar()->addMenu("Главное");
    mainMenu->addAction(m_greetingAction);
    mainMenu->addSeparator();
    mainMenu->addAction(m_exitAction);

    QMenu *colorMenu = menuBar()->addMenu("Цвет");
    colorMenu->addActions(m_colorGroup->actions());

    QMenu *viewMenu = menuBar()->addMenu("Вид");
    viewMenu->addAction(m_compactAction);
    viewMenu->addAction(m_fullSizeAction);
}

void MainWindow::createToolBar()
{
    QToolBar *toolBar = addToolBar("Панель инструментов");
    toolBar->setObjectName("mainToolBar");
    toolBar->addAction(m_greetingAction);
    toolBar->addAction(m_exitAction);
    toolBar->addSeparator();
    toolBar->addAction(m_compactAction);
    toolBar->addAction(m_fullSizeAction);
}

void MainWindow::showGreeting()
{
    QMessageBox::information(this, "Приветствие", "Здравствуйте!");
}

void MainWindow::setLabelColor(const QColor &color)
{
    QPalette palette = m_label->palette();
    palette.setColor(QPalette::WindowText, color);
    m_label->setPalette(palette);
}

void MainWindow::setCompactSize()
{
    showNormal();
    resize(800, 600);
}

void MainWindow::setFullSize()
{
    showNormal();
    resize(1200, 900);
}
