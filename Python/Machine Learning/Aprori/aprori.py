import pandas as pd
from apyori import apriori

dataset = pd.read_csv('Market_Basket_Optimisation.csv', header=None)
transactions = dataset.values.astype('str')

# min_support -> Minimal occurances of particular value
# min_confidence -> Its minimal probality of occuring value and b_value in given record
# lift -> confidance/min_support
min_support = 3 * 7 / len(transactions)
rules = apriori(
    transactions,
    min_support=min_support,
    min_confidence=0.20,
    min_lift=3,
    min_length=2)

rules = map(lambda rule: rule[2][0], rules)
rules_sorted = sorted(rules, key=lambda rule: -rule.confidence)
for rule in rules_sorted[:5]:
    print(f'{tuple(rule.items_base)} ---> {tuple(rule.items_add)} have {rule.confidence * 100}%')
