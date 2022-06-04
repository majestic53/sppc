# SPPC
# Copyright (C) 2022 David Jolly
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
# associated documentation files (the "Software"), to deal in the Software without restriction,
# including without limitation the rights to use, copy, modify, merge, publish, distribute,
# sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all copies or
# substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
# INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
# PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
# COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
# AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
# WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

BUILD_DIRECTORY=../build/
INSTALL_DIRECTORY=/usr/local/bin/

BINARY_FILE=sppc
PATCH_FILE=../include/common/define.h
OBJECT_FILES=$(patsubst %.c,%.o,$(shell find ./ -name '*.c'))

INCLUDE_FLAGS=$(subst ../include/,-I../include/,$(shell find ../include/ -maxdepth 2 -type d))
INSTALL_FLAGS=0755
LIBRARY_FLAGS=
PATCH_FLAGS="s/SPPC_PATCH .*/SPPC_PATCH 0x$(shell git rev-parse --short HEAD)/g"

.PHONY: all
all: build

.PHONY: build
build: $(BUILD_DIRECTORY)$(BINARY_FILE)

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIRECTORY)
	@rm -f $(OBJECT_FILES)

.PHONY: install
install:
	@mkdir -p $(INSTALL_DIRECTORY)
	@install -m $(INSTALL_FLAGS) $(BUILD_DIRECTORY)$(BINARY_FILE) $(INSTALL_DIRECTORY)

.PHONY: patch
patch:
	@sed -i $(PATCH_FLAGS) $(PATCH_FILE)

.PHONY: strip
strip:
	@strip $(BUILD_DIRECTORY)$(BINARY_FILE)

.PHONY: uninstall
uninstall:
	@rm -f $(INSTALL_DIRECTORY)$(BINARY_FILE)

$(BUILD_DIRECTORY):
	@mkdir -p $@

$(BUILD_DIRECTORY)$(BINARY_FILE): $(BUILD_DIRECTORY) $(OBJECT_FILES)
	cc $(FLAGS) $(OBJECT_FILES) $(LIBRARY_FLAGS) -o $@

%.o: %.c
	cc $(FLAGS) $(INCLUDE_FLAGS) -c -o $@ $<
