USERID UTS

/* utsbasic.c : utsbrdp.c */


rdp_main()
{
   double value;
   value = Expression();
   return value;
}


Expression()
{
   char ch;
   int pi;
   double Value;

   pi = e_pos;
   ch = p_string[pi];
   if(IsAddop(ch))
   {
     Value = 0;
   }
   else
   {
     Value = Term();
     pi = e_pos;
     ch = p_string[pi];
   }
   while(IsAddop(ch))
   {
     switch(ch)
     {
       case '+':
          Match('+');
          Value = Value + Term();
          break;

       case '-':
          Match('-');
          Value = Value - Term();
          break;
   
       default:
          break;
     }
     pi = e_pos;
     ch = p_string[pi];
   }
   return Value;
}


Term()
{
  char ch;
   int pi;
  double Value;

  Value = Factor();
  pi = e_pos;
  ch = p_string[pi];

  while(IsMultop(ch))
   {
     switch(ch)
     {
       case '*':
          Match('*');
          Value = Value * Factor();
          break;

       case '/':
          Match('/');
          Value = Value / Factor();
          break;

       case '^':
          Match('^');
          Value = pow(Value, Factor());
          break;

/*
       case '%':
          Match('%');
          Value = Value % Factor();
          break;
*/
   
       default:
          break;
     }
     pi = e_pos;
     ch = p_string[pi];
   }
   return Value;
}


Factor()
{
  char ch;
  int pi;
  double value;

  pi = e_pos;
  ch = p_string[pi];
  if(ch == '(')
  {
    Match('(');
    value = Expression();
    Match(')');
  }
  else
  {
    if(isalpha(ch))
    {
      get_vnam();
      strcpy(s_holder, vnam);
      value = get_varvalue();
      SkipWhite();
    }
    else if(ch == '?')
    {
       value = math_functn();
       SkipWhite();
    }
    else
    {
      value = GetNum();
    }
  }
  return value;
}


Match(x)
  char x;
{
  char ch, string[6];
  int pi, ab_code=12, ln=line_ndx;

  pi = e_pos;
  ch = p_string[pi];
  if(ch != x)
  {
    strcpy(string, "\" \"");
    string[1] = x;
    strcpy(t_holder, string);
    a_bort(ab_code, ln);
  }
  else
  {
    _GetChar();
    SkipWhite();
  }
}


_GetChar()
{
   e_pos++;
}


Is_White(ch)
  char ch;
{
  int test = 0;

  if((ch == ' ') || (ch == '\t'))
  {
    test = -1;
  }
  return test;
}


SkipWhite()
{
   char ch;
   int pi;

   pi = e_pos;
   ch = p_string[pi];
   while(Is_White(ch))
   {
     _GetChar();
     pi = e_pos;
     ch = p_string[pi];
   }
}


IsAddop(ch)
  char ch;
{
  int rval = 0;

  if((ch == '+') || (ch == '-'))
  {
    rval = 1;
  }
  return rval;
}


IsMultop(ch)
  char ch;
{
  int rval = 0;

  if((ch == '*') || (ch == '/'))
  {
    rval = 1;
  }
  return rval;
}


GetNum()
{
  char ch;
  int pi, ab_code=12, ln=line_ndx;
  double value = 0;

  pi = e_pos;
  ch = p_string[pi];
  if(!isdigit(ch))
  {
    strcpy(t_holder, "Integer");
    a_bort(ab_code, ln);
  }
  while(isdigit(ch))
  {
    value = 10 * value + ch - '0';
    _GetChar();
    pi = e_pos;
    ch = p_string[pi];
  }
  SkipWhite();
  return value;
}



math_functn()
{
   int pi, type;
   int value = 0;

   pi = e_pos;
   pi++;
   e_pos = pi;
   type = get_avalue();

   switch(type)
   {
      case 1:		/* ABS */
        value = get_ABS();
        break;
      case 8:		/* INT */
        value = get_INT();
        break;
      default:
	break;
   }
   return value;
}



get_ABS()
{
   int ivalue;
   int value;

   ivalue = Factor();
   value = abs(ivalue);
   return value;
}

get_INT()
{
   int ivalue;
   int value;

   ivalue = Factor();
   value = ivalue;
   return value;
}


