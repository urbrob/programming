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


class ClassificationComparer:
    CLASSIFICATORS = [
        {'name': "SVM linear", "classifier": SVC(kernel="linear"), 'best': 0.0},
        {'name': "K-nearest", "classifier": KNeighborsClassifier(), 'best': 0.0},
        {'name': "Kernel_SVM", "classifier": SVC(), 'best': 0.0},
        {'name': "Random Forest", "classifier": RandomForestClassifier(criterion='entropy', n_estimators=10, random_state=0), 'best': 0.0},
        {'name': "Logistic", "classifier": LogisticRegression(), 'best': 0.0},
        {'name': "Tree", "classifier": DecisionTreeClassifier(criterion='entropy'), 'best': 0.0},
        {'name': "Naive Bayes", "classifier": GaussianNB(), 'best': 0.0},
    ]

    def __init__(self, x, y):
        self.results = {}
        self.X_train, self.X_test, self.Y_train, self.Y_test = train_test_split(x, y, test_size=0.20)
        self.scaller = StandardScaler()
        self.X_train = self.scaller.fit_transform(self.X_train)
        self.X_test = self.scaller.transform(self.X_test)

    def accuracy(self, result):
        correct = result[0][0] + result[1][1]
        incorrect = result[0][1] + result[1][0]
        return correct / (incorrect + correct)

    def precision(self, result):
        return result[1][1] / (result[0][1] + result[1][1])

    def recall(self, result):
        return result[1][1] / (result[1][0] + result[1][1])

    def f1(self, result):
        return 2 * self.precision(result) * self.recall(result) / (self.precision(result) + self.recall(result))

    def fit_for_all(self):
        for classification in self.CLASSIFICATORS:
            classifier = classification['classifier']
            classifier.fit(self.X_train, self.Y_train)
            Y_predict = classifier.predict(self.X_test)
            matrix = confusion_matrix(self.Y_test, Y_predict)
            results = {
                'Accuracy': self.accuracy(matrix),
                'Precision': self.precision(matrix),
                'Recall': self.recall(matrix),
                'F1': self.f1(matrix),
            }
            self.results[classification['name']] = results

    def summary(self):
        print('---- Classification Summary ----')
        for classification, result in self.results.items():
            print(f'---- {classification} ----')
            for name, value in result.items():
                print(f'{name}: {value}')
