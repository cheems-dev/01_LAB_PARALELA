#include <iostream>
#include <chrono>
#include <fstream>

using namespace std;

void multiplyMatrices(int **A, int **B, int **C, int N)
{
  // Inicializar la matriz C
  for (int i = 0; i < N; ++i)
  {
    for (int j = 0; j < N; ++j)
    {
      C[i][j] = 0;
    }
  }

  for (int j = 0; j < N; ++j) // Columna por columna
  {
    for (int i = 0; i < N; ++i)
    {
      for (int k = 0; k < N; ++k)
      {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
}

int main()
{
  int sizes[] = {0, 20, 50, 100, 200, 500, 1000, 2000}; // Tamaños hasta 10,000
  ofstream file("02_program.csv");
  file << "Size,Time (ms)\n"; // Encabezados del CSV

  for (int N : sizes)
  {
    if (N == 0)
    {
      file << N << ",0\n"; // Tiempo de 0 para tamaño 0
      continue;
    }

    int **A = new int *[N];
    int **B = new int *[N];
    int **C = new int *[N];
    for (int i = 0; i < N; ++i)
    {
      A[i] = new int[N];
      B[i] = new int[N];
      C[i] = new int[N];
    }

    // Inicializar las matrices A y B
    for (int i = 0; i < N; ++i)
    {
      for (int j = 0; j < N; ++j)
      {
        A[i][j] = 1;
        B[i][j] = 1;
      }
    }

    // Medir el tiempo usando steady_clock
    auto start = std::chrono::steady_clock::now();
    multiplyMatrices(A, B, C, N);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start; // Tiempo en milisegundos

    file << N << "," << elapsed.count() << "\n"; // Guardar tamaño y tiempo

    // Liberar la memoria
    for (int i = 0; i < N; ++i)
    {
      delete[] A[i];
      delete[] B[i];
      delete[] C[i];
    }
    delete[] A;
    delete[] B;
    delete[] C;
  }

  file.close(); // Cerrar el archivo
  return 0;
}
