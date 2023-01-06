USERID UTS

/* utsbasic : utsbginp.c                       */
/* Copyright:(c) sarbayo, 2001-2011            */
/* Modified T. Chandler utsbasic utsbginp.c    */


get_lninput()
{
    char ch, varname[VAR_NAME];
    int pi, loc=0;

    pi = e_pos;
    ch = p_string[pi];
    if(ch == '#')
    {
printf("get_lninput Startin\n");
        p_string[pi] = '@';
        input_io();
        return;
    }
    else if(ch == ';')		/* do not echo newline */
    {   loc = 1;
        pi++;
        pi = iswhite(pi);
        ch = p_string[pi];
        e_pos = pi;
    }
    if(ch == '\"')          	/* Prompt: "enter string"; */
    {   get_prnstring();
        pi = e_pos;
        pi++;
        pi = iswhite(pi);
        ch = p_string[pi];
        e_pos = pi;
    }
/* --- input string --- */
    get_vnam();
    strcpy(varname, vnam);
    input_str(varname,loc);
}



get_input()
{
   char ch, varname[VAR_NAME];
   int pi, len, type, loc = 0;
   int ab_code = 19, x = line_ndx;

   pi = e_pos;
   ch = p_string[pi];

   if(ch == '#')
   {
      input_io();
      return;
   }
   else if(ch ==';')
   {
      loc = 1;
      pi++;
      pi = iswhite(pi);
      ch = p_string[pi];
      e_pos = pi;
   }
   len = strlen(p_string);
   while(pi < len)
   {
      if(ch == '\"')
      {
         /* get_prnstring(); */
         parse_print();
         pi = e_pos;
         pi++;
         pi = iswhite(pi);
         ch = p_string[pi];
         e_pos = pi;
      }
      else if(isalpha(ch))
      {
         type = get_vtype(pi);
         get_vnam();
         strcpy(varname, vnam);
         if(type == 3)
         {
            input_str(varname, loc);
            pi = e_pos;
            ch = p_string[pi];
         }
         else
         {
             input_val(varname, loc);
             pi = e_pos;
             ch = p_string[pi];
         }
      }
      else
      {
         a_bort(ab_code,x);
      }
   }
}



input_str(name,loc)
  char *name;
  int loc;
{
   char ch, varname[VAR_NAME], string[BUFSIZE];
   int pi, ndx, len, row, col;
   unsigned xsize;

   strcpy(varname, name);
   ndx = get_varndx(varname);
   if(loc == 1)
   {
      gets(string);
      len = strlen(string);
   }
   else
   {
      gets(string);
   }

   xsize = strlen(string);
   xsize++;
   sv_stack[ndx] = realloc(sv_stack[ndx], xsize * sizeof(char));
   strcpy(sv_stack[ndx], string);

   pi = e_pos;
   pi++;
   ch = p_string[pi];
   if(ch == ':')
   {
      pi++;
      set_TabN1(ch);
   }
   else if(ch == ';')
   {
      pi++;
      set_TabN1(ch);
   }
   else if(ch == ',')
   {
      pi++;
      set_TabN1(ch);
   }
   pi = iswhite(pi);
   e_pos = pi;
}



input_val(name, loc)
   char *name;
   int loc;
{
   char ch, cx, varname[VAR_NAME], string[VAR_NAME];
   int pi, ndx, len, row, col;

   strcpy(varname, name);
   pi = e_pos;
   ch = p_string[pi];

   if(loc == 1)
   {
      gets(string);
      len = strlen(string);
   }
   else
   {
      gets(string);
   }

   if(ch == '#')
   {

   }
   else if(ch == '!')
   {
  
   }
   else if(ch == '%')
   {
  
   }
   else
   {
      ndx = get_intndx(varname);
      iv_stack[ndx] = atoi(string);
   }
   pi = iswhite(pi);
   ch = p_string[pi];
   if(ch == ':')
   {
      pi++;
      set_TabN1(ch);
   }
   else if(ch == ';')
   {
      pi++;
      set_TabN1(ch);
   }
   else if(ch == ',')
   {
      pi++;
      set_TabN1(ch);
   }
   pi = iswhite(pi);
   e_pos = pi;
}



