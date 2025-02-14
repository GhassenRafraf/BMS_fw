# This project is currently under development.

---
# Battery Management System (BMS) Firmware

## Overview
This project is a firmware implementation for a low-voltage Battery Management System (BMS) using the **STM32F401RE** microcontroller. The firmware is built on **FreeRTOS** with a priority-based task scheduler and static task allocation.

## Features
- **Cell Voltage & Current Measurement**
- **State of Charge (SOC) Estimation**
- **State of Health (SOH) Monitoring**
- **Cell Balancing (Passive)**
- **CAN Communication (To be implemented)**
- **Diagnostics & Logging**
- **Real-Time Task Scheduling with FreeRTOS**

## Project Structure
```
/BMS_Project
 ├── /Core
 │    ├── /Inc  # Main header files
 │    ├── /Src  # Main source files
 ├── /Drivers  # HAL drivers
 ├── /Middleware
 │    ├── /FreeRTOS  # FreeRTOS kernel
 ├── /App  # BMS Application Logic
 │    ├── /Measurement  # ADC, SPI (LTC6811)
 │    ├── /SOC  # SOC Estimation Algorithms
 │    ├── /SOH  # SOH Estimation Algorithms
 │    ├── /Balancing  # Cell Balancing Control
 │    ├── /CAN_Comm  # CAN Tx/Rx Handling
 │    ├── /StateMachine  # BMS Main State Machine
 │    ├── /Diagnostics  # Logging & Error Handling
 │    ├── /Config  # System Configuration
 ├── /Tasks  # FreeRTOS Task Implementations
 ├──
```

## Future Improvements
- Implement power management for low-power modes.
- Add fault detection & safety mechanisms.
- Optimize SOC/SOH estimation accuracy.


