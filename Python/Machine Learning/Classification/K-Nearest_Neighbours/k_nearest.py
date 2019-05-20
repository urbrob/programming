import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import confusion_matrix


def calculate_results(result):
    correct = result[0][0] + result[1][1]
    incorrect = result[0][1] + result[1][0]
    return [result, correct / (incorrect + correct)]

dataset = pd.read_csv('Social_Network_Ads.csv')
X = dataset.iloc[:, [2, 3]].values
Y = dataset.iloc[:, -1].values
results = []
for _ in range(10):
    X_train, X_test, Y_train, Y_test = train_test_split(X, Y, test_size=0.25)
    scaller = StandardScaler()
    X_train = scaller.fit_transform(X_train)
    X_test = scaller.transform(X_test)

    classifier = KNeighborsClassifier()
    classifier.fit(X_train, Y_train)

    Y_predict = classifier.predict(X_test)

    matrix = confusion_matrix(Y_test, Y_predict)
    results.append(matrix)

results = map(calculate_results, results)
for result in results:
    print(result)
