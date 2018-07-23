#
# MSX port on RS-97
#
# by pingflood; 2018
#

MSX_VERSION=1.1.0

TARGET = assets/dingux-msx
SDL_CONFIG = /usr/bin/sdl-config

OBJS = gp2x_psp.o \
cpudingux.o \
fMSX.o MSX.o Patch.o Sound.o Disk.o \
Z80.o I8255.o AY8910.o YM2413.o SCC.o V9938.o I8251.o \
SDLgfx.o SDLsnd.o SDLfilter.o \
emu2413.o emu2212.o emu2149.o \
fmopl.o ymdeltat.o \
psp_main.o \
psp_sdl.o \
psp_kbd.o \
psp_font.o \
psp_menu.o \
psp_joy.o \
psp_danzeff.o \
psp_menu_set.o \
psp_menu_help.o \
psp_menu_joy.o \
psp_menu_kbd.o \
psp_menu_cheat.o \
psp_menu_list.o \
psp_editor.o \
unzip.o \
ioapi.o \
sha1.o \
psp_fmgr.o

CC = gcc
CXX = g++

MORE_CFLAGS = -DFMSX -DUNIX -DNARROW -DSOUND -DBPP16 -DSDL -DLSB_FIRST `$(SDL_CONFIG) --cflags` \
-I. -I$(CHAINPREFIX)/usr/include/ \
 -O3 -fsigned-char -ffast-math -fomit-frame-pointer -fno-strength-reduce \
 -DDINGUX_MODE \
 -DLINUX_MODE \
 -DNO_STDIO_REDIRECT \
 -DMSX_VERSION=\"$(MSX_VERSION)\"

LDFLAGS =   -lm -lz `$(SDL_CONFIG) --libs`

LIBS += -lSDL_image -lpng -lpthread  -ldl -lSDL

MORE_CFLAGS += -O0 -g -DINLINE=inline
LDFLAGS     +=

CFLAGS = $(DEFAULT_CFLAGS) $(MORE_CFLAGS) 

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(CFLAGS) $(OBJS) $(LIBS) -o $(TARGET)

#install: $(TARGET)
#	cp $< /media/dingux/local/emulators/dingux-msx/

clean:
	rm -f $(OBJS) $(TARGET)

ctags: 
	ctags *[ch]
