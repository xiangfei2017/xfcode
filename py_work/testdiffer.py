#!/usr/bin/env python

import mathdiffer as nt


x=nt.TN(2,'x')
y=nt.TN(3,'y')

z=x*nt.log(x)
g=z.grad(x)

print('x=',x)
print('z=',z)
print('expression of z:\n',z.getexpstr())

print('g=',g)
#print(g.getpostsort())
print('expression of g:\n',g.getexpstr())

def func(x):
    y=x*nt.sin(x)
    return y

df=nt.get_diff(func)
yy=func(x)
print('f(x)=',yy.getexpstr())
print('df(x)=',df(x))
print('df(x):',df(x).getexpstr())

