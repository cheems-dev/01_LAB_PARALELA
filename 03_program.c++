#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>

using namespace std;

void multiplyMatricesClassic(int **A, int **B, int **C, int N)
{
  // Inicializar la matriz C
  for (int i = 0; i < N; ++i)
  {
    for (int j = 0; j < N; ++j)
    {
      C[i][j] = 0;
    }
  }

  for (int j = 0; j < N; ++j)
  { // Columna por columna
    for (int i = 0; i < N; ++i)
    {
      for (int k = 0; k < N; ++k)
      {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
}

void multiplyMatricesBlocked(int **A, int **B, int **C, int N, int blockSize)
{
  // Inicializar la matriz C
  for (int i = 0; i < N; ++i)
  {
    for (int j = 0; j < N; ++j)
    {
      C[i][j] = 0;
    }
  }

  for (int i = 0; i < N; i += blockSize)
  {
    for (int j = 0; j < N; j += blockSize)
    {
      for (int k = 0; k < N; k += blockSize)
      {
        // Multiplicación de bloques
        for (int ii = i; ii < min(i + blockSize, N); ++ii)
        {
          for (int jj = j; jj < min(j + blockSize, N); ++jj)
          {
            for (int kk = k; kk < min(k + blockSize, N); ++kk)
            {
              C[ii][jj] += A[ii][kk] * B[kk][jj];
            }
          }
        }
      }
    }
  }
}

int main()
{
  int sizes[] = {0, 10, 20, 30, 50, 100};               // Tamaños de matriz actualizados
  ofstream file("03_program.csv");                      // Nombre de archivo actualizado
  file << "Size,Classic Time (ms),Blocked Time (ms)\n"; // Encabezados del CSV

  for (int N : sizes)
  {
    if (N == 0)
    {
      file << N << ",0,0\n"; // Tiempo de 0 para tamaño 0
      continue;
    }

    int **A = new int *[N];
    int **B = new int *[N];
    int **C_classic = new int *[N];
    int **C_blocked = new int *[N];
    for (int i = 0; i < N; ++i)
    {
      A[i] = new int[N];
      B[i] = new int[N];
      C_classic[i] = new int[N];
      C_blocked[i] = new int[N];
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

    // Medir el tiempo usando steady_clock para multiplicación clásica
    auto start_classic = std::chrono::steady_clock::now();
    multiplyMatricesClassic(A, B, C_classic, N);
    auto end_classic = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> elapsed_classic = end_classic - start_classic; // Tiempo en milisegundos

    // Medir el tiempo usando steady_clock para multiplicación por bloques
    int blockSize = 64; // Puedes ajustar el tamaño del bloque según sea necesario
    auto start_blocked = std::chrono::steady_clock::now();
    multiplyMatricesBlocked(A, B, C_blocked, N, blockSize);
    auto end_blocked = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> elapsed_blocked = end_blocked - start_blocked; // Tiempo en milisegundos

    file << N << "," << elapsed_classic.count() << "," << elapsed_blocked.count() << "\n";

    // Liberar la memoria
    for (int i = 0; i < N; ++i)
    {
      delete[] A[i];
      delete[] B[i];
      delete[] C_classic[i];
      delete[] C_blocked[i];
    }
    delete[] A;
    delete[] B;
    delete[] C_classic;
    delete[] C_blocked;
  }

  file.close(); // Cerrar el archivo
  return 0;
}
