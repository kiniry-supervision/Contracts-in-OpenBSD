/*@
    predicate swapped {L1, L2}(int* a, int* b) =
        \at(*a, L1) == \at(*b, L2) &&
        \at(*b, L1) == \at(*a, L2);
*/
/*@
    requires \valid(a);
    requires \valid(b);
    assigns *a;
    assigns *b;

    ensures *a == \old(*b);
    ensures *b == \old(*a);
    ensures swapped{Here, Old}(a,b);
*/
void swap (int* a, int* b )
{
    int c = *a;
    *a = *b;
    *b = c;
}
