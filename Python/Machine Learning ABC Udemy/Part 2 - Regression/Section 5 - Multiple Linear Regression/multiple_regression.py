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

# Dummy variables
x[:, 3] = LabelEncoder().fit_transform(x[:, 3]) # Set string values their integer values
x = OneHotEncoder(categorical_features=[3]).fit_transform(x).toarray()[:, 1:] # Format data for each string integer value (pivot table)

# Split data
x_train, x_test, y_train, y_test = train_test_split(x, y, test_size = 1/3)

# Create regressor
regressor = LinearRegression()
regressor.fit(x_train, y_train)

# Add indexes
x = np.append(arr=np.ones((50, 1)).astype(int), values=x, axis=1)
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


# Test some values
y_predict = regressor.predict(x_test)
plt.plot(x_test[:, [3]], y_test, 'r+', x_test[:, [3]], y_predict, 'b+')
plt.show()
