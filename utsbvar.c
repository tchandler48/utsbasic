USERID UTS

/*  utsbasic.c : utsbvar.c */


parse_let()
{
  char ch, varname[VAR_NAME];
  int pi, si = 0, stlen, ndx = 0, x=line_ndx;
  int ab_code;

  stlen = strlen(p_string);
  pi = e_pos; 
/* retrieve variable name from statement */

  pi = get_alpha(pi, stlen);
  if(pi == stlen)
  {
    ab_code = 11;
    a_bort(ab_code,x);
  }
  e_pos = pi;
  get_vnam();
  strcpy(varname, vnam);
  pi = e_pos;
  ch = p_string[pi];
/* now compare name to array for existing variables */
  if(ch == '$')
  {
    e_pos = pi;
    parse_str(varname);
  }
  else
  {
    ndx = get_intndx(varname);
    pi = iswhite(pi);
    e_pos = pi;
    Match('=');
    iv_stack[ndx] = rdp_main();
  }
}


get_varndx(name)
  char *name;
{   
   char varname[VAR_NAME];
   int ndx = 0, vflag = 0, vi_pos = 0;

   strcpy(varname, name);
   while((ndx < smax_vars) && (strcmp(sn_stack[ndx], varname) != 0))
   {
     if(vflag == 0)
     {
       if(sn_stack[ndx][0] == '\0')
       {
         vi_pos = ndx;
         vflag = 1;
       }
     }
     ndx++;
   }

   if(ndx == smax_vars)
   {
     ndx = vi_pos;
     if(vflag == 0)
     {
       init_str();
       ndx = smax_vars;
       ndx--;
       strcpy(sn_stack[ndx], varname);
     }
     else
     {
       strcpy(sn_stack[ndx], varname);
     }
   }
   return ndx;
}
/*--------- end get_varndx ----------*/


get_intndx(name)
   char *name;
{
   char varname[VAR_NAME];
   int ndx = 0, vflag = 0, vi_pos = 0;

   strcpy(varname, name);

   while((ndx < imax_vars) && (strcmp(in_stack[ndx], varname) != 0))
   {
     if(vflag == 0)
     {
       if(in_stack[ndx][0] == '\0')
       {
         vi_pos = ndx;
         vflag = 1;
       }
     }
     ndx++;
   }

   if(ndx == imax_vars)
   {
     ndx = vi_pos;
     if(vflag == 0)
     {
       init_int();
       ndx = imax_vars;
       ndx--;
       strcpy(in_stack[ndx], varname);
     }
     else
     {
       strcpy(in_stack[ndx], varname);
     }
   }
   return ndx;
}



get_varvalue()
{
   char ch, varname[VAR_NAME];
    int pi, si=0, ndx=0, ivalue;
    int ab_code=13, x=line_ndx;

   e_pos = 0;   /* add tec */
   pi = e_pos;
   ch = p_string[pi];
   while((isalnum(ch) != 0))
   {
      varname[si] = ch;
      si++;
      pi++;
      ch = p_string[pi];
   }
   varname[si] = '\0';

   while((ndx < imax_vars) && (strcmp(in_stack[ndx], varname) != 0))
   {
     ndx++;
   }
   if(ndx == imax_vars)
   {
     a_bort(ab_code, x);
   }
   ivalue = iv_stack[ndx];
   e_pos = pi;
   return ivalue;
}


init_int()
{
   int ndx;
   unsigned size;

   if(imax_vars == 0)
   {
     ndx = imax_vars;
     imax_vars++;
     size = imax_vars;
     iv_stack = malloc(size * sizeof(long));
     in_stack = malloc(size * sizeof(char *));
     size = VAR_NAME;
     in_stack[ndx] = malloc(size * sizeof(char));
   }
   else
   {
     ndx = imax_vars;
     imax_vars++;
     size = imax_vars;
     iv_stack = realloc(iv_stack, size * sizeof(long));
     in_stack = realloc(in_stack, size * sizeof(char *));
     size = VAR_NAME;
     in_stack[ndx] = malloc(size * sizeof(char));
   }
}


init_str()
{
   int ndx;
   unsigned size;

   if(smax_vars == 0)
   {
     ndx = smax_vars;
     smax_vars++;
     size = smax_vars;
     sv_stack = malloc(size * sizeof(char *));
     sv_stack[ndx] = malloc(1 * sizeof(char));
     sn_stack = malloc(size * sizeof(char *));
     size = VAR_NAME;
     sn_stack[ndx] = malloc(size * sizeof(char));
   }
   else
   {
     ndx = smax_vars;
     smax_vars++;
     size = smax_vars;
     sv_stack = realloc(sv_stack, size * sizeof(char *));
     sv_stack[ndx] = malloc(1 * sizeof(char));
     sn_stack = realloc(sn_stack, size * sizeof(char *));
     size = VAR_NAME;
     sn_stack[ndx] = malloc(size * sizeof(char));
   }
}


/*
clr_str()
{
   int ndx;

   if(smax_vars > 0)
   {
     for(ndx = 0; ndx < smax_vars; ndx++)
     {
       free(sv_stack[ndx]);
       free(sn_stack[ndx]);
     }
     free(sv_stack);
     free(sn_stack);
     smax_vars = 0;
}
*/




get_vnam()
{
   char ch;
   int pi, si=0;

   pi = e_pos;
   ch = p_string[pi];
   while((isalnum(ch) != 0))
   {
     vnam[si] = ch;
     si++;
     pi++;
     ch = p_string[pi];
   }
   vnam[si] = '\0';
   e_pos = pi;
   return vnam;
}

 
