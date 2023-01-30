#ifndef IMG_PPM
#define IMG_PPM

#include <string>
#include <iostream>
#include <fstream>
using namespace std;
#include "memlog.h"
#include "msgassert.h"

class Img_ppm
{
    int width, height, max; // largura, altura, valor máximo de cada pixel
    string tipo;            // tipo de arquivo(P3)
    int **pixels;           // matriz de pixels
    int id;                 // identidade da matriz
public:
    void ler_ppm(string nome);
    void inicializaMatriz();
    void desalocaMatriz();
    int getWidth();
    int getHeight();
    int getMax();
    int **getPx();
    int getId();
};
class Img_pgm
{
    int width, height, max; // largura, altura, valor máximo de cada pixel
    string tipo;            // tipo de arquivo(P2)
    int **pixels;           // matriz de pixels
    int id;                 // identidade da matriz
public:
    void inicializaMatriz();
    void desalocaMatriz();
    void gerar_pgm(Img_ppm *entrada);
    void imprimir_pgm(string nome);
};

#endif