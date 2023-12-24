import numpy as np
import matplotlib.pyplot as plt

def unit_step(a, n):
    unit = []
    for sample in n:
        if sample < a:
            unit.append(0)
        else:
            unit.append(1)
    return unit

a = 2
UL = 11
LL = -10
n = np.arange(LL, UL, 1)
unit = unit_step(a, n)
signal = np.where(np.array(unit) == 1, (0.8)**n, 0)

plt.stem(n, signal)
plt.xlabel('n')
plt.xticks(np.arange(LL, UL, 1))
plt.ylabel('0.8^n * u[n]')
plt.title('Signal 0.8^n * u[n]')
plt.savefig('Signal.png')
plt.show()
