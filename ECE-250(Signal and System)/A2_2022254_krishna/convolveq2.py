import matplotlib.pyplot as plt
import numpy as np

# Input for alpha (a)
a = float(input("Enter the value of alpha (a): "))

# Define the time axis
n = np.arange(0, 10)

# Define the first signal a^n (0 <= n <= 4)
signal1 = [a**n_i if 0 <= n_i <= 6 else 0 for n_i in n]

# Define the second signal (1 for 0 <= n <= 4)
signal2 = [1 if 0 <= n_i <= 4 else 0 for n_i in n]

# Perform convolution
convolution_result = np.convolve(signal1, signal2, mode='full')

# Plot the convolution result
plt.stem(range(len(convolution_result)), convolution_result, basefmt=' ', markerfmt='ro', linefmt='-r', use_line_collection=True)
plt.xlabel('n')
plt.ylabel('Convolution Result')
plt.title(f'Convolution of {a}^n and 1')
plt.grid(True)
plt.show()
