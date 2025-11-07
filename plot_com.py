import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def read_data(filename):
    data = np.loadtxt(filename)
    x = np.unique(data[:,0])
    y = np.unique(data[:,1])
    X, Y = np.meshgrid(x, y)
    Z = data[:,2].reshape(len(x), len(y))
    return X, Y, Z

methods = {
    "Jacobi": "Jacobi.txt",
    "Gauss-Seidel": "Gauss_seidel.txt",
    "SOR": "output.txt"
}

for name, file in methods.items():
    X, Y, Z = read_data(file)
    
    # 3D Surface Plot
    fig = plt.figure(figsize=(8,6))
    ax = fig.add_subplot(111, projection='3d')
    ax.plot_surface(X, Y, Z, cmap='viridis')
    ax.set_title(f"{name} Method - 3D Surface")
    ax.set_xlabel("X")
    ax.set_ylabel("Y")
    ax.set_zlabel("Phi")
    plt.savefig(f"{name.lower()}_3d.png", dpi=300)
    plt.close()

    # 2D Heatmap
    plt.figure(figsize=(6,5))
    plt.imshow(Z, extent=[0,1,0,1], origin='lower', cmap='plasma')
    plt.colorbar(label='Phi')
    plt.title(f"{name} Method - Heatmap")
    plt.xlabel("X")
    plt.ylabel("Y")
    plt.savefig(f"{name.lower()}_heatmap.png", dpi=300)
    plt.close()

print("✅ All plots saved: jacobi_*.png, gs_*.png, sor_*.png")
