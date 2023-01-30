// https://www.youtube.com/watch?v=ATXYi49eM6k 4:25
// https://www.vivaolinux.com.br/artigo/Manipulacao-de-imagens-no-formato-PPM?pagina=2
// https://www.youtube.com/watch?v=UTFw9SY42bY
#include <iostream>
using namespace std;
#include "IMAGEM.hpp"
#include <string>
#include <sstream>
#include <cstring>
#include "msgassert.h"
void Img_ppm::ler_ppm(string nome)
{

  fstream file(nome, ios::in);
  erroAssert(file, "Arquivo não existe"); // verifica se o arquivo exite

  this->id = 0;

  string linha;
  string tipo;

  getline(file, linha); // leitura do tipo de arquivo
  this->tipo = linha;   // armazenamento do tipo de arquivo

  getline(file, linha); // leitura da altura e da largura da imagem
  stringstream s(linha);
  s >> this->width >> this->height; // armazena as dimensões da imagem

  getline(file, linha); // leitura do valor máximo por pixel
  stringstream max(linha);
  max >> this->max; // armazenamento do valor máximo por pixel

  this->inicializaMatriz();

  for (int k = 0; k < this->height; k++)
  {
    getline(file, linha); // leitura dos pixels da imagem
    stringstream px(linha);
    for (int l = 0; l < this->width * 3; l++)
    {
      px >> this->pixels[k][l]; // armazenamento dos pixels
      ESCREVEMEMLOG((long int)&(this->pixels[k][l]), sizeof(int), this->id);
    }
  }

  file.close();
}
void Img_ppm::inicializaMatriz()
{ // aloca o espaço de memoria necessátio para armazenar a imagem

  this->pixels = new int *[this->height];
  if (this->height)
  {
    for (int k = 0; k < this->height; k++)
    {
      this->pixels[k] = new int[this->width * 3];
    }
  }

  for (int l = 0; l < this->height; l++)
  {
    for (int m = 0; m < this->width * 3; m++)
    {
      this->pixels[l][m] = 0; // preenche a matriz com 0's
      ESCREVEMEMLOG((long int)&(this->pixels[l][m]), sizeof(int), this->id);
    }
  }
}

int Img_ppm::getWidth()
{
  return this->width;
}

int Img_ppm::getHeight()
{
  return this->height;
}

int **Img_ppm::getPx()
{
  return this->pixels;
}

int Img_ppm::getMax()
{
  return this->max;
}

int Img_ppm::getId()
{
  return this->id;
}

void Img_ppm::desalocaMatriz()
{ // libera o espaço de memória utilizado pela matriz
  if (this->pixels != nullptr)
  {
    for (int i = 0; i < this->height; i++)
    {
      delete[] this->pixels[i];
    }
    delete this->pixels;
  }
}

void Img_pgm::gerar_pgm(Img_ppm *entrada)
{

  this->tipo = "P2";
  this->width = entrada->getWidth();
  this->height = entrada->getHeight();
  this->max = 49;
  this->id = 1;

  this->inicializaMatriz();

  int **temp = entrada->getPx(); // inicia variável utilizada para facilitar a leitura dos pixel da imagem ppm

  for (int i = 0; i < this->height; i++)
  {
    int aux = 0;
    for (int j = 0; j < this->width * 3; j += 3)
    {
      float R = ((temp[i][j] * 0.30) + (temp[i][j + 1] * 0.59) + (temp[i][j + 2] * 0.11)) * 49 / 255; // converte o RGB em um pixel preto e branco
      this->pixels[i][aux] = (int)R;
      aux++;

      LEMEMLOG((long int)&(temp[i][j]), sizeof(int), entrada->getId());
      LEMEMLOG((long int)&(temp[i][j + 1]), sizeof(int), entrada->getId());
      LEMEMLOG((long int)&(temp[i][j + 2]), sizeof(int), entrada->getId());

      ESCREVEMEMLOG((long int)&(this->pixels[i][aux]), sizeof(int), this->id);
    }
  }
}

void Img_pgm::inicializaMatriz()
{ // aloca o espaço de memoria necessátio para armazenar a imagem

  this->pixels = new int *[this->height];
  if (this->height)
  {
    for (int k = 0; k < this->height; k++)
    {
      this->pixels[k] = new int[this->width];
    }
  }
  for (int l = 0; l < this->height; l++)
  {
    for (int m = 0; m < this->width; m++)
    {
      this->pixels[l][m] = 0;
      ESCREVEMEMLOG((long int)&(this->pixels[l][m]), sizeof(int), this->id);
    }
  }
}

void Img_pgm::imprimir_pgm(string nome)
{
  fstream myFile;
  myFile.open(nome, ios::out); // write
  if (myFile.is_open())
  {
    myFile << this->tipo << endl;

    myFile << this->width << " " << this->height << endl;

    myFile << this->max << endl;

    for (int i = 0; i < this->height; i++)
    {
      for (int j = 0; j < this->width; j++)
      {
        myFile << this->pixels[i][j] << " "; // escreve os pixels convertidos em um arquivo

        LEMEMLOG((long int)&(this->pixels[i][j]), sizeof(int), this->id);
      }
      myFile << endl;
    }
    myFile.close();
  }
}
void Img_pgm::desalocaMatriz()
{ // libera o espaço de memória utilizado pela matriz
  if (this->pixels != nullptr)
  {
    for (int i = 0; i < this->height; i++)
    {
      delete[] this->pixels[i];
    }
    delete this->pixels;
  }
}
