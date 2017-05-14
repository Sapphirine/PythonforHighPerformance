from instant import inline
source = """
double find_sum(double r1, double r2)
{
return sum(r1 + r2);
}
"""
find_sum = inline(source)

x= 1.0
y =2.5
print("sin({0}+{1}) = {2}".format(x,y,find_sum(x,y)))
