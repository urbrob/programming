from sklearn.ensemlbe import RandomForestRegressor
import pandas as pd


# Importing the dataset
dataset = pd.read_csv('Position_Salaries.csv')
x = dataset.iloc[:, 1:2].values
y = dataset.iloc[:, -1].values

regressor = RandomForestRegressor(n_estimators=100)
regressor.fit(x, y)
