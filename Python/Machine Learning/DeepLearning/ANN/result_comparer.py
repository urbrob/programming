from sklearn.metrics import confusion_matrix

class ResultComparer:
    def __init__(self, predict, test):
        self.matrix = confusion_matrix(test, predict)

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

    def summary(self):
        results = {
            'Accuracy': self.accuracy(self.matrix),
            'Precision': self.precision(self.matrix),
            'Recall': self.recall(self.matrix),
            'F1': self.f1(self.matrix),
        }
        print('---- Classification Summary ----')
        for name, value in results.items():
            print(f'{name}: {value}')
