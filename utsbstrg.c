USERID UTS

/*  utsbasic.c : utsbvar.c */

parse_str(*name)
   char *name;
{
   char ch, varname[VAR_NAME];
   int pi, ndx, indx;
   unsigned size;

   strcpy(varname, name);
   pi = e_pos;
   ch = p_string[pi];
   ndx = get_varndx(varname);
   pi++;
   pi = iswhite(pi);
   e_pos = pi;
   Match('=');
   pi = e_pos;
   ch = p_string[pi];
   if(ch == '\"')
   {
      strng_assgn();
   }
   else if(isdigit(ch))
   {
      asn_function();
   }
   else
   {
      strvar_assgn();
   }
   size = strlen(s_holder);
   size++;
   sv_stack[ndx] = realloc(sv_stack[ndx], size * sizeof(char));
   strcpy(sv_stack[ndx], s_holder);
   str_ndx = ndx;
}


str_express()
{
    char ch;
    char temp[BUFSIZE];
    int pi, len;

    temp[0] = '\0';
    len = strlen(p_string);
    pi = e_pos;
    while(pi < len)
    {   ch = p_string[pi];
        if(ch == '\"')
        {   strng_assgn();		/* quotes string */
        }
        else if(isdigit(ch))
        {   asn_function();		/* string function */
        }
        else
        {   strvar_assgn();		/* copy variable */
        }
        strcat(temp, s_holder);		/* concatenate */
        pi = e_pos;
        pi++;
        pi = iswhite(pi);
        e_pos = pi;
        if(pi < len)
        {   
            Match('+');			/* concatenate symbol */
            pi = e_pos;
        }
    }
    return temp;
}
/*---------- end str_express ----------*/



strvar_assgn()
{  
   int indx;

   indx = get_strndx();
   strcpy(s_holder, sv_stack[indx]);
}
/*---------- end strvar_assgn ----------*/


strng_assgn()
{
   char ch, quote = '\"';
   int pi, stlen, si = 0, ab_code = 6, x = line_ndx;
   unsigned size;
  
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
   s_holder[si] = '\0';

   if(pi == stlen)
   {
     a_bort(ab_code, x);
   }
}


get_strndx()
{
   char varname[VAR_NAME];
   int indx = 0, ab_code = 13, x = line_ndx;

   get_vnam();
   strcpy(varname, vnam);
   while((indx < smax_vars) && (strcmp(sn_stack[indx], varname) != 0))
   {
      indx++;
   }
   if(indx == smax_vars)
   {
      a_bort(ab_code,x);
   }
   return indx;
}


asn_function()
{
   int type;

   type = get_avalue();
   switch(type)
   {
      case 2:
        leftstr();
        break;

      case 3:
        rightstr();
        break;

      case 4:
        midstr();
        break;

      default:
        break;
    }
}


leftstr()
{
   int i, pi, indx, count, len;

   pi = e_pos;
   pi++;
   pi = iswhite(pi);
   e_pos = pi;
   indx = get_strndx();
   pi = e_pos;
   pi += 2;
   pi = iswhite(pi);
   e_pos = pi;
   count = get_avalue();
   if(count < 1)
   {
      count = 0;
   }
   len = strlen(sv_stack[indx]);
   if(count > len)
   {
      count = len;
   }
   for(i=0; i < count; i++)
   {
      s_holder[i] = sv_stack[indx][i];
   }
   s_holder[count] = '\0';
}


rightstr()
{
   int ii, pi, indx, count, len, left;

   pi = e_pos;
   pi++;
   pi = iswhite(pi);
   e_pos = pi;
   indx = get_strndx();
   pi = e_pos;
   pi += 2;
   pi = iswhite(pi);
   e_pos = pi;
   count = get_avalue();
   if(count < 1)
   {
      count = 0;
   }
   len = strlen(sv_stack[indx]);
   if(count > len)
   {
      count = len;
   }
   left = (len - count);
   for(ii=0; ii < count; ii++, left++)
   {
      s_holder[ii] = sv_stack[indx][left];
   }
   s_holder[count] = '\0';
}


midstr()
{
   char ch;
   int ii, pi, indx, count, len, left;

   pi = e_pos;
   pi++;
   pi = iswhite(pi);
   e_pos = pi;
   indx = get_strndx();
   pi = e_pos;
   pi += 2;
   pi = iswhite(pi);
   e_pos = pi;
   left = get_avalue();
   pi = e_pos;
   pi = iswhite(pi);
   ch = p_string[pi];
   e_pos = pi;
   if(ch == ')')
   {
      count = 255;
   }
   else
   {
      pi++;
      pi = iswhite(pi);
      e_pos = pi;
      count = get_avalue();
   }
   if(count < 1)
   {
      count = 0;
   }
   len = strlen(sv_stack[indx]);
   left--;
   if((left + count) > len)
   {
      count = (len - left);
   }
   for(ii=0; ii < count; ii++, left++)
   {
      s_holder[ii]  = sv_stack[indx][left];
   }
   s_holder[count] = '\0';
}


    

