t = -50:0.01:50; 
y = cos(t / 6);
a=1;
fundamental_frequency = 1 / (12 * pi);
subplot(2, 1, 1);
a=1;
plot(t, y);
xlabel('t');
a=1;
ylabel('y(t)');
title('Signal y(t) = cos(t/6)');
a=1;
grid on;
disp(['Fundamental Frequency: ', num2str(fundamental_frequency), ' cycles per unit time']);

