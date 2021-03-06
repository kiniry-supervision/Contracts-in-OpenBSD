// this is to demonstrate that 'strlen' is in include headers.
// beryllium version does not include "share/frama-c/jessie/jessie_prolog.h"
// so we need to use the following command for this file.
//  frama-c -jessie -pp-annot -cpp-extra-args " -include e:/frama-c/share/frama-c/jessie/jessie_prolog.h" e:/fr/expl/18.c

/*@ requires valid_string(s);
  @ assigns \nothing;
  @ ensures \result == strlen(s) && \forall unsigned int k; 0 <= k < \result && s[k] != '\0';
  @*/
 unsigned int strlen (const char *s)
 {
	 //@ ghost int x = strlen(s); // this ?
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



