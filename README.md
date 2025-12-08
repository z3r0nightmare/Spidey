# 🕷️ Spider – The Robotic Pet

**Spider** is a small, open-source quadruped robot built using affordable components.  
Designed around the **Arduino Nano**, it combines **motion, expression, and wireless control** to make robotics fun and approachable. It features a custom walking gait, expressive OLED eyes, and full Bluetooth remote control via your phone.

---

## 🚀 Features

- 🦾 **Quadruped Design** – 8× SG90 servos for articulated leg movement.
- 🧠 **Arduino Nano + PCA9685** – Efficient 16-channel servo control via I2C.
- 📱 **Bluetooth Control** – Wireless walking, dancing (twerking), and actions via a specific Android app.
- 🔋 **High-Current Power** – Powered by 2× 18650 Li-Ion batteries with separate logic/motor rails.
- 🖥️ **OLED Eyes** – Animated expressions (Happy, Focused, Wink, Sleep) that react to commands.
- 🧩 **Modular Chassis** – 3D printed parts designed for easy modification.

---

## 🧰 Components Used

| Component | Quantity | Description |
|------------|-----------|-------------|
| Arduino Nano | 1 | Main microcontroller |
| PCA9685 Servo Driver | 1 | 16-Channel PWM driver (I2C) |
| SG90 Servo Motor | 8 | Joints (4 Hips, 4 Knees) |
| HC-05 Bluetooth Module | 1 | For wireless app control |
| 18650 Batteries | 2 | 7.4V Power Source |
| OLED Display (SSD1306) | 1 | 128x64 I2C Display |
| Jumper Wires & Screws | – | Wiring and assembly |

---

## ⚡ Circuit Diagram & Wiring

The robot uses a **Split Power System** to prevent brownouts. The servos draw power directly from the batteries, while the Arduino gets regulated power via VIN.

![Circuit Diagram Placeholder](https://via.placeholder.com/800x400?text=Insert+Your+Circuit+Diagram+Here)
*(Replace this image link with your own circuit diagram)*

### 1. Power Connections
* **Battery (+)** → **PCA9685 Green Terminal (+)** → **Arduino VIN**
* **Battery (-)** → **PCA9685 Green Terminal (-)** → **Arduino GND**
    * *Note: Do not power servos through the Arduino 5V pin!*

### 2. Logic Connections (I2C Bus)
* **PCA9685 SDA** → **Arduino A4**
* **PCA9685 SCL** → **Arduino A5**
* **PCA9685 VCC** → **Arduino 5V**
* **PCA9685 GND** → **Arduino GND**
* *(Optional OLED shares the same SDA/SCL pins)*

### 3. Bluetooth (HC-05)
* **HC-05 VCC** → **Arduino 5V**
* **HC-05 GND** → **Arduino GND**
* **HC-05 TX** → **Arduino D10** (SoftwareSerial RX)
* **HC-05 RX** → **Arduino D11** (SoftwareSerial TX)

### 4. Servo Pin Mapping
*Connect servos to the PCA9685 board pins as follows:*

| Leg | Position | Hip Pin | Knee Pin | Notes |
| :--- | :--- | :--- | :--- | :--- |
| **Leg 1** | Front Right | 0 | 1 | Normal |
| **Leg 2** | Back Right | 2 | 3 | Normal |
| **Leg 3** | Back Left | **5** | **4** | **SWAPPED** (Hip=5, Knee=4) |
| **Leg 4** | Front Left | 6 | 7 | Normal |

---

## 📱 Mobile App Configuration

To control the robot, you need to use a specific app that supports **Gamepad Mode**.

1.  **Download:** Go to the Google Play Store and download **"Arduino Bluetooth Control"** (look for the controller icon).
2.  **Connect:** Pair your phone with the HC-05 module (Default pin is usually `1234` or `0000`).
3.  **Mode:** Open the app, connect to the robot, and select **"Gamepad Mode"**.
4.  **Button Mapping:**
    The code is pre-configured to work with the default keys of this app:
    * **Forward Arrow (F):** Walk Forward
    * **Circle Button (C):** Twerk (Dance)
    * **Triangle Button (T):** Hello (Wave)
    * **Cross Button (X):** Stop / Home Position
    * **Pause Button (P):** Stop / Home Position

---

## ⚙️ Setup & Usage

1.  **3D Print** the chassis parts.
2.  **Wiring:** Follow the circuit diagram above. Ensure Leg 3 wires are swapped (Pin 5/4) as per the code logic.
3.  **Upload Code:** Flash the `Spider_Main.ino` to the Nano via Arduino IDE.
4.  **Power Up:** Turn on the battery switch. The robot will move to the "Home" position and wait.
5.  **Connect & Play:** Open the app, hit connect, and press **Forward** to make it walk!

---

## 🔮 Future Upgrades (Planned)

- 📡 **ESP32 Upgrade** – Replace Nano with ESP32 for built-in Bluetooth/WiFi and faster processing.
- 📐 **Inverse Kinematics** – Smoother, mathematically calculated leg movement.
- 🦇 **Ultrasonic Sensors** – Obstacle avoidance and autonomous roaming mode.
- 🗣️ **Voice Control** – Commands via voice recognition module.

---

## 🤝 Contribute

Spider is **open source** — feel free to fork, modify, and share your own version!
If you fix a bug or design a cool new chassis, pull requests are welcome.

---

## 📸 Credits

Developed by **Biswa (Secr0ti)** Follow for more open-source robotics and creative hardware projects 👇  
📷 [Instagram – @secr0ti](https://instagram.com/secr0ti)
