import numpy as np
import matplotlib.pyplot as plt
def unit_step(a, n):
    unit =[]
    for sample in n:
        if sample<a:
            unit.append(0)
        else:
            unit.append(1)
    return(unit)
a = 3
UL = 11
LL = -10
n = np.arange(LL, UL, 1)
unit = unit_step(a, n)
plt.stem(n, unit)
plt.xlabel('n')
plt.xticks(np.arange(LL, UL, 1))
plt.yticks([0, 1])
plt.ylabel('u[n]')
plt.title('Unit step u[n-a]')
plt.savefig('UnitStep.png')