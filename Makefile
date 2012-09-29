BUILDDIR=build
#BUILDDIR=build_debug

#change to Debug for debug mode
BUILDTYPE=Release
#BUILDTYPE=Debug

all: build

mkbuilddir:
	[ -d $(BUILDDIR) ] || mkdir $(BUILDDIR)

cmake: mkbuilddir CMakeLists.txt
	cd $(BUILDDIR) && cmake -DCMAKE_BUILD_TYPE=$(BUILDTYPE) ..

build: cmake
	$(MAKE) -C $(BUILDDIR)

package: cmake
	$(MAKE) -C $(BUILDDIR) package

deb:
	cd $(BUILDDIR) && cpack -G DEB

clean: mkbuilddir
	$(MAKE) -C $(BUILDDIR) clean

install: mkbuilddir
	$(MAKE) -C $(BUILDDIR) install
	
clean-all:
	cd $(BUILDDIR) && rm -rf *
	
