// string length
// not finalized.

//#pragma JessieIntegerModel(modulo) //temp

/*@
requires \valid_string(s);
requires \exists int k; 0<=k<=INT_MAX && \valid_range(s, 0, k) && s[k] == '\0';
terminates \exists int k; 0<=k<=INT_MAX && \valid_range(s, 0, k) && s[k] == '\0';
assigns \nothing;
ensures \result >= 0;
ensures s[\result] == '\0' && \forall int k; 0 <= k < \result && s[k] != '\0';
*/
 unsigned int strlen (const char *s)
 {
     unsigned int n = 0;
     char *p = s;
     /*@ loop invariant p >= s && n == (p-s);
         loop invariant \forall unsigned int k; 0 < k < n && s[k] != '\0';
         loop invariant \forall unsigned int k; 0 <= k < n && s[n] == '\0' ==> s[k] != '\0';
       */
     while ( *p != '\0')
     {
    	 n++;
         p++;
     }
     //@ assert *p == '\0';
     return n;
 }



