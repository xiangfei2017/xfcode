import sys
import pprint

#确定有效的状态集合
state={}
for s in range(128):
   boollist=[]
   for i in range(7):
      boollist.append(s//(2**i)%2)

   if boollist[0] not in boollist[1:5]:
      continue
   if boollist[1] != boollist[4] and (boollist[4]==boollist[2] or boollist[4]==boollist[3]):
      continue
   if boollist[2] != boollist[5] and (boollist[5]==boollist[1] or boollist[5]==boollist[3]):
      continue
   if boollist[3] != boollist[6] and (boollist[6]==boollist[1] or boollist[6]==boollist[2]):
      continue

   #state.setdefault(s,boollist)
   state[s]=boollist

print(len(state))
pprint.pprint(state) 

def chk_trans(sv1,sv2):
   if sv1[0] == sv2[0]: #船必须过河
      return False

#与船同侧的过河动物数目c1，其中划船动物数c2,与船不同侧过河数c3
   c1=c2=c3=0
   for i in range(1,7):
      if sv1[i]==sv1[0]:
         if sv1[i]!=sv2[i]:
            c1+=1
            if i in range(1,5):
               c2+=1
      elif sv1[i]!=sv2[i]:
         c3+=1
   if 0<c1<=2 and c2>0 and c3==0:
      return True
   return False

sg={}
for sk1,sv1 in state.items():
   for sk2,sv2 in state.items():
      if sk1==sk2 :continue
      if chk_trans(sv1,sv2):
         if sk1 not in sg.keys():
            sg.setdefault(sk1,[])
         sg[sk1].append(sk2)

pprint.pprint(sg)
flag={}
for k in state.keys():
   flag.setdefault(k,0)
stack=[0]
flag[0]=1
while len(stack)>0:
   top=stack[-1]
   if top==127:break
   if top not in sg.keys():
      stack.pop()
      continue
   to_state=-1
   for s in sg[top]:
      if flag[s]==0:
         to_state=s
         break
   if to_state==-1:
      stack.pop()
   else:
      stack.append(to_state)
      flag[s]=1
if len(stack)==0:
   print("no solution found")
   sys.exit()

print('state list:') 
for s in stack:
   print(state[s])

name={1:'Tiger',2:'Bear',3:'Lion',4:'tiger',5:'bear',6:'lion'} 
print('steps:')
prev=stack[0]
for next in stack[1:]:
   sp=state[prev]
   sn=state[next]
   if sn[0]==1:
      print('>>: ',end='')
   else:
      print('<<: ',end='')
   for i in range(1,7):
      if sp[i] != sn[i]:
         print(name[i],end=' ')
   print('')
   prev=next
