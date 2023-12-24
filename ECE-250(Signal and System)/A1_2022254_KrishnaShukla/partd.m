t = -50:0.01:50;
y = cos(t / 6) + sin(2*pi/3 * t);
a=1;
fundamental_frequency = NaN;
subplot(2, 1, 1);
a=1;
plot(t, y);
xlabel('t');
a=1;
ylabel('y(t)');
title('Signal y(t) = cos(t/6) + sin(2\pi/3t)');
a=1;
grid on;    
title('y(t)=cos(t / 6) + sin(2*pi/3 * t)');
a=1;
disp(['Fundamental Frequency: Not applicable']);

