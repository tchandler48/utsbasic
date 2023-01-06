USERID UTS

/* utsbasic : utsbutl.c                        */
/* Copyright:(c) sarbayo, 2001-2011            */
/* Modified T. Chandler utsbasic utsbutl.c     */


get_alpha(pi, stlen)
  int pi;
  int stlen;
{
  char ch;
  ch = p_string[pi];
  while((isalpha(ch) == 0) && (pi < stlen))
  {
    pi++;
    ch = p_string[pi];
  }
  return pi;
}


get_digit(pi, stlen)
  int pi;
  int stlen;
{
   char ch;
   ch = p_string[pi];
   while((isdigit(ch) == 0) && (pi < stlen))
   {
     pi++;
     ch = p_string[pi];
   }
   return pi;
}


iswhite(pi)
  int pi;
{
   char ch;
   ch = p_string[pi];
   while(isspace(ch) != 0)
   {
     pi++;
     ch = p_string[pi];
   }
   return pi;
}


get_upper(pi, stlen)
   int pi;
   int stlen;
{
   char ch;

   ch = p_string[pi];
   while((isupper(ch) == 0) && (pi < stlen))
   {
     pi++;
     ch = p_string[pi];
   }
   return pi;
}




find_strng(tmp)
   char *tmp;
{
   char ch, cx, quote='\"';
   char temp[TOKEN_LEN], xxstring[TOKEN_LEN];
   int pi, i, mark, len, len2;

   strcpy(xxstring, tmp);
   len = strlen(p_string);
   len2 = strlen(xxstring);
   pi = s_pos;
   ch = p_string[pi];
   cx = xxstring[0];
   while(pi < len)
   {
      while((ch != cx) && (pi < len))
      {
         if(ch == quote)
         {
            pi++;
            ch = p_string[pi];
            while(ch != quote)
            {
               pi++;
               ch = p_string[pi];
            }
          }
          pi++;
          ch = p_string[pi];
       }
       if((pi == len) || (pi > len))
       {
          mark = 0;
          return mark;
       }
       mark = pi;
       for(i=0; i < len2; i++)
       {
          temp[i] = ch;
          pi++;
          ch = p_string[pi];
       }
       temp[i] = '\0';
       if(strcmp(temp, xxstring) != 0)
       {
          pi = (mark+1);
          ch = p_string[pi];
       }
       else
       {
          mark++;
          pi = len;
       }
    }
    return mark;
}


iswhiter(pi)
   int pi;
{
   char ch;

    ch = p_string[pi];                   
    while(ch == ' ')                             
    {   
        pi++;
        ch = p_string[pi];
    }
    return pi;
}
/*-------- end iswhiter ---------*/

