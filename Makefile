BUILD_DIR=build

clean:
	rm -Rf ${BUILD_DIR}

build:
	mkdir -p ${BUILD_DIR}
	cd ${BUILD_DIR}; cmake ..
	cd ${BUILD_DIR}; make

test: build
	cd build; ${MAKE} test

3dparty:
	git submodule update --init
	cp 3dparty/better_enums/enum.h include/cpput/better_enum.h
	cp 3dparty/popl/include/popl.hpp include/cpput/popl.h

allheader:
	echo "#pragma once" > include/cpput/all.h
	cd include/cpput; ls *.h | grep -v "all.h" | sed 's/^\(.*\)/#include "\1"/' >> all.h
	cat include/cpput/all.h

.PHONY: build test 3dparty
