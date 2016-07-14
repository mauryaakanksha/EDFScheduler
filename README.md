# EDFScheduler
A car monitoring and emergency detection system for which uses following sensors and actuators connected to RPi2:
1.	Button: Ignition button to start/stop the engine.
2.	Two-color LED: While the engine is on, the ignition LED is also on.
3.	Auto-flash LED: Warning indicator - when the engine temperature is higher than a threshold, it will start flashing.
4.	RGB LED: Varies actuation when different warning/alert scenarios are seen
5.	Active Buzzer: Audible alarm when temperature threshold is exceeded

Implements a software that correctly interacts with them and an EDF scheduler that manages the sensing program in an energy efficient manner.
