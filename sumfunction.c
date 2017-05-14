double sum1(double r1, double r2)
{
    double s;
    s = sin(r1 + r2);
    return s;
}

void sum2(double r1, double r2)
{
    double s;
    s = sin(r1 + r2);
    printf(sin(%g+%g)=%g\n", r1, r2, s);
}
