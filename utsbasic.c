USERID UTS

/* utsbasic : utsbasic.c                       */
/* Copyright:(c) sarbayo, 2001-2011            */
/* Modified T. Chandler utsbasic utsbasic.c    */

/*--------------------- DECLARE HEADERS ---------------------*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/types.h>

#define BUFSIZE             78
#define LINE_NUM            6
#define TOKEN_LEN           21
#define VAR_NAME            33
#define LLEN                33
#define IOARRAY             25
#define PATH                80
 

	FILE *pgm, *f_out,*f_in;
        FILE *f_src;
        FILE *f_hdl;
	char prog_name[32];
	char p_string[BUFSIZE];
       char **array1;
 	char t_holder[20];
	char s_holder[BUFSIZE];
       char xstring[BUFSIZE];
	 int nrows;
 	 int ncolumns = BUFSIZE;
	 int line_ndx;
	 int s_pos, e_pos;
        char **temp_prog;
        char **temp_label;
         int *temp_byte;
         int *byte_array;
        char **label_nam;
         int token;
        char vnam[VAR_NAME];
         int fornxt_flg = 0;
         int str_ndx;

        char **sn_stack;
        char **sv_stack;
         int smax_vars = 0;

         int *iv_stack;
        char **in_stack;
         int imax_vars = 0;

         int *gosub_stack;
         int gs_ptr = -1;

        struct io_handles
        {
            char path[PATH];
            char mode;
            FILE *fptr;
        };
        struct io_handles fp[IOARRAY];


#include "utsbginp.c"
#include "utsbfile.c"
#include "utsbif.c"
#include "utsbinp.c"
#include "utsbloop.c"
#include "utsbout.c"
#include "utsbrdp.c"
#include "utsbstrg.c"
#include "utsbutl.c"
#include "utsbvar.c"


main(argc, argv)  
     int argc;
     char *argv[];
{	
  
  int ab_code = 1;
  int x = 0;

  printf("UTSBasic Intepreter\n");
  if(argc != 2)
  {
    a_bort(ab_code, x);
  }
  strcpy(t_holder, argv[1]);
  line_cnt(argv);
  clr_iohandles();
  pgm_par();
  exit(1);
}




pgm_par()
{
  line_ndx = 0;
  while(line_ndx < nrows)
  {
    s_pos = 0;
    e_pos = 0;
    get_token();

    parser();
    line_ndx++;
  }
}


get_token()
{
  strcpy(p_string, array1[line_ndx]);
  token = byte_array[line_ndx];
}


parser()
{
  int ab_code = 4;
  int x = line_ndx;
 
  switch(token)
  {
     case 1:		/* LET */
       parse_let();
       break;

     case 2:		/* CLEAR */
       break;

     case 3:		/* LOCATE */
       break;

     case 4:		/* PRINT */
       parse_print();
       break;

     case 5:		/* GOTO */
       go_to();
       break;

     case 6:		/* BEEP */
       break;

     case 7:		/* CLS */
       break;

     case 8:		/* END */
       printf("End of Program\n");
       line_ndx = nrows;
       break;

     case 9:		/* GOSUB */
       do_gosub();
       break;

     case 10:		/* RETURN */
       do_return();	
       break;

     case 11:		/* FOR */
       do_for();	
       break;

     case 12:		/* NEXT */
       do_next();	
       break;

     case 13:		/* IF */
       do_if();
       break;

     case 14:		/* ELSEIF */
       do_if();
       break;

     case 15:		/* ELSE */
       return;
       break;

     case 16:		/* ENDIF */
       return;
       break;

     case 17:		/* INPUT */
       get_input();
       break;

     case 18:		/* LINE INPUT */
       get_lninput();
       break;

    case 19:		/* OPEN */
       parse_open();
       break;

     case 20:		/* CLOSE */
       do_fclose();
       break; 

     case 21:		/* WRITE */
       write_io();
       break;

     case -1:
       break;

     default:
       a_bort(ab_code, x);
       break;
    }
}


go_to()
{
  char ch;
  char goto_label[LLEN];
  int pi;
  int si = 0;
  int ab_code=8;
  int xtest, x=line_ndx;
 
  pi = e_pos;
  pi = iswhite(pi);
  ch = p_string[pi];

  while(isalnum(ch))
  {
    goto_label[si] = ch;
    pi++;
    si++;
    ch = p_string[pi];
  }
  goto_label[si] = '\0';

  pi = -1;
  xtest = -1;
  while(xtest != 0)
  {
    pi++;
    if(pi == nrows)
    {
      strcpy(t_holder, goto_label);
      a_bort(ab_code, x);
    }
    xtest = strcmp(label_nam[pi], goto_label);
  }
  pi--;
  line_ndx = pi;
}


do_gosub()
{
   unsigned size;

   gs_ptr++;
   if(gs_ptr == 0)
   {
     size = 1;
     gosub_stack = malloc(size * sizeof(int));
   }
   else
   {
     size = (gs_ptr + 1);
     gosub_stack = realloc(gosub_stack, size * sizeof(int));
   }
   gosub_stack[gs_ptr] = line_ndx;
   go_to();
}


do_return()
{
   unsigned size;

   if(gs_ptr < 0)
   {
     return;
   }
   else if(gs_ptr == 0)
   {
     line_ndx = gosub_stack[gs_ptr];
     free(gosub_stack);
   }
   else
   {
     line_ndx = gosub_stack[gs_ptr];
   }
   gs_ptr--;
}








 