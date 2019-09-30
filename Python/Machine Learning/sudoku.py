from collections import Counter
from tensorflow.keras import models, layers
import numpy as np
import pandas as pd

""" SAMPLE
quizzes,solutions
004300209005009001070060043006002087190007400050083000600000105003508690042910300,864371259325849761971265843436192587198657432257483916689734125713528694542916378
040100050107003960520008000000000017000906800803050620090060543600080700250097100,346179258187523964529648371965832417472916835813754629798261543631485792254397186
600120384008459072000006005000264030070080006940003000310000050089700000502000190,695127384138459672724836915851264739273981546946573821317692458489715263562348197
497200000100400005000016098620300040300900000001072600002005870000600004530097061,497258316186439725253716498629381547375964182841572639962145873718623954534897261
"""

def number_one_hot(value):
    vektor = np.zeros((9,))
    vektor[value - 1] = 1
    return vektor


def split_dataset_rows(dataset):
    new_dataset = np.zeros((len(dataset), 2, 81), dtype=int)
    for index, _ in enumerate(dataset):
        new_dataset[index][0] = [int(char) for char in dataset[index][0]]
        new_dataset[index][1] = [int(char) for char in dataset[index][1]]
    return new_dataset

def one_hot_encoder(dataset):
    new_dataset = np.zeros((len(dataset), 9 * 9 * 9), dtype=int)
    for index, sequence in enumerate(dataset):
        for number_index, number in enumerate(sequence):
            if number != 0:
                new_dataset[index][number_index * 9 + number - 1] = 1
    return new_dataset

def get_first_missing_value(dataset):
    new_array = np.zeros((len(dataset), 9), dtype=int)
    for index, sequence in enumerate(dataset):
        for number_index, number in enumerate(sequence[0]):
            if number == 0:
                new_array[index] = number_one_hot(sequence[1][number_index])
                break
    return new_array


"""
Y = one_hot_encoder(dataset[:, 1])
"""

dataset = split_dataset_rows(np.array(pd.read_csv('sudoku.csv')))
X = one_hot_encoder(dataset[:, 0])
Y = get_first_missing_value(dataset)
x_train, x_val, x_test, y_train, y_val, y_test = X[:600000], X[600000:900000], X[900000:], Y[:600000], Y[600000:900000], Y[900000:]

# Create model
model = models.Sequential()
model.add(layers.Dense(2048, activation='relu', input_shape=(9 * 9 * 9, ))) # Relu is max(0, x)
model.add(layers.Dense(9, activation='softmax'))

# Compile
model.compile(optimizer='rmsprop', loss='categorical_crossentropy', metrics=['acc'])
history = model.fit(x_train, y_train, epochs=20, batch_size=2048, validation_data=(x_val, y_val))
import pdb; pdb.set_trace()
