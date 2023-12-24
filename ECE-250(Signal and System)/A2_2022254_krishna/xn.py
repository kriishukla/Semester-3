import numpy as np
import matplotlib.pyplot as plt

def signal(n):
    unit = []
    for sample in n:
        if sample < 0 or sample > 4:
            unit.append(0)
        else:
            unit.append(1)
    return unit

UL = 11
LL = -10
n = np.arange(LL, UL, 1)
unit = signal(n)  # Use the signal function here
plt.stem(n, unit)
plt.xlabel('n')
plt.xticks(np.arange(LL, UL, 1))
plt.yticks([0, 1])
plt.ylabel('x[n]')
plt.title('Signal of x[n]')
plt.savefig('Signal.png')
plt.show()
