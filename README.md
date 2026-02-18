# Observator-Intersection 🚗
Welcome to the **Observator Intersection** project, an automated traffic management system built with an ATmega32 controller. **The goal:** To synchronize vehicle and pedestrian traffic across two main directions (Observator -> Zorilor/Zorilor -> Observator and Mama Manu -> Observator) using hardware timers and interrupts to ensure safety and efficiency. We encourage you to see how embedded C can manage real-world infrascture.
# Description 📖
The project simulates a four way intersection. The system uses three distinct hardware timers to handle state transitions and visual signaling: **Timer 0** manages the master clock for state changes, while **Timer 1** and **Timer 2** control the blinking of pedestrian signals. By manipulating PORTA through PORTD, the system control a complex array of LEDs representing traffic lights for multiple lanes.
# Features 🌟
* **Synchronyzed State Machine:** Manages three distinct phases for Traffic light A and Traffic light B, ensuring that intersecting traffic never has a green light simultaneously.
* **Precision timing:** Using OCR0 = 125 with a prescaler to generate accurate 1ms interrupts for counting down light durations.
* **Active pedestrian signaling:** Features dedicated interrupt service routines for **Timer 1** and **Timer 2** to create blinking effects for pedestrian crossing.
* **Binary Port Mapping:** Controls multiple LEDs banks by writing directly to registers:
* * **PORTB:** Secondary signals and lane indicators/
  * **PORTC & PORTD:** Primary intersection traffic lights.
  * **PORTAL** Pedestrian indicator lights with toggle logic.
* **Automated cycle:** Operates in a continuos loop once initialized, requiring no external input to mantain the flow of the intersection.
# Hardware Components ⚙️
* **Microcontroller:** ATmega32.
* **Development board:** EasyAVR v7.
* **Indicators:** Red, yellow and green LEDs across 4 ports.
* **Timing System:** Internal Crystal Oscillator utilizing 8-bit and 16-bit timers.
