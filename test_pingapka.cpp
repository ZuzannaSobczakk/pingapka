#include <QtTest>
#include <QCoreApplication>

class PingapkaTest : public QObject {
    Q_OBJECT
private slots:
    void test_matematyki() {
        int wynik = 2 + 2;
        QCOMPARE(wynik, 4);
    }

    void test_napisu() {
        QString str = "Pingapka";
        QVERIFY(str.startsWith("Ping"));
    }
};

QTEST_MAIN(PingapkaTest)
#include "test_pingapka.moc"