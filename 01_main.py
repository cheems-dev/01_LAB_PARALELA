import matplotlib.pyplot as plt
import csv

# Leer los datos desde el archivo CSV
sizes = []
tiempos_fila_ms = []
tiempos_columna_ms = []

with open('01_program.csv', 'r') as file:
    reader = csv.reader(file)
    next(reader)  # Saltar la primera línea (encabezados)
    for row in reader:
        sizes.append(int(row[0]))
        tiempos_fila_ms.append(float(row[1]))  # Cambiar a float
        tiempos_columna_ms.append(float(row[2]))  # Cambiar a float

# Crear gráfico lineal
plt.plot(sizes, tiempos_fila_ms, label='Fila por Fila (ms)', marker='o')
plt.plot(sizes, tiempos_columna_ms, label='Columna por Columna (ms)', marker='o')

# Añadir etiquetas y título
plt.xlabel('Tamaño de la Matriz (N)')
plt.ylabel('Tiempo de Ejecución (milisegundos)')
plt.title('Comparación de Algoritmos: Fila vs Columna (Tiempo en milisegundos)')
plt.legend()

# Guardar el gráfico como archivo
plt.grid(True)
plt.savefig('01_grafico_tiempos_ms.png')
plt.close()  # Cerrar la figura
