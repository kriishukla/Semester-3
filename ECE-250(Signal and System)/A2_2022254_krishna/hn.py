import numpy as np
import matplotlib.pyplot as plt

# Define the value of alpha
alpha = float(input("Enter the value of alpha: "))

def signal(n):
    unit = []
    for sample in n:
        if sample < 0 or sample > 6:
            unit.append(0)
        else:
            unit.append(alpha ** sample)
    return unit

UL = 11
LL = -10
n = np.arange(LL, UL, 1)
unit = signal(n)

plt.stem(n, unit)
plt.xlabel('n')
plt.xticks(np.arange(LL, UL, 1))
plt.ylabel('x[n]')
plt.title('Signal of x[n]')

# Set y-axis limits to ensure both 0 and 1 are displayed
plt.ylim([1, alpha**6+alpha**6])

plt.savefig('Signal.png')
plt.show()
