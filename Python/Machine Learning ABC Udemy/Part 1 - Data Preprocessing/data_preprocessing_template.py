# Data Preprocessing Template

# Importing the libraries
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from sklearn.preprocessing import Imputer, LabelEncoder, OneHotEncoder, StandardScaler
from sklearn.model_selection import train_test_split

# Importing the dataset
dataset = pd.read_csv('Data.csv') # Load csv file
x = dataset.iloc[:, :-1].values # Features
y = dataset.iloc[:, -1].values # Results
x[:, 1:3] = Imputer().fit(x[:, 1:3]).transform(x[:, 1:3]) # Fix missing values
x[:, 0] = LabelEncoder().fit_transform(x[:, 0]) # Set string values their integer values
x = OneHotEncoder(categorical_features=[0]).fit_transform(x).toarray() # Format data for each string integer value (pivot table)
y = LabelEncoder().fit_transform(y)
train_x, test_x, train_y, test_y = train_test_split(x, y, test_size=0.8) # Split data for train and test data
train_x = StandardScaler().fit_transform(train_x)
test_x = StandardScaler().fit_transform(test_x)
plt.plot(x_test, y_test, 'r+', x_test, predicted_values, 'b')
plt.show()
