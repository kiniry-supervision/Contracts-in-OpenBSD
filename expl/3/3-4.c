/*@ lemma mean : \forall integer x, y; x <= y ==> x <= (x+y)/2 <= y; */
/*@ requires n >= 0 && \valid_range(t,0,n-1);
@ ensures -1 <= \result <= n-1;
@*/
int binary_search4(int* t, int n, int v) {
int l = 0, u = n-1, p = -1;
/*@ loop invariant
@ 0 <= l && u <= n-1 && -1 <= p <= n-1;
@*/
while (l <= u) {
int m = l + (u - l) / 2;
if (t[m] < v)
l = m + 1;
else if (t[m] > v)
u = m - 1;
else {
p = m; break;
}
}
return p;
}

