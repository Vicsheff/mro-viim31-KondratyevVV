import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Инициализируем словарь для хранения точек данных, сгруппированных по размерности
data_by_dim = {}

# Читаем координаты из файла
with open('vectors.txt', 'r') as file:
    for line in file:
        # Удаляем начальные и конечные пробелы и пропускаем пустые строки
        line = line.strip()
        if not line:
            continue
        # Парсим координаты в строке
        coords = [float(num) for num in line.split()]
        dim = len(coords)   # Определяем размерность
        # Добавляем координаты в соответствующую группу размерности
        data_by_dim.setdefault(dim, []).append(coords)

# Строим точки данных для каждой размерности
for dim, points in data_by_dim.items():
    if dim == 2:
        x_vals, y_vals = zip(*points)
        plt.figure()
        plt.scatter(x_vals, y_vals)
        plt.title(f'2D Scatter Plot')
        plt.xlabel('X')
        plt.ylabel('Y')
        plt.grid(True)
        plt.show()
    elif dim == 3:
        x_vals, y_vals, z_vals = zip(*points)
        fig = plt.figure()
        ax = fig.add_subplot(111, projection='3d')
        ax.scatter(x_vals, y_vals, z_vals)
        plt.title('3D Scatter Plot')
        ax.set_xlabel('X')
        ax.set_ylabel('Y')
        ax.set_zlabel('Z')
        plt.show()
    else:
        print(f'Cannot plot data with dimension {dim}')
