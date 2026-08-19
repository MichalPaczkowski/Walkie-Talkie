# Walkie-Talkie
# Cyfrowy Radiotelefon Walkie-Talkie ESP32 (ESP-NOW & I2S Audio)

Przenośny, cyfrowy komunikator radiowy dwukierunkowy (walkie-talkie) oparty na mikrokontrolerze **ESP32**. Układ rejestruje i odtwarza dźwięk za pośrednictwem cyfrowej magistrali **I2S** oraz przesyła pakiety audio w paśmie **2.4 GHz** z wykorzystaniem protokołu bezpośredniego **ESP-NOW** (bez potrzeby łączenia z routerem Wi-Fi). Całość została zamknięta w dedykowanej obudowie zoptymalizowanej pod druk 3D, zaprojektowanej w programie **Autodesk Fusion 360**.

---

## 🚀 Kluczowe Funkcje

* **Bezpośrednia komunikacja Peer-to-Peer:** Transmisja pakietów radiowych o niskim opóźnieniu w paśmie 2.4 GHz przy użyciu protokołu ESP-NOW.
* **W pełni cyfrowy tor audio (I2S):** Eliminacja szumów i zakłóceń analogowych, precyzyjne próbkowanie oraz czyste odtwarzanie dźwięku.
* **Przycisk Push-to-Talk (PTT):** Sprzętowe wyzwalanie nadawania głosu.
* **Dedykowana konstrukcja mechaniczna:** Wydzielona komora akustyczna na głośnik, gniazdo montażowe na antenę  oraz spasowanie elementów obudowy na wcisk.
* **Zasilanie akumulatorowe:** Zintegrowany układ ładowania ogniwa Li-Ion przez port USB.

---

## 🛠️ Zastosowane Komponenty (BOM)

| Element | Model / Opis | Interfejs / Protokół |
| :--- | :--- | :--- |
| **Mikrokontroler** | ESP32-WROOM-32 (płytka rozwojowa) | SPI / I2S / RF 2.4 GHz |
| **Mikrofon** | INMP441 – cyfrowy mikrofon dookólny | Magistrala I2S (Wejście) |
| **Wzmacniacz Audio** | MAX98357A – wzmacniacz audio  przetwornikiem DAC | Magistrala I2S (Wyjście) |
| **Głośnik** | Miniaturowy głośnik dynamiczny 8Ω / 2W | Sygnał ze wzmacniacza |
| **Tor radiowy / Antena** | Zewnętrzna antena 2.4 GHz | RF 2.4 GHz |
| **Układ zasilania** | Moduł ładowarki TP4056 (USB-C) + akumulator Li-Ion | 3.7V – 4.2V DC |
| **Sterowanie** | Przyciski microswitch (PTT, włącznik zasilania) | GPIO (Wejścia cyfrowe) |
| **Obudowa** | Dedykowany projekt 3D (druk FDM z materiału) | Zaprojektowana w Fusion 360 |

---

## 🧠 Architektura Systemu i Przepływ Sygnału

```text
[ Nadajnik TX ]
Mowa -> Mikrofon INMP441 -> Próbki audio I2S -> ESP32 -> Pakiety radiowe ESP-NOW (2.4 GHz)
                                                                     │
                                                                     ▼
[ Odbiornik RX ]
Głośnik <- Wzmacniacz MAX98357A <- Strumień I2S <- ESP32 <- Odbiór pakietów ESP-NOW
                                                                    
