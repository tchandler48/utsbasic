USERID UTS
/* utsbasic : utsbloop.c :                    */
/* Copyright:(c) sarbayo, 2001-2011           */
/* Modified T. Chandler utsbasic - utsbloop.c */


do_for()
{
   char ch, varname[VAR_NAME];
   int pi, f_ndx, Inc=1, ab_code;
   int start, next_tru, x=line_ndx;
   int From, Final;

   f_ndx = get_From();

   Final = get_To();

   pi = e_pos;
   ch = p_string[pi];
   if(ch == 'S')
   {
     Inc = get_Step();
   }

   From = iv_stack[f_ndx];
   start = line_ndx;
   fornxt_flg++;

/*  increment loop */
   if(From < Final)
   {
     for(; From <= Final; From += Inc)
     {
        next_tru = 1;
        line_ndx = start + 1;
        while(next_tru == 1)
        {
          get_token();
          s_pos = 0;
          e_pos = 0;
          parser();
          if(token == 12)
          {
            next_tru = 0;
            token = 0;
          }
          else
          {
            line_ndx++;
          }
        }
      }
    }
    else
    {
      for(; From >= Final; From += Inc)
      {
        next_tru = 1;
        line_ndx = start + 1;
        while(next_tru == 1)
        {
          get_token();
          e_pos = 0;
          s_pos = 0;
          parser();
          if(token == 12)
          {
            next_tru = 0;
            token = 0;
          }
          else
          {
            line_ndx++;
          }
        }
      }
    }
    fornxt_flg--;
}


get_From()
{
  char ch, varname[VAR_NAME];
  int pi, f_ndx, sav_pi, ab_code, x=line_ndx;
  int si = 0;

  pi = e_pos;
  sav_pi = pi;

  ch = p_string[pi];
  get_vnam();
  pi = e_pos;
  strcpy(varname, vnam);

  ch = p_string[pi];
   
  e_pos = sav_pi;
  parse_let();
  pi = e_pos;
  ch = p_string[pi];

  f_ndx = get_intndx(varname);

  return f_ndx;
}


get_To()
{
   char ch, varname[VAR_NAME];
   int pi, ab_code, x=line_ndx;
   int Final, si=0;

   pi = e_pos;
   ch = p_string[pi];

   if(ch != 'T')
   {
     strcpy(t_holder, "TO");
     ab_code = 7;
     a_bort(ab_code,x);
   }
   else
   {
     while((isalnum(ch) != 0))
     {
       varname[si] = ch;
       si++;
       pi++;
       ch = p_string[pi];
     }
     varname[si] = '\0';

     ch = p_string[pi];
     if(strcmp(varname, "TO") != 0)
     {
       strcpy(t_holder, "TO");
       ab_code = 7;
       a_bort(ab_code,x);
     }
   }
   pi = iswhite(pi);
   ch = p_string[pi];
   e_pos = pi;

   if(isalnum(ch))
   {
     Final = get_avalue();
   }
   else
   {
     strcpy(t_holder, "TO");
     ab_code = 15;
     a_bort(ab_code,x);
   }
   return Final;
}


get_Step()
{
   char ch, varname[VAR_NAME];
   int pi, Inc;
   int ab_code, x=line_ndx;
   char sav_ch = ' ';
}


do_next()
{
   int ab_code = 16, x=line_ndx;

   if(fornxt_flg == 0)
   {
     a_bort(ab_code, x);
   }
}


get_avalue()
{
  char ch, varname[VAR_NAME];
  int pi, si=0;
  int value = 0;

  pi = e_pos;
  ch = p_string[pi];
  if(isalpha(ch))
  {
    e_pos = pi;
    strcpy(s_holder, get_varname());
    value = get_varvalue();
    pi = e_pos;
  }                  
  else if((isdigit(ch)) || (IsAddop(ch)))
  {
    if(IsAddop(ch))
    {
      varname[si] = ch;
      si++;
      pi++;
      ch = p_string[pi];
    }
    while(isdigit(ch) != 0)
    {
      varname[si] = ch;
      pi++;
      si++;
      ch = p_string[pi];
    }
    varname[si] = '\0';
    value = atoi(varname);
  }
  pi = iswhite(pi);
  e_pos = pi;
  return value;
}



