USERID UTS

/* utsbasic : utsbinp.c :                    */
/* Copyright:(c) sarbayo, 2001-2011          */
/* Modified T. Chandler utsbasic - utsbinp.c */


line_cnt(argv[])
   char *argv[];
{
  int ii=0, x=0;
  int ab_code = 2;
 
   nrows = 0;

   strcpy(prog_name, argv[1]);

   f_in = fopen(prog_name,"r");
   if(f_in == NULL)                
   {
      a_bort(ab_code, x);
   }
   else
   {
      load_src();            
      loader_1();            
      loader_2();           
   }
}
/*------- end line_cnt ----------*/


load_src()
{   
   char *tmp="source.tmp";
   int pi, len;
     
   f_out = fopen(tmp,"w");                      
   while(fgets(p_string, BUFSIZE, f_in) != NULL)
   {
     pi = 0;
     pi = iswhite(pi);
     len = strlen(p_string);
     if((len > 2) && (pi < len))              
     {
       if(!feof(f_in))
       {   
         save_tmp();
       }
     }
    }
    fclose(f_in);
    fclose(f_out);
}
/*------- end load_src ----------*/


save_tmp()
{
   char ch;
   int pi, len;

   strcpy(xstring, "  ");
   strcat(xstring, p_string);
   pi = 0;
   ch = p_string[pi];

   if(isupper(ch) != 0)
   {
     len = (LLEN-2);
     while(isalnum(ch) != 0)
     {
       pi++;
       ch = p_string[pi];
     }
     if((ch == ':') && (pi <= len))
     {
       pi++;
       p_string[pi] = '\0';
       strcat(p_string, "\n\0");
       fprintf(f_out, "%s", p_string);
       nrows++;
     }
     else
     {
       fprintf(f_out, "%s", xstring);
       nrows++;
     }
   }
   else if(isdigit(ch))
   {
     fprintf(f_out, "%s", p_string);
     nrows++;
   }
   else
   {
     pi = iswhite(pi);
     ch = p_string[pi];
     if(ch != '\'')
     {
       fprintf(f_out, "%s", xstring);
       nrows++;
     }
   }
}


loader_1()
{
   char ch, ln_holder[LLEN];
   char *tmp = "source.tmp";
    int ii, len,pi;
   unsigned size = ncolumns;

   temp_prog = malloc(nrows * sizeof(char *));
   for(ii = 0; ii < nrows; ii++)
   {
      temp_prog[ii] = malloc(size * sizeof(char));
   }
   temp_label = malloc(nrows * sizeof(char *));
   for(ii = 0; ii < nrows; ii++)
   {
      temp_label[ii] = malloc(LLEN * sizeof(char));
   }
   temp_byte = malloc(nrows * sizeof(int));

   f_in = fopen(tmp, "r");
   ii = 0;
   while(!feof(f_in))
   {
     fgets(p_string, BUFSIZE, f_in);
     if(!feof(f_in))
     {
       len = strlen(p_string);
       tmp_label(ii);
       pi = e_pos;
       ch = p_string[pi];
       if(ch == ':')
       {
         temp_byte[ii] = -1;
         strcpy(temp_prog[ii], "\n\0");
       }
       else
       {
          tmp_byte(ii);
          tmp_prog(ii);
       }
     }
     ii++;
   }
   fclose(f_in); 
}


tmp_label(ii)
   int ii;
{
   char ch, ln_label[LLEN];
    int pi;

   pi = 0;
   ch = p_string[pi];
   if(isalnum(ch))
   {
     while(isalnum(ch))
     {
        ln_label[pi] = ch;
        pi++;
        ch = p_string[pi];
      }
      ln_label[pi] = '\0';
      strcpy(temp_label[ii], ln_label);
    }
    else
    {
       strcpy(temp_label[ii], " \0");
    }
    e_pos = pi;
}


tmp_byte(ii)
  int ii;
{
   char ch;
    int pi, si, byte;
    int x=ii, ab_code=4;

   pi = e_pos;
   pi = iswhite(pi);
   ch = p_string[pi];
   if(ch == '\'')
   {
     byte = 0;
     strcpy(temp_prog[ii], "\n\0");
   }
   else
   {
     if(isupper(ch))
     {
       e_pos = pi;
       byte = get_byte(ii);
       pi = e_pos;
     }
     else
     {
       si = pi;
       while(isalnum(ch))
       {
         pi++;
         ch = p_string[pi];
       }
       pi = iswhite(pi);
       ch = p_string[pi];
       if(ch == '=')
       {
         byte = 1;
         get_MOD(pi);
         pi = si;
       }
       else if(ch == '$')
       {
         byte = 1;
         get_MOD(pi);
         pi = si;
       }
       else if(ch == '%')
       {
         byte = 1;
         get_MOD(pi);
         pi = si;
       }
       else
       {
         a_bort(ab_code, x);
       }
     }
   }
   temp_byte[ii] = byte;
   e_pos = pi;
}


get_byte(ii)
  int ii;
{
   char ch, keyword[TOKEN_LEN];
    int pi, si = 0, byte;
    int x = ii, ab_code = 4;

   pi = e_pos;
   ch = p_string[pi];
   while(isalnum(ch))
   {
     keyword[si] = ch;
     si++;
     pi++;
     ch = p_string[pi];
   }
   keyword[si] = '\0';

   if(strcmp(keyword, "REM") == 0)         byte = 0;
   else if(strcmp(keyword, "LET") == 0)    byte = 1;
   else if(strcmp(keyword, "CLEAR") == 0)  byte = 2;
   else if(strcmp(keyword, "LOCATE") == 0) byte = 3;
   else if(strcmp(keyword, "PRINT") == 0)  byte = 4;
   else if(strcmp(keyword, "GOTO") == 0)   byte = 5;
   else if(strcmp(keyword, "BEEP") == 0)   byte = 6;
   else if(strcmp(keyword, "CLS") == 0)    byte = 7;
   else if(strcmp(keyword, "END") == 0)    byte = 8;
   else if(strcmp(keyword, "GOSUB") == 0)  byte = 9;
   else if(strcmp(keyword, "RETURN") == 0) byte = 10;
   else if(strcmp(keyword, "FOR") == 0)    byte = 11;
   else if(strcmp(keyword, "NEXT") == 0)   byte = 12;
   else if(strcmp(keyword, "IF") == 0)     byte = 13;
   else if(strcmp(keyword, "ELSEIF") == 0) byte = 14;
   else if(strcmp(keyword, "ELSE") == 0)   byte = 15;
   else if(strcmp(keyword, "ENDIF") == 0)  byte = 16;
   else if(strcmp(keyword, "INPUT") == 0)  byte = 17;
   else if(strcmp(keyword, "OPEN") == 0)   byte = 19;
   else if(strcmp(keyword, "CLOSE") == 0)  byte = 20;
   else if(strcmp(keyword, "WRITE") == 0)  byte = 21;
   else
   {
     pi = iswhite(pi);
     ch = p_string[pi];
     if(ch == '=')
     {
       byte = 1;
       get_MOD(pi);
       pi = e_pos;
     }
     else if(ch == '$')
     {
       byte = 1;
       get_MOD(pi);
       pi = e_pos;
     }
     else if(ch == '%')
     {
       byte = 1;
       get_MOD(pi);
       pi = e_pos;
     }
     else
     {
       a_bort(ab_code, x);
     }
   }
   e_pos = pi;
   return byte;
}


tmp_prog(ii)
  int ii;
{
   char ch, prog[BUFSIZE];
    int pi, si=0, len;

   len = strlen(p_string);
   pi = e_pos;
   pi = iswhite(pi);
   if((pi < len) && (temp_byte[ii] != 0))
   {
     ch = p_string[pi];
     while(ch != '\0')
     {
       prog[si] = ch;
       si++;
       pi++;
       ch = p_string[pi];
     }
     prog[si] = '\0';
   }
   else
   {
     strcpy(prog, "\n\0");
   }
   strcpy(temp_prog[ii], prog);
}



loader_2()
{
   int ndx, ii, line_count = 0, lines = nrows;
   unsigned size;

   for(ndx = 0; ndx < nrows; ndx++)
   {
     if(temp_byte[ndx] != 0)
     {
       line_count++;
     }

     if((temp_byte[ndx] == 13) || (temp_byte[ndx] == 14))
     {
       token_if(ndx);
     }
     else if(temp_byte[ndx] == 1)
     {
       str_functn(ndx);
     }
     else if(temp_byte[ndx] == 4)
     {
       str_fun2(ndx);
     }
   }
   nrows = line_count;

   array1 = malloc(nrows * sizeof(char *));
   label_nam = malloc(nrows * sizeof(char *));
   for(ii = 0; ii < nrows; ii++)
   {
     label_nam[ii] = malloc(LLEN * sizeof(char));
   }
   byte_array = malloc(nrows * sizeof(int));

   ndx = 0;
   for(ii = 0; ii < lines;  ii++)
   {
     if(temp_byte[ii] != 0)
     {
       strcpy(label_nam[ndx], temp_label[ii]);
       byte_array[ndx] = temp_byte[ii];
       size = strlen(temp_prog[ii]);
       size++;
       array1[ndx] = malloc(size * sizeof(char));
       strcpy(array1[ndx], temp_prog[ii]);
       ndx++;
     }
   }
  
   for(ii = 0; ii < lines; ii++)
   {
     free(temp_label[ii]);
     free(temp_prog[ii]);
   }
   free(temp_label);
   free(temp_byte);
   free(temp_prog);
}


get_MOD(pi)
  int pi;
{
   char ch, temp[VAR_NAME];
   int i, si=0, xi, len;

   len = strlen(p_string);
   pi++;
   pi = iswhite(pi);
   ch = p_string[pi];
   while(pi < (len - 2))
   {
      if(ch == 'M')
      {
         si = pi;
         i = 0;
         while(isalnum(ch))
         {
            temp[i] = ch;
            pi++;
            i++;
            ch = p_string[pi];
         }
         temp[i] = '\0';
         if(strcmp(temp, "MOD") == 0)
         {
            p_string[si] = '%';
            si++;
            xi = si;
            while(pi < len)
            {
               p_string[si] = p_string[pi];
               pi++;
               si++;
            }
            p_string[si] = '\0';
            pi = xi;
          }
          pi++;
       }
       else
       {
          pi++;
       }
       ch = p_string[pi];
    }
}


token_if(ndx)
  int ndx;
{
   char temp[TOKEN_LEN];
   int loc;

   strcpy(p_string, temp_prog[ndx]);
   s_pos = 0;
   strcpy(temp, "AND");
   loc = 0;
   while(loc >= 0)
   {
      loc = find_strng(temp);
      loc--;
      if(loc > 0)
      {
         p_string[loc] = '&';
         p_string[loc+1] = ' ';
         p_string[loc+2] = ' ';
      }
   }
   strcpy(temp, "OR");
   loc = 0;
   while(loc >= 0)
   {
      loc = find_strng(temp);
      loc--;
      if(loc > 0)
      {
         p_string[loc] = '|';
         p_string[loc+1] = ' ';
      }
   }
   strcpy(temp, "THEN");
   loc = 0;
   while(loc >= 0)
   {
      loc = find_strng(temp);
      loc--;
      if(loc > 0)
      {
         p_string[loc] = '\n';
         p_string[loc+1] = '\0';
      }
   }
   strcpy(temp_prog[ndx], p_string);
}

/*  old version 
str_functn(ndx)
   int ndx;
{
   char ch, temp[VAR_NAME];
   int pi = 0;
   int type;

   strcpy(p_string, temp_prog[ndx]);
   type = get_vtype(pi);
   if(type != 3)
   {
      return;
   }
   while(IsEqu(pi) == 0)
   {
      pi = e_pos;
      pi++;
   }
   pi = e_pos;
   pi++;
   pi = iswhite(pi);
   ch = p_string[pi];
   if(isalpha(ch) == 0)
   {
      return;
   }
   else if(isupper(ch) == 0)
   {
      return;
   }
   e_pos = pi;
   get_vnam();
   strcpy(temp, vnam);
   e_pos = pi;
   get_strfunc(temp, ndx);
}
*/


str_functn(ndx)
   int ndx;
{
   char ch, temp[VAR_NAME];
   int pi = 0, len;

   strcpy(p_string, temp_prog[ndx]);
   while(IsEqu(pi) == 0)
   {
      pi = e_pos;
      pi++;
   }
   pi = e_pos;
   len = strlen(p_string);
   while(pi < len)
   {
      pi = get_upper(pi, len);
      if(pi < len)
      {
         e_pos = pi;
         get_vnam();
         strcpy(temp, vnam);
         s_pos = e_pos;
         ch = p_string[s_pos];
         if(ch == '$')
         {
            e_pos = pi;
            get_strfunc(temp, ndx);
         }
         else
         {
            e_pos = pi;
            get_mathfunc(temp,ndx);
         }
         pi = e_pos;
         pi++;
      }
   }
}


str_fun2(ndx)
   int ndx;
{
   char ch, temp[VAR_NAME];
   int pi = 0, len;

   strcpy(p_string, temp_prog[ndx]);
   len = strlen(p_string);
   while(pi < len)
   {
      pi = get_upper(pi, len);
      if(pi < len)
      {
         e_pos = pi;
         get_vnam();
         strcpy(temp, vnam);
         s_pos = e_pos;
         ch = p_string[s_pos];
         if(ch == '$')
         {
            e_pos = pi;
            get_strfunc(temp,ndx);
         }
         else
         {
            e_pos = pi;
            get_mathfunc(temp,ndx);
         }
         pi = e_pos;
         pi++;
      }
   }
}




/*
str_fun2(ndx)
   int ndx;
{
   char ch, temp[VAR_NAME];
   int pi = 0, len;

   strcpy(p_string, temp_prog[ndx]);
   len = strlen(p_string);
   while(pi < len)
   {
      pi = get_upper(pi, len);
      if(pi < len)
      {
         e_pos = pi;
         get_vnam();
         strcpy(temp, vnam);
         s_pos = e_pos;
         ch = p_string[s_pos];
         if(ch == '$')
         {
            e_pos = pi;
            get_strfunc(temp,ndx);
         }
         pi = e_pos;
         pi++;
      }
   }
}
*/


get_mathfunc(*name, ndx)
   char *name;
   int ndx;
{
   char varname[VAR_NAME], temp[TOKEN_LEN];

   strcpy(varname, name);
   temp[0] = '\0';

   if(strcmp(varname, "ABS") == 0)
   {
      strcpy(temp, " ?1");
   }
   else if(strcmp(varname, "INT") == 0)
   {
      strcpy(temp, " ?8");
   }
   str_copy(temp,ndx);
}




get_strfunc(*name, ndx)
   char *name;
   int ndx;
{
   char varname[VAR_NAME], temp[TOKEN_LEN];

   strcpy(varname, name);
   temp[0] = '\0';

   if(strcmp(varname, "LEFT") == 0)
   {
      strcpy(temp, "    2");
   }
   else if(strcmp(varname, "RIGHT") == 0)
   {
      strcpy(temp, "     3");
   }
   else if(strcmp(varname, "MID") == 0)
   {               
      strcpy(temp, "   4");
   }
   str_copy(temp,ndx);
}


str_copy(*temp,ndx)
   char *temp;
   int ndx;
{
   char ch, tok[TOKEN_LEN];
   int pi, si=0;

   strcpy(tok, temp);
   pi = e_pos;
   ch = tok[si];
   if(ch != '\0')
   {
      while(ch != '\0')
      {
         p_string[pi] = ch;
         si++;
         pi++;
         ch = tok[si];
      }
      strcpy(temp_prog[ndx], p_string);
      e_pos = pi;
   }
}



IsEqu(pi)
   int pi;
{
   char ch;
   int bool = 0;

   pi = iswhite(pi);
   e_pos = pi;
   ch = p_string[pi];
   if(ch == '=')
   {
      bool = 1;
   }
   return bool;
}





