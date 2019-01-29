BUILD_DIR?=build
MAKE_FLAGS?=-j1

default:
	@grep -v "^	" Makefile | grep -v "^$$"

clean:
	rm -Rf ${BUILD_DIR}
	rm -Rf include/cpput/cpput_config.h

build:
	git submodule update --init
	mkdir -p ${BUILD_DIR}
	cd ${BUILD_DIR}; cmake ..
	cd ${BUILD_DIR}; make ${MAKE_FLAGS}

test: build
	cd build; ${MAKE} ${MAKE_FLAGS} test

3rdparty:
	git submodule update --init
	cp 3rdparty/better_enums/enum.h include/cpput/better_enum.h
	cp 3rdparty/popl/include/popl.hpp include/cpput/popl.h
	cp 3rdparty/SafeInt/SafeInt.hpp include/cpput/safe_int.h
	${MAKE} allheader

allheader:
	echo "#ifndef H_CPPUT_ALL" > include/cpput/all.h
	echo "#define H_CPPUT_ALL" >> include/cpput/all.h
	cd include/cpput; ls *.h | grep -v "all.h" | sed 's/^\(.*\)/#include "\1"/' >> all.h
	echo "#endif" >> include/cpput/all.h
	cat include/cpput/all.h

.PHONY: build test 3rdparty
