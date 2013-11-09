BUILDTRIPLET=$(shell libenet/config.guess)

ifeq ($(strip $(PREFIX)),)
PREFIX=$(BUILDTRIPLET)
endif

STRIP=
ifeq (,$(findstring -ggdb,$(CXXFLAGS)))
  STRIP=strip
endif

ifneq (, $(findstring x86_64,$(PREFIX)))
override CPUINFO+= -m64 
else
override CPUINFO+= -m32 
endif

ifneq (, $(findstring mingw,$(PREFIX)))
PREFIXHYPEN=$(PREFIX)-
CXX=$(PREFIXHYPEN)g++
CC=$(PREFIXHYPEN)gcc
ifneq (, $(findstring x86_64,$(PREFIX)))
WINDRES=$(PREFIXHYPEN)windres -F pe-x86-64 
else
WINDRES=$(PREFIXHYPEN)windres -F pe-i386 
endif
WINDOWS="esisto porca puttana"
ifneq (, $(STRIP))
STRIP=x86_64-w64-mingw32-strip
endif
else ifneq (, $(findstring linux,$(PREFIX)))
LINUX="esisto porca puttana"
else ifneq (, $(findstring darwin,$(PREFIX)))
CXX=clang++
CC=clang
override CPUINFO+= -mmacosx-version-min=10.5
MAC="esisto porca puttana"
else
$(error Unknown architecture $(PREFIX))
endif

OPTFLAGS= -ffast-math -O3 -fomit-frame-pointer

ifndef MAC
CXXSTD= -std=c++11
endif

CXXFLAGS=$(OPTFLAGS)
override CXXFLAGS+= $(CXXSTD) -fvisibility=hidden -fvisibility-inlines-hidden -Wall -fsigned-char -fno-exceptions -fno-rtti $(CPUINFO)

ifdef MAC
override OPTFLAGS += -fvisibility=hidden -fvisibility-inlines-hidden 
else
override OPTFLAGS += -fvisibility=hidden 
endif

TOPDIR= $(shell pwd)

INCLUDES= -Ishared -Iengine -Ifpsgame -Iinclude -Iinclude/SDL2

ifdef WINDOWS
CLIENT_INCLUDES= $(INCLUDES)
CLIENT_LIBS= -mwindows -static-libgcc -static-libstdc++ -Llib -lenet -lSDL2 -lSDL2_image -ljpeg -lpng -lz -lSDL2_mixer -logg -lvorbis -lvorbisfile -lws2_32 -lwinmm -lopengl32 -ldxguid -lgdi32 -lole32 -limm32 -lversion -loleaut32
endif
ifdef LINUX
CLIENT_INCLUDES= $(INCLUDES) -I/usr/X11R6/include
CLIENT_LIBS= -Llib -L/usr/X11R6/lib -lX11 -lGL -lenet -lSDL2 -lpthread -lSDL2_image -ljpeg -lpng -lz -lSDL2_mixer -logg -lvorbis -lvorbisfile -lm -ldl
endif
ifdef MAC
CLIENT_INCLUDES= $(INCLUDES)
CLIENT_LIBS= -Llib -lenet -lSDL2 -lpthread -lSDL2_image -ljpeg -lpng -lz -lSDL2_mixer -logg -lvorbis -lvorbisfile -lm -ldl
endif

CLIENT_OBJS= \
	shared/crypto.o \
	shared/geom.o \
	shared/stream.o \
	shared/tools.o \
	shared/zip.o \
	engine/3dgui.o \
	engine/bih.o \
	engine/blend.o \
	engine/blob.o \
	engine/client.o	\
	engine/command.o \
	engine/console.o \
	engine/cubeloader.o \
	engine/decal.o \
	engine/dynlight.o \
	engine/glare.o \
	engine/grass.o \
	engine/lightmap.o \
	engine/main.o \
	engine/material.o \
	engine/menus.o \
	engine/movie.o \
	engine/normal.o	\
	engine/octa.o \
	engine/octaedit.o \
	engine/octarender.o \
	engine/physics.o \
	engine/pvs.o \
	engine/rendergl.o \
	engine/rendermodel.o \
	engine/renderparticles.o \
	engine/rendersky.o \
	engine/rendertext.o \
	engine/renderva.o \
	engine/server.o	\
	engine/serverbrowser.o \
	engine/shader.o \
	engine/shadowmap.o \
	engine/sound.o \
	engine/texture.o \
	engine/water.o \
	engine/world.o \
	engine/worldio.o \
	fpsgame/ai.o \
	fpsgame/client.o \
	fpsgame/entities.o \
	fpsgame/fps.o \
	fpsgame/monster.o \
	fpsgame/movable.o \
	fpsgame/render.o \
	fpsgame/scoreboard.o \
	fpsgame/server.o \
	fpsgame/waypoint.o \
	fpsgame/weapon.o
MACOBJC= \
	xcode/Launcher.o \
	xcode/main.o
MACOBJCXX= xcode/macutils.o

ifdef LINUX
ifneq (, $(findstring x86_64,$(PREFIX)))
override LDFLAGS+= -Wl,--wrap=__pow_finite,--wrap=__acosf_finite,--wrap=__log_finite,--wrap=__exp_finite,--wrap=__logf_finite,--wrap=__expf_finite,--wrap=__asin_finite,--wrap=__atan2f_finite,--wrap=__log10f_finite,--wrap=__atan2_finite,--wrap=__acos_finite,--wrap=memcpy
override CLIENT_OBJS+= quirks/oldglibc64.o
else
override LDFLAGS+= -Wl,--wrap=__pow_finite
override CLIENT_OBJS+= quirks/oldglibc32.o
endif
endif

quirks/oldglibc%: CXXFLAGS += -fno-fast-math

default: all

all: client

libenet/Makefile:
	cd libenet; PKG_CONFIG_PATH="$(TOPDIR)/lib/pkgconfig" PATH="$(TOPDIR)/bin:$(PATH)" CC=$(CC) ac_cv_func_memcmp_working=yes ./configure --host=$(PREFIX) --build=$(BUILDTRIPLET) --prefix="$(TOPDIR)" --enable-shared=no CPPFLAGS="-I$(TOPDIR)/include" CFLAGS="-I$(TOPDIR)/include $(CPUINFO) $(OPTFLAGS)" LDFLAGS="$(CPUINFO) -L$(TOPDIR)/lib"

libz/Makefile:
	cd libz; PKG_CONFIG_PATH="$(TOPDIR)/lib/pkgconfig" PATH="$(TOPDIR)/bin:$(PATH)" CHOST="$(PREFIX)" CPPFLAGS="-I$(TOPDIR)/include" CFLAGS="-I$(TOPDIR)/include $(CPUINFO) $(OPTFLAGS)" LDFLAGS="$(CPUINFO) -L$(TOPDIR)/lib" CC=$(CC) ./configure --prefix="$(TOPDIR)" --static

libjpeg/Makefile:
	cd libjpeg; PKG_CONFIG_PATH="$(TOPDIR)/lib/pkgconfig" PATH="$(TOPDIR)/bin:$(PATH)" CC=$(CC) ac_cv_func_memcmp_working=yes ./configure --host=$(PREFIX) --build=$(BUILDTRIPLET) --prefix="$(TOPDIR)" --without-turbojpeg --enable-shared=no CPPFLAGS="-I$(TOPDIR)/include" CFLAGS="-I$(TOPDIR)/include $(CPUINFO) $(OPTFLAGS)" LDFLAGS="$(CPUINFO) -L$(TOPDIR)/lib"

libpng/Makefile: libz
	cd libpng; PKG_CONFIG_PATH="$(TOPDIR)/lib/pkgconfig" PATH="$(TOPDIR)/bin:$(PATH)" CC=$(CC) ac_cv_func_memcmp_working=yes ./configure --host=$(PREFIX) --build=$(BUILDTRIPLET) --prefix="$(TOPDIR)" --enable-shared=no CPPFLAGS="-I$(TOPDIR)/include" CFLAGS="-I$(TOPDIR)/include $(CPUINFO) $(OPTFLAGS)" LDFLAGS="$(CPUINFO) -L$(TOPDIR)/lib"

libogg/Makefile:
	cd libogg; PKG_CONFIG_PATH="$(TOPDIR)/lib/pkgconfig" PATH="$(TOPDIR)/bin:$(PATH)" CC=$(CC) ac_cv_func_memcmp_working=yes ./configure --host=$(PREFIX) --build=$(BUILDTRIPLET) --prefix="$(TOPDIR)" --enable-shared=no CPPFLAGS="-I$(TOPDIR)/include" CFLAGS="-I$(TOPDIR)/include $(CPUINFO) $(OPTFLAGS)" LDFLAGS="$(CPUINFO) -L$(TOPDIR)/lib"

libvorbis/Makefile: libogg
	cd libvorbis; PKG_CONFIG_PATH="$(TOPDIR)/lib/pkgconfig" PATH="$(TOPDIR)/bin:$(PATH)" CC=$(CC) ac_cv_func_memcmp_working=yes ./configure --host=$(PREFIX) --build=$(BUILDTRIPLET) --prefix="$(TOPDIR)" --enable-shared=no --disable-oggtest --enable-docs=no --enable-examples=no CPPFLAGS="-I$(TOPDIR)/include" CFLAGS="-I$(TOPDIR)/include $(CPUINFO) $(OPTFLAGS)" LDFLAGS="$(CPUINFO) -L$(TOPDIR)/lib"

ifdef WINDOWS
libSDL/Makefile:
	cd libSDL; PKG_CONFIG_PATH="$(TOPDIR)/lib/pkgconfig" PATH="$(TOPDIR)/bin:$(PATH)" CC=$(CC) ac_cv_func_memcmp_working=yes ./configure --host=$(PREFIX) --build=$(BUILDTRIPLET) --prefix="$(TOPDIR)" --enable-shared=no --enable-video-dummy=no --enable-dummyaudio=no --enable-diskaudio=no --enable-joystick=no --disable-haptic --disable-power --enable-video-opengles=no --enable-render=no --enable-render-d3d=no LDFLAGS="$(CPUINFO) -L$(TOPDIR)/lib" CPPFLAGS="-I$(TOPDIR)/include" CFLAGS="-I$(TOPDIR)/include $(OPTFLAGS) $(CPUINFO) -DDECLSPEC=\"\""
libSDL_mixer/Makefile: libSDL libvorbis
	cd libSDL_mixer; PKG_CONFIG_PATH="$(TOPDIR)/lib/pkgconfig" PATH="$(TOPDIR)/bin:$(PATH)" CC=$(CC) ac_cv_func_memcmp_working=yes ./configure --host=$(PREFIX) --build=$(BUILDTRIPLET) --prefix="$(TOPDIR)" --enable-shared=no --enable-music-cmd=no --enable-music-mod=no --enable-music-mod-modplug=no --enable-music-midi=no --enable-music-fluidsynth-shared=no --enable-music-ogg-tremor=no --enable-music-ogg-shared=no --enable-music-flac=no --enable-music-flac-shared=no --enable-music-mp3=no --enable-music-mp3-mad-gpl=no --disable-sdltest --enable-render=no --enable-render-d3d=no LDFLAGS="$(CPUINFO) -L$(TOPDIR)/lib" CPPFLAGS="-I$(TOPDIR)/include" CFLAGS="-I$(TOPDIR)/include $(CPUINFO) $(OPTFLAGS) -DDECLSPEC=\"\"" LIBS="-logg -lvorbis -logg -lm"
libSDL_image/Makefile: libSDL libjpeg libpng
	cd libSDL_image; PKG_CONFIG_PATH="$(TOPDIR)/lib/pkgconfig" PATH="$(TOPDIR)/bin:$(PATH)" CC=$(CC) ac_cv_func_memcmp_working=yes ac_cv_lib_jpeg_jpeg_CreateDecompress=yes ./configure --host=$(PREFIX) --build=$(BUILDTRIPLET) --prefix="$(TOPDIR)" --enable-shared=no --enable-jpg-shared=no --enable-png-shared=no --enable-webp=no --enable-tif=no --disable-sdltest LDFLAGS="$(CPUINFO) -L$(TOPDIR)/lib" CPPFLAGS="-I$(TOPDIR)/include" CFLAGS="-I$(TOPDIR)/include $(CPUINFO) $(OPTFLAGS) -DDECLSPEC=\"\""
endif

ifdef LINUX
libSDL/Makefile:
	cd libSDL; PKG_CONFIG_PATH="$(TOPDIR)/lib/pkgconfig" PATH="$(TOPDIR)/bin:$(PATH)" CC=$(CC) ac_cv_func_memcmp_working=yes ./configure --host=$(PREFIX) --build=$(BUILDTRIPLET) --prefix="$(TOPDIR)" --enable-shared=no --enable-video-dummy=no --enable-dummyaudio=no --enable-diskaudio=no --enable-video-directfb=no --enable-joystick=no --disable-haptic --disable-power --disable-dbus --disable-fusionsound --disable-libudev --disable-alsatest --enable-render=no --enable-video-opengles=no CPPFLAGS="-I$(TOPDIR)/include" CFLAGS="-I$(TOPDIR)/include $(CPUINFO) $(OPTFLAGS)" LDFLAGS="$(CPUINFO) -L$(TOPDIR)/lib"
libSDL_mixer/Makefile: libSDL libvorbis
	cd libSDL_mixer; PKG_CONFIG_PATH="$(TOPDIR)/lib/pkgconfig" PATH="$(TOPDIR)/bin:$(PATH)" CC=$(CC) ac_cv_func_memcmp_working=yes ./configure --host=$(PREFIX) --build=$(BUILDTRIPLET) --prefix="$(TOPDIR)" --enable-shared=no --enable-music-cmd=no --enable-music-mod=no --enable-music-mod-modplug=no --enable-music-midi=no --enable-music-fluidsynth-shared=no --enable-music-ogg-tremor=no --enable-music-ogg-shared=no --enable-music-flac=no --enable-music-flac-shared=no --enable-music-mp3=no --enable-music-mp3-mad-gpl=no --disable-sdltest CPPFLAGS="-I$(TOPDIR)/include" CFLAGS="-I$(TOPDIR)/include $(CPUINFO) $(OPTFLAGS)" LDFLAGS="$(CPUINFO) -L$(TOPDIR)/lib" LIBS="-logg -lvorbis -logg -lm"
libSDL_image/Makefile: libSDL libjpeg libpng
	cd libSDL_image; PKG_CONFIG_PATH="$(TOPDIR)/lib/pkgconfig" PATH="$(TOPDIR)/bin:$(PATH)" CC=$(CC) ac_cv_func_memcmp_working=yes ./configure --host=$(PREFIX) --build=$(BUILDTRIPLET) --prefix="$(TOPDIR)" --enable-shared=no --enable-jpg-shared=no --enable-png-shared=no --enable-webp=no --enable-tif=no --disable-sdltest CPPFLAGS="-I$(TOPDIR)/include" CFLAGS="-I$(TOPDIR)/include $(CPUINFO) $(OPTFLAGS)" LDFLAGS="$(CPUINFO) -L$(TOPDIR)/lib"
endif

ifdef MAC
libSDL/Makefile:
	cd libSDL; PKG_CONFIG_PATH="$(TOPDIR)/lib/pkgconfig" PATH="$(TOPDIR)/bin:$(PATH)" CC=$(CC) ac_cv_func_memcmp_working=yes ./configure --host=$(PREFIX) --build=$(BUILDTRIPLET) --prefix="$(TOPDIR)" --enable-shared=no --enable-video-dummy=no --enable-dummyaudio=no --enable-diskaudio=no --enable-video-directfb=no --enable-joystick=no --disable-haptic --disable-power --disable-dbus --disable-fusionsound --disable-libudev --enable-render=no --enable-video-opengles=no --enable-video-x11=no --disable-alsatest CPPFLAGS="-I$(TOPDIR)/include" CFLAGS="-I$(TOPDIR)/include $(CPUINFO) $(OPTFLAGS)" LDFLAGS="$(CPUINFO) -L$(TOPDIR)/lib"
libSDL_mixer/Makefile: libSDL libvorbis
	cd libSDL_mixer; PKG_CONFIG_PATH="$(TOPDIR)/lib/pkgconfig" PATH="$(TOPDIR)/bin:$(PATH)" CC=$(CC) ac_cv_func_memcmp_working=yes ./configure --host=$(PREFIX) --build=$(BUILDTRIPLET) --prefix="$(TOPDIR)" --enable-shared=no --enable-music-cmd=no --enable-music-mod=no --enable-music-mod-modplug=no --enable-music-midi=no --enable-music-fluidsynth-shared=no --enable-music-ogg-tremor=no --enable-music-ogg-shared=no --enable-music-flac=no --enable-music-flac-shared=no --enable-music-mp3=no --enable-music-mp3-mad-gpl=no --disable-sdltest CPPFLAGS="-I$(TOPDIR)/include" CFLAGS="-I$(TOPDIR)/include $(CPUINFO) $(OPTFLAGS)" LDFLAGS="$(CPUINFO) -L$(TOPDIR)/lib" LIBS="-logg -lvorbis -logg -lm"
libSDL_image/Makefile: libSDL libjpeg libpng
	cd libSDL_image; PKG_CONFIG_PATH="$(TOPDIR)/lib/pkgconfig" PATH="$(TOPDIR)/bin:$(PATH)" CC=$(CC) ac_cv_lib_jpeg_jpeg_CreateDecompress=yes ac_cv_func_memcmp_working=yes ./configure --host=$(PREFIX) --build=$(BUILDTRIPLET) --prefix="$(TOPDIR)" --enable-shared=no --enable-imageio=no --enable-jpg-shared=no --enable-png-shared=no --enable-webp=no --enable-tif=no --disable-sdltest CPPFLAGS="-I$(TOPDIR)/include" CFLAGS="-I$(TOPDIR)/include $(CPUINFO) $(OPTFLAGS)" LDFLAGS="$(CPUINFO) -L$(TOPDIR)/lib"
endif

ifndef MAC
lib%: lib%/Makefile
	$(MAKE)	-C $@/ -j$(THREADS) install
else
lib%: lib%/Makefile
	$(MAKE)	-C $@/ install
endif

clean-lib%:
	-$(MAKE) -C lib$*/ uninstall distclean

clean-libz:
	-$(MAKE) -C libz/ uninstall distclean
	-$(RM) libz/Makefile libz/zconf.h

clean:
	-$(RM) -r $(CLIENT_OBJS) $(MACOBJC) $(MACOBJCXX) quirks/*.o sauer_client sauerbraten.exe vcpp/mingw.res

distclean: clean-libSDL_image clean-libSDL_mixer clean-libSDL clean-libvorbis clean-libogg clean-libpng clean-libjpeg clean-libz clean-libenet clean
	-$(RM) -r share man lib bin etc

$(CLIENT_OBJS): CXXFLAGS += $(CLIENT_INCLUDES)

ifdef WINDOWS
client: libenet libSDL libSDL_image libSDL_mixer $(BUILDXLIB) $(CLIENT_OBJS)
	$(WINDRES) -I vcpp -i vcpp/mingw.rc -J rc -o vcpp/mingw.res -O coff 
	$(CXX) $(CXXFLAGS) -o sauerbraten.exe vcpp/mingw.res $(CLIENT_OBJS) -Wl,--as-needed -Wl,--start-group $(CLIENT_LIBS) -Wl,--end-group
	$(STRIP) sauerbraten.exe
ifeq (, $(findstring x86_64,$(PREFIX)))
	upx sauerbraten.exe
endif
endif
ifdef MAC

$(MACOBJCXX):
	clang++ -c $(CXXFLAGS) $(CLIENT_INCLUDES) -o $@ $(subst .o,.mm,$@)
$(MACOBJC):
	clang -c $(CXXFLAGS) $(CLIENT_INCLUDES) -o $@ $(subst .o,.m,$@)

client:	libenet libSDL libSDL_image libSDL_mixer $(BUILDXLIB) $(CLIENT_OBJS) $(MACOBJCXX) $(MACOBJC)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o sauer_client $(CLIENT_OBJS) $(MACOBJCXX) $(MACOBJC) $(CLIENT_LIBS) -framework IOKit -framework Cocoa -framework Carbon -framework CoreAudio -framework OpenGL -framework AudioUnit
	$(STRIP) sauer_client
endif
ifdef LINUX
client:	libenet libSDL libSDL_image libSDL_mixer $(BUILDXLIB) $(CLIENT_OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o sauer_client $(CLIENT_OBJS) -Wl,--as-needed -Wl,--start-group $(CLIENT_LIBS) -lrt -Wl,--end-group
	$(STRIP) sauer_client
ifneq (, $(findstring x86_64,$(PREFIX)))
	./remove_symbol_version memcpy@GLIBC_2.2.5
endif
	upx sauer_client
endif

# DO NOT DELETE

engine/3dgui.o: engine/engine.h engine/textedit.h
engine/bih.o: engine/engine.h
engine/blend.o: engine/engine.h
engine/blob.o: engine/engine.h
engine/client.o: engine/engine.h
engine/command.o: engine/engine.h
engine/console.o: engine/engine.h engine/sdl2_keymap_extrakeys.h
engine/cubeloader.o: engine/engine.h
engine/decal.o: engine/engine.h
engine/dynlight.o: engine/engine.h
engine/engine.h: shared/cube.h engine/world.h engine/octa.h engine/lightmap.h engine/bih.h engine/texture.h engine/model.h engine/varray.h
engine/glare.o: engine/engine.h engine/rendertarget.h
engine/grass.o: engine/engine.h
engine/lightmap.o: engine/engine.h
engine/main.o: engine/engine.h
engine/master.o: shared/cube.h
engine/material.o: engine/engine.h
engine/menus.o: engine/engine.h
engine/movie.o: engine/engine.h
engine/normal.o: engine/engine.h
engine/octa.o: engine/engine.h
engine/octaedit.o: engine/engine.h
engine/octarender.o: engine/engine.h
engine/physics.o: engine/engine.h engine/mpr.h
engine/pvs.o: engine/engine.h
engine/rendergl.o: engine/engine.h engine/varray.h
engine/rendermodel.o: engine/engine.h engine/ragdoll.h engine/animmodel.h engine/vertmodel.h engine/skelmodel.h engine/md2.h engine/md3.h engine/md5.h engine/obj.h engine/smd.h engine/iqm.h
engine/renderparticles.o: engine/engine.h engine/rendertarget.h engine/depthfx.h engine/explosion.h engine/lensflare.h engine/lightning.h
engine/rendersky.o: engine/engine.h
engine/rendertext.o: engine/engine.h
engine/renderva.o: engine/engine.h
engine/serverbrowser.o: engine/engine.h
engine/server.o: engine/engine.h
engine/shader.o: engine/engine.h
engine/shadowmap.o: engine/engine.h engine/rendertarget.h
engine/sound.o: engine/engine.h
engine/texture.o: engine/engine.h engine/scale.h
engine/water.o: engine/engine.h
engine/world.o: engine/engine.h
engine/worldio.o: engine/engine.h
fpsgame/ai.o: fpsgame/game.h
fpsgame/cdemo.o: fpsgame/cdemo.h
fpsgame/cdemo.h: fpsgame/game.h
fpsgame/client.o: fpsgame/game.h fpsgame/cdemo.h fpsgame/capture.h fpsgame/ctf.h fpsgame/collect.h
fpsgame/entities.o: fpsgame/game.h fpsgame/cdemo.h
fpsgame/fps.o: fpsgame/game.h
fpsgame/game.h: shared/cube.h fpsgame/ai.h
fpsgame/monster.o: fpsgame/game.h
fpsgame/movable.o: fpsgame/game.h
fpsgame/render.o: fpsgame/game.h
fpsgame/scoreboard.o: fpsgame/game.h
fpsgame/server.o: fpsgame/game.h fpsgame/capture.h fpsgame/ctf.h fpsgame/collect.h fpsgame/extinfo.h fpsgame/aiman.h
fpsgame/waypoint.o: fpsgame/game.h
fpsgame/weapon.o: fpsgame/game.h fpsgame/cdemo.h
shared/crypto.o: shared/cube.h
shared/cube.h: shared/tools.h shared/geom.h shared/ents.h shared/command.h shared/iengine.h shared/igame.h
shared/geom.o: shared/cube.h
shared/stream.o: shared/cube.h
shared/tools.o: shared/cube.h
shared/zip.o: shared/cube.h

xcode/Launcher.o: xcode/Launcher.h
xcode/main.o: xcode/Launcher.h

quirks/oldglibc32.o: quirks/wrapper.hpp
quirks/oldglibc64.o: quirks/wrapper.hpp

