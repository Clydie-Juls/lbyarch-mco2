void write_to_double(double v, double *d)
{
  *d = v;
}

int main()
{
  double v = 2.5;
  write_to_double(v, &v);

  return 0;
}