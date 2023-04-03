.PHONY: all build rebuild check test memtest clean

all: clean check build test memtest

clean:
	rm -rf build

build:
	./build.sh

rebuild: clean build

check:
	./run_linters.sh

test:
	./build.sh -DWITH_MEMCHECK=OFF
	./run_tests.sh

memtest:
	./build.sh -DWITH_MEMCHECK=ON
	./run_tests.sh --memcheck