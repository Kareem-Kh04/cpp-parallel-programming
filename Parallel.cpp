
#include <iostream>
#include <pthread.h>
using namespace std;

const int MATRIX_SIZE = 10;
const int VECTOR_SIZE = 10;

int matrix[MATRIX_SIZE][MATRIX_SIZE] = {
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
    {11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
    {21, 22, 23, 24, 25, 26, 27, 28, 29, 30},
    {31, 32, 33, 34, 35, 36, 37, 38, 39, 40},
    {41, 42, 43, 44, 45, 46, 47, 48, 49, 50},
    {51, 52, 53, 54, 55, 56, 57, 58, 59, 60},
    {61, 62, 63, 64, 65, 66, 67, 68, 69, 70},
    {71, 72, 73, 74, 75, 76, 77, 78, 79, 80},
    {81, 82, 83, 84, 85, 86, 87, 88, 89, 90},
    {91, 92, 93, 94, 95, 96, 97, 98, 99, 100}};

int vector1[VECTOR_SIZE] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

int result[VECTOR_SIZE] = {0};

// Structure to pass row number to each thread
struct ThreadData
{
    int row;
};

// Function executed by each thread
void *multiply(void *arg)
{
    ThreadData *data = (ThreadData *)arg;

    int i = data->row;

    for (int j = 0; j < VECTOR_SIZE; ++j)
    {
        result[i] += matrix[i][j] * vector1[j];
    }

    return NULL;
}

int main()
{
    pthread_t threads[MATRIX_SIZE];
    ThreadData data[MATRIX_SIZE];

    // Create threads
    for (int i = 0; i < MATRIX_SIZE; ++i)
    {
        data[i].row = i;

        pthread_create(&threads[i], NULL, multiply, &data[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < MATRIX_SIZE; ++i)
    {
        pthread_join(threads[i], NULL);
    }

    // Print result
    cout << "Result Vector :" << endl;

    for (int i = 0; i < MATRIX_SIZE; ++i)
    {
        cout << result[i] << endl;
    }

    cout << endl;

    return 0;
}
