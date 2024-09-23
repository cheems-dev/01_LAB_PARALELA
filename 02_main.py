import matplotlib.pyplot as plt
import csv

# Leer los datos desde el archivo CSV
sizes = []
tiempos_s = []

with open('02_program.csv', 'r') as file:
    reader = csv.reader(file)
    next(reader)  # Saltar la primera línea (encabezados)
    for row in reader:
        sizes.append(int(row[0]))
        tiempos_s.append(float(row[1]))  # Tiempo ya en milisegundos

# Crear gráfico lineal
plt.plot(sizes, tiempos_s, label='Tiempo de Ejecución (ms)', marker='o')

# Añadir etiquetas y título
plt.xlabel('Tamaño de la Matriz (N)')
plt.ylabel('Tiempo de Ejecución (ms)')
plt.title('Tiempo de Ejecución de Multiplicación de Matrices')
plt.legend()

# Guardar el gráfico como archivo
plt.grid(True)
plt.savefig('02_grafico_tiempos_s.png')
plt.close()  # Cerrar la figura
