# Cornell Notes

## Topic: [Driver] I2C (Inter-Integrated Circuit)

## Date: 

---

### Cue Column (Questions, Keywords, or Prompts)

- [Insert question or keyword]
- [Insert question or keyword]
- [Insert question or keyword]

---

### Notes Section (Main Notes)

#### Introduction

I2C is a serial, synchronous, multi-device, half-duplex communication protocol that allows co-existence of multiple masters and slaves on the same bus. I2C uses two bidirectional open-drain lines: serial data line (SDA) and serial clock line (SCL), pulled up by resistors.

For more information about I2C with full details, please refer to:
- [I2C UXP specification](https://www.nxp.com/docs/en/user-guide/UM10204.pdf)

#### ESP32-S3 I2C Overview

ESP32-S3 has 2 I2C controller(s) (also called port), responsible for handling communication on the I2C bus.

A single I2C controller can be a master or a slave.

Typically, an I2C slave device has a 7-bit address or 10-bit address. ESP32-S3 supports both I2C Standard-mode (Sm) and Fast-mode (Fm) which can go up to 100 kHz and 400 kHz respectively.

For more information about I2C provided by Espressif, please refer to:
- [Inter-Integrated Circuit (I2C)](https://docs.espressif.com/projects/esp-idf/en/v6.0/esp32s3/api-reference/peripherals/i2c.html).
- [ESP32S3 Technical Reference Manual](https://www.espressif.com/sites/default/files/documentation/esp32-s3_technical_reference_manual_en.pdf) (Chapter 27 I2C)

##### Warning
The clock frequency of SCL in master mode should not be larger than 400 kHz.

##### Note
The frequency of SCL is influenced by both the pull-up resistor and the wire capacitance. Therefore, it is strongly recommended to choose appropriate pull-up resistors to make the frequency accurate. The recommended value for pull-up resistors usually ranges from `1 kΩ` to `10 kΩ`.

Keep in mind that the higher the frequency, the smaller the pull-up resistor should be (but not less than `1 kΩ`). Indeed, large resistors will decline the current, which will increase the clock switching time and reduce the frequency. A range of `2 kΩ` to `5 kΩ` is recommended, but adjustments may also be necessary depending on their current draw requirements.

##### File Structure
![alt text](image.png)
##### Functional Overview
The I2C driver offers following services:
- **Resource Allocation** - covers how to allocate I2C bus with properly set of configurations. It also covers how to recycle the resources when they finished working.
- **I2C Master Controller** - covers behavior of I2C master controller. Introduce data transmit, data receive, and data transmit and receive.
- **I2C Slave Controller** - covers behavior of I2C slave controller. Involve data transmit and data receive.
- **Power Management** - describes how different source clock will affect power consumption.
- **IRAM Safe** - describes tips on how to make the I2C interrupt work better along with a disabled cache.
- **Thread Safety**- lists which APIs are guaranteed to be thread safe by the driver.
- **Kconfig Options** - lists the supported Kconfig options that can bring different effects to the driver.

###### Note
Above information can be found more detail in [Inter-Integrated Circuit (I2C)](https://docs.espressif.com/projects/esp-idf/en/v6.0/esp32s3/api-reference/peripherals/i2c.html). 

It is not necessary to read all the details in the document, but it is recommended to have a quick look at the document to get familiar with the I2C driver.

#### STM32F411CEU6 I2C Overview
TBD
##### File Structure
TBD
##### Functional Overview
TBD


#### AUTOSAR-based I2C API Overview
The AUTOSAR-based I2C API is a set of APIs that provide a high-level interface for I2C communication. It is designed to be easy to use and to provide a consistent interface across different platforms.

The AUTOSAR-based I2C API is built on top of the Espressif I2C driver and provides additional features such as error handling and support for multiple I2C devices.

##### File Structure
The file structure of the AUTOSAR-based I2C API is as follows:

##### Functional Overview
The AUTOSAR-based I2C API could be found full detail in [Specification of I2C Driver](../01_Specification/AUTOSAR_CP_SWS_I2CDriver.pdf)

##### API Reference
```c
void I2C_Init(const I2C_ConfigType *ConfigPtr);
```
Initializes the I2C Driver.
- **Parameters:** `ConfigPtr` - Pointer to a structure containing the configuration information for the I2C Driver.
- **Returns:** None

###### Flow Chart

###### Sequence Diagrams

###### Wavedrom Diagrams
```wavedrom
{ "signal": [
  { "name": "SCL", "wave": "p...." },
  { "name": "SDA", "wave": "1.0..", "data": ["A6","A0","R/W","ACK"] }
]}
```



---

### Summary Section (Summary of Notes)

[Insert a brief summary of the key ideas and takeaways]