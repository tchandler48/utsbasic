USERID UTS


/* utsbasic : utsbif.c :                     */
/* Copyright:(c) sarbayo, 2001-2011          */
/* Modified T. Chandler utsbasic - utsbif.c  */


do_if()
{
   int bool, els_ndx, end_ndx;

   bool = boolexpress();

   if(bool == 1)
   {
      els_ndx = find_else(line_ndx);
      end_ndx = find_endif(line_ndx);

      line_ndx++;
      while(line_ndx < els_ndx)
      {
         s_pos = 0;
         e_pos = 0;
         get_token();
         if(token == 5)
         {
            break;
         }
         parser();
         line_ndx++;
      }
      if(token == 5)
      {
         line_ndx--;
         return;
      }
      line_ndx = end_ndx;
    }
    else
    {
       els_ndx = find_else(line_ndx);
       els_ndx--;
       line_ndx = els_ndx;
    }
}


find_else(ndx)
  int ndx;
{
   int tok=0;

   while((tok != 14) && (tok != 15) && (tok != 16))
   {
      ndx++;
      tok = byte_array[ndx];
      if(tok == 13)
      {
         ndx = find_endif(ndx);
      }
    }
    return ndx;
}


find_endif(ndx)
  int ndx;
{
   int tok=0;
   while(tok != 16)
   {
      ndx++;
      tok = byte_array[ndx];
      if(tok == 13)
      {
         ndx = find_endif(ndx);
      }
   }
   return ndx;
}


boolexpress()
{
   int bool, type, a_bool, or_bool, op;
   int ab_code=17, x=line_ndx;
 
   type = get_type();

   if((type == 1) || (type == 2))
   {
      bool = Nboolterm(type);
   }
   else if((type == 3) || (type == 4))
   {
      bool = Sboolterm(type);
   }
   else if(type == 5)
   {
      bool = is_eof();
      if(bool != 0)
      {
         bool = 1;
      }
   }  
   else
   {
      a_bort(ab_code, x);
   }

/* ---- process AND / OR --- */
   op = IsAndOrOp();
   while(op != 0)
   {
      if(op == 1)
      {
         a_bool = AndOrBoolExp();
         if((bool == 1) && (a_bool == 1))
         {
            bool = 1;
         }
         else
         {
            bool = 0;
         }
       }
       else if(op == 2)
       {
          or_bool = AndOrBoolExp();
          if((bool == 1) || (or_bool == 1))
          {
             bool = 1;
          }
       }
       op = IsAndOrOp();
    }
    return bool;
}


AndOrBoolExp()
{
   int bool, type;
   int ab_code=17, x=line_ndx;

   type = get_type();
   if((type == 1) || (type == 2))
   {
      bool = Nboolterm(type);
   }
   else if((type == 3) || (type == 4))
   {
      bool = Sboolterm(type);
   }
   else
   {
      a_bort(ab_code, x);
   }
   return bool;
}


Nboolterm(type)
  int type;
{
   char ch;
   int pi, bool, a_bool=0;
   int lvalue;

   if(type == 1)
   {
      lvalue = get_avalue();
   }
   else
   {
      lvalue = rdp_main();
   }
   bool = Nrelation(lvalue);
   return bool;
}


Nrelation(lvalue)
  int lvalue;
{
   int bool, op, type;
   int ab_code=17, x=line_ndx;
   int rvalue;

   op = get_op();
   type = get_type();
   if(type == 1)
   {
      rvalue = get_avalue();
   }
   else if(type == 2)
   {
      rvalue = rdp_main();
   }
   else
   {
      a_bort(ab_code,x);
   }
   bool = eval_value(lvalue, rvalue, op);
   return bool;
}


eval_value(lval, rval, op)
  int lval;
  int rval;
  int op;
{
   int bool=0;

   if(op == 1)
   {
      if(lval == rval)   
      {
         bool = 1;
      }
    }
    else if(op == 2)
    {
      if(lval < rval)
      {
         bool = 1;
      }
    }
    else if(op == 3)
    {
      if(lval > rval)
      {
         bool = 1;
      }
    }
    else if(op == 4)
    {
      if(lval <= rval)
      {
         bool = 1;
      }
    }
    else if(op == 5)
    {
      if(lval >= rval)
      {
         bool = 1;
      }
    }
    else if(op == 6)
    {
      if(lval != rval)
      {
         bool = 1;
      }
    }
    return bool;
}


Sboolterm(type)
   int type;
{
   char lstring[BUFSIZE];
   int bool, ndx;

   if(type == 3)
   {
      ndx = get_string();
      strcpy(lstring, sv_stack[ndx]);
   }
   else
   {
      get_qstring();
      strcpy(lstring, s_holder);
   }
   bool = Srelation(lstring);
   return bool;
}



Srelation(lstr)
   char *lstr;
{
   char lstring[BUFSIZE], rstring[BUFSIZE];
   int bool, ndx, op, type;
   int ab_code=17, x=line_ndx;

   strcpy(lstring, lstr);
   op = get_op();
   type = get_type();
   if(type == 3)
   {
      ndx = get_string();
      strcpy(rstring, sv_stack[ndx]);
   }
   else  if(type == 4)
   {
      get_qstring();
      strcpy(rstring, s_holder);
   }
   else
   {
      a_bort(ab_code,x);
   }
   bool = eval_string(lstring, rstring, op);
   return bool;
}


eval_string(lstr, rstr, op)
   char *lstr;
   char *rstr;
   int op;
{
   char lstring[BUFSIZE], rstring[BUFSIZE];
   int bool=0, comp;

   strcpy(lstring, lstr);
   strcpy(rstring, rstr);
   comp = strcmp(lstring, rstring);

   if(op == 1)
   {
      if(comp == 0)
      {
         bool = 1;
      }
   }
   else if(op == 2)
   {
      if(comp < 0)
      {
         bool = 1;
      }
   }
   else if(op == 3)
   {
      if(comp > 0)
      {
         bool = 1;
      }
   }
   else if(op == 4)
   {
      if(comp <= 0)
      {
         bool = 1;
      }
   }
   else if(op == 5)
   {
      if(comp >= 0)
      {
         bool = 1;
      }
   }
   else if(op == 6)
   {
      if(comp != 0)
      {
         bool = 1;
      }
   }
   return bool;
}


IsAndOrOp()
{
   char ch;
   int pi, op=0;

   pi = e_pos;
   pi = iswhiter(pi);
   ch = p_string[pi];
   if(ch == '&')
   {
      op = 1;
      pi++;
      pi = iswhiter(pi);
   }
   else if(ch == '|')
   {
      op = 2;
      pi++;
      pi = iswhiter(pi);
   }
   e_pos = pi;
   return op;
}


get_type()
{
    char ch;
    int pi, type=0;

    pi = e_pos;
    pi = iswhiter(pi);
    ch = p_string[pi];

    if(isalpha(ch))
    {   
       type = get_vtype(pi);          /* variable name */
    }
    else if(isdigit(ch))
    {   
       type = 1;                      /* number value */
    }
    else if(ch == '(')
    {   
       type = 2;                      /* expression in parens */
    }
    else if(ch == '\"')
    {   
       type = 4;                      /* quoted string */
    }
    e_pos = pi;
    return type;
}



get_vtype(pi)
   int pi;
{
   char ch;
   int type=0, f_flag = 0;

   ch = p_string[pi];

   while(isalnum(ch))
   {
      pi++;
      ch = p_string[pi];
   }
   if(ch == '$')
   {
      type = 3;
   }
   else if(ch == '=')
   {
      type = 1;
   }
   else if(ch == '<')
   {
      type = 1;
   }
   else if(ch == '>')
   {
      type = 1;
   }
   else if(ch == '(')
   {
      f_flag = if_eof();
      f_flag--;
      if(f_flag == s_pos)
      {
         type = 5;
         e_pos = pi;
      }
   }
   return type;
}


get_string()
{
   char ch, varname[VAR_NAME];
   int pi, ndx=0, ab_code=13, x=line_ndx;

   get_vnam();
   strcpy(varname, vnam);
   while((ndx < smax_vars) && (strcmp(sn_stack[ndx], varname) != 0))
   {
      ndx++;
   }
   if(ndx == smax_vars)
   {
      a_bort(ab_code,x);
   }
   pi = e_pos;
   pi++;
   pi = iswhiter(pi);
   ch = p_string[pi];
   e_pos = pi;
   return ndx;
}


get_qstring()
{
   char ch, quote='\"';
   int pi, si=0, stlen, ab_code=6, x=line_ndx;

   stlen = strlen(p_string);
   pi = e_pos;
   pi++;
   ch = p_string[pi];

   si = 0;
   while((ch != quote) && (pi < stlen))
   {
      s_holder[si] = ch;
      si++;
      pi++;
      ch = p_string[pi];
   }
   s_holder[pi] = '\0';
   if(pi == stlen)
   {
      a_bort(ab_code,x);
   }
   pi++;
   e_pos = pi;
}


get_op()
{
   char ch;
   int pi, op, ab_code=18, x=line_ndx;

   pi = e_pos;
   ch = p_string[pi];
   if(ch == '$')
   {
      pi++;
   }
   if(ch == '\"')
   {
      pi++;
   }
   pi = iswhite(pi);
   ch = p_string[pi];
   if(ch == '=')
   {
      op = 1;
   }
   else if(ch == '<')
   {
      pi++;
      ch = p_string[pi];
      if(ch == '>')
      {
         op = 6;
      }
      else if(ch == '=')
      {
         op = 4;
      }
      else
      {
         op = 2;
      }
   }
   else if(ch == '>')
   {
      pi++;
      ch = p_string[pi];
      if(ch == '=')
      {
         op = 5;
      }
      else
      {
         op = 3;
      }
   } 
   else
   {
      a_bort(ab_code, x);
   }
   if(ch == '=>')
   {
      pi++;
   }
   pi++;
   e_pos = pi;
   return op;
}

if_eof()
{
   char tmp[4];
   int flag = 0;

   strcpy(tmp, "EOF");
   flag = find_strng(tmp);
   return flag;
}


is_eof()
{
   char ch;
   int pi, len, bool, port;
   int maxfiles=IOARRAY, x = line_ndx, ab_code = 23;
   int fnum;

   len = strlen(p_string);
   pi = e_pos;
   e_pos = get_digit(pi, len);
   fnum = get_avalue();
   port = fnum;
   port--;

   if((port < 0) || (port > maxfiles))
   {
      strcpy(xstring, "Invalid File Number\n");
      a_bort(ab_code, x);
   }
   else if(fp[port].path[0] == '\0')
   {
      strcpy(xstring, "File Handle is Closed\n");
      a_bort(ab_code, x);
   }
   f_hdl = fp[port].fptr;
   bool = feof(f_hdl);
   return bool;
}


