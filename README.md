<h1 align="center">🔐 IoT Embedded Access Control System</h1>

<p align="center">
  <img src="https://img.shields.io/badge/Arduino-%2300979D.svg?style=for-the-badge&logo=arduino&logoColor=white"/>
  <img src="https://img.shields.io/badge/Embedded-Systems-%23FF6F00.svg?style=for-the-badge"/>
  <img src="https://img.shields.io/badge/IoT-%2300C853.svg?style=for-the-badge"/>
  <img src="https://img.shields.io/badge/GSM-Alerts-%231E88E5.svg?style=for-the-badge"/>
</p>

<hr/>

<h2>📌 Problem Motivation</h2>
<p>
Traditional door locks lack intelligence, traceability, and real-time response to unauthorized access.  
This project demonstrates how embedded hardware and IoT communication can create a responsive, user-aware
security system capable of authentication, occupancy monitoring, and automated alerting.
</p>

<h2>🧠 System Overview</h2>
<p>
An Arduino-based smart access control system that authenticates residents through keypad passwords,
monitors entry conditions via sensors, and sends alerts using GSM communication.
The system combines physical security with behavioral monitoring in a low-cost embedded environment.
</p>

---

<h2>🏗 System Architecture</h2>

```
User Input (Keypad)
        │
        ▼
Arduino Controller ─────► LCD Feedback
        │
        ├──► Servo Motor (Door Lock)
        ├──► Ultrasonic Sensor (People Count)
        ├──► Buzzer (Alert)
        └──► GSM Module ──► SMS / Call Notification
```

📌 Replace this section later with an actual diagram image if available:

```
![Architecture Diagram](docs/architecture.png)
```

---

<h2>🛠 Hardware Requirements</h2>

* Arduino Uno (ATmega328P)
* 16x2 LCD (I2C)
* 4x4 Matrix Keypad
* GSM Module (SIM800/SIM900)
* Ultrasonic Sensor HC-SR04
* Servo Motor
* Buzzer
* Breadboard & Jumper Wires
* External GSM Power Supply

---

<h2>🔌 Pin Configuration (Example)</h2>

| Component          | Arduino Pins         |
| ------------------ | -------------------- |
| LCD I2C            | SDA → A4, SCL → A5   |
| Keypad             | D2–D9                |
| Servo              | D10                  |
| Buzzer             | D11                  |
| Ultrasonic Trigger | D12                  |
| Ultrasonic Echo    | D13                  |
| GSM TX/RX          | Software Serial Pins |

*(Modify according to your wiring)*

---

<h2>⚙️ Installation & Setup</h2>

### 1️⃣ Arduino IDE Setup

* Install Arduino IDE
* Install required libraries:

  * Keypad
  * LiquidCrystal_I2C
  * Servo
  * SoftwareSerial

### 2️⃣ Upload Firmware

* Connect Arduino
* Select Board & Port
* Upload `.ino` file

### 3️⃣ GSM Configuration

* Insert active SIM card
* Update phone numbers in code
* Verify signal availability

---

<h2>🔑 Functional Modules</h2>

### Authentication

* Unique password per resident
* Personalized welcome message
* Servo unlock on success

### Intrusion Detection

* Lockout after 3 failed attempts
* SMS + call alerts triggered

### Occupancy Monitoring

* Real-time headcount
* User-specific limits
* Alerts on anomaly detection

---

<h2>🎥 Demo</h2>

Add demo visuals here:

```
![Project Demo](docs/demo.gif)
```

or

```
![Circuit Image](docs/circuit.jpg)
```

---

<h2>📊 Key Takeaways</h2>

* Multi-layer embedded security implementation
* Sensor-based behavioral monitoring
* GSM-based remote alerting
* Practical system design under hardware constraints

---

<h2>🚀 Future Scope</h2>

* Biometric / Face recognition verification
* OTP-based authentication
* Cloud logging & analytics dashboard
* Mobile app remote unlock

---

<h2>👩‍💻 Author</h2>

**Bhoomika Saxena**
B.Tech — Computer Science (IoT & Intelligent Systems)
Embedded AI & IoT Projects | Research | Patents

---

<h2>📜 License</h2>

This project is for academic and research demonstration purposes.

<hr/>

<p align="center">
⭐ If you found this project useful — consider starring the repository!
</p>
