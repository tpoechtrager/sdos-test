BUILDTRIPLET=$(shell libenet/config.guess)

ifeq ($(strip $(PREFIX)),)
PREFIX=$(BUILDTRIPLET)
endif

STRIP=true
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
override CXXFLAGS+= $(CXXSTD) -pthread -fvisibility=hidden -fvisibility-inlines-hidden -Wall -fsigned-char -fno-exceptions -fno-rtti $(CPUINFO)

ifdef MAC
override OPTFLAGS += -fvisibility=hidden -fvisibility-inlines-hidden 
else
override OPTFLAGS += -fvisibility=hidden 
endif

TOPDIR= $(shell pwd)

INCLUDES= -Ishared -Iengine -Ifpsgame -Iinclude -Iinclude/SDL2

ifdef WINDOWS
CLIENT_INCLUDES= $(INCLUDES)
CLIENT_LIBS= -mwindows -static-libgcc -static-libstdc++ -Llib -lenet -lSDL2 -lSDL2_image -ljpeg -lpng -lz -lSDL2_mixer -logg -lvorbis -lvorbisfile -lws2_32 -lwinmm -lopengl32 -ldxguid -lgdi32 -lole32 -limm32 -lversion -loleaut32 -Wl,-Bstatic -lpthread
endif
ifdef LINUX
CLIENT_INCLUDES= $(INCLUDES) -I/usr/X11R6/include
CLIENT_LIBS= -Llib -L/usr/X11R6/lib -lX11 -lGL -lenet -lSDL2 -lSDL2_image -ljpeg -lpng -lz -lSDL2_mixer -logg -lvorbis -lvorbisfile -lm -ldl
endif
ifdef MAC
CLIENT_INCLUDES= $(INCLUDES)
CLIENT_LIBS= -Llib -lenet -lSDL2 -lSDL2_image -ljpeg -lpng -lz -lSDL2_mixer -logg -lvorbis -lvorbisfile -lm -ldl
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

SAUER_DEPLIBS= libz libenet libSDL libSDL_image libSDL_mixer

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
	cd libenet; PKG_CONFIG_PATH="$(TOPDIR)/lib/pkgconfig" PATH="$(TOPDIR)/bin:$(PATH)" CC=$(CC) ac_cv_func_memcmp_working=yes ./configure --host=$(PREFIX) --build=$(BUILDTRIPLET) --prefix="$(TOPDIR)" --enable-shared=no CPPFLAGS="-pthread -I$(TOPDIR)/include" CFLAGS="-pthread -I$(TOPDIR)/include $(CPUINFO) $(OPTFLAGS)" LDFLAGS="$(CPUINFO) -L$(TOPDIR)/lib"

libz/Makefile:
	cd libz; PKG_CONFIG_PATH="$(TOPDIR)/lib/pkgconfig" PATH="$(TOPDIR)/bin:$(PATH)" CHOST="$(PREFIX)" CPPFLAGS="-pthread -I$(TOPDIR)/include" CFLAGS="-pthread -I$(TOPDIR)/include $(CPUINFO) $(OPTFLAGS)" LDFLAGS="$(CPUINFO) -L$(TOPDIR)/lib" CC=$(CC) ./configure --prefix="$(TOPDIR)" --static

libjpeg/Makefile:
	cd libjpeg; PKG_CONFIG_PATH="$(TOPDIR)/lib/pkgconfig" PATH="$(TOPDIR)/bin:$(PATH)" CC=$(CC) ac_cv_func_memcmp_working=yes ./configure --host=$(PREFIX) --build=$(BUILDTRIPLET) --prefix="$(TOPDIR)" --without-turbojpeg --enable-shared=no CPPFLAGS="-pthread -I$(TOPDIR)/include" CFLAGS="-pthread -I$(TOPDIR)/include $(CPUINFO) $(OPTFLAGS)" LDFLAGS="$(CPUINFO) -L$(TOPDIR)/lib"

libpng/Makefile: libz
	cd libpng; PKG_CONFIG_PATH="$(TOPDIR)/lib/pkgconfig" PATH="$(TOPDIR)/bin:$(PATH)" CC=$(CC) ac_cv_func_memcmp_working=yes ./configure --host=$(PREFIX) --build=$(BUILDTRIPLET) --prefix="$(TOPDIR)" --enable-shared=no CPPFLAGS="-pthread -I$(TOPDIR)/include" CFLAGS="-pthread -I$(TOPDIR)/include $(CPUINFO) $(OPTFLAGS)" LDFLAGS="$(CPUINFO) -L$(TOPDIR)/lib"

libogg/Makefile:
	cd libogg; PKG_CONFIG_PATH="$(TOPDIR)/lib/pkgconfig" PATH="$(TOPDIR)/bin:$(PATH)" CC=$(CC) ac_cv_func_memcmp_working=yes ./configure --host=$(PREFIX) --build=$(BUILDTRIPLET) --prefix="$(TOPDIR)" --enable-shared=no CPPFLAGS="-pthread -I$(TOPDIR)/include" CFLAGS="-pthread -I$(TOPDIR)/include $(CPUINFO) $(OPTFLAGS)" LDFLAGS="$(CPUINFO) -L$(TOPDIR)/lib"

libvorbis/Makefile: libogg
	cd libvorbis; PKG_CONFIG_PATH="$(TOPDIR)/lib/pkgconfig" PATH="$(TOPDIR)/bin:$(PATH)" CC=$(CC) ac_cv_func_memcmp_working=yes ./configure --host=$(PREFIX) --build=$(BUILDTRIPLET) --prefix="$(TOPDIR)" --enable-shared=no --disable-oggtest --enable-docs=no --enable-examples=no CPPFLAGS="-pthread -I$(TOPDIR)/include" CFLAGS="-pthread -I$(TOPDIR)/include $(CPUINFO) $(OPTFLAGS)" LDFLAGS="$(CPUINFO) -L$(TOPDIR)/lib"

ifdef WINDOWS
libSDL/Makefile:
	cd libSDL; PKG_CONFIG_PATH="$(TOPDIR)/lib/pkgconfig" PATH="$(TOPDIR)/bin:$(PATH)" CC=$(CC) ac_cv_func_memcmp_working=yes ./configure --host=$(PREFIX) --build=$(BUILDTRIPLET) --prefix="$(TOPDIR)" --enable-shared=no --enable-video-dummy=no --enable-dummyaudio=no --enable-diskaudio=no --enable-joystick=no --disable-haptic --disable-power --enable-video-opengles=no --enable-render=no --enable-render-d3d=no LDFLAGS="$(CPUINFO) -L$(TOPDIR)/lib" CPPFLAGS="-pthread -I$(TOPDIR)/include" CFLAGS="-pthread -I$(TOPDIR)/include $(OPTFLAGS) $(CPUINFO) -DDECLSPEC=\"\""
libSDL_mixer/Makefile: libSDL libvorbis
	cd libSDL_mixer; PKG_CONFIG_PATH="$(TOPDIR)/lib/pkgconfig" PATH="$(TOPDIR)/bin:$(PATH)" CC=$(CC) ac_cv_func_memcmp_working=yes ./configure --host=$(PREFIX) --build=$(BUILDTRIPLET) --prefix="$(TOPDIR)" --enable-shared=no --enable-music-cmd=no --enable-music-mod=no --enable-music-mod-modplug=no --enable-music-midi=no --enable-music-fluidsynth-shared=no --enable-music-ogg-tremor=no --enable-music-ogg-shared=no --enable-music-flac=no --enable-music-flac-shared=no --enable-music-mp3=no --enable-music-mp3-mad-gpl=no --disable-sdltest --enable-render=no --enable-render-d3d=no LDFLAGS="$(CPUINFO) -L$(TOPDIR)/lib" CPPFLAGS="-pthread -I$(TOPDIR)/include" CFLAGS="-pthread -I$(TOPDIR)/include $(CPUINFO) $(OPTFLAGS) -DDECLSPEC=\"\"" LIBS="-logg -lvorbis -logg -lm"
libSDL_image/Makefile: libSDL libjpeg libpng
	cd libSDL_image; PKG_CONFIG_PATH="$(TOPDIR)/lib/pkgconfig" PATH="$(TOPDIR)/bin:$(PATH)" CC=$(CC) ac_cv_func_memcmp_working=yes ac_cv_lib_jpeg_jpeg_CreateDecompress=yes ./configure --host=$(PREFIX) --build=$(BUILDTRIPLET) --prefix="$(TOPDIR)" --enable-shared=no --enable-jpg-shared=no --enable-png-shared=no --enable-webp=no --enable-tif=no --disable-sdltest LDFLAGS="$(CPUINFO) -L$(TOPDIR)/lib" CPPFLAGS="-pthread -I$(TOPDIR)/include" CFLAGS="-pthread -I$(TOPDIR)/include $(CPUINFO) $(OPTFLAGS) -DDECLSPEC=\"\""
endif

ifdef LINUX
libSDL/Makefile:
	cd libSDL; PKG_CONFIG_PATH="$(TOPDIR)/lib/pkgconfig" PATH="$(TOPDIR)/bin:$(PATH)" CC=$(CC) ac_cv_func_memcmp_working=yes ./configure --host=$(PREFIX) --build=$(BUILDTRIPLET) --prefix="$(TOPDIR)" --enable-shared=no --enable-video-dummy=no --enable-dummyaudio=no --enable-diskaudio=no --enable-video-directfb=no --enable-joystick=no --disable-haptic --disable-power --disable-dbus --disable-fusionsound --disable-libudev --disable-alsatest --enable-render=no --enable-video-opengles=no CPPFLAGS="-pthread -I$(TOPDIR)/include" CFLAGS="-pthread -I$(TOPDIR)/include $(CPUINFO) $(OPTFLAGS)" LDFLAGS="$(CPUINFO) -L$(TOPDIR)/lib"
libSDL_mixer/Makefile: libSDL libvorbis
	cd libSDL_mixer; PKG_CONFIG_PATH="$(TOPDIR)/lib/pkgconfig" PATH="$(TOPDIR)/bin:$(PATH)" CC=$(CC) ac_cv_func_memcmp_working=yes ./configure --host=$(PREFIX) --build=$(BUILDTRIPLET) --prefix="$(TOPDIR)" --enable-shared=no --enable-music-cmd=no --enable-music-mod=no --enable-music-mod-modplug=no --enable-music-midi=no --enable-music-fluidsynth-shared=no --enable-music-ogg-tremor=no --enable-music-ogg-shared=no --enable-music-flac=no --enable-music-flac-shared=no --enable-music-mp3=no --enable-music-mp3-mad-gpl=no --disable-sdltest CPPFLAGS="-pthread -I$(TOPDIR)/include" CFLAGS="-pthread -I$(TOPDIR)/include $(CPUINFO) $(OPTFLAGS)" LDFLAGS="$(CPUINFO) -L$(TOPDIR)/lib" LIBS="-logg -lvorbis -logg -lm"
libSDL_image/Makefile: libSDL libjpeg libpng
	cd libSDL_image; PKG_CONFIG_PATH="$(TOPDIR)/lib/pkgconfig" PATH="$(TOPDIR)/bin:$(PATH)" CC=$(CC) ac_cv_func_memcmp_working=yes ./configure --host=$(PREFIX) --build=$(BUILDTRIPLET) --prefix="$(TOPDIR)" --enable-shared=no --enable-jpg-shared=no --enable-png-shared=no --enable-webp=no --enable-tif=no --disable-sdltest CPPFLAGS="-pthread -I$(TOPDIR)/include" CFLAGS="-pthread -I$(TOPDIR)/include $(CPUINFO) $(OPTFLAGS)" LDFLAGS="$(CPUINFO) -L$(TOPDIR)/lib"
endif

ifdef MAC
libSDL/Makefile:
	cd libSDL; PKG_CONFIG_PATH="$(TOPDIR)/lib/pkgconfig" PATH="$(TOPDIR)/bin:$(PATH)" CC=$(CC) ac_cv_func_memcmp_working=yes ./configure --host=$(PREFIX) --build=$(BUILDTRIPLET) --prefix="$(TOPDIR)" --enable-shared=no --enable-video-dummy=no --enable-dummyaudio=no --enable-diskaudio=no --enable-video-directfb=no --enable-joystick=no --disable-haptic --disable-power --disable-dbus --disable-fusionsound --disable-libudev --enable-render=no --enable-video-opengles=no --enable-video-x11=no --disable-alsatest CPPFLAGS="-pthread -I$(TOPDIR)/include" CFLAGS="-pthread -I$(TOPDIR)/include $(CPUINFO) $(OPTFLAGS)" LDFLAGS="$(CPUINFO) -L$(TOPDIR)/lib"
libSDL_mixer/Makefile: libSDL libvorbis
	cd libSDL_mixer; PKG_CONFIG_PATH="$(TOPDIR)/lib/pkgconfig" PATH="$(TOPDIR)/bin:$(PATH)" CC=$(CC) ac_cv_func_memcmp_working=yes ./configure --host=$(PREFIX) --build=$(BUILDTRIPLET) --prefix="$(TOPDIR)" --enable-shared=no --enable-music-cmd=no --enable-music-mod=no --enable-music-mod-modplug=no --enable-music-midi=no --enable-music-fluidsynth-shared=no --enable-music-ogg-tremor=no --enable-music-ogg-shared=no --enable-music-flac=no --enable-music-flac-shared=no --enable-music-mp3=no --enable-music-mp3-mad-gpl=no --disable-sdltest CPPFLAGS="-pthread -I$(TOPDIR)/include" CFLAGS="-pthread -I$(TOPDIR)/include $(CPUINFO) $(OPTFLAGS)" LDFLAGS="$(CPUINFO) -L$(TOPDIR)/lib" LIBS="-logg -lvorbis -logg -lm"
libSDL_image/Makefile: libSDL libjpeg libpng
	cd libSDL_image; PKG_CONFIG_PATH="$(TOPDIR)/lib/pkgconfig" PATH="$(TOPDIR)/bin:$(PATH)" CC=$(CC) ac_cv_lib_jpeg_jpeg_CreateDecompress=yes ac_cv_func_memcmp_working=yes ./configure --host=$(PREFIX) --build=$(BUILDTRIPLET) --prefix="$(TOPDIR)" --enable-shared=no --enable-imageio=no --enable-jpg-shared=no --enable-png-shared=no --enable-webp=no --enable-tif=no --disable-sdltest CPPFLAGS="-pthread -I$(TOPDIR)/include" CFLAGS="-pthread -I$(TOPDIR)/include $(CPUINFO) $(OPTFLAGS)" LDFLAGS="$(CPUINFO) -L$(TOPDIR)/lib"
endif

lib%: lib%/Makefile
	$(MAKE)	-C $@/ install

clean-lib%:
	-$(MAKE) -C lib$*/ uninstall distclean

clean-libz:
	-$(MAKE) -C libz/ uninstall distclean
	-$(RM) libz/Makefile libz/zconf.h

clean-libSDL:
	-$(MAKE) -C libSDL/ uninstall distclean
	-$(RM) libSDL/include/SDL_config.h libSDL/sdl2.pc

clean-libSDL_mixer:
	-$(MAKE) -C libSDL_mixer/ uninstall distclean
	-$(RM) libSDL_mixer/SDL2_mixer.spec

clean-libjpeg:
	-$(MAKE) -C libjpeg/ uninstall distclean
	-$(RM) libjpeg/simd/jsimdcfg.inc

clean:
	-$(RM) -r $(CLIENT_OBJS) $(MACOBJC) $(MACOBJCXX) quirks/*.o sauer_client sauerbraten.exe vcpp/mingw.res

distclean: clean-libSDL_image clean-libSDL_mixer clean-libSDL clean-libvorbis clean-libogg clean-libpng clean-libjpeg clean-libz clean-libenet clean
	-$(RM) -r share man lib bin etc

$(CLIENT_OBJS): CXXFLAGS += $(CLIENT_INCLUDES)

ifdef WINDOWS
client: $(CLIENT_OBJS)
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

client:	$(CLIENT_OBJS) $(MACOBJCXX) $(MACOBJC)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o sauer_client $(CLIENT_OBJS) $(MACOBJCXX) $(MACOBJC) $(CLIENT_LIBS) -framework IOKit -framework Cocoa -framework Carbon -framework CoreAudio -framework OpenGL -framework AudioUnit
	$(STRIP) sauer_client
endif
ifdef LINUX
client:	$(CLIENT_OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o sauer_client $(CLIENT_OBJS) -Wl,--as-needed -Wl,--start-group $(CLIENT_LIBS) -lrt -Wl,--end-group
	$(STRIP) sauer_client
ifeq (,$(findstring -ggdb,$(CXXFLAGS)))
ifneq (, $(findstring x86_64,$(PREFIX)))
	./remove_symbol_version memcpy@GLIBC_2.2.5
endif
	upx sauer_client
endif
endif

# DO NOT DELETE

engine/3dgui.o:		$(SAUER_DEPLIBS) engine/engine.h engine/textedit.h
engine/bih.o:		$(SAUER_DEPLIBS) engine/engine.h
engine/blend.o:		$(SAUER_DEPLIBS) engine/engine.h
engine/blob.o:		$(SAUER_DEPLIBS) engine/engine.h
engine/client.o:	$(SAUER_DEPLIBS) engine/engine.h
engine/command.o:	$(SAUER_DEPLIBS) engine/engine.h
engine/console.o:	$(SAUER_DEPLIBS) engine/engine.h engine/sdl2_keymap_extrakeys.h
engine/cubeloader.o:	$(SAUER_DEPLIBS) engine/engine.h
engine/decal.o:		$(SAUER_DEPLIBS) engine/engine.h
engine/dynlight.o:	$(SAUER_DEPLIBS) engine/engine.h
engine/engine.h:	$(SAUER_DEPLIBS) shared/cube.h engine/world.h engine/octa.h engine/lightmap.h engine/bih.h engine/texture.h engine/model.h engine/varray.h
engine/glare.o:		$(SAUER_DEPLIBS) engine/engine.h engine/rendertarget.h
engine/grass.o:		$(SAUER_DEPLIBS) engine/engine.h
engine/lightmap.o:	$(SAUER_DEPLIBS) engine/engine.h
engine/main.o:		$(SAUER_DEPLIBS) engine/engine.h
engine/master.o:	$(SAUER_DEPLIBS) shared/cube.h
engine/material.o:	$(SAUER_DEPLIBS) engine/engine.h
engine/menus.o:		$(SAUER_DEPLIBS) engine/engine.h
engine/movie.o:		$(SAUER_DEPLIBS) engine/engine.h
engine/normal.o:	$(SAUER_DEPLIBS) engine/engine.h
engine/octa.o:		$(SAUER_DEPLIBS) engine/engine.h
engine/octaedit.o:	$(SAUER_DEPLIBS) engine/engine.h
engine/octarender.o:	$(SAUER_DEPLIBS) engine/engine.h
engine/physics.o:	$(SAUER_DEPLIBS) engine/engine.h engine/mpr.h
engine/pvs.o:		$(SAUER_DEPLIBS) engine/engine.h
engine/rendergl.o:	$(SAUER_DEPLIBS) engine/engine.h engine/varray.h
engine/rendermodel.o:	$(SAUER_DEPLIBS) engine/engine.h engine/ragdoll.h engine/animmodel.h engine/vertmodel.h engine/skelmodel.h engine/md2.h engine/md3.h engine/md5.h engine/obj.h engine/smd.h engine/iqm.h
engine/renderparticles.o: $(SAUER_DEPLIBS) engine/engine.h engine/rendertarget.h engine/depthfx.h engine/explosion.h engine/lensflare.h engine/lightning.h
engine/rendersky.o:	$(SAUER_DEPLIBS) engine/engine.h
engine/rendertext.o:	$(SAUER_DEPLIBS) engine/engine.h
engine/renderva.o:	$(SAUER_DEPLIBS) engine/engine.h
engine/serverbrowser.o:	$(SAUER_DEPLIBS) engine/engine.h
engine/server.o:	$(SAUER_DEPLIBS) engine/engine.h
engine/shader.o:	$(SAUER_DEPLIBS) engine/engine.h
engine/shadowmap.o:	$(SAUER_DEPLIBS) engine/engine.h engine/rendertarget.h
engine/sound.o:		$(SAUER_DEPLIBS) engine/engine.h
engine/texture.o:	$(SAUER_DEPLIBS) engine/engine.h engine/scale.h
engine/water.o:		$(SAUER_DEPLIBS) engine/engine.h
engine/world.o:		$(SAUER_DEPLIBS) engine/engine.h
engine/worldio.o:	$(SAUER_DEPLIBS) engine/engine.h
fpsgame/ai.o:		$(SAUER_DEPLIBS) fpsgame/game.h
fpsgame/cdemo.o:	$(SAUER_DEPLIBS) fpsgame/cdemo.h
fpsgame/cdemo.h:	$(SAUER_DEPLIBS) fpsgame/game.h
fpsgame/client.o:	$(SAUER_DEPLIBS) fpsgame/game.h fpsgame/cdemo.h fpsgame/capture.h fpsgame/ctf.h fpsgame/collect.h
fpsgame/entities.o:	$(SAUER_DEPLIBS) fpsgame/game.h fpsgame/cdemo.h
fpsgame/fps.o:		$(SAUER_DEPLIBS) fpsgame/game.h
fpsgame/game.h:		$(SAUER_DEPLIBS) shared/cube.h fpsgame/ai.h
fpsgame/monster.o:	$(SAUER_DEPLIBS) fpsgame/game.h
fpsgame/movable.o:	$(SAUER_DEPLIBS) fpsgame/game.h
fpsgame/render.o:	$(SAUER_DEPLIBS) fpsgame/game.h
fpsgame/scoreboard.o:	$(SAUER_DEPLIBS) fpsgame/game.h
fpsgame/server.o:	$(SAUER_DEPLIBS) fpsgame/game.h fpsgame/capture.h fpsgame/ctf.h fpsgame/collect.h fpsgame/extinfo.h fpsgame/aiman.h
fpsgame/waypoint.o:	$(SAUER_DEPLIBS) fpsgame/game.h
fpsgame/weapon.o:	$(SAUER_DEPLIBS) fpsgame/game.h fpsgame/cdemo.h
shared/crypto.o:	$(SAUER_DEPLIBS) shared/cube.h
shared/cube.h:		$(SAUER_DEPLIBS) shared/tools.h shared/geom.h shared/ents.h shared/command.h shared/iengine.h shared/igame.h
shared/geom.o:		$(SAUER_DEPLIBS) shared/cube.h
shared/stream.o:	$(SAUER_DEPLIBS) shared/cube.h
shared/tools.o:		$(SAUER_DEPLIBS) shared/cube.h
shared/zip.o:		$(SAUER_DEPLIBS) shared/cube.h

xcode/Launcher.o:	$(SAUER_DEPLIBS) xcode/Launcher.h
xcode/main.o:		$(SAUER_DEPLIBS) xcode/Launcher.h

quirks/oldglibc32.o:	$(SAUER_DEPLIBS) quirks/wrapper.hpp
quirks/oldglibc64.o:	$(SAUER_DEPLIBS) quirks/wrapper.hpp

