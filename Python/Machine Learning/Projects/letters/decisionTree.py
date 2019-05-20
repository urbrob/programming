from sklearn import tree
import numpy as np
import pandas as pd
from sklearn import metrics

# Wczytujemy nasz dataset litery
letters = pd.read_csv('letter-recognition.txt')

# Lista danych testu
training_points = np.array(letters[:19000].drop(['letter'], 1))
# Lista liter
training_labels = np.array(letters[:19000]['letter'])

# Wybieramy sposób nauki i uczymy nasz algorytm clf na podstawie 15000 danych
clf = tree.DecisionTreeClassifier()
# Tutaj uczymy
clf = clf.fit(training_points,training_labels)

# Teraz wyciągamy dane które będziemy porównywać z tym co wylosuje test
test_points = np.array(letters[19000:].drop(['letter'], 1))
test_labels = np.array(letters[19000:]['letter'])

# Kalkulujemy trafność zgadnięć
accuracy = clf.score(test_points, test_labels)
print("Średnia trafność: ", float(accuracy))


expected = test_labels
# Wyciągamy dokładniejsze dane
predicted = clf.predict(test_points)

# Wypisujemy dokładne statystyki
print(metrics.classification_report(expected, predicted))
# Precision - Okresla jaka czesc wyników wskazanych przez klasyfikator jako dodatnie jest faktycznie dodatnia
# Recall - Okresla jaka czesc dodatnich wyników wykrył klasyfikator
# F1-score - To jest tak naprawdę "środkowa" wartość między Precision a Recall
# Support - Ilość prób na daną literę
