///@file mainwindow.h
/// @brief główne okno aplikacji pingapka.
/// @autor Zuzanna Sobczak i Katarzyna Staśczak
///
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QVector>
#include <QNetworkAccessManager>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
/**
 * @class MainWindow
 * @brief Klasa zarządzająca interfejsem użytkownika oraz logiką testowania połączenia (ping).
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
    friend class PingapkaTest;

public:
    /**
     * @brief Konstruktor głównego okna.
     * @param parent Wskaźnik na rodzica okna (domyślnie nullptr).
     */
    MainWindow(QWidget *parent = nullptr);
    /**
     * @brief Destruktor klasy MainWindow. Czyści zasoby UI i pamięć.
     */
    ~MainWindow();

private slots:
    /**
     * @brief Slot wywoływany po kliknięciu przycisku "Gotowe".
     * Rozpoczyna proces sprawdzania wpisanego adresu.
     */
    void on_btnGotowe_clicked();
    /**
     * @brief Slot wywoływany po kliknięciu przycisku "Wykres".
     * Generuje i wyświetla wizualizację zebranych danych.
     */
    void on_btnWykres_clicked();

private:
    Ui::MainWindow *ui; ///< Wskaźnik na interfejs użytkownika zaprojektowany w Qt Designerze.
    QVector<double> pingTimes;///< Kontener przechowujący czasy odpowiedzi (ping) w milisekundach.
    QNetworkAccessManager *networkManager;///< Zarządca operacji sieciowych.
    /**
     * @brief Przeprowadza test opóźnienia (ping) dla podanego adresu IP.
     * @param ip Ciąg znaków zawierający adres docelowy.
     */
    void runPing(QString ip);
    /**
     * @brief Zapisuje zebrane wyniki testów do pliku tekstowego lub bazy danych.
     */
    void saveResults();
    /**
     * @brief Tworzy kod skryptu w języku Python służący do zaawansowanej analizy danych.
     * @return QString zawierający pełny kod skryptu Python.
     */
    QString generatePythonScript();
    /**
     * @brief Uruchamia zewnętrzny skrypt Python.
     * @param script Treść skryptu do wykonania.
     */
    void runPythonScript(QString script);
};

#endif