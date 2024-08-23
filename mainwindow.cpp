#include "mainwindow.h"
#include <QLabel>
#include <QPushButton>
#include <QMenu>
#include <QProcess>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QPalette>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), terminal(nullptr),
    ipRetrievalProcess(nullptr)
{
    setWindowTitle("SharkVPN Prototype");
    resize(1000, 650);
    
    //Central Widget to hold layout
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    //Vertical layout to organize widgets
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->setSpacing(5);

    // Terminal Configuration
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
    connect(ServerMenu->addAction("US-East"), &QAction::triggered, this, &MainWindow::returnServerName);
    connect(ServerMenu->addAction("US-West"), &QAction::triggered, this, &MainWindow::returnServerName);
    connect(ServerMenu->addAction("Canada"), &QAction::triggered, this, &MainWindow::returnServerName);
    connect(ServerMenu->addAction("Mexico"), &QAction::triggered, this, &MainWindow::returnServerName);
    connect(ServerMenu->addAction("London"), &QAction::triggered, this, &MainWindow::returnServerName);

    ServerSelectionButton->setMenu(ServerMenu);



    ipRetrievalProcess = new QProcess(this);
    QPushButton *ipRetrievalButton = new QPushButton("Check Current IP", this);
    ipRetrievalButton->setFixedWidth(150);

    //Process begins
    connect(ipRetrievalButton, &QPushButton::clicked, this, [this]() {
        ipRetrievalProcess->start("curl", QStringList() << "icanhazip.com");
    });

    //Read from Process upon Completion
    connect(ipRetrievalProcess, &QProcess::readyReadStandardOutput, this, [this]() {
        QString ipAddress = ipRetrievalProcess->readAllStandardOutput();
        terminal->append("Current IP Address: " + ipAddress.trimmed());
    });

    ipRetrievalButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ServerSelectionButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    layout->addWidget(ipRetrievalButton, 0, Qt::AlignLeft | Qt::AlignTop);
    layout->addWidget(ServerSelectionButton, 0, Qt::AlignLeft | Qt::AlignTop);
    layout->addWidget(terminal, 1, Qt::AlignCenter | Qt::AlignBottom);


}

//Qt handles deleting child objects when the parent is destroyed (Parent being "this")
MainWindow::~MainWindow() {}

//Slot Functions
void MainWindow::returnServerName() {
    //Sender returns Pointer to object emitting signal, qobject_cast casts Object Pointer to Specific Type
    QAction *action = qobject_cast<QAction*>(sender());

    if (action) {
        QString serverName = action->text();
        terminal->append("Switching Server to " + serverName);
    }
}
