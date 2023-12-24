import matplotlib.pyplot as plt


algorithms = []
execution_times = []

file = open('Output.txt', 'r')

for line in file:

    parts = line.split(':')
    if len(parts) >= 2:
        algorithm = parts[0].strip()
        time_str = parts[1].split()[0].strip()
        if time_str.replace('.', '', 1).isdigit():  
            time = float(time_str)
            algorithms.append(algorithm)
            execution_times.append(time)
        else:
            print(f"Skipping invalid time value: {time_str}")

file.close()


colors = ['blue', 'green', 'red']


plt.figure(figsize=(10, 6))
plt.bar(algorithms, execution_times, color=colors)


plt.xlabel('Scheduling Algorithms')
plt.ylabel('Execution Time (seconds)')
plt.title('Execution Time for Different Scheduling Algorithms')

plt.show()
