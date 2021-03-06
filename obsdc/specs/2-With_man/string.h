// specs for top functions without looking at man or code - cleaned out rest of the functions out.
// had to add missing parameter names.
// had to create the include file structure and copy include files.

#ifndef _STRING_H_
#define	_STRING_H_

#include <sys/cdefs.h>
#include <machine/_types.h>

#ifndef	_SIZE_T_DEFINED_
#define	_SIZE_T_DEFINED_
typedef	__size_t	size_t;
#endif

#ifndef	NULL
#ifdef 	__GNUG__
#define	NULL	__null
#else
#define	NULL	0L
#endif
#endif

__BEGIN_DECLS
int	 memcmp(const void *, const void *, size_t);
/*@ requires valid_string(s1) && valid_string(s2) && \valid_range(s1, 0, strlen(s1) + strlen(s2));
   assigns s1;
   ensures strlen(s1) == \old(strlen(s1) + strlen(s2));
   ensures \forall integer i; 0 <= i < \at(strlen(s1), Old) && s1[i] == \old(s1[i]);
   ensures \forall integer j; \old(strlen(s1)) <= j < strlen(s1) && s1[j] == s2[j];
   ensures  \result == s1;
 */
char	*strcat(char *s1, const char *s2);
/*@ requires valid_string(s);
    assigns \nothing;
    ensures \exists integer i; 0 <= i <= strlen(s) && s[i] == c &&
       \forall integer j; 0 <= j < i && s[j] != c ==> \result == s+i;
    ensures \forall integer i; 0 <= i <= strlen(s) && s[i] != c ==> \result == \null;
 */
char	*strchr(const char *s, int c);
/*@ requires valid_string(s1) && valid_string(s2);
    assigns \nothing;
    behavior same_strings:
      assumes strlen(s1) == strlen(s2) && \forall integer i; 0 <= i < strlen(s1) && s1[i] == s2[i];
      ensures \result == 0;
    behavior s1_smaller:
      assumes strlen(s1) < strlen(s2) || (strlen(s1) == strlen(s2) && \exists integer i; 0<=i<strlen(s1) && (unsigned char)s1[i] < (unsigned char) s2[i]);
      ensures \result < 0;
    behavior s2_smaller:
      assumes strlen(s2) < strlen(s1) || (strlen(s1) == strlen(s2) && \exists integer i; 0<=i<strlen(s2) && (unsigned char) s2[i] < (unsigned char)s1[i]);
      ensures \result > 0;
 */
int	 strcmp(const char *s1, const char *s2);
/*@ requires valid_string(dst) && valid_string(src);
    assigns dst[0..minimum(strlen(dst), strlen(src))];
    ensures \forall integer i; 0 <= i <= minimum(strlen(dst), strlen(src)) && dst[i] == src[i];
    ensures \result == dst;
 */
char	*strcpy(char *dst, const char *src);
/*@
  @ requires valid_string(s) && valid_string(charset);
  @ assigns \nothing;
  @ ensures \exists integer i; 0 <= i < strlen(s) &&
  @         \forall integer j; 0 <= j < strlen(charset) &&
  @          charset[j] != s[i] ==> \result == i + 1;
 */
size_t	 strcspn(const char *s, const char *charset);
/*@ requires valid_string(s);
  @ assigns \nothing;
  @ ensures \valid_range(s, 0, \result) && s[\result] == '\0' && \forall unsigned int k; 0 <= k < \result && s[k] != '\0';
  @*/
size_t	 strlen(const char *s);
/*@
  requires \valid_range(s, 0, minimum(count, strlen(append))) && valid_string(append);
  assigns s[0..minimum(count, strlen(append)) - 1];
  ensures strlen(s) == \old(strlen(s)) + minimum(count, strlen(append)) + 1;
  ensures \forall integer k; 0 <= k < \old(strlen(s)) ==> s[k] == \old(s[k]);
  ensures \forall integer k; \old(strlen(s)) <= k < minimum(count, strlen(append)) ==>
    s[k] == append[k-\old(strlen(s))];
  ensures s[minimum(count, strlen(append)) + 1] == '\0';
  ensures \result == s;
 */
char	*strncat(char *s, const char *append, size_t count)
		__attribute__ ((__bounded__(__string__,1,3)));
/*@ requires valid_string(s1) && valid_string(s2);
    assigns \nothing;
    behavior same_strings:
      assumes \forall integer i; 0 <= i < minimum(len, minimum(strlen(s1), strlen(s2))) && s1[i] == s2[i];
      ensures \result == 0;
    behavior s1_smaller:
      assumes \exists integer i; 0<= i < minimum(len, minimum(strlen(s1), strlen(s2))) && (unsigned char)s1[i] < (unsigned char) s2[i];
      ensures \result < 0;
    behavior s2_smaller:
      assumes \exists integer i; 0<= i< minimum(len, minimum(strlen(s1), strlen(s2))) && (unsigned char) s2[i] < (unsigned char)s1[i];
      ensures \result > 0;
 */
int	 strncmp(const char *s1, const char *s2, size_t len);
//man: what happens if dst is shorter?
/*@ requires valid_string(dst) && valid_string(src);
    requires \valid_range(dst, 0, len);
    assigns dst[0..len];
    ensures \forall integer i; 0 <= i < minimum(len, strlen(src)) && dst[i] == src[i];
    ensures strlen(src) < len ==> \forall integer i; strlen(src) <= i < len && dst[i] == '\0';
    ensures \result == dst;
 */
char	*strncpy(char *dst, const char *src, size_t len)
		__attribute__ ((__bounded__(__string__,1,3)));
/*@
  @ requires valid_string(s);
  @ assigns \nothing;
  @ ensures \exists integer i; 0 <= i < strlen(charset) &&
  @         \exists integer j; 0 <= j < strlen(s) &&
  @          charset[i] == s[j] ==> \result == s+j;
  @ ensures \forall integer i; 0 <= i < strlen(charset) &&
  @         \forall integer j; 0 <= j < strlen(s) &&
  @          charset[i] != s[j] ==> \result == \null;
 */
char	*strpbrk(const char *s, const char *charset);
/*@
  @ requires valid_string(s);
  @ assigns \nothing;
  @ ensures \exists integer i; 0 <= i <= strlen(s) && s[i] == c &&
  @    (\forall integer j; i < j <= strlen(s) ==> s[j] != c) ==> \result == s+i;
  @ ensures \forall integer i; 0 <= i <= strlen(s) && s[i] != c ==> \result == \null;
 */
char	*strrchr(const char *s, int c);

/*@ predicate contains_string_at_i{L}(char *big, char *little, integer i) =
  @   strlen(big) >= strlen(little) && \forall integer k; i <= k <= strlen(little) && big[k] == little[k];
  @
  @*/

/*@
  @ requires valid_string(big) && valid_string(little);
  @ assigns \nothing;
  @ ensures strlen(little) == 0 ==> \result == big;
  @ ensures strlen(big) < strlen(little) ==> \result == \null;
  @ ensures strlen(big) >= strlen(little) && \exists integer i; 0 <= i <= (strlen(big) - strlen(little)) && contains_string_at_i(big, little, i) &&
  @    \forall integer k; 0 <= k < i && !contains_string_at_i(big, little, k) ==> \result == big + i;
  @ ensures strlen(big) >= strlen(little) && \forall integer i; 0 <= i <= (strlen(big) - strlen(little)) &&
  @     !contains_string_at_i(big, little, i) ==> \result == \null;
 */
char	*strstr(const char *big, const char *little);

/*@ logic integer tolower(integer c) = (65 <= c <= 90)  ? (c + 32) : c;
  @*/


#if __BSD_VISIBLE || __XPG_VISIBLE >= 420
/*@ requires valid_string(s1) && valid_string(s2);
    assigns \nothing;
    behavior same_strings:
      assumes strlen(s1) == strlen(s2) && \forall integer i; 0 <= i < strlen(s1) && tolower(s1[i]) == tolower(s2[i]);
      ensures \result == 0;
    behavior s1_smaller:
      assumes strlen(s1) < strlen(s2) || (strlen(s1) == strlen(s2) && \exists integer i; 0<=i<strlen(s1) && (unsigned char)tolower(s1[i]) < (unsigned char) tolower(s2[i]));
      ensures \result < 0;
    behavior s2_smaller:
      assumes strlen(s2) < strlen(s1) || (strlen(s1) == strlen(s2) && \exists integer i; 0<=i<strlen(s2) && (unsigned char)tolower(s2[i]) < (unsigned char)tolower(s1[i]));
      ensures \result > 0;
 */
int	 strcasecmp(const char *s1, const char *s2);
int	 strncasecmp(const char *, const char *, size_t);
char	*strdup(const char *s);
#endif

#if __BSD_VISIBLE
/*@
  requires valid_string(src) && valid_string(dst) && \valid_range(dst, 0, size);
  assigns dst;
  behavior b1:
	  assumes size == 0 || strlen(src) == 0;
	  assigns \nothing;
	  ensures \result == 0;
  behavior b2:
      assumes size > 0 && strlen(src) > 0 && strlen(dst) < size;
	  ensures strlen(dst) == \old(strlen(dst)) + minimum(size, strlen(src));
	  ensures \forall integer k; 0 <= k < \old(strlen(dst)) ==> dst[k] == \old(dst[k]);
	  ensures \forall integer k; 0 <= k < minimum(size, strlen(src)) ==>
			dst[k + \old(strlen(dst))] == src[k];
	  ensures dst[strlen(dst)] == '\0';
	  ensures \result == \old(strlen(dst)) + strlen(src);
behavior b3:
      assumes size > 0 && strlen(src) > 0 && strlen(dst) >= size;
	  assigns \nothing;
	  ensures \result == size + strlen(src);
 */
size_t	 strlcat(char *dst, const char *src, size_t size)
		__attribute__ ((__bounded__(__string__,1,3)));
/*@ requires \valid_range(dst, 0, size) && valid_string(src);
    behavior b1:
		assumes size == 0 || strlen(src) == 0;
		assigns \nothing;
		ensures \result == 0;
	behavior b2:
		assumes size > 0 && strlen(src) > 0;
		assigns dst[0..size];
		ensures \forall integer i; 0 <= i < minimum(size, strlen(src)) ==> dst[i] == src[i];
		ensures dst[size] == 0;
		ensures \result == strlen(src);
 */
size_t	 strlcpy(char *dst, const char *src, size_t size)
		__attribute__ ((__bounded__(__string__,1,3)));
#endif
__END_DECLS
#endif /* _STRING_H_ */
