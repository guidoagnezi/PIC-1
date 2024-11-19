#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{

    int cartas[51];
    int carta;
    char comando, comandoCOM;
    int vocePassou = 0, COMpassou = 0;
    int i, j, numero = 1, naipe = 1;
    int suaMao = 0, maoCOM = 0;
    srand(time(NULL));

    for (i = 0; i < 51; i++)
    {
        cartas[i] = numero;
        naipe++;
        if (naipe > 4 && numero < 10)
        {
            numero++;
            naipe = 1;
        }
    }

    while (1)
    {

        scanf("%c", &comando);
        scanf("%*c");
        vocePassou = 0;
        COMpassou = 0;
        if (comando == 'c')
        {
            int random = rand() % 52;
            carta = cartas[random];
            suaMao += carta;

            printf("Carta comprada: %d\n", carta);
        }
        else
        {

            printf("Voce passou!\n");
            vocePassou = 1;
        }

        if (maoCOM > 21 || suaMao == 21)
        {
            printf("Voce ganhou!\n");
            break;
        }
        if (suaMao > 21 || maoCOM == 21)
        {
            printf("Voce perdeu!\n");
            break;
        }

        comandoCOM = rand() % 8;

        if (maoCOM <= 10)
        {

            carta = cartas[rand() % 52];
            maoCOM += carta;

            printf("Carta comprada pelo adversário: %d\n\n", carta);
        }

        else if (maoCOM > 10 && maoCOM <= 15)
        {

            if (comandoCOM <= 5 || suaMao > maoCOM)
            {
                carta = cartas[rand() % 52];
                maoCOM += carta;

                printf("Carta comprada pelo adversário: %d\n", carta);
            }
            else
            {
                printf("Inimigo passou\n");
                COMpassou = 1;
            }
        }
        else if (maoCOM > 15 && maoCOM <= 20)
        {

            if (comandoCOM <= 1 || suaMao > maoCOM)
            {
                carta = cartas[rand() % 52];
                maoCOM += carta;

                printf("Carta comprada pelo adversário: %d\n", carta);
            }
            else
            {

                printf("Inimigo passou\n");
                COMpassou = 1;
            }
        }

        printf("Soma da sua mao: %d\n", suaMao);
        printf("Soma da mao do adversário: %d\n", maoCOM);

        if (vocePassou && COMpassou)
        {
            printf("Todos passaram\n");
            if (abs(suaMao - 21) < abs(maoCOM - 21))
            {
                printf("Voce ganhou!\n");
            }
            else
            {
                printf("Voce perdeu!\n");
            }
            break;
        }

        if (maoCOM > 21 || suaMao == 21)
        {
            printf("Voce ganhou!\n");
            break;
        }
        if (suaMao > 21 || maoCOM == 21)
        {
            printf("Voce perdeu!\n");
            break;
        }
    }

    return 0;
}