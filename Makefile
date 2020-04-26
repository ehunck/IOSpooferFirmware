
TARGET = NUCLEO_F429ZI
TOOLCHAIN = GCC_ARM

all:
	mbed compile -m ${TARGET} -t ${TOOLCHAIN} --profile debug

release:
	mbed compile -m ${TARGET} -t ${TOOLCHAIN} --profile release

clean:
	rm -r BUILD

.PHONY: all clean release