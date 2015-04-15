import math
def dif_dividides(x,y,n):
    c = [[0 for i in range(len(y))] for i in range(len(y))]
    for i in range(len(y)):
        c[0][i]=y[i]
    k=0;
    for i in range(1,len(c)):
        k=i;
        for j in range(len(y)-i):
            c[i][j]=(c[i-1][j+1]-c[i-1][j])/(x[k]-x[j])
            k+=1
    for i in range(len(c)):
        y[i]=c[i][0]
    print "DIVIDED DIFFERENCES APPLIED ON Y=",y

def aval(x,z,t):
    suma = 0
    for i in range(len(x)):
        print i, suma
        if i==0:
            suma += z[i]   
        else:
            mul = t-x[i-1]
            for j in range(1,i):
                mul=mul*(t-x[i-1])  
            suma += z[i]*mul
    print "ENDED SUMA"
    return suma

def f(t):
    return math.exp(math.sin(t)+math.cos(t))
def createX():
    
    x=[0]
    a=1
    while x[a-1]<(math.pi*2.0):
        x.append(math.pi*0.002*a)
        a+=1
    print "CREATED X =", x
    return x
def createY(x):
    y=[]
    for i in x:
        y.append(f(i))  
    print "CREATED Y =", y
    return y
def createPN(x):
    
    y = createY(x)
    dif_dividides(x,y,n)
    pn = avalpn(x,y)    
    print "CREATED PN=", pn
    return  pn
def avalpn(x,z):
    av=[]
    for i in x:
        j = aval(x,z,i)
        av.append(j)
    print "EVALUATED PN=",av
    return av
def createER(y,pn):
    er = []
    for i in range(len(y)):
        er.append(abs(y[i]-pn[i]))
    print "CREATED ER=",er
    return er

def main():
    n=4
    x= createX()
    y=createY(x)
    pn = createPN(x)
    #er = createER(y,pn)
    for i in range(len(x)):
        print x[i], y[i], pn[i]#, er[i]
        
        
            
        
x = [30,40,50,60]
y = [-9.5,-15.4,-21.9,-33.6]
n = 3
dif_dividides(x,y,n)
aval(x,y,45)
#main()
        

