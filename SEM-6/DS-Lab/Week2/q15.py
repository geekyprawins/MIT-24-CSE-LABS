import pandas as pd

students_data = {"Name": ["Praveen", "Pratik", "Yashwanth"], "Height": ["5'11", "5'10", "5'11"],"Qualifications": ["Engineering", "Medicine", "Law"]}

new_df = pd.DataFrame(students_data)
print(new_df)
address_data = ["Hyderabad", "Qatar", "Mumbai"]
new_df["Address"] = address_data
print(new_df)
