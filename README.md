# pingapka - Monitor Sieci z AI

**Pingapka** to nowoczesna aplikacja desktopowa stworzona w środowisku Qt 6, służąca do monitorowania opóźnień sieciowych (ping) oraz inteligentnej analizy danych przy użyciu modelu językowego (LLM).

## 🚀 Funkcje (Wymagania na 5.0)
- **Wielowątkowość:** Proces pingowania odbywa się w tle przy użyciu `QtConcurrent`, dzięki czemu GUI pozostaje responsywne.
- **Integracja z AI:** Wykorzystanie modelu Gemma 3 (via Ollama) do generowania dedykowanych skryptów wizualizacji danych w Pythonie.
- **GUI:** Przejrzysty interfejs zbudowany w oparciu o framework Qt.
- **Analiza danych:** Automatyczne generowanie wykresów za pomocą bibliotek `pandas` i `matplotlib`.
- **Testy jednostkowe:** Zaimplementowane testy w module `Qt Test`.

## 🛠 Technologie
- **Język:** C++ (Standard 17/20)
- **Framework:** Qt 6.10
- **AI Model:** Gemma 3 (12b)
- **Skryptowanie:** Python 3 (Pandas, Matplotlib)
- **Dokumentacja:** Doxygen

## 📖 Dokumentacja
Pełna dokumentacja techniczna projektu dostępna jest pod adresem:
https://zuzannasobczakk.github.io/pingapka/

## 🏗️ Jak uruchomić?
(wpierw nalezy zapoznac sie z plikiem requirements)
1. Upewnij się, że masz zainstalowane Qt 6.
2. Uruchom serwer Ollama z modelem `gemma3:12b`.
3. Skompiluj projekt za pomocą CMake.
4. Wymagane biblioteki Pythona: `pip install pandas matplotlib`.
