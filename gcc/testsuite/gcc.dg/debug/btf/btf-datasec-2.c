/* Test BTF generation of DATASEC records for extern functions.

   Only functions declared extern should have entries in DATASEC records.  */

/* { dg-do compile } */
/* { dg-options "-O0 -gbtf -dA" } */

/* Expect one DATASEC with vlen=1 (.foo_sec) and one with vlen=2 (.bar_sec) */
/* { dg-final { scan-assembler-times " BTF_KIND_DATASEC '.foo_sec'\[\\r\\n\]+\[^\\r\\n\]*0xf000001\[\t \]+\[^\n\]*btt_info" 1 } } */
/* { dg-final { scan-assembler-times " BTF_KIND_DATASEC '.bar_sec'\[\\r\\n\]+\[^\\r\\n\]*0xf000002\[\t \]+\[^\n\]*btt_info" 1 } } */

/* Function entries should have offset with a label and size of 0 at compile time.  */
/* { dg-final { scan-assembler-times "chacha\[\t \]+\[^\n\]*bts_offset" 1 { target { bpf-*-* } }} } */
/* { dg-final { scan-assembler-times "bar\[\t \]+\[^\n\]*bts_offset" 1 { target { bpf-*-* } } } } */
/* { dg-final { scan-assembler-times "foo\[\t \]+\[^\n\]*bts_offset" 1 { target { bpf-*-* } } } } */
/* { dg-final { scan-assembler-times "0\[\t \]+\[^\n\]*bts_offset" 3 { target { ! bpf-*-* } } } } */

/* { dg-final { scan-assembler-times "0\[\t \]+\[^\n\]*bts_size" 3 } } */

extern int foo (int a) __attribute__((section(".foo_sec")));


extern int bar (int b) __attribute__((section(".bar_sec")));
extern void chacha (void) __attribute__((section(".bar_sec")));

__attribute__((section(".foo_sec")))
void baz (int *x)
{
  chacha ();

  *x = foo (bar (*x));
}
