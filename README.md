# Sharing Code

This project demonstrates custom GPIO control and external interrupt handling on the STM32F103 (Blue Pill) microcontroller. It includes a basic driver for GPIO initialization, reading, writing, and toggling, as well as SysTick-based delay functions and an external interrupt to toggle a signal.

## 🧠 Project Structure

### 1. `gpio_driver.h / gpio_driver.c`
Custom GPIO driver implementation with the following functionalities:
- `Gpio_init(...)`: Initialize GPIO pin as input/output with options.
- `Gpio_read(...)`: Read digital value from a GPIO pin.
- `Gpio_write(...)`: Write digital value to a GPIO pin.
- `Gpio_Toggle(...)`: Toggle a GPIO pin value.
- `systick_init()`, `delayM()`, `delay(t)`: SysTick-based millisecond delays.

Also includes macro definitions for:
- Port names (PortA, PortB, PortC)
- Modes and configurations (IN, OUT, push-pull/open-drain, etc.)
- Logic levels (HIGH, LOW)

### 2. `main.c`
The main application does the following:
- Configures PA0 as an input pin with interrupt capability.
- Configures PC13 and PA12 as output pins.
- When the interrupt on PA0 is triggered, it toggles a signal flag.
- Based on the flag:
  - PC13 LED blinks at 1-second intervals.
  - PA12 reflects the signal level (HIGH/LOW).

### 3. `stm32f10x.h`
This is the STM32 standard peripheral header (assumed to be from the STM32 Standard Peripheral Library) which provides the necessary CMSIS definitions for the STM32F103.

---

## 🔧 Requirements

- STM32F103C8T6 board (Blue Pill)
- STM32CubeIDE or Keil or any compatible IDE
- ST-Link or equivalent debugger
- STM32 Standard Peripheral Library
- Clock Frequency: 108 MHz (as defined in the code)

---

## 🚀 How to Run

1. Flash the code onto an STM32F103 board using ST-Link and your IDE.
2. Connect a push-button to PA0.
3. Observe:
   - On button press, `signal` toggles.
   - When `signal` is `1`, PC13 LED blinks with 1s delay.
   - PA12 outputs the `signal` state directly.

---

## 📁 File Summary

| File           | Description                            |
|----------------|----------------------------------------|
| `gpio_driver.h/.c` | Custom GPIO functions and macros         |
| `main.c`       | Application code using GPIO and EXTI   |
| `stm32f10x.h`  | CMSIS/Peripheral definitions (assumed) |

---

## 📌 Notes

- Ensure external interrupt is connected to PA0 (EXTI0).
- This project avoids HAL libraries to demonstrate register-level control.
- Great for learning low-level embedded programming on STM32!
---



## 📷 Preview

