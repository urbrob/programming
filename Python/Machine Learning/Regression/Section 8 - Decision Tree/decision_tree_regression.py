from sklearn.tree import DecisionTreeRegressor
import pandas as pd


# Importing the dataset
dataset = pd.read_csv('Position_Salaries.csv')
x = dataset.iloc[:, 1:2].values
y = dataset.iloc[:, -1].values

regressor = DecisonTreeRegression()
regressor.fit(x, y)
