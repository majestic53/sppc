# SPPC

[![License: MIT](https://shields.io/badge/license-MIT-blue.svg?style=flat)](https://github.com/majestic53/sppc/blob/master/LICENSE.md) [![Build Status](https://github.com/majestic53/sppc/workflows/Build/badge.svg)](https://github.com/majestic53/sppc/actions/workflows/build.yml)

### A Sharp pocket-PC serial interface, written in C.

`SPPC` sends files from a PC to a Sharp pocket-PC (PCG8XX or similar), over USB to 11-pin serial:

```
 --------       --------       -----       ----
| PCG8XX | <-- | Serial | <-- | USB | <-- | PC |
 --------       --------       -----       ----
```

__NOTE__: A USB/Serial adapter is required for `SPPC` to work.

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

### Example

```bash
# Send a binary file at 9600 baud to /dev/ttyUSB0
sppc --baud 9600 --device /dev/ttyUSB0 file.bin
```

## License

Copyright (C) 2022 David Jolly. Released under the [MIT License](https://github.com/majestic53/sppc/blob/master/LICENSE.md).
