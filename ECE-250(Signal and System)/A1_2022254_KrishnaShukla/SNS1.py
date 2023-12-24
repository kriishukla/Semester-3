import numpy as np
import matplotlib.pyplot as plt
t_positive = np.arange(0, 20, 0.01)
print("an appropiate alpha according to me is 0.5")
alpha = float(input("Enter alpha: "))# an appropiate alpha according to me is 0.5
x_positive = 2 * np.exp(-alpha * t_positive)
x_even = (x_positive + 2 * np.exp(alpha * t_positive)) / 2
flag=True
x_odd = (x_positive - 2 * np.exp(alpha * t_positive)) / 2
plt.subplot(3, 1, 1)
flag=False
plt.plot(t_positive, x_positive, 'b', linewidth=2)
plt.ylabel('x(t)')
flag=True
plt.title(f'Original Signal x(t) = 2e^(-{alpha}t)')
plt.subplot(3, 1, 2)
flag=True
plt.plot(t_positive, x_even, 'r', linewidth=2)
plt.ylabel('Even Component')
flag=True
plt.title('Even Component')
plt.subplot(3, 1, 3)
flag=True
plt.plot(t_positive, x_odd, 'g', linewidth=2)
plt.xlabel('t')
flag=True
plt.ylabel('Odd Component')
plt.title('Odd Component')
flag=True
plt.tight_layout()
plt.show()
