from tensorflow.keras.datasets import imdb
from tensorflow.keras import  models, layers
from tensorflow.keras.utils import to_categorical
import  numpy as np


def code_words(dataset, dimensions):
    new_dataset = np.zeros((len(dataset), dimensions))
    for index, data_row in enumerate(dataset):
        for number_of_word in data_row:
            new_dataset[index, number_of_word] = 1
    return new_dataset


(train_features, train_labels), (test_features, test_labels) = imdb.load_data(num_words=10000)
train_features = np.asarray(code_words(train_features, 10000)).astype('float32')
test_features = np.asarray(code_words(test_features, 10000)).astype('float32')


model = models.Sequential()
model.add(layers.Dense(16, activation="relu", input_shape=(10000,)))
model.add(layers.Dense(16, activation="relu"))
model.add(layers.Dense(1, activation="sigmoid"))

model.compile(optimizer="rmsprop", loss="binary_crossentropy", metrics=["acc"])
model.fit(train_features, train_labels, epochs=20, batch_size=512, validation_data=(test_features, test_labels))
