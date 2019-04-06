#include <stdio.h>
#include <stdlib.h>
#include "calculadora.h"

int calculadora()
{
    float numeroUno;
    float numeroDos;
    int eleccion;

    do{
        menuOperacion(numeroUno, numeroDos,&eleccion);
        operaciones(&numeroUno, &numeroDos, eleccion);
    }while(eleccion != 5);

    return 0;
}
//Aqui mostramos todas las opciones disponible en la funcion----------------
int menuOperacion(float numeroUno, float numeroDos,int *eleccion)
{
    int operacionElegida;

    printf("\n1-Ingrese el primer operando (%.2f)\n", numeroUno);
    printf("2-Ingrese el segundo operando (%.2f)\n", numeroDos);
    printf("3-Calcular todas las operaciones \n");
    printf("4-Mostrar todos los resultados \n");
    printf("5-SALIR \n");
    printf("Elija la opcion deseada: ");
    scanf("%d",&operacionElegida);
    *eleccion=operacionElegida;

    return 0;
}
//--------------------------------------------------------------------------
//Aqui haremos las operaciones de (SUMA,RESTA,MULTIPLICACION,DIVISION Y FACTORIAL DE AMBOS)-------------
//El primer y segundo numero se pasan por referencia, ya que  deben guardarse en una variable del scope de las funciones MenuOperacion y Calculadora
//para luego mostrarse en el menu de manera correcta.
int operaciones(float *primerNumero, float *segundoNumero,int eleccion)
{
    float numeroUno;
    float numeroDos;

    switch(eleccion)
    {
        case 1:
            printf("Ingrese el primer operando: ");
            scanf("%f",&numeroUno);
            *primerNumero = numeroUno;
            break;
        case 2:
            printf("Ingrese el segundo operando: ");
            scanf("%f",&numeroDos);
            *segundoNumero = numeroDos;
            break;
        case 3:
            printf(". Cacular la suma (%.2f + %.2f) \n", *primerNumero, *segundoNumero);
            printf(". Cacular la resta (%.2f - %.2f)\n", *primerNumero, *segundoNumero);
            printf(". Cacular la multiplicacion (%.2f * %.2f)\n", *primerNumero, *segundoNumero);
            printf(". Cacular la division(%.2f / %.2f)\n", *primerNumero, *segundoNumero);
            printf(". Cacular el factorial de (%.2f!)\n", *primerNumero);
            printf(". Cacular el factorial de (%.2f!)\n\n", *segundoNumero);
            break;
        case 4:
            suma(*primerNumero, *segundoNumero);
            resta(*primerNumero, *segundoNumero);
            multiplicacion(*primerNumero, *segundoNumero);
            division(*primerNumero, *segundoNumero);
            factorial(*primerNumero);
            factorial(*segundoNumero);
            break;
        case 5:
            break;
        default:
            printf("Opcion Incorrecta \n");//EN caso de que el usuario apriete otro boton, dara error.
    }
    return 0;
}
//----------------------------------------------------------------------------------------------------
//Aqui estan todas las funciones de operacion de los numeros ingresadoa anteriormente-----------------
int suma(float numeroUno, float numeroDos)
{
    float resultado;

    resultado = numeroUno + numeroDos;
    printf("El resultado de la suma es : %.2f \n", resultado);

    return 0;
}
//------------------------------------------------------------------------------------------------------
int resta (float numeroUno,float numeroDos)
{
    float resultado;

    resultado = numeroUno - numeroDos;
    printf("El resultado de la suma es : %.2f \n", resultado);

    return 0;
}
//------------------------------------------------------------------------------------------------------
int multiplicacion(float numeroUno,float numeroDos)
{
    float resultado;
    resultado = numeroUno*numeroDos;
    printf("El resultado de la multiplicaion es: %.2f\n", resultado);
    return 0;
}
//------------------------------------------------------------------------------------------------------
int division(float numeroUno, float numeroDos)
{
    int retorno=-1;
    float resultado;
    if(numeroDos != 0)//Obviamente NO se puede hacer la division si el DENOMIDADOR sea 0.
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
//------------------------------------------------------------------------------------------------------+
//Tener en cuenta que con el tipo de dato long, la factorizacion de numeros mayores a 13 van a dar numeros incorrectos.
//Cualquier numero ingresado menor o igual a 12, sera calculado correctamente
int factorial(float numeroUno)
{
    int retorno=-1;
    int numeroUnoINT=(int)numeroUno;//Se CASTEA a INT ya que no se puede hacer factorial de numero con
    long resultado;
    if(numeroUnoINT<0)//Este if, es porque no se puede hacer un factorial de numeros negativos.
    {
        printf("No se puede calcular el factorial de un numero negativo \n");//Aqui muestra el error.
    }else
         {
             if(numeroUnoINT==0)
             {
                 resultado = 1;//Por definicion el factorial de 0 es 1.
                 retorno = 0;
             }else//Si el numero es mayor a 0, hace las operaciones pertinentes.
                {
                    int aux = numeroUnoINT;//Se copia el numero a un aux, asi se puede decrementar
                                            //para luego mostrar el numero ingresado
                    resultado = numeroUnoINT;//Se copia el numero ingresado, para multiplicar directamente en resultado.
                    do{
                        aux --;
                        resultado*=aux;//Aca se hacen las multiplicaciones en decrimento.
                    }while(aux>1);
                    retorno = 0;
                }
        printf("El factorial de %d es %ld \n \n",numeroUnoINT, resultado);//Aqui se muestra el resultado pertinente
        }
    return retorno;
}
//-------------------------------------------------------------------------------------------------


