# SPPC (DMG-Lite)

[![License: MIT](https://shields.io/badge/license-MIT-blue.svg?style=flat)](https://github.com/majestic53/sppc/blob/master/LICENSE.md) [![Build Status](https://github.com/majestic53/sppc/workflows/Build/badge.svg)](https://github.com/majestic53/sppc/actions/workflows/build.yml)

### A Sharp pocket-pc serial interface, written in C.

`SPPC` sends files from a PC to a Sharp pocket-PC (PCG8XX or similar), over 11-pin serial.

## Installation

```bash
git clone https://github.com/majestic53/sppc
cd sppc
sudo make install
```

## Usage

```
Usage: sppc [options] file...

Options:
   -b, --baud         Specify baud rate
   -d, --device       Specify device
   -h, --help         Show help information
   -v, --version      Show version information
```

### Examples

```bash
# Send a binary file at 9600 baud to /dev/ttyUSB0
sppc --baud 9600 --device /dev/ttyUSB0 file.bin
```

## License

Copyright (C) 2022 David Jolly. Released under the [MIT License](https://github.com/majestic53/sppc/blob/master/LICENSE.md).
