import pandas as pd


df1_data = {'Name' : ['Ram','Diya','Chandan','James','Alice']}
df2_data = {'Maths':[80.0,90.0,77.5,87.5,86.5], 'Physics' : [81.0,94.0,74.5,83.0,82.5],'Chemistry' : [91.5,86.5,85.5,90.0,91.0],'Biology':[82.5,83.5,84.5,85.0,93.0]}

df1 = pd.DataFrame(df1_data)
df2 = pd.DataFrame(df2_data)
print(df1)
print(df2)

df_combined = pd.concat([df1,df2],axis=1)
print(df_combined)

df_combined['Total'] = df_combined.loc[0:4, ['Maths','Physics','Chemistry','Biology']].sum(axis=1)
print(df_combined)
