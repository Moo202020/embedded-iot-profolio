# STM32 foundations

My HAMK studies covered STM32 GPIO, timers, ADC, UART and SPI. Original lab source and the exact MCU are not available in this package. `FoundationLogic.h` is NEW portable C++ practice code, host-tested without STM32 hardware. It is not a complete CubeIDE/HAL firmware project and does not demonstrate a tested driver for a particular MCU.

## Exercises to implement on your board

| Topic | CubeIDE work | Evidence to record |
| --- | --- | --- |
| GPIO | Configure a button input and LED output using the actual board schematic | Button behaviour and debouncing |
| Timer | Configure a periodic timer interrupt; post a flag/counter for main-loop handling | Measured period with scope or logic analyser |
| ADC | Select a valid analogue pin, sampling time and resolution; read a known input | Raw counts, reference voltage and calculated millivolts |
| UART | Configure TX/RX; queue received bytes and feed LineParser from main context | Valid line, CRLF, overflow and recovery |
| SPI | Choose a real peripheral, verify CPOL/CPHA, word length and chip select | Read a documented ID register with captured waveform |

## Integration outline

1. Create a CubeIDE project for the exact board/MCU. Generate the vendor initialisation code rather than copying guessed pin/peripheral settings.
2. Copy `FoundationLogic.h` into the C++ include path; call the helpers from a `.cpp` application file. Keep the generated HAL integration appropriate to the project language and linker setup.
3. Use the actual ADC resolution and measured reference voltage when calling `adcMillivolts`.
4. Do not parse strings or make blocking calls inside an ISR. Transfer bytes safely to main context; protect shared indices according to the MCU and concurrency model.
5. Capture the board name, clock settings, peripheral settings and real test results before publishing a completed lab demonstration.

Portable tests cover saturation, invalid ADC configuration, CRLF, partial lines and parser overflow/recovery. Hardware-specific GPIO, timer and SPI behaviour is not tested here.
