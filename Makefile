#
# MSX port on RS-97
#
# by pingflood; 2018
#

CHAINPREFIX := /opt/mipsel-linux-uclibc
CROSS_COMPILE := $(CHAINPREFIX)/usr/bin/mipsel-linux-

CC = $(CROSS_COMPILE)gcc
CXX = $(CROSS_COMPILE)g++
STRIP = $(CROSS_COMPILE)strip

SYSROOT     := $(shell $(CC) --print-sysroot)

MSX_VERSION=1.1.0

TARGET = ./dingux-msx/dingux-msx.dge
SDL_CONFIG = $(SYSROOT)/usr/bin/sdl-config
OBJS = ./src/gp2x_psp.o \
./src/cpudingux.o \
./src/fMSX.o ./src/MSX.o ./src/Patch.o ./src/Sound.o ./src/Disk.o \
./src/Z80.o ./src/I8255.o ./src/AY8910.o ./src/YM2413.o ./src/SCC.o ./src/V9938.o ./src/I8251.o \
./src/SDLgfx.o ./src/SDLsnd.o ./src/SDLfilter.o \
./src/emu2413.o ./src/emu2212.o ./src/emu2149.o \
./src/fmopl.o ./src/ymdeltat.o \
./src/psp_main.o \
./src/psp_sdl.o \
./src/psp_kbd.o \
./src/psp_font.o \
./src/psp_menu.o \
./src/psp_joy.o \
./src/psp_danzeff.o \
./src/psp_menu_set.o \
./src/psp_menu_help.o \
./src/psp_menu_joy.o \
./src/psp_menu_kbd.o \
./src/psp_menu_cheat.o \
./src/psp_menu_list.o \
./src/psp_editor.o \
./src/unzip.o \
./src/ioapi.o \
./src/sha1.o \
./src/psp_fmgr.o

DEFAULT_CFLAGS = $(shell $(SDL_CONFIG) --cflags)

MORE_CFLAGS  = -DFMSX -DUNIX -DNARROW -DSOUND -DBPP16 -DSDL -DLSB_FIRST -std=gnu11
MORE_CFLAGS += -I. -I$(CHAINPREFIX)/usr/include/
MORE_CFLAGS += -DMPU_JZ4740 -mips32 -G0
MORE_CFLAGS += -O3 -fsigned-char -ffast-math -fomit-frame-pointer -fno-strength-reduce
MORE_CFLAGS += -DDINGUX_MODE
MORE_CFLAGS += -DLINUX_MODE
MORE_CFLAGS += -DNO_STDIO_REDIRECT
MORE_CFLAGS += -DMSX_VERSION=\"$(MSX_VERSION)\"
MORE_CFLAGS += -O2 -fomit-frame-pointer -ffunction-sections -ffast-math -fsingle-precision-constant

LDFLAGS  = -s -lm -lz `$(SDL_CONFIG) --libs`
LDFLAGS += -Wl,--gc-sections

LIBS += -lSDL_image -lpng
LIBS += -lpthread  -ldl
LIBS += -B$(SYSROOT)/usr/lib
LIBS += -R$(SYSROOT)/usr/lib
LIBS += -L$(SYSROOT)/usr/lib

CFLAGS = $(DEFAULT_CFLAGS) $(MORE_CFLAGS) 

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(CFLAGS) $(OBJS) $(LIBS) -o $(TARGET) && $(STRIP) $(TARGET)

ipk: $(TARGET)
	@rm -rf /tmp/.dingux-msx-ipk/ && mkdir -p /tmp/.dingux-msx-ipk/root/home/retrofw/emus/dingux-msx /tmp/.dingux-msx-ipk/root/home/retrofw/apps/gmenu2x/sections/emulators /tmp/.dingux-msx-ipk/root/home/retrofw/apps/gmenu2x/sections/systems
	@cp -r dingux-msx/*.rom dingux-msx/dingux-msx.dge dingux-msx/dingux-msx.man.txt dingux-msx/dingux-msx.png dingux-msx/splash.png dingux-msx/thumb.png dingux-msx/graphics /tmp/.dingux-msx-ipk/root/home/retrofw/emus/dingux-msx
	@cd /tmp/.dingux-msx-ipk/root/home/retrofw/emus/dingux-msx && mkdir cht disk joy kbd roms save scr set txt
	@cp dingux-msx/dingux-msx.lnk /tmp/.dingux-msx-ipk/root/home/retrofw/apps/gmenu2x/sections/emulators
	@cp dingux-msx/msx.dingux-msx.lnk /tmp/.dingux-msx-ipk/root/home/retrofw/apps/gmenu2x/sections/systems
	@sed "s/^Version:.*/Version: $$(date +%Y%m%d)/" dingux-msx/control > /tmp/.dingux-msx-ipk/control
	@tar --owner=0 --group=0 -czvf /tmp/.dingux-msx-ipk/control.tar.gz -C /tmp/.dingux-msx-ipk/ control
	@tar --owner=0 --group=0 -czvf /tmp/.dingux-msx-ipk/data.tar.gz -C /tmp/.dingux-msx-ipk/root/ .
	@echo 2.0 > /tmp/.dingux-msx-ipk/debian-binary
	@ar r dingux-msx/dingux-msx.ipk /tmp/.dingux-msx-ipk/control.tar.gz /tmp/.dingux-msx-ipk/data.tar.gz /tmp/.dingux-msx-ipk/debian-binary

clean:
	rm -f $(OBJS) $(TARGET)

ctags: 
	ctags *[ch]
