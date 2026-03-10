# Services Libraries (SrvLibs)

## Responsible

[Thach Nguyen Ba Vu](https://github.com/VuThach3001)

## Overview

This module provides AUTOSAR-compliant library services for embedded systems, offering optimized mathematical and bit manipulation functions for real-time applications.

## Library Services

The following library services are provided:

- **Bfx**: Bit handling operations
- **Efx**: Extended functions on fixed-point arithmetic
- **Ifl**: Interpolation functions for floating-point operations
- **Ifx**: Interpolation functions for fixed-point operations
- **Mfl**: Mathematical floating-point calculations
- **Mfx**: Mathematical fixed-point calculations

## Implementation

Every service in SrvLibs is implemented in standard C and can run on any controller. However, controller-specific implementations are provided to achieve:

- Better runtime performance
- Reduced code size
- Optimized memory usage

### Assembly Optimization

Assembler-specific implementations are used for efficient execution in terms of run-time and memory consumption. These implementations leverage hardware-specific instructions for maximum performance.

## Supported Controllers

Assembly implementations under the HighTec compiler are currently supported for the following controllers:

### ESP32

**Architecture**: Xtensa LX6

**Specifications**:

- **Processor**: Dual-core 32-bit Xtensa LX6 microprocessor
- **Clock Speed**: Up to 240 MHz
- **SRAM**: 520 KB
- **Flash**: Supports external flash (typically 4MB - 16MB)
- **Instruction Set**: Xtensa ISA with 16/24-bit instructions
- **FPU**: Single-precision floating-point unit
- **DSP**: Digital Signal Processing instructions

