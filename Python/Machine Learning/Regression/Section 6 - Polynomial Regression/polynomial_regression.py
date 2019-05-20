from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.preprocessing import PolynomialFeatures
import statsmodels.formula.api as sm
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np


def compare_values(value, compartor):
    return value / compartor if value < compartor else compartor / value

# Importing the dataset
dataset = pd.read_csv('Position_Salaries.csv')
x = dataset.iloc[:, 1:2].values
y = dataset.iloc[:, -1].values

# Compare to linear
regressor_lin = LinearRegression()
regressor_lin.fit(x, y)


regressor_poly = PolynomialFeatures(degree=3)
x_poly = regressor_poly.fit_transform(x)
regressor_poly.fit(x_poly, y)

regressor_poly_lin = LinearRegression()
regressor_poly_lin.fit(x_poly, y)

# Compare linear and poly
values = [(compare_values(poly, value), compare_values(lin, value)) for poly, lin, value in zip(regressor_poly_lin.predict(regressor_poly.fit_transform(x)), regressor_lin.predict(x), y)]
poly_values = [val[0] for val in values]
line_values = [val[1] for val in values]

print(regressor_poly_lin.predict(regressor_poly.fit_transform(x)))
print(regressor_poly_lin.predict(regressor_poly.fit_transform([[1.1]])))
print('Poly :', sum(poly_values) / len(poly_values))
print('Linear :', sum(line_values) / len(line_values))
