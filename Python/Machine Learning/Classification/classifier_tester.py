from sklearn.tree import DecisionTreeClassifier
from sklearn.ensemble import RandomForestClassifier
from sklearn.naive_bayes import GaussianNB
from sklearn.linear_model import LogisticRegression
from sklearn.svm import SVC
from sklearn.neighbors import KNeighborsClassifier
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import confusion_matrix


def calculate_results(result):
    correct = result[0][0] + result[1][1]
    incorrect = result[0][1] + result[1][0]
    return correct / (incorrect + correct)

dataset = pd.read_csv('Social_Network_Ads.csv')
X = dataset.iloc[:, [2, 3]].values
Y = dataset.iloc[:, -1].values
classificators = [
    {'name': "SVM linear", "classifier": SVC(kernel="linear"), 'best': 0.0},
    {'name': "K-nearest", "classifier": KNeighborsClassifier(), 'best': 0.0},
    {'name': "Kernel_SVM", "classifier": SVC(), 'best': 0.0},
    {'name': "Random Forest", "classifier": RandomForestClassifier(criterion='entropy'), 'best': 0.0},
    {'name': "Logistic", "classifier": LogisticRegression(), 'best': 0.0},
    {'name': "Tree", "classifier": DecisionTreeClassifier(criterion='entropy'), 'best': 0.0},
    {'name': "Naive Bayes", "classifier": GaussianNB(), 'best': 0.0},
]

for classification in classificators:
    for _ in range(100):
        X_train, X_test, Y_train, Y_test = train_test_split(X, Y, test_size=0.25)
        scaller = StandardScaler()
        X_train = scaller.fit_transform(X_train)
        X_test = scaller.transform(X_test)

        classifier = classification['classifier']
        classifier.fit(X_train, Y_train)

        Y_predict = classifier.predict(X_test)

        matrix = confusion_matrix(Y_test, Y_predict)
        result = calculate_results(matrix)
        classification['best'] = result if result > classification['best'] else classification['best']

for classification in classificators:
    print(classification['name'], classification['best'])
