# SPPC

[![License: MIT](https://shields.io/badge/license-MIT-blue.svg?style=flat)](https://github.com/majestic53/sppc/blob/master/LICENSE.md) [![Build Status](https://github.com/majestic53/sppc/workflows/Build/badge.svg)](https://github.com/majestic53/sppc/actions/workflows/build.yml)

### A Sharp pocket-PC serial interface, written in C.

`SPPC` allows for reading and writing files between a PC and a Sharp pocket-PC (PCG8XX or similar), over USB to 11-pin serial.

__NOTE__: A USB/Serial adapter, with inverted Rx/Tx signals, is required for `SPPC` to work. For example, an FTDI adapter can be used for this purpose:

<img src="https://github.com/majestic53/sppc/blob/master/docs/adapter.jpg" alt="Adapter" /><img src="https://github.com/majestic53/sppc/blob/master/docs/circuit.jpg" alt="Adapter circuit" />

## Latest release

The latest release can be found [here](https://github.com/majestic53/sppc/releases).

## Build from source

```bash
git clone https://github.com/majestic53/sppc
cd sppc
sudo make
```

## Usage

```
Usage: sppc [options] file...

Options:
   -b, --baud         Specify baud rate
   -d, --device       Specify device
   -h, --help         Show help information
   -r, --read         Specify read mode
   -v, --version      Show version information
```

### Example

```bash
# Write a file to /dev/ttyUSB0 at 9600 baud
sppc --device /dev/ttyUSB0 --baud 9600 file.bin

# Read a file from /dev/ttyUSB0 at 9600 baud
sppc --device /dev/ttyUSB0 --baud 9600 --read file.bin
```

## License

Copyright (C) 2022 David Jolly. Released under the [MIT License](https://github.com/majestic53/sppc/blob/master/LICENSE.md).
