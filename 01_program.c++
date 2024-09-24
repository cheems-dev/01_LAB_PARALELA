#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>

void rowByRow(int MAX, std::vector<double> &tiempos)
{
  double A[MAX][MAX], x[MAX], y[MAX];
  // Inicializar A y x, y asignar y = 0
  for (int i = 0; i < MAX; ++i)
  {
    for (int j = 0; j < MAX; ++j)
    {
      A[i][j] = i + j;
    }
    x[i] = i;
    y[i] = 0;
  }

  // Medir tiempo en milisegundos para fila por fila con steady_clock
  auto start = std::chrono::steady_clock::now();

  for (int i = 0; i < MAX; ++i)
  {
    for (int j = 0; j < MAX; ++j)
    {
      y[i] += A[i][j] * x[j];
    }
  }

  auto end = std::chrono::steady_clock::now();
  std::chrono::duration<double, std::milli> elapsed = end - start; // Tiempo en milisegundos
  tiempos.push_back(elapsed.count());                              // Guardar el tiempo en milisegundos
}

void columnByColumn(int MAX, std::vector<double> &tiempos)
{
  double A[MAX][MAX], x[MAX], y[MAX];
  // Inicializar A y x, y asignar y = 0
  for (int i = 0; i < MAX; ++i)
  {
    for (int j = 0; j < MAX; ++j)
    {
      A[i][j] = i + j;
    }
    x[i] = i;
    y[i] = 0;
  }

  // Medir tiempo en milisegundos para columna por columna con steady_clock
  auto start = std::chrono::steady_clock::now();

  for (int j = 0; j < MAX; ++j)
  {
    for (int i = 0; i < MAX; ++i)
    {
      y[i] += A[i][j] * x[j];
    }
  }

  auto end = std::chrono::steady_clock::now();
  std::chrono::duration<double, std::milli> elapsed = end - start; // Tiempo en milisegundos
  tiempos.push_back(elapsed.count());                              // Guardar el tiempo en milisegundos
}

int main()
{
  std::vector<int> sizes = {25, 50, 75, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
  std::vector<double> timeRow, timeColumn;

  // Crear archivo para guardar resultados
  std::ofstream file("01_program.csv");
  file << "Tamaño_Matriz,Tiempo_Fila_ms,Tiempo_Columna_ms\n"; // Encabezados

  // Ejecutar ambos algoritmos para cada tamaño y medir el tiempo en milisegundos
  for (int size : sizes)
  {
    rowByRow(size, timeRow);
    columnByColumn(size, timeColumn);

    // Guardar resultados en el archivo
    file << size << "," << timeRow.back() << "," << timeColumn.back() << "\n";
  }

  file.close(); // Cerrar el archivo después de guardar todos los resultados

  std::cout << "Resultados guardados en 01_program.csv\n";
  return 0;
}
