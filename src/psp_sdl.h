/*

Copyright 2005-2011 - Ludovic Jacomme - All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are
permitted provided that the following conditions are met:

   1. Redistributions of source code must retain the above copyright notice, this list of
      conditions and the following disclaimer.

   2. Redistributions in binary form must reproduce the above copyright notice, this list
      of conditions and the following disclaimer in the documentation and/or other materials
      provided with the distribution.

THIS SOFTWARE IS PROVIDED BY LUDOVIC JACOMME 'AS IS'' AND ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL LUDOVIC JACOMME OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those of the
authors and should not be interpreted as representing official policies, either expressed
or implied, of Ludovic Jacomme.

*/

# ifndef _PSP_SDL_H_
# define _PSP_SDL_H_

#ifdef __cplusplus
extern "C" {
#endif
# define psp_debug(m)   loc_psp_debug(__FILE__,__LINE__,m)

# define PSP_SDL_NOP   0
# define PSP_SDL_XOR   1

# define PSP_LINE_SIZE  320

# define PSP_SDL_SCREEN_WIDTH    320
# define PSP_SDL_SCREEN_HEIGHT   240

  typedef unsigned char   uchar;
  typedef unsigned int    uint;
  typedef unsigned short  ushort;

  extern SDL_Surface* back_surface;
  extern SDL_Surface* blit_surface;
  extern SDL_Surface* save_surface;
  extern SDL_Surface* thumb_surface;

  extern int psp_load_fonts(void);
  extern int psp_print_text(char * str, int colour, int v, int h);

  extern void loc_psp_debug(char *file, int line, char *message);

  /* PG -> SDL function */

  extern void psp_sdl_print(int x,int y, char *str, int color);
  extern void psp_sdl_clear_screen(int color);
  extern void psp_sdl_fill_rectangle(int x, int y, int w, int h, int color, int mode);
  extern void psp_sdl_draw_rectangle(int x, int y, int w, int h, int border, int mode);
  extern void psp_sdl_put_char(int x, int y, int color, int bgcolor, uchar c, int drawfg, int drawbg);
  extern void psp_sdl_fill_print(int x,int y,const char *str, int color, int bgcolor);
  extern void psp_sdl_flip(void);

  extern void psp_sdl_gu_stretch(SDL_Rect* srcRect, SDL_Rect* dstRect);
  extern void psp_sdl_lock(void);
  extern void psp_sdl_unlock(void);
  extern int psp_sdl_init(void);
  extern void psp_sdl_flush(void);
  extern void psp_sdl_save_bmp(char *filename);
  extern void psp_sdl_blit_background();
  extern void psp_sdl_exit(int status);
  extern void psp_sdl_select_font_6x10();
  extern void psp_sdl_select_font_8x8();
  extern uint psp_sdl_rgb(uchar R, uchar G, uchar B);
  extern void psp_sdl_save_screenshot(void);
  extern ushort * psp_sdl_get_vram_addr(uint x, uint y);

#ifdef __cplusplus
}
#endif
# endif
