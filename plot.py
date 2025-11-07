import numpy as np
import matplotlib.pyplot as plt

# Load data from file
phi = np.loadtxt("output.txt")

plt.figure(figsize=(6,5))
cp = plt.imshow(phi, cmap='plasma', origin='lower')
plt.colorbar(label='Potential (phi)')
plt.title("2D Poisson Equation – SOR Method")
plt.xlabel("X direction (grid)")
plt.ylabel("Y direction (grid)")
plt.show()
