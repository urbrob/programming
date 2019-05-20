from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.preprocessing import PolynomialFeatures
from sklearn.svm import SVR
from sklearn.tree import DecisionTreeRegressor
from sklearn.ensemlbe import RandomForestRegressor
import numpy as np


class RegressionComparer:
    def linear_regression():
        regression = LinearRegression()
        regression.fit(self.x_train, self.y_train)
        
