/** fMSX: portable MSX emulator ******************************/
/**                                                         **/
/**                          Disk.c                         **/
/**                                                         **/
/** This file contains standard disk access drivers working **/
/** with disk images from files.                            **/
/**                                                         **/
/** Copyright (C) Marat Fayzullin 1994-2003                 **/
/**     You are not allowed to distribute this software     **/
/**     commercially. Please, notify me, if you make any    **/
/**     changes to this file.                               **/
/*************************************************************/

#include "MSX.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <zlib.h>

#ifdef __BORLANDC__
#include <io.h>
#endif

#ifdef UNIX
#include <unistd.h>
#endif

#ifndef O_BINARY
#define O_BINARY 0
#endif

static byte   DrivesFormat[2]   = { 0, 0 };  /* 0 = dsk, 1 = dsz */
static gzFile DrivesGZ[2]       = { 0, 0 };
static int    Drives[2]         = { -1,-1 }; /* Disk image files */

static int   RdOnly[2];                     /* 1 = read-only    */ 

static int
my_open(byte ID, byte Read_only, byte GZ_Format, char* Name)
{
  if(ID>=MAXDRIVES) return -1;
  Drives[ID] = -1;
  DrivesGZ[ID] = 0;
  DrivesFormat[ID] = GZ_Format;
  if (GZ_Format) Read_only = 1;
  RdOnly[ID] = Read_only;
  if (GZ_Format) {
    DrivesGZ[ID] = gzopen( Name, "rb" );
    if (! DrivesGZ[ID]) return -1;
  } else {
    if (Read_only) Drives[ID] = open(Name, O_RDONLY|O_BINARY);
    else           Drives[ID] = open(Name, O_RDWR|O_BINARY);
    if (Drives[ID] < 0) return -1;
  }
  return 0;
}

static int
my_close(byte ID)
{
  if(ID>=MAXDRIVES) return -1;

  if (DrivesFormat[ID]) {
    if (DrivesGZ[ID] != 0) { gzclose(DrivesGZ[ID]); }
  } else {
    if (Drives[ID]>=0) { close(Drives[ID]); }
  }
  Drives[ID] = -1;
  DrivesGZ[ID] = 0;
}

static int
my_read(byte ID, byte* Buf, int Len)
{
  int ret_val = -1;
  if (ID>=MAXDRIVES) return -1;

//fprintf(stdout, "read %d %lx %d\n", ID, Buf, Len);

  if (DrivesFormat[ID]) {
    if (DrivesGZ[ID] != 0) {
      ret_val = gzread( DrivesGZ[ID], Buf, Len);
//fprintf(stdout, "gzread ret_val=%d\n", ret_val);
    }
  } else {
    if (Drives[ID] >= 0) {
      ret_val = read( Drives[ID], Buf, Len);
//fprintf(stdout, "read ret_val=%d\n", ret_val);
    }
  }
  return ret_val;
}

static int
my_lseek(byte ID, long offset, int whence)
{
  int ret_val = -1;
  if (ID>=MAXDRIVES) return -1;

//fprintf(stdout, "lseek %d %ld %d\n", ID, offset, whence);

  if (DrivesFormat[ID]) {
    if (DrivesGZ[ID] != 0) {
      ret_val = gzseek( DrivesGZ[ID], offset, whence);
//fprintf(stdout, "gzseek ret_val=%d\n", ret_val);
    }
  } else {
    if (Drives[ID] >= 0) {
      ret_val = lseek( Drives[ID], offset, whence);
//fprintf(stdout, "lseek ret_val=%d\n", ret_val);
    }
  }
  return ret_val;
}

static int
my_write(byte ID, byte* Buf, int Len)
{
  int ret_val = -1;
  if (ID>=MAXDRIVES) return -1;

//fprintf(stdout, "write %d %lx %d\n", ID, Buf, Len);

  if (DrivesFormat[ID]) {
    if (DrivesGZ[ID] != 0) {
      ret_val = gzwrite( DrivesGZ[ID], Buf, Len);
    }
  } else {
    if (Drives[ID] >= 0) {
      ret_val = write( Drives[ID], Buf, Len);
    }
  }
//fprintf(stdout, "ret_val=%d\n", ret_val);
  return ret_val;
}

/** DiskPresent() ********************************************/
/** Return 1 if disk drive with a given ID is present.      **/
/*************************************************************/
byte DiskPresent(byte ID)
{
  if (ID < MAXDRIVES) {
    if (DrivesFormat[ID]) {
      return DrivesGZ[ID] != 0;
    }
    return Drives[ID] >= 0;
  }
  return 0;
}

/** DiskRead() ***********************************************/
/** Read requested sector from the drive into a buffer.     **/
/*************************************************************/
byte DiskRead(byte ID,byte *Buf,int N)
{
  if (DiskPresent(ID)) {
    if(my_lseek(ID,N*512L,0)==N*512L)
      return(my_read(ID,Buf,512)==512);
  }
  return(0);
}

/** DiskWrite() **********************************************/
/** Write contents of the buffer into a given sector of the **/
/** disk.                                                   **/
/*************************************************************/
byte DiskWrite(byte ID,byte *Buf,int N)
{
  if((ID<MAXDRIVES)&&(Drives[ID]>=0)&&!RdOnly[ID])
    if(my_lseek(ID,N*512L,0)==N*512L)
      return(my_write(ID,Buf,512)==512);
  return(0);
}

/** ChangeDisk() *********************************************/
/** Change disk image in a given drive. Closes current disk **/
/** image if Name=0 was given. Returns 1 on success or 0 on **/
/** failure.                                                **/
/*************************************************************/
byte ChangeDisk(byte ID, char *Name)
{
  byte GZ_Format = 0;
  char* scan = 0;
  /* We only have MAXDRIVES drives */
  if(ID>=MAXDRIVES) return 0;
  /* Close previous disk image */
  my_close( ID );
  if(!Name) return 1;

  scan = strrchr(Name, '.');
  if (scan && (!strcasecmp(scan, ".dsz"))) {
    GZ_Format = 1;
  }
//fprintf(stdout, "ChangeDisk id=%d Name=%s gz=%d\n", ID, Name, GZ_Format);
  /* Open new disk image */
  if (my_open( ID, 0, GZ_Format, Name ) < 0) {
    /* If failed to open for writing, open read-only */
    if (my_open( ID, 1, GZ_Format, Name ) < 0) {
      return 0;
    }
  }
  return 1;
}
