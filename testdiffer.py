import mathdiffer as df


x=df.TN(2,'x')
y=df.TN(3,'y')

z=(df.exp(x)-df.exp(-x))/2
g=z.grad(x)

print('z=',z)
print('expression of z:\n',z.getexpstr())

print('g=',g)
print(g.getpostsort())
print('expression of g:\n',g.getexpstr())