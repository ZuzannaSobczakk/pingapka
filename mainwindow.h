#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QVector>
#include <QNetworkAccessManager>
#include <QtConcurrent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    friend class PingapkaTest;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void pingFinished();

private slots:
    void on_btnGotowe_clicked();
    void on_btnWykres_clicked();
    void handlePingResults();

private:
    Ui::MainWindow *ui;
    QVector<double> pingTimes;
    QNetworkAccessManager *networkManager;

    void runPing(QString ip);
    void saveResults();
    QString generatePythonScript();
    void runPythonScript(QString script);
};

#endif