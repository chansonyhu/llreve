extern int __mark(int);
int f(int n) {
  int i = 0;
  int j = 0;

  while (__mark(42) & (i <= n)) {
    i++;
    j++;
  }
  return j;
}
