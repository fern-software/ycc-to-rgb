# Call "bin/ycc2rgb testimages/clips.jpg out.bin" 100 times to get the average execution time of ycc2rgb
import os
import time

times = []

for _ in range(100):
    start = time.time()
    os.system("bin/ycc2rgb testimages/clips.jpg out.bin")
    end = time.time()
    times.append(end - start)
    print(round(end - start, 6))

print(f"Average execution time: {round(sum(times) / len(times), 5)}s")