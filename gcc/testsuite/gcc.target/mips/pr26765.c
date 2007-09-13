/* PR target/pr26765
   This testcase used to trigger an unrecognizable insn.  */

/* { dg-do compile } */
/* { dg-options "-O2 -w" } */

__thread int *a = 0;

#define NOMIPS16 __attribute__ ((nomips16))

NOMIPS16 void foo (void)
{
  extern int *b;
  b = (int *) ((*a));
}
