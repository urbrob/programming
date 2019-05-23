import pandas as pd
from sklearn.feature_extraction.text import CountVectorizer
from classifier_comparer import ClassificationComparer

dataset = pd.read_csv('Restaurant_reviews.tsv', delimiter='\t', quoting=3)
cv = CountVectorizer()
X = cv.fit_transform(dataset['Review']).toarray()
y = dataset['Liked']

comparer = ClassificationComparer(X, y)
comparer.fit_for_all()
comparer.summary()
