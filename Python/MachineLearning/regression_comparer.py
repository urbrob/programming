
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.svm import SVR
from sklearn.ensemble import RandomForestRegressor
from sklearn.tree import DecisionTreeRegressor
import pandas as pd
from sklearn.preprocessing import StandardScaler, PolynomialFeatures, LabelEncoder, OneHotEncoder
import statsmodels.formula.api as sm
import matplotlib.pyplot as plt


class RegressionComparer:
    def __init__(self):
        self.loaded = False
        self.REGRESSORS = {
            'Linear/Multilinear': self.linear_regression,
            'Polynomial': self.polynomial_regression,
            'Support vector regression': self.svr_regression,
            #'Tree': DecisionTreeRegressor,
            #'Forest': RandomForestRegressor
        }

    def _compare_values(self, value, compartor):
        value = abs(value)
        compartor = abs(compartor)
        return value / compartor if value < compartor else compartor / value

    def compare_prediction(self, predicted_values):
        values = [self._compare_values(predicted_value, value) for predicted_value, value in zip(predicted_values, self.y_test)]
        return sum(values) / len(values)

    def linear_regression(self):
        regressor = LinearRegression()
        regressor.fit(self.x_train, self.y_train)
        predict = regressor.predict(self.x_test)
        return self.compare_prediction(predict)

    def polynomial_regression(self):
        regressor_poly = PolynomialFeatures()
        x_poly = regressor_poly.fit_transform(self.x_test)
        regressor_poly.fit(self.x_test, self.y_test)
        regressor_poly_lin = LinearRegression()
        regressor_poly_lin.fit(x_poly, self.y_test)
        y_predict = regressor_poly_lin.predict(regressor_poly.fit_transform(self.x_test))
        return self.compare_prediction(y_predict)

    def svr_regression(self):
        svr_reggressor = SVR()
        svr_reggressor.fit(self.x_train_sc, self.y_train_sc)
        y_svr = self.y_scaller.inverse_transform(svr_reggressor.predict(self.x_scaller.transform(self.x_test_sc)))
        return self.compare_prediction(y_svr)


    def load_data(self, x, y):
        self.x_scaller = StandardScaler()
        self.y_scaller = StandardScaler()
        self.loaded = True
        self.x = x
        self.x_scalled = self.x_scaller.fit_transform(x)
        self.y = y
        self.y_scalled = self.y_scaller.fit_transform(y)
        self.regression_results = {}
        self.x_train, self.x_test, self.y_train, self.y_test = train_test_split(self.x, self.y, test_size = 1/3)
        self.x_train_sc, self.x_test_sc, self.y_train_sc, self.y_test_sc = train_test_split(self.x_scalled, self.y_scalled, test_size = 1/3, random_state=0)

    def fit_for_all(self):
        print('\nIT REGRESSION COMPARATOR 0.1.0v\n\n')
        for regression_name, reggresion in self.REGRESSORS.items():
            print(f'Preparing regression : {regression_name} [----]\n')
            self.regression_results[regression_name] = self.REGRESSORS[regression_name]()
            print(f'Regression : {regression_name} [DONE]\n')


    def summary_reggression(self):
        print('\nResults:\n')
        for regression_name, result in self.regression_results.items():
            print(regression_name, result)




if __name__ == '__main__':
    dataset = pd.read_csv('50_Startups.csv')
    x = dataset.iloc[:, :-1].values
    y = dataset.iloc[:, -1:].values
    regresion_comparer = RegressionComparer()
    regresion_comparer.load_data(x, y)
    regresion_comparer.fit_for_all()
    regresion_comparer.summary_reggression()
