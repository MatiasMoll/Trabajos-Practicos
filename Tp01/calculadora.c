#include <stdio.h>
#include <stdlib.h>
#include "calculadora.h"

int calculadora()
{
    float numeroUno;
    float numeroDos;
    int eleccionUsuario;
    int eleccion;
    do{
        ingresoOperandos(&numeroUno, &numeroDos);
        menuOperacion(numeroUno, numeroDos,&eleccion);//Elige la opcion deseada, y se la pasa al switch como parametro
        operaciones(numeroUno, numeroDos, eleccion);
        printf("\n Desea continuar operando (Debera ingresar nuevamente los numeros)? \n 1-SI \n 2-NO ");
        scanf("%d",&eleccionUsuario);
    }while(eleccionUsuario == 1);
    return 0;
}
int ingresoOperandos(float *numeroUno, float *numeroDos)
{
    float primerNumero;
    float segundoNumero;

    if(numeroUno != NULL && numeroDos != NULL)
    {
        printf("Ingrese el primer operando: ");
        scanf("%f",&primerNumero);
        printf("Ingrese el segundo operando: ");
        scanf("%f",&segundoNumero);

        *numeroUno = primerNumero;
        *numeroDos = segundoNumero;
    }else
        {
            printf("ERROR, ingrese un numero");
        }



    return 0;
}

int menuOperacion(float numeroUno, float numeroDos, int *eleccion)
{
    int operacionElegida;

    printf("Elija la operacion a realizar: \n");
    printf("1-SUMA.(%.2f + %.2f)\n", numeroUno, numeroDos);
    printf("2-RESTA.(%.2f - %.2f)\n", numeroUno, numeroDos);
    printf("3-MULTIPLICACION.(%.2f * %.2f)\n", numeroUno, numeroDos);
    printf("4-DIVISION.(%.2f / %.2f)\n", numeroUno, numeroDos);
    printf("5-FACTORIAL DEL PRIMER NUMERO.(%.2f!)(PRESICION ASEGURADA CON NUMEROS MENORES A 13)\n", numeroUno);
    printf("6-REALIZAR TODAS LAS OPERACIONES ANTERIORES \n");
    printf("7-SALIR \n");

    scanf("%d",&operacionElegida);
    *eleccion=operacionElegida;

    return 0;
}

int operaciones(float numeroUno, float numeroDos, int eleccion)
{
    switch(eleccion)
    {
        case 1:
            suma(numeroUno, numeroDos);
            break;
        case 2:
            resta(numeroUno, numeroDos);
            break;
        case 3:
            multiplicacion(numeroUno, numeroDos);
            break;
        case 4:
            division(numeroUno, numeroDos);
            break;
        case 5:
            factorial(numeroUno);
            break;
        case 6:
            suma(numeroUno, numeroDos);
            resta(numeroUno, numeroDos);
            multiplicacion(numeroUno, numeroDos);
            division(numeroUno, numeroDos);
            factorial(numeroUno);
            break;
        case 7:
            break;
        default:
            printf("Opcion Incorrecta \n");
    }
    return 0;
}

int suma(float numeroUno, float numeroDos)
{
    float resultado;

    resultado = numeroUno + numeroDos;

    printf("El resultado de la suma es: %.2f \n", resultado);
    return 0;
}

int resta (float numeroUno,float numeroDos)
{
    float resultado;

    resultado = numeroUno-numeroDos;

    printf("El resultado de la resta es: %.2f \n", resultado);
    return 0;
}

int multiplicacion(float numeroUno,float numeroDos)
{
    float resultado;

    resultado = numeroUno*numeroDos;

    printf("El resultado de la multiplicacion es: %.2f \n", resultado);

    return 0;
}

int division(float numeroUno, float numeroDos)
{
    int retorno=-1;
    float resultado;
    if(numeroDos != 0)
    {
        resultado = numeroUno / numeroDos;
        retorno = 0;
        printf("El resultado de la division es %.2f \n", resultado);
    }else
        {
            printf("No se puede dividir por 0 \n");
        }


     return retorno;
}
int factorial(float numeroUno)
{
    int retorno=-1;
    int numeroUnoINT=(int)numeroUno;
    long resultado;
    if(numeroUnoINT<0)
    {
        printf("No se puede calcular el factorial de un numero negativo \n");
    }else
         {
             if(numeroUnoINT==0)
             {
                 resultado = 1;
                 retorno = 0;
             }else
                {
                    int aux = numeroUnoINT;
                    resultado = numeroUnoINT;
                    do{
                        aux --;
                        resultado*=aux;
                    }while(aux>1);
                    retorno = 0;
                }
        printf("\n El factorial de %d es %ld",numeroUnoINT, resultado);
        }
    return retorno;
}



