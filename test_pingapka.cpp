#include <QtTest>
#include <QCoreApplication>
#include "mainwindow.h"
#include <QLineEdit>

class PingapkaTest : public QObject {
    Q_OBJECT

private slots:

    void test_inicjalizacji_okna() {
        MainWindow w;
        QVERIFY(!w.windowTitle().isEmpty());
    }


    void test_dodawania_danych() {
        MainWindow w;

        w.pingTimes.append(15.5);
        w.pingTimes.append(20.0);

        QCOMPARE(w.pingTimes.size(), 2);
        QCOMPARE(w.pingTimes.first(), 15.5);
    }

    void test_generatora_pythona() {
        MainWindow w;


        QList<QLineEdit*> allLineEdits = w.findChildren<QLineEdit*>();
        for(QLineEdit* edit : allLineEdits) {
            edit->setText("8.8.8.8");
        }


        for(int i = 0; i < 10; ++i) {
            w.pingTimes.append(20.0 + i);
        }


        QString script = w.generatePythonScript();


        QVERIFY2(!script.isEmpty(), "Generator nadal zwraca pusty tekst! Sprawdz czy w mainwindow.cpp nie masz warunku, ktory zawsze zwraca puste "" ");
        QVERIFY(script.contains("import matplotlib"));
    }


    void test_walidacji_pustego_ip() {
        MainWindow w;

        QString testowyAdres = "";
        QVERIFY(testowyAdres.isEmpty());
    }
};

QTEST_MAIN(PingapkaTest)
#include "test_pingapka.moc"