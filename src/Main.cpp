#include <iostream>
#include <stdio.h>
#include "IMAGEM.hpp"
#include <fstream>
#include <getopt.h>
#include <cstring>
using namespace std;
#include "msgassert.h"
typedef struct opt
{
    int opescolhida;
    char lognome[100];
    int regmem;
    char inFile[100];
    char outFile[100];
} opt_tipo;

void get_args(int argc, char **argv, opt_tipo *opt)
{
    // variaveis externas do getopt
    extern char *optarg;

    // variavel auxiliar
    int c;

    opt->opescolhida = 0;
    opt->regmem = 0;
    opt->lognome[0] = 0;

    while ((c = getopt(argc, argv, ":i:o:p:l")) != EOF)
    {
        switch (c)
        {
        case 'i':
            erroAssert(strlen(optarg) > 4, "Arquivo não existe, o nome do arquivo deve seguir o modelo: nome.ppm");
            erroAssert(optarg[strlen(optarg) - 3] == 'p', "o arquivo não é do tipo .ppm");
            erroAssert(optarg[strlen(optarg) - 2] == 'p', "o arquivo não é do tipo .ppm");
            erroAssert(optarg[strlen(optarg) - 1] == 'm', "o arquivo não é do tipo .ppm");
            strcpy(opt->inFile, optarg);
            break;
        case 'o':
            erroAssert(strlen(optarg) > 4, "A saída do arquivo deve seguir o modelo: nome.pgm");
            erroAssert(optarg[strlen(optarg) - 3] == 'p', "o arquivo não é do tipo .pgm");
            erroAssert(optarg[strlen(optarg) - 2] == 'g', "o arquivo não é do tipo .pgm");
            erroAssert(optarg[strlen(optarg) - 1] == 'm', "o arquivo não é do tipo .pgm");
            strcpy(opt->outFile, optarg);
            break;
        case 'p':
            strcpy(opt->lognome, optarg);
            break;
        case 'l':
            opt->regmem = 1;
            break;
        default:
            exit(1);
            break;
        }
    };
}

int main(int argc, char *argv[])
{
    opt_tipo opt;

    get_args(argc, argv, &opt);
    
    // iniciaMemLog
    iniciaMemLog(opt.lognome);

    // ativar ou nao o registro de acesso
    if (opt.regmem)
    {
        ativaMemLog();
    }
    else
    {
        desativaMemLog();
    }

    Img_ppm imagem;
    Img_pgm out;

    imagem.ler_ppm(opt.inFile);

    out.gerar_pgm(&imagem);
    out.imprimir_pgm(opt.outFile);

    imagem.desalocaMatriz();
    out.desalocaMatriz();

    finalizaMemLog();
    return 0;
}