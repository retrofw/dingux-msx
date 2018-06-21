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

#ifndef __CPUGP2X_H__
#define __CPUGP2X_H__

# define GP2X_DEF_CLOCK      200
# define GP2X_DEF_EMU_CLOCK  200
# define GP2X_MIN_CLOCK      100
# define GP2X_MAX_CLOCK      270

/*Definicion de funciones*/

void cpu_init(void);

int cpu_deinit(void);

void save_system_regs(void);

void load_system_regs(void);

unsigned cpu_get_clock(void);

void cpu_set_clock(int psp_speed);

unsigned get_freq_920_CLK();

unsigned short get_920_Div();

unsigned get_display_clock_div();

void set_display_clock_div(unsigned div);

void set_FCLK(unsigned MHZ);

void set_DCLK_Div( unsigned short div );

void set_920_Div(unsigned short div);

void Disable_940(void);

unsigned short Disable_Int_940(void);

unsigned get_status_UCLK();

unsigned get_status_ACLK();

void set_status_UCLK(unsigned s);

void set_status_ACLK(unsigned s);

void set_display(int mode);


/* Frecuencia de reloj de sistema */
#define SYS_CLK_FREQ 7372800

#endif
