import pandas as pd

df_data = {
    'Name':['Annie','Diya','Charles','James','Emily'],
    'Quiz_1/10':[8.0,9.0,7.5,8.5,6.5],
    'In-sem_1/15':[11.0,14.0,14.5,13.0,12.5],
    'Quiz_2/10':[9.5,6.5,8.5,9.0,9.0],
    'Insem_2/15':[12.5,13.5,14.5,15.0,13.0]
    }


df = pd.DataFrame(df_data)
print(df)


df['Total'] = df.loc[0:4, ['Name','Quiz_1/10','In-sem_1/15','Quiz_2/10','Insem_2/15']].sum(axis=1)

print(df)

df.loc['Mean'] = df.mean()
print(df)