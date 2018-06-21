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

# ifndef _PSP_EDITOR_H_
# define _PSP_EDITOR_H_

#ifdef __cplusplus
extern "C" {
#endif

  typedef struct PSPWRITE_t {

    char psp_homedir[MAX_PATH];
    char edit_filename[MAX_PATH];
    int  is_modified;
    int  ask_overwrite;
    int  psp_cpu_clock;
    int  psp_font_size;

    int  dos_mode;
    int  expand_tab;
    int  tab_stop;
    int  fg_color;
    int  bg_color;
    int  screen_w;
    int  screen_h;
    int  wrap_w;
    int  wrap_mode;
    int  move_on_text;

  } PSPWRITE_t;

  extern PSPWRITE_t PSPWRITE;


#ifdef __cplusplus
}
#endif

# define COLOR_WHITE              0
# define COLOR_BLACK              1
# define COLOR_DARK_BLUE          2
# define COLOR_GREEN              3
# define COLOR_RED                4
# define COLOR_BROWN              5
# define COLOR_MAGENTA            6
# define COLOR_ORANGE             7
# define COLOR_YELLOW             8
# define COLOR_BRIGHT_GREEN       9
# define COLOR_CYAN              10
# define COLOR_BRIGHT_BLUE       11
# define COLOR_BLUE              12
# define COLOR_PINK              13
# define COLOR_GRAY              14
# define COLOR_BRIGHT_GRAY       15
# define COLOR_IMAGE             16
# define EDITOR_MAX_COLOR        17

# define EDITOR_SCREEN_MIN_WIDTH  50
# define EDITOR_SCREEN_MIN_HEIGHT 12
# define EDITOR_MAX_WRAP_WIDTH   200

  extern int editor_colors[EDITOR_MAX_COLOR];

  extern char* editor_colors_name[EDITOR_MAX_COLOR];

  extern void psp_editor_main_loop();
  extern int psp_editor_save(char *filename);
  extern int psp_editor_load(char *filename);
  extern void psp_editor_new();
  
  extern void psp_editor_update_column();
  extern void psp_editor_update_line();
  extern void psp_editor_menu(char* filename);

# endif
