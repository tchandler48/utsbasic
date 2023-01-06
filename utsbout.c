USERID UTS

/* utsbasic : utsbout.c :                    */
/* Copyright:(c) sarbayo, 2001-2011          */
/* Modified T. Chandler utsbasic - utsbout.c */


get_prnstring()
{   char ch, quote='\"';
    int pi, si=0, stlen;
    int ab_code=6, x=line_ndx;

    stlen = strlen(p_string);
    pi = e_pos;
    pi++;
    ch = p_string[pi];
    while((ch != quote) && (pi < stlen))
    {   xstring[si] = ch;
        pi++;
        si++;
        ch = p_string[pi];
    }
    xstring[si]='\0';

/* --- error: no closing quote --- */
    if(pi >= stlen)
    {   a_bort(ab_code, x);
    }

/* --- advance to next character --- */
    pi++;
    pi = iswhiter(pi);
    ch = p_string[pi];
    e_pos = pi;

/* --- print quoted string --- */
    if(ch == ',')      printf("%s\t", xstring);
    else if(ch == ';') printf("%s", xstring);
    else               printf("%s\n", xstring);
}
/*-------- end get_prnstring --------*/



get_vartype()
{
   char ch;
   int pi;

   pi = e_pos;
   ch = p_string[pi];
   while(isalnum(ch))
   {
     pi++;
     ch = p_string[pi];
   }
   return ch;
}


get_strvar()
{
   char ch, varname[VAR_NAME];
   int pi, ndx=0, ab_code=13, x=line_ndx;
   int stlen, si=0;

   stlen = strlen(p_string);
   ch = p_string[pi];

   while((isalnum(ch) != 0))
   {
     varname[si] = ch;
     si++;
     pi++;
     ch = p_string[pi];
   }
   varname[si] = '\0';

   while((ndx < smax_vars) && (strcmp(sn_stack[ndx], varname) != 0))
   {
     ndx++;
   }

   if(ndx == smax_vars)
   {
     a_bort(ab_code, x);
   }

   pi = e_pos;
   pi++;
   pi = iswhite(pi);
   ch = p_string[pi];
   
   printf("%s\n", sv_stack[ndx]);
}



get_prnvar()
{
   char ch;
   int pi, ivalue;

   pi = e_pos;
   pi = iswhite(pi);
   e_pos = pi;

   ivalue = get_varvalue();
   pi = e_pos;
   pi = iswhite(pi);
   ch = p_string[pi];
   if(ch == ',')
   {
      printf("%d", ivalue);
   }
   else if(ch == ';')
   {
      printf("%d", ivalue);
   }
   else
   {
      printf("%d\n", ivalue);
   }
}


set_TabNl(ch)
   int ch;
{
   if(ch == ',')
   {
       printf("\t");
   }
   else if(ch == ':')
   {
       printf("\n");
   }
}



parse_print()
{
   char ch, quote='\"';
   int pi, ab_code = 9, x = line_ndx;
   int ndx = 0;

   pi = e_pos;
   pi = iswhite(pi);
   ch = p_string[pi];
   e_pos = pi;

   if(ch == ':')
   {
      printf("\n");
      return;
   }

   while(ch != '\n')
   {
      if(isalpha(ch))
      {
         get_vnam();
         strcpy(s_holder, vnam);
      /*   strcpy(s_holder, get_varname()); */
         pi = e_pos;
         ch = p_string[pi];

         if(ch == '$')
         {
            get_strvar();  
         }
         else
         {
            get_prnvar();
         }
      }
      else if(isdigit(ch))
      {
         prn_strfunc();
      }
      else if(ch == quote)
      {
         get_prnstring();
      }
      else
      {
         a_bort(ab_code, x);
      }
   
      pi = e_pos;
      ch = p_string[pi];

      if(ch != '\n')
      {
         pi++;
         pi = iswhiter(pi);
         ch = p_string[pi];
         e_pos = pi;
       }
   }
}


prn_strfunc()
{
   char ch;
   int pi;

   asn_function();
   pi = e_pos;
   pi++;
   pi = iswhiter(pi);
   ch = p_string[pi];
   e_pos = pi;

   printf("%s\n", s_holder);
}

