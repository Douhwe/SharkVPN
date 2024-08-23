#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QProcess>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void returnServerName();

private:
    QTextEdit *terminal;
    QProcess *ipRetrievalProcess;
};
#endif // MAINWINDOW_H
