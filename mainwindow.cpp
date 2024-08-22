#include "mainwindow.h"
#include <QLabel>
#include <QPushButton>
#include <QMenu>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QPalette>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), terminal(nullptr)
{
    setWindowTitle("SharkVPN Prototype");
    resize(1000, 650);
    
    //Central Widget to hold layout
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    //Vertical layout to organize widgets
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    QLabel *label = new QLabel(this);
    label->setText("welcome to sharkvpn!");
    label->move(150, 150);
    label->setFont(QFont("DejaVu Sans", 15, QFont::Bold));
    label->setStyleSheet("color:mediumslateblue");

    terminal = new QTextEdit(this);
    terminal->setReadOnly(true);
    terminal->setFixedSize(550, 150);

    // Configuring Terminal's Visuals to Emulate an actual terminal
    QPalette consolePalette = terminal->palette();
    consolePalette.setBrush(QPalette::Base, QBrush(Qt::black));
    terminal->setPalette(consolePalette);
    terminal->setFont(QFont("Consolas", 10, QFont::DemiBold));
    terminal->setStyleSheet("color: #00FF00;"); //Neon Green Color
    terminal->setText("Welcome to SharkVPN!");

    QPushButton *ServerSelectionButton = new QPushButton("Server Selection", this);
    ServerSelectionButton->setFixedWidth(150);
    // QSize size = (*ServerSelectionButton).size();
    // qDebug() << "Width:" << size.width() << "Height:" << size.height();

    QMenu *ServerMenu = new QMenu();
    connect(ServerMenu->addAction("US-East"), &QAction::triggered, this, &MainWindow::onServerSelection);
    connect(ServerMenu->addAction("US-West"), &QAction::triggered, this, &MainWindow::onServerSelection);
    connect(ServerMenu->addAction("Canada"), &QAction::triggered, this, &MainWindow::onServerSelection);
    connect(ServerMenu->addAction("Mexico"), &QAction::triggered, this, &MainWindow::onServerSelection);
    connect(ServerMenu->addAction("London"), &QAction::triggered, this, &MainWindow::onServerSelection);

    ServerSelectionButton->setMenu(ServerMenu);

    layout->addWidget(ServerSelectionButton, 0, Qt::AlignLeft | Qt::AlignTop);
    layout->addWidget(terminal, 0, Qt::AlignCenter | Qt::AlignBottom);

}

MainWindow::~MainWindow() {}

void MainWindow::onServerSelection() {
    //Sender returns Pointer to object emitting signal, qobject_cast casts Object Pointer to Specific Type
    QAction *action = qobject_cast<QAction*>(sender());

    if (action) {
        QString serverName = action->text();
        terminal->append("Switching Server to " + serverName);
    }
}
