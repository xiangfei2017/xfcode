import os
import math

def log(x):
    v=x.data if isinstance(x,TN) else x
    ret=TN(math.log(v))
    ret.fromvars=['log',x]
    return ret
    

def exp(x):
    v=x.data if isinstance(x,TN) else x
    ret=TN(math.exp(v))
    ret.fromvars=['exp',x]
    return ret
    
 
def sin(x):
    v=x.data if isinstance(x,TN) else x
    ret=TN(math.sin(v))
    ret.fromvars=['sin',x]
    return ret
    

def cos(x):
    v=x.data if isinstance(x,TN) else x
    ret=TN(math.cos(v))
    ret.fromvars=['cos',x]
    return ret
    

def tan(x):
    v=x.data if isinstance(x,TN) else x
    ret=TN(math.tan(v))
    ret.fromvars=['tan',x]
    return ret
    
def cot(x):
    v=x.data if isinstance(x,TN) else x
    ret=TN(1.0/math.tan(v))
    ret.fromvars=['cot',x]
    return ret

def isCon(y,x):
    if not isinstance(y,TN):
        return True
    if id(y)==id(x):
        return False
        
    if len(y.fromvars)==0:
        return True
        
    ret=True
    for v in y.fromvars[1:]:
        if isinstance(v,TN):
            if id(v)==id(x):
                ret=False
            else:
                ret=isCon(v,x)
        if not ret:break
    
    return ret
    
class TN:
    def __init__(self,v,name=''):
        self.data=float(v)
        self.fromvars=[]
        self.name=name
        self.vflag=0
        
    def __repr__(self):
        return f'tn({self.data},{self.name})'
    
    def __add__(self,r):
        if isinstance(r,TN):
            v=self.data+r.data
        else:
            r=float(r)
            v=self.data+r
        ret=TN(v)
        ret.fromvars=['+',self,r]
        return ret
 
    def __sub__(self,r):
        if isinstance(r,TN):
            v=self.data-r.data
        else:
            r=float(r)
            v=self.data-r
        ret=TN(v)
        ret.fromvars=['-',self,r]
        return ret
    
    def __mul__(self,r):
        if isinstance(r,TN):
            v=self.data*r.data
        else:
            r=float(r)
            v=self.data*r
        ret=TN(v)
        ret.fromvars=['*',self,r]
        return ret
        
    def __truediv__(self,r):
        if isinstance(r,TN):
            v=self.data/r.data
        else:
            r=float(r)
            v=self.data/r
        ret=TN(v)
        ret.fromvars=['/',self,r]
        return ret
        
    def __pow__(self,r):
        if isinstance(r,TN):
            v=self.data**r.data
        else:
            r=float(r)
            v=self.data**r
        ret=TN(v)
        ret.fromvars=['**',self,r]
        return ret
        
    def __radd__(self,l):
        if isinstance(l,TN):
            v=l.data+self.data
        else:
            l=float(l)
            v=l+self.data
        ret=TN(v)
        ret.fromvars=['+',l,self]
        return ret
        
    def __rsub__(self,l):
        if isinstance(l,TN):
            v=l.data-self.data
        else:
            l=float(l)
            v=l-self.data
        ret=TN(v)
        ret.fromvars=['-',l,self]
        return ret
        
    def __rmul__(self,l):
        if isinstance(l,TN):
            v=l.data*self.data
        else:
            l=float(l)
            v=l*self.data
        ret=TN(v)
        ret.fromvars=['*',l,self]
        return ret
        
    def __rtruediv__(self,l):
        if isinstance(l,TN):
            v=l.data/self.data
        else:
            l=float(l)
            v=l/self.data
        ret=TN(v)
        ret.fromvars=['/',l,self]
        return ret
        
    def __rpow__(self,l):
        if isinstance(l,TN):
            v=l.data**self.data
        else:
            l=float(l)
            v=l**self.data
        ret=TN(v)
        ret.fromvars=['**',l,self]
        return ret
        
    def __pos__(self):
        v=self.data
        ret=TN(v)
        ret.fromvars=['pos',self]
        return ret
        
    def __neg__(self):
        v=-self.data
        ret=TN(v)
        ret.fromvars=['neg',self]
        return ret
        
    def getcalctree(self):
        if len(self.fromvars)==0:
            return self
            
        t=[]
        t.append(self.fromvars[0])
        for var in self.fromvars[1:]:
            if isinstance(var,TN):
                t.append(var.getcalctree())
            else:
                t.append(var)
        return t
        
        
    def grad(self,x):
        if id(self)==id(x):
            return 1.0
            
        if len(self.fromvars)==0:
            return 0.0
            
        op=self.fromvars[0]
        a=self.fromvars[1]
        
        if op=='+':
            b=self.fromvars[2]
            g1=(0.0 if isCon(a,x) else a.grad(x))
            g2=(0.0 if isCon(b,x) else b.grad(x))
            return g1+g2
            
        elif op=='-':
            b=self.fromvars[2]
            g1=(0.0 if isCon(a,x) else a.grad(x))
            g2=(0.0 if isCon(b,x) else b.grad(x))
            return g1-g2
            
        elif op=='*':
            b=self.fromvars[2]
            if isCon(a,x) and (not isCon(b,x)):
                g=a*b.grad(x)
            elif (not isCon(a,x)) and isCon(b,x):
                g=b*a.grad(x)
            elif (not isCon(a,x)) and (not isCon(b,x)):
                g=a.grad(x)*b+a*b.grad(x)
            else:
                g=0.0
            return g
            
        elif op=='/':
            b=self.fromvars[2]
            if isCon(a,x) and (not isCon(b,x)):
                g=-a*b.grad(x)/b**2
            elif (not isCon(a,x)) and isCon(b,x):
                g=a.grad(x)/b
            elif (not isCon(a,x)) and (not isCon(b,x)):
                g=(a.grad(x)*b-a*b.grad(x))/(b**2)
            else:
                g=0.0
            return g
            
        elif op=='**':
            b=self.fromvars[2]
            if isCon(a,x) and (not isCon(b,x)):
                g=a**b*log(a)*b.grad(x)
            elif (not isCon(a,x)) and isCon(b,x):
                g=b*(a**(b-1.0))*a.grad(x)
            elif (not isCon(a,x)) and (not isCon(b,x)):
                g1=b*(a**(b-1.0))*a.grad(x)
                g2=a**b*log(a)*b.grad(x)
                g=g1+g2
            else:
                g=0.0
            return g
         
        elif op=='neg':
            return -a.grad(x)
            
        elif op=='pos':
            return a.grad(x)
            
        elif op=='log':
            return a.grad(x)/a
            
        elif op=='exp':
            return exp(a)*a.grad(x)
            
        elif op=='sin':
            return cos(a)*a.grad(x)
        
        elif op=='cos':
            return -sin(a)*a.grad(x)
            
        elif op=='tan':
            return a.grad(x)/cos(a)**2.0
        elif op=='cot':
            return -a.grad(x)/sin(a)**2.0
            
    #end of def grad
    
    def getpostsort(self):
        s=[]
        s.append(self)
        self.vflag=0
        top=self
        
        def isleaf(x):
            if not isinstance(x,TN):
                return True
            
            if x.fromvars==[]:
                return True
            return False
        
        def push(s,v):
            if isinstance(v,TN):
                v.vflag=0
            s.append(v)
            
        while not isleaf(top):
            push(s,top.fromvars[1])
            top=s[-1]
            
        s1=[]
        while not (s==[]):
            
            top=s[-1]
            if isleaf(top):
                s.pop()
                s1.append(top)
                if not (s==[]):
                    s[-1].vflag+=1
            else:
                if top.vflag==0:
                    push(s,top.fromvars[1])
                elif top.vflag==1:
                    if top.fromvars[0] in ['+','-','*','/','**']:
                        push(s,top.fromvars[2])
                    else:
                        top=s.pop()
                        s1.append(top.fromvars[0])
                        if not (s==[]):
                            s[-1].vflag+=1
                else:
                    top=s.pop()
                    s1.append(top.fromvars[0])
                    if not (s==[]):
                        s[-1].vflag+=1
                
        
        return s1
    #end of def
    
    def getexpstr(self):
        
        def cmpopr(op1,op2):
            opv={'+':1,'-':1,'*':2,'/':2,'pos':3,'neg':3,'**':4,'':5,'exp':6,'log':6,'sin':6,'cos':6,'tan':6,'cot':6}
            if opv[op1]>opv[op2]:
                return 1
            elif opv[op1]==opv[op2]:
                if op1=='+':
                    return 0
                elif op1=='-':
                    return 1
                elif op1=='*': 
                    return 0
                elif op1=='/':
                    return 1
                else:
                    return 0
            else:
                if op1=='-' and op2=='neg':
                    return 1
                else:
                    return -1
                    
        def cmpopl(op1,op2):
            opv={'+':1,'-':1,'*':2,'/':2,'pos':3,'neg':3,'**':4,'':5,'exp':6,'log':6,'sin':6,'cos':6,'tan':6,'cot':6}
            if opv[op1]>opv[op2]:
                return 1
            elif opv[op1]==opv[op2]:
                return 0
            else:
                return -1
                
        def addleftneg(rv):
            s=f'-{rv}'
            if '--' in s:
                s=rv[1:]
            return s
                
        s=self.getpostsort()
        values=[]
        for v in s:
            if v not in ['+','-','*','/','pos','neg','**','exp','log','sin','cos','tan','cot']:
                exp=v.name if isinstance(v,TN) else str(v)
                values.append(('',exp))
                continue
                
            if v=='neg':
                r=values.pop()
                ro=r[0]
                rv=r[1]
                if cmpopr(v,ro)>0:
                    exp=(v,f'-({rv})')
                else:
                    exp=(v,addleftneg(rv))
            elif v=='pos':
                r=values.pop()
                rv=r[1]
                exp=(v,f'{rv}')
            elif v=='log':
                r=values.pop()
                rv=r[1]
                exp=(v,f'log({rv})')
            elif v=='exp':
                r=values.pop()
                rv=r[1]
                exp=(v,f'exp({rv})') 
            elif v=='sin':
                r=values.pop()
                rv=r[1]
                exp=(v,f'sin({rv})')
            elif v=='cos':
                r=values.pop()
                rv=r[1]
                exp=(v,f'cos({rv})')
            elif v=='tan':
                r=values.pop()
                rv=r[1]
                exp=(v,f'tan({rv})')
            elif v=='cot':
                r=values.pop()
                rv=r[1]
                exp=(v,f'cot({rv})')
            else:
                r=values.pop()
                ro=r[0]
                rv=r[1]
                l=values.pop()
                lo=l[0]
                lv=l[1]
                
                if (v=='+') and ('0.0' in [lv,rv]):
                    if lv=='0.0' and rv!='0.0':
                        exp=('',rv)
                    elif lv!='0.0' and rv=='0.0':
                        exp=('',lv)
                    else:
                        exp=('','0.0')
                elif (v=='-') and ('0.0' in [lv,rv]):
                    if lv=='0.0' and rv!='0.0':
                        exp=('',addleftneg(rv))
                    elif lv!='0.0' and rv=='0.0':
                        exp=('',lv)
                    else:
                        exp=('','0.0')
                elif (v=='*') and ('0.0' in [lv,rv]):
                    exp=('','0.0')
                elif (v=='*') and ('1.0' in [lv,rv]):
                    if lv=='1.0' and rv!='1.0':
                        exp=('',f'{rv}')
                    elif lv!='1.0' and rv=='1.0':
                        exp=('',lv)
                    else:
                        exp=('','1.0')
                elif (v=='*') and ('-1.0' in [lv,rv]):
                    if lv=='-1.0' and rv!='-1.0':
                        exp=('',addleftneg(rv))
                    elif lv!='-1.0' and rv=='-1.0':
                        exp=('',addleftneg(lv))
                    else:
                        exp=('','1.0')
                elif (v=='/')and((lv=='0.0')or(rv=='1.0')or(rv=='-1.0')):
                    if lv=='0.0':
                        exp=('','0.0')
                    elif rv=='1.0':
                        exp=('',lv)
                    else:
                        exp=('',addleftneg(lv))
                elif (v=='**')and(('1.0' in [lv,rv])or('0.0' in [lv,rv])):
                    if lv=='1.0':
                        exp=('','1.0')
                    elif lv=='0.0':
                        exp=('','0.0')
                    elif rv=='0.0':
                        exp=('','1.0')
                    else:
                        exp=('',lv)
                else:
                    cmp=cmpopr(v,ro)
                    if cmp==1:
                        expr=f'{v}({rv})'
                    else:
                        if rv[0]=='-':
                            expr=f'{v}({rv})'
                        else:
                            expr=f'{v}{rv}'
                    cmp=cmpopl(v,lo)
                    if cmp==1:
                        expl=f'({lv})'
                    else:
                        if lv[0]=='-' and v=='**':
                            expl=f'({lv})'
                        else:
                            expl=f'{lv}'
                    exp=(v,expl+expr) 
                #end if
            #end if
            
            values.append(exp)
        #end for  
        return values[-1][1]              
                
    #end def
    
#end of class



