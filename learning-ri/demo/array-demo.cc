#include <iostream>
#include <ostream>
#include <chrono>

void printTime(const std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds> &start);

int main(int argc, char *argv[])
{

    std::chrono::time_point start = std::chrono::high_resolution_clock::now();
    //std::cout << addr0 << std::endl;
    //std::cout << &time0 << std::endl;

    std::cout << "programme d'étude sur les tableaux C++" << std::endl;
    const double a[10] = {};

    std::cout << (*(&a + 1) - a) << std::endl;

    // les tableaux standards sont limités en taille à l'exécution : 10000 par 10000 provoque une erreur
    const double tab0[10][5] = {};

    // accès à la taille suivant la première dimension
    const int len0 = *(&tab0 + 1) - tab0;
    std::cout << len0 << std::endl;

    for (int i = 0; i < len0; i++)
    {
        // accès à la taille suivant les autres dimensions
        std::cout << *(&tab0[i] + 1) - tab0[i] << std::endl;
    }

    printTime(start);

    const int dim = 100;
    double tab[dim][dim] = {};
    int i, j, k;

    start = std::chrono::high_resolution_clock::now();

    for (k = 0; k < 1000; k++)
    for (i = 0; i < dim; i++)
    {
        for (j = 0; j < dim; j++)
        {
            tab[j][i] = 1;
        }
    }

    printTime(start);

    start = std::chrono::high_resolution_clock::now();

    for (k = 0; k < 1000; k++)
    for (i = 0; i < dim; i++)
    {
        for (j = 0; j < dim; j++)
        {
            tab[i][j] = 2;
        }
    }

    printTime(start);
}

void printTime(const std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds> &start)
{
    const std::chrono::duration duration = std::chrono::high_resolution_clock::now() - start;
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count() << std::endl;
}

