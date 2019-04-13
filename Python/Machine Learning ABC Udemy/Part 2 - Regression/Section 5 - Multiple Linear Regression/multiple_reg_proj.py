from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.preprocessing import LabelEncoder, OneHotEncoder
import statsmodels.formula.api as sm
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

# Importing the dataset
dataset = pd.read_csv('julka.csv')
x = dataset.iloc[:, :-1].values
y = dataset.iloc[:, -1].values

# Create regressor
regressor = LinearRegression()
regressor.fit(x, y)

# Add indexes
x = np.append(arr=np.ones((10, 1)).astype(int), values=x, axis=1)
x_feature_indexes = list(range(len(x[0])))

# Backward elimination - Creating model
while True:
    x_opt = x[:, x_feature_indexes]
    regressor_OLS = sm.OLS(endog=y, exog=x_opt).fit()
    maximum = max(regressor_OLS.pvalues)
    if maximum < 0.05:
        break
    del x_feature_indexes[np.where(regressor_OLS.pvalues==maximum)[0][0]]

print("Columns:", x_feature_indexes)
print(regressor_OLS.summary())
print(regressor_OLS.predict(np.array([0.5, 0.9, 1, 1.5, 1.8, 2.7, 3, 4.5, 5.4, 8.1, 9, 13.5, 16.2]).reshape(-1, 1)))
