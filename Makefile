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

SOURCE_DIRECTORY=./src/

BUILD_FLAGS=-march=native\ -mtune=native\ -std=c11\ -Wall\ -Werror
DEBUG_BUILD_FLAGS=FLAGS=$(BUILD_FLAGS)\ -DDEBUG\ -g
RELEASE_BUILD_FLAGS=FLAGS=$(BUILD_FLAGS)\ -O3
MAKE_FLAGS=--no-print-directory -C

.PHONY: all
all: release

.PHONY: analyze
analyze:
	@cloc .
	@cppcheck --enable=all --std=c11 --suppress=missingIncludeSystem .

.PHONY: clean
clean:
	@make $(MAKE_FLAGS) $(SOURCE_DIRECTORY) clean

.PHONY: debug
debug: clean
	@make $(MAKE_FLAGS) $(SOURCE_DIRECTORY) build $(DEBUG_BUILD_FLAGS)

.PHONY: install
install: release
	@make $(MAKE_FLAGS) $(SOURCE_DIRECTORY) install

.PHONY: patch
patch:
	@make $(MAKE_FLAGS) $(SOURCE_DIRECTORY) patch

.PHONY: release
release: clean
	@make $(MAKE_FLAGS) $(SOURCE_DIRECTORY) build $(RELEASE_BUILD_FLAGS)
	@make $(MAKE_FLAGS) $(SOURCE_DIRECTORY) strip

.PHONY: uninstall
uninstall:
	@make $(MAKE_FLAGS) $(SOURCE_DIRECTORY) uninstall
