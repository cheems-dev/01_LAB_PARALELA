import matplotlib.pyplot as plt
import csv

# Inicializar listas para almacenar los datos
sizes = []
classic_times = []
blocked_times = []

# Leer los datos desde el archivo CSV
with open('03_program.csv', 'r') as file:
    reader = csv.reader(file)
    next(reader)  # Saltar la primera línea (encabezados)
    for row in reader:
        sizes.append(int(row[0]))
        classic_times.append(float(row[1]))  # Tiempo de multiplicación clásica
        blocked_times.append(float(row[2]))  # Tiempo de multiplicación por bloques

# Crear gráfico lineal para multiplicación clásica
plt.plot(sizes, classic_times, label='Multiplicación Clásica', marker='o')

# Crear gráfico lineal para multiplicación por bloques
plt.plot(sizes, blocked_times, label='Multiplicación por Bloques', marker='s')

# Añadir etiquetas y título
plt.xlabel('Tamaño de la Matriz (N)')
plt.ylabel('Tiempo de Ejecución (ms)')
plt.title('Comparación del Tiempo de Ejecución de Multiplicación de Matrices')
plt.legend()

# Configurar el gráfico
plt.grid(True)

# Guardar el gráfico como archivo
plt.savefig('03_grafico_tiempos.png')
plt.close()  # Cerrar la figura
