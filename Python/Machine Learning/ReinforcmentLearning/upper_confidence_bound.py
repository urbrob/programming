import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import math
from collections import defaultdict



class UPC:
    def fit(self, dataset):
        self.dataset = dataset
        self.rows_count, self.columns_count = self.dataset.shape
        self.pick_rate_per_value = defaultdict(lambda : 0)
        self.rewards_per_value = defaultdict(lambda : 0)
        for row_index in range(self.rows_count):
            max_upper_confidance_bound_value = 0
            max_upper_confidance_bound_id = 0
            for column_index in range(self.columns_count):
                upper_confidance_bound_value = self._calculate_upper_bound(self.rewards_per_value[column_index], self.pick_rate_per_value[column_index], row_index)
                if upper_confidance_bound_value > max_upper_confidance_bound_value:
                    max_upper_confidance_bound_value = upper_confidance_bound_value
                    max_upper_confidance_bound_id = column_index
            self.pick_rate_per_value[max_upper_confidance_bound_id] += 1
            self.rewards_per_value[max_upper_confidance_bound_id] += int(dataset.values[row_index, max_upper_confidance_bound_id])


    # For formula check UCB_Algorithm_Slide
    def _calculate_upper_bound(self, rewards, selected_count, n):
        try:
            average_reward = rewards / selected_count
            delta = math.sqrt(3/2 * math.log(n + 1) / selected_count)
            return average_reward + delta
        except ZeroDivisionError: # We have to handle starting phase when we didn't select anything
            return 1e400

    def print_pick_rate(self):
        for column, value in self.pick_rate_per_value.items():
            print(f'Value {column + 1}: {value}')

    @property
    def total_value(self):
        return sum(self.rewards_per_value.values())

    def histogram(self):
        plt.plot(range(10), self.pick_rate_per_value.values())
        plt.title('Histogram of pick rate')
        plt.xlabel('Value')
        plt.ylabel('Amount of pick')
        plt.show()


if __name__ == '__main__':
    dataset = pd.read_csv('Ads_CTR_Optimisation.csv')
    upc_algo = UPC()
    upc_algo.fit(dataset)
    upc_algo.print_pick_rate()
    print(upc_algo.total_value)
    upc_algo.histogram()
