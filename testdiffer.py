import mathdiffer as df


x=df.TN(2,'x')
y=df.TN(3,'y')

z=x**2*df.sin(x)
g=z.grad(x)

print('z=',z)
print('expression of z:\n',z.getexpstr())

print('g=',g)
print(g.getpostsort())
print('expression of g:\n',g.getexpstr())
