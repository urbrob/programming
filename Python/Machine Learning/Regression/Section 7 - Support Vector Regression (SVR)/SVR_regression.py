from sklearn.linear_model import LinearRegression
from sklearn.svm import SVR
import pandas as pd
import numpy as np
from sklearn.preprocessing import StandardScaler, PolynomialFeatures
from matplotlib import  pyplot as plt

def compare_values(value, compartor):
    return value / compartor if value < compartor else compartor / value


# Importing the dataset
dataset = pd.read_csv('Position_Salaries.csv')
x = dataset.iloc[:, 1:2].values
y = dataset.iloc[:, 2:3].values

# Compare to linear
regressor_lin = LinearRegression()
regressor_lin.fit(x, y)

x_scaler = StandardScaler()
y_scaler = StandardScaler()
x_trans = x_scaler.fit_transform(x)
y_trans = y_scaler.fit_transform(y)

regressor_poly = PolynomialFeatures()
x_poly = regressor_poly.fit_transform(x)
regressor_poly.fit(x_poly, y)

regressor_poly_lin = LinearRegression()
regressor_poly_lin.fit(x_poly, y)

svr_reggressor = SVR()
svr_reggressor.fit(x_trans, y_trans)

y_lin = regressor_lin.predict(x)
y_svr = y_scaler.inverse_transform(svr_reggressor.predict(x_scaler.transform(x)))
y_poly = regressor_poly_lin.predict(regressor_poly.fit_transform(x))

# Compare linear and poly
values = [(compare_values(poly, value), compare_values(lin, value), compare_values(svr, value)) for poly, lin, svr, value in zip(y_poly, y_lin, y_svr, y)]
poly_values = [val[0] for val in values]
line_values = [val[1] for val in values]
svr_values = [val[2] for val in values]

print('Poly :', sum(poly_values) / len(poly_values))
print('Linear :', sum(line_values) / len(line_values))
print('SVR :', sum(svr_values) / len(svr_values))
