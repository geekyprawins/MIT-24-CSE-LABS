import pandas as pd
import numpy as np

s = pd.Series([3,9,-2,10,5])
sum = s.sum()
min = s.min()
max = s.max()
print(sum,min,max)


data = [['Dinesh',10],['Nitya',12],['Raji',13]]
df = pd.DataFrame(data, columns=['Name','Age'])

print(df)


dt = {'Name':['Kavitha', 'Sudha', 'Raju','Vignesh'],'Age':[28,34,29,42]}
dfs = pd.DataFrame(dt, index=['rank1','rank2','rank3','rank4'])

print(dfs)


df1=pd.DataFrame({'A':pd.Timestamp('20130102'),'B':np.array([3]*4,dtype='int32'),
'C':pd.Categorical(['Male','Female','Male','Female'])})

print(df1)
print(df1.shape)
print(df1.dtypes)

print(df1.head())
print(df1.tail())

# df1.T 
