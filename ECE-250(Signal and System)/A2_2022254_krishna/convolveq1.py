import matplotlib.pyplot as plt
import numpy as np
# Define the time axis
n = range(0, 10)

# Define the unit step function u[n]
def unit_step(n):
    return [1 if sample >= 0 else 0 for sample in n]

# Generate the signals u[n-3] and 0.8^n * u[n-2]
signal1 = unit_step([n_i - 3 for n_i in n])
signal2 = [0.8**n_i if n_i >= 2 else 0 for n_i in n]

# Initialize an empty list to store the convolution result
convolution_result = []

# Lengths of the two signals
len_signal1 = len(signal1)
len_signal2 = len(signal2)

# Perform convolution using a for loop
for n_index in range(len_signal1 + len_signal2 - 1):
    result_n = 0  # Initialize the convolution result at index n_index

    for k in range(len_signal1):
        if n_index - k >= 0 and n_index - k < len_signal2:
            result_n += signal1[k] * signal2[n_index - k]

    convolution_result.append(result_n)

import numpy as np
import matplotlib.pyplot as plt

# Define the range for n
n = np.arange(0, 20)

# Create the u[n-3] signal
u_n_minus_3 = np.where(n >= 3, 1, 0)

# Create the 0.8^n * u[n-2] signal
u_n_minus_2 = np.where(n >= 2, 0.8**n, 0)

# Calculate the convolution of u[n-3] and 0.8^n * u[n-2]
convolution_result = np.convolve(u_n_minus_3, u_n_minus_2, 'full')[:len(n)]

# Plot the convolution result
plt.stem(n, convolution_result, basefmt=' ', markerfmt='ro', linefmt='-r', use_line_collection=True)
plt.xlabel('n')
plt.ylabel('Convolution Result')
plt.title('Convolution of u[n-3] and 0.8^n * u[n-2]')
plt.grid(True)
plt.show()
