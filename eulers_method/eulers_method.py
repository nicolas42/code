f = lambda x,y: 2*x-y
x,y,step = 1,1,0.1

for i in range(10):
    x += step
    y += f(x,y)*step
    print( '%.2f %.2f' % (x,y) )



