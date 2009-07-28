/*@ requires n > 0 && \valid(t+(0..n -1));
  @ ensures \result== \max(0,n-1 ,(\lambda integer k; t[k]));
*/
double max(int t[], int n) {
 int i = 0; double m,v;
 do
 {
   v = t[i++];
   m = v > m ? v : m;
   /*@ invariant m == \max(0,i-1 ,( \lambda integer k ; t[k])); */
 } while (i < n);
 return m;
}

/*@ requires n > 0;
  @ ensures \result == \max(0,n-1, \lambda integer k; t[k]);
*/
 double max_array (double t[], int n) {
 double m; int i =0;
 goto L;
 do {
   if (t[i] > m) { L: m = t[i]; }
   /*@ invariant
     @ 0 <= i < n && m == \max(0,i, \lambda integer k; t[k]);
   @*/
   i++;
 }
 while (i < n);
 return m;
 }
