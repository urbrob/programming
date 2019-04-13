import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
import matplotlib.pyplot as plt


dataset = pd.read_csv('Salary_Data.csv')
x = dataset.iloc[:, :-1]
y = dataset.iloc[:, -1]

x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=1/3, random_state=0)
regressor = LinearRegression()
regressor.fit(x_train, y_train)
predicted_values = regressor.predict(x_test)
plt.plot(x_test, y_test, 'r+', x_test, predicted_values, 'b')
plt.show()
