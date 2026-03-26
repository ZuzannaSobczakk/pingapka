/**
 * @file mainwindow.h
 * @brief Główne okno aplikacji Pingapka.
 * @details Zawiera definicję klasy MainWindow zarządzającej interfejsem oraz logiką komunikacji z AI i systemem.
 * @authors Zuzanna Sobczak i Katarzyna Staśczak
 */

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

/**
 * @class MainWindow
 * @brief Klasa odpowiedzialna za zarządzanie GUI, procesami sieciowymi (ping) oraz integrację z modelem LLM.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

    /** @brief Pozwala klasie testowej na dostęp do prywatnych pól (wymagane dla poprawnego działania testów jednostkowych). */
    friend class PingapkaTest;

public:
    /**
     * @brief Konstruktor klasy MainWindow. Inicjalizuje UI oraz managera sieci.
     * @param parent Wskaźnik na obiekt nadrzędny (domyślnie nullptr).
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destruktor klasy MainWindow. Zwalnia zasoby zajmowane przez interfejs.
     */
    ~MainWindow();

signals:
    /**
     * @brief Sygnał emitowany po zakończeniu operacji pingowania w osobnym wątku roboczym.
     * @details Umożliwia bezpieczne powiadomienie głównego wątku (UI) o gotowości danych.
     */
    void pingFinished();

private slots:
    /**
     * @brief Obsługuje kliknięcie przycisku "Gotowe". Inicjuje proces pingowania asynchronicznego.
     */
    void on_btnGotowe_clicked();

    /**
     * @brief Obsługuje kliknięcie przycisku "Wykres". Rozpoczyna proces generowania skryptu przez AI.
     */
    void on_btnWykres_clicked();

    /**
     * @brief Slot odbierający sygnał o zakończeniu pingowania. Odświeża UI i zapisuje wyniki.
     */
    void handlePingResults();

private:
    Ui::MainWindow *ui; ///< Wskaźnik na komponenty interfejsu użytkownika.
    QVector<double> pingTimes; ///< Kontener przechowujący zebrane czasy odpowiedzi (ms).
    QNetworkAccessManager *networkManager; ///< Manager odpowiedzialny za komunikację z API modelu językowego.

    /**
     * @brief Wykonuje operację pingowania. Funkcja przeznaczona do pracy w tle (wątek roboczy).
     * @param ip Adres docelowy do przetestowania.
     */
    void runPing(QString ip);

    /**
     * @brief Zapisuje zebrane dane do pliku CSV, który służy jako wejście dla skryptu Python.
     */
    void saveResults();

    /**
     * @brief Komunikuje się z lokalnym modelem LLM (np. Gemma) w celu wygenerowania kodu wizualizacji danych.
     * @return QString Wygenerowany kod Python lub skrypt rezerwowy (fallback).
     */
    QString generatePythonScript();

    /**
     * @brief Zapisuje kod do pliku .py i uruchamia zewnętrzny interpreter Pythona (podejście wieloprocesowe).
     * @param script Treść skryptu Python do wykonania.
     */
    void runPythonScript(QString script);
};

#endif // MAINWINDOW_H