USERID UTS

/* utsbasic : utsbfile.c                       */
/* Copyright:(c) sarbayo, 2001-2011            */ 
/* Modified T. Chandler utsbasic utsbfile.c    */


parse_open()
{
   int pi, len, ab_code = 20, x = line_ndx;
   char ch;

printf("parse_open Start\n");

   len = strlen(p_string);
   pi = e_pos;
   pi = get_upper(pi, len);

   if(pi < len)
   {
      e_pos = pi;
      get_iomode(len);
   }
   else
   {
      strcpy(xstring, "Invalid Open Mode: ");
      a_bort(ab_code, x);
   }
}


get_iomode(len)
   int len;
{
   char ch,io_mode;
   int pi, ndx, maxfiles=IOARRAY, x = line_ndx, ab_code = 2;
   int fnum;

   pi = e_pos;
   ch = p_string[pi];

   io_mode = ch; 
 
   pi = get_digit(pi, len);

   if(pi == len)
   {
      strcpy(xstring, "Invalid File Format:");
      a_bort(ab_code,x);
   }
   else
   {
      e_pos = pi;
      fnum = get_avalue();
      ndx = fnum;
      ndx--;

      if((ndx < 0) || (ndx > maxfiles))
      {
         strcpy(xstring, "Invalid File Number:\n");
         a_bort(ab_code, x);
      }
      else if(fp[ndx].path[0] != '\0')
      {
         strcpy(xstring, "File Number in Use:");
         a_bort(ab_code,x);
      }
      else
      {
         fopen_short(io_mode, ndx, len);
      }
   }
}


fopen_short(io_mode, ndx, len)
   char io_mode;
   int ndx;
   int len;
{
   char ch, quote = '\"', io_path[PATH];
   int pi, indx, x = line_ndx, ab_code = 20;

   pi = e_pos;
   ch = p_string[pi];

   while((ch != quote) && (isalpha(ch) == 0) && (pi < len))
   {
      pi++;
      ch = p_string[pi];
   }

   if(pi == len)
   {
      strcpy(xstring, "Invalid File Name:");
      a_bort(ab_code, x);
   }

   e_pos = pi;
   if(ch == quote)
   {
      strng_assgn();
      strcpy(io_path, s_holder);
   }
   else
   {
      indx = get_strndx();
      strcpy(io_path, sv_stack[indx]);
   }
   pi = e_pos;

   fp[ndx].mode = io_mode;
   strcpy(fp[ndx].path, io_path);

   switch(io_mode)
   {
      case 'I':
        f_hdl = fopen(io_path, "r");
        strcpy(xstring, "File Not Found:\n");
        break;

      case 'O':
        f_hdl = fopen(io_path, "w");
        strcpy(xstring, "Unable to Open File:\n");
	break;

      case 'A':
	f_hdl = fopen(io_path, "a");
        strcpy(xstring, "Unable to Open File:\n");
	break;

      default:
        strcpy(xstring, "Invalid Mode:\n");
        a_bort(ab_code, x);
   }
   if(f_hdl == NULL)
   {
      a_bort(ab_code, x);
   }
   else
   {
      fp[ndx].fptr = f_hdl;
   }
}



do_fclose()
{
   char ch;
   int ii, pi, ndx, len, maxfiles=(IOARRAY-1), x = line_ndx, ab_code = 22;
   int fnum;

   len = strlen(p_string);
   pi = e_pos;
   pi = get_digit(pi, len);
   if(pi == len)
   {
      for(ii = 0; ii < IOARRAY; ii++)
      {
         if(fp[ii].path[0] != '\0')
         {
            reset_handle(ii);
         }
      }
   }
   else
   {
      ch = p_string[pi];
      while(pi < len)
      {
         if(isdigit(ch) == 0)
         {
            pi = get_digit(pi,len);
         }
         if(pi < len)
         {
            e_pos = pi;
            fnum = get_avalue();
            ndx = fnum;
            ndx--;
            if((ndx < 0) || (ndx > maxfiles))
            {
               strcpy(xstring, "Invalid File Number:\n");
               a_bort(ab_code,x);
            }
            else if(fp[ndx].path[0] != '\0')
            {
               reset_handle(ndx);
            }
            pi = e_pos;
            ch = p_string[pi];
         }
      }
   }
}


input_io()
{
   char ch;
   int pi, port = 0, len, maxfiles=IOARRAY, x = line_ndx, ab_code = 21;
   int fnum = 0;

   len = strlen(p_string);
   pi = e_pos;
   ch = p_string[pi];
   pi = get_digit(pi, len);

   if(pi == len)
   {
      strcpy(xstring, "Invalid Input Format;");
      a_bort(ab_code, x);
   }
   else
   {
      e_pos = pi;
      fnum = get_avalue();
      port = fnum;
      port--; 
      if((port < 0) || (port > maxfiles))
      {
         strcpy(xstring, "Invalid File number\n");
         a_bort(ab_code, x);
      }
      else if(fp[port].mode != 'I')
      {
         strcpy(xstring, "FILE is not OPEN for INPUT\n");
         a_bort(ab_code, x);
      }
      else
      {
         get_finput(port, len, ch);
      }
   }

}



get_finput(port,len, chx)
   int port;
   int len;
   char chx;
{
   char ch, varname[VAR_NAME];
   int pi, type;

   pi = e_pos;
   ch = p_string[pi];

printf("get_finput Starting\n");

   while((pi < len) && (ch != '\n'))
   {
      if(isalpha(ch) == 0)
      {
         pi = get_alpha(pi, len);
         ch = p_string[pi];
      }

      if(pi < len)
      {
         e_pos = pi;
         type = get_vtype(pi);
         e_pos = pi;
         get_vnam();
         strcpy(varname, vnam);
printf("get_finput chx = %c\n",chx);
printf("get_finput varname = %s\n",varname);
printf("get_finput type = %d\n",type);
         if(chx == '@')
         {
            read_fline(port, varname);
            break;
         }
         else if(type == 3)
         {
            read_fstring(port, varname);
         }
         else
         {
            read_fvalue(port, varname);
         }
         pi = e_pos;
         ch = p_string[pi];
      }
   }
}


read_fstring(port, *name)
   int port;
   char *name;
{
   char chIn='\0', varname[VAR_NAME], temp[BUFSIZE];
   int ii = 0, ndx = 0, indx = 0, xsize;

   strcpy(varname, name);
   ndx = get_varndx(varname);
   
   f_hdl = fp[port].fptr;
   while((chIn != '\"') && (!feof(f_hdl)))
   {
      ii = fgetc(f_hdl);
      chIn = (char) ii;
   }
   chIn ='\0';

   if(!feof(f_hdl))
   {
      while((chIn != '\"') && (!feof(f_hdl)))
      {
         ii = fgetc(f_hdl);
         chIn = (char) ii;
         if(chIn != '\"')
         {
            temp[indx] = chIn;
            indx++;
         }
      }
   }
   temp[indx] = '\0';
   xsize = strlen(temp);
   xsize++;
   sv_stack[ndx] = realloc(sv_stack[ndx], xsize * sizeof(char));
   strcpy(sv_stack[ndx], temp);
}


read_fvalue(port, *name)
   int port;
   char *name;
{
   char chi = '\0', varname[VAR_NAME], temp[BUFSIZE];
   int pi, type, ii = 0, ndx = 0, indx = 0;

   strcpy(varname, name);
   pi = e_pos;
   type = get_vtype(pi);
 
   ndx = get_intndx(varname);

   f_hdl = fp[port].fptr;
   while((isdigit(chi) == 0) && (!feof(f_hdl)))
   {
      ii = fgetc(f_hdl);
      chi = (char) ii;
      if((chi == '-') || (chi == '.'))
      {
         temp[indx] = chi;
         indx++;
      }
   }
   while((isdigit(chi) != 0) || (chi == '.') && (!feof(f_hdl)))
   {
      temp[indx] = chi;
      indx++;
      ii = getc(f_hdl);
      chi = (char) ii;
   }
   temp[indx] = '\0';

   iv_stack[ndx] = atoi(temp);

}


write_io()
{
   char chmode;
   int pi, len, port, maxfiles=IOARRAY, x = line_ndx, ab_code = 24;
   int fnum;

   len = strlen(p_string);
   pi = e_pos;
   pi = get_digit(pi, len);

   if(pi == len)
   {
      strcpy(xstring, "Invallid Write Format:\n");
      a_bort(ab_code, x);
   }
   else
   {
      e_pos = pi;
      fnum = get_avalue();
      port = fnum;
      port--;
      chmode = fp[port].mode;
      if((port < 0) || (port > maxfiles))
      {
         strcpy(xstring, "Invalid File Number:\n");
         a_bort(ab_code, x);
      }
      else if((chmode != 'O') && (chmode != 'A'))
      {
         strcpy(xstring, "File Not Open for Output:\n");
         a_bort(ab_code, x);
      }
      else
      {
         get_foutput(port, len);
      }
   }
}


get_foutput(port, len)
   int port;
   int len;
{
   char ch, nl='\n', varname[VAR_NAME];
   int pi, type, wflag = 0, maxfiles=IOARRAY, x = line_ndx, ab_code = 24;
   int fnum;

   pi = e_pos;
   ch = p_string[pi];
   while((pi < len) && (ch != '\n'))
   {
      if(isalpha(ch) == 0)
      {
         pi = get_alpha(pi, len);
         ch = p_string[pi];
      }
      if(pi < len)
      {
         e_pos = pi;
         type = get_vtype(pi);
         e_pos = pi;
         get_vnam();
         strcpy(varname, vnam);
         if(type == 3)
         {
            wflag = write_fstring(wflag,port,varname);
         }
         else
         {
            wflag = write_fvalue(wflag, port,varname);
         }
         pi = e_pos;
         ch = p_string[pi];
      }
   }
   f_hdl = fp[port].fptr;
   fprintf(f_hdl, "%c", nl);
}


write_fstring(wflag, port, *name)
   int wflag;
   int port;
   char *name;
{
   char quote='\"', comma=',', varname[VAR_NAME], temp[BUFSIZE];
   int ndx;

   strcpy(varname, name);
   ndx = get_varndx(varname);
   strcpy(temp, sv_stack[ndx]);

   f_hdl =  fp[port].fptr;
   if(wflag > 0)
   {
      fprintf(f_hdl, "%c", comma);
   }
   fprintf(f_hdl, "%c%s%c", quote, temp, quote);
   wflag++;
   return wflag;
}


write_fvalue(wflag, port, *name)
   int wflag;
   int port;
   char *name;
{
   char ch, comma=',', varname[VAR_NAME], temp[BUFSIZE];
   int pi, type, ndx = 0, indx = 0, len, idx;
   int ivalue;
   int lvalue;
   int fvalue;
   int dvalue;

   strcpy (varname, name);
   pi = e_pos;
   type = get_vtype(pi);

   ndx = get_intndx(varname);
   ivalue = iv_stack[ndx];
   sprintf(temp, "%d", ivalue);

   len = strlen(temp);
   idx = len - 1;
   ch = temp[idx];
   if((type == 4) || (type == 3))
   {
      if(ch == '0')
      {
         while(ch == '0')
         {
            temp[idx] = '\0';
            idx--;
            ch = temp[idx];
            if(ch == '.')
            {
               temp[idx] = '\0';
            }
          }
       }
     }
     f_hdl = fp[port].fptr;
     if(wflag > 0)
     {
        fprintf(f_hdl, "%c", comma);
     }
     fprintf(f_hdl, "%s", temp);
     wflag++;
     return wflag;
}


read_fline(port,*name)
   int port;
   char *name;
{
   char varname[VAR_NAME], temp[BUFSIZE];
   int ndx = 0, xsize, ii;

   strcpy(varname, name);
   ndx = get_varndx(varname);
   temp[0] = '\0';
   f_hdl = fp[port].fptr;
   if(!feof(f_hdl))
   {
      fgets(temp, BUFSIZE, f_hdl);
   }
   xsize = strlen(temp);
   xsize++;
   if(xsize > 2)
   {
      temp[(xsize-2)] = '\0';
   }
   sv_stack[ndx] = realloc(sv_stack[ndx], xsize * sizeof(char));
   strcpy(sv_stack[ndx], temp);
}



reset_handle(ndx)
   int ndx;
{
   f_hdl = fp[ndx].fptr;
   fclose(f_hdl);
   zero_handle(ndx);
}


zero_handle(ndx)
   int ndx;
{
   fp[ndx].path[0] = '\0';
   fp[ndx].mode = '\0';
   fp[ndx].fptr = '\0';
}


clr_iohandles()
{
   int ii;

   for(ii = 0; ii < IOARRAY;  ii++)
   {
      zero_handle(ii);
   }
}










