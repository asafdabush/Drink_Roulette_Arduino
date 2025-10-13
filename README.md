# 🎰 Drink Roulette – Arduino LED Game

A simple and fun **Arduino-based roulette** that randomly selects a drink by lighting one of three lamps — Arak, Tequila, or Van Gogh.

---

## 🧠 Overview
When idle, all LEDs are ON.  
Pressing the button starts a fast “roulette” sequence that stops randomly on one lamp for 10 seconds.  
Pressing again restarts the spin.  

Demonstrates:
- Digital output control  
- Random number generation (`random()`)  
- Timing (`delay()`)  
- State switching via button input  

---

## ⚡ Hardware
| Component | Quantity | Note |
|------------|-----------|------|
| Arduino Nano | 1 | Main controller |
| LEDs | 3 | Represent the drinks |
| N-MOSFETs (e.g. BS170) | 3 | Drive LEDs |
| Push Button | 1 | Input control |
| Resistors | As needed | 220 Ω for LEDs, 10 kΩ for pull-downs |
| 5 V Power Supply | 1 | Common rail |

---

## 🎥 Demo
<video width="500" controls>
  <source src="media/demo_video.mp4" type="video/mp4">
  Your browser does not support the video tag.
</video>

---

## 📸 Photos
| Setup | Final Version |
|--------|----------------|
| ![Setup](media/setup_photo.jpg) | ![Final](media/final_photo.jpg) |

---

## 🧰 Tools Used
- Arduino IDE  
- Basic breadboard prototyping  
- Random number and delay control  
- MOSFET switching logic  

---

## 👤 Author
**Asaf Refael Dabush**  
Ariel University, 2026  
