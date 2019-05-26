import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.preprocessing import OneHotEncoder, LabelEncoder
import keras
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense
from result_comparer import ResultComparer


dataset = pd.read_csv('Churn_Modelling.csv')
X = dataset.iloc[:, 3:-1].values
Y = dataset.iloc[:, -1].values

# Remove String variables
labelencoder_X_1 = LabelEncoder()
labelencoder_X_2 = LabelEncoder()
X[:, 1] = labelencoder_X_1.fit_transform(X[:, 1])
X[:, 2] = labelencoder_X_2.fit_transform(X[:, 2])

# Split int String variables to
onehotencoder = OneHotEncoder(categorical_features = [1])
X = onehotencoder.fit_transform(X).toarray()

# Dummy variable trap
X = X[:, 1:]

x_train, x_test, y_train, y_test = train_test_split(X, Y, test_size=0.25)

# Scale all features
scaller = StandardScaler()
x_train = scaller.fit_transform(x_train)
x_test = scaller.transform(x_test)

classifier = Sequential()
classifier.add(Dense(6, activation='relu', input_dim=11))
classifier.add(Dense(6, activation='relu'))
classifier.add(Dense(1, activation='sigmoid'))
classifier.compile(optimizer='adam', loss='binary_crossentropy', metrics=['accuracy'])

classifier.fit(x_train, y_train, batch_size=10, nb_epoch=100)

y_pred = classifier.predict(x_test)
y_pred = (y_pred > 0.5)
ResultComparer(y_pred, y_test).summary()
