.PHONY: all build rebuild check test memtest clean

all: clean check build test memtest

clean:
	rm -rf build

build:
	sh build.sh

rebuild: clean build

test:
	sh build.sh -DWITH_MEMCHECK=OFF
	sh run_tests.sh

memtest:
	sh build.sh -DWITH_MEMCHECK=ON
	sh run_tests.sh --memcheck