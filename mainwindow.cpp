
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QProcess>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkProxy>
#include <QEventLoop>
#include <QDebug>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QCoreApplication>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    networkManager = new QNetworkAccessManager(this);
    networkManager->setProxy(QNetworkProxy::NoProxy);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnGotowe_clicked()
{
    QString ip = ui->IP->text();
    if(ip.isEmpty()) {
        ui->pingResult->setText("Wpisz adres IP!");
        return;
    }
    runPing(ip);
    saveResults();
}


void MainWindow::runPing(QString ip)
{
    pingTimes.clear();
    QProcess process;

#ifdef Q_OS_WIN
    process.start("ping", QStringList() << "-n" << "10" << ip);
#else
    process.start("ping", QStringList() << "-c" << "10" << ip);
#endif
    process.waitForFinished();
    QString output = process.readAllStandardOutput();

    QRegularExpression regex("time[=<]?\\s*([0-9]+)ms");
    auto it = regex.globalMatch(output);
    while(it.hasNext()) {
        pingTimes.append(it.next().captured(1).toDouble());
    }

    if(!pingTimes.isEmpty()) {
        ui->pingResult->setText("Dane zebrane! Kliknij teraz generowanie wykresu.");
    } else {
        ui->pingResult->setText("Błąd: Host nie odpowiedział.");
    }
}


void MainWindow::saveResults()
{

    QString path = QCoreApplication::applicationDirPath() + "/ping_results.csv";
    QFile file(path);
    if(file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file);
        // --- TO JEST NOWA LINIA (ROZWIĄZUJE BŁĄD KEYERROR) ---
        out << "Ping\n";
        // -----------------------------------------------------
        for(double &t : pingTimes) {
            out << t << "\n";
        }
        file.close();
        //qDebug() << "Zapisano CSV z nagłówkiem do: " << path;
    }
}


QString MainWindow::generatePythonScript()
{
    QUrl url("http://127.0.0.1:11434/api/generate");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QString csvPath = QCoreApplication::applicationDirPath() + "/ping_results.csv";
    csvPath.replace("\\", "/");

    QJsonObject json;
    json["model"] = "gemma3:12b";

    json["system"] = "You are a specialized C++ helper that returns ONLY pure Python code. "
                     "No markdown, no explanations, no backticks.";

    json["prompt"] = QString("Write Python code using pandas and matplotlib. "
                             "Read the file '%1'. The file has a header 'Ping'. "
                             "Plot the 'Ping' column and show the chart.").arg(csvPath);
    json["stream"] = false;

    QNetworkReply *reply = networkManager->post(request, QJsonDocument(json).toJson());

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QByteArray data = reply->readAll();
    reply->deleteLater();

    QJsonDocument responseJson = QJsonDocument::fromJson(data);
   return responseJson.object().value("response").toString().trimmed();
}


void MainWindow::runPythonScript(QString script)
{

    if (script.contains("```")) {
        QRegularExpression codeRegex("```(?:python)?\\s*(.*?)\\s*```", QRegularExpression::DotMatchesEverythingOption);
        auto match = codeRegex.match(script);
        if (match.hasMatch()) script = match.captured(1).trimmed();
    }

    if(script.isEmpty()) return;

    QString path = QCoreApplication::applicationDirPath() + "/plot.py";
    QFile file(path);
    if(file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file);
        out << script;
        file.close();
    }


    QProcess::startDetached("python", QStringList() << path);
}

void MainWindow::on_btnWykres_clicked()
{
    ui->pingResult->setText("AI generuje wykres... Czekaj...");
    QCoreApplication::processEvents();

    QString script = generatePythonScript();

    if(!script.isEmpty()) {
        runPythonScript(script);
        ui->pingResult->setText("Wykres powinien się pojawić!");
    } else {
        ui->pingResult->setText("Błąd: Brak odpowiedzi od AI.");
    }
}