int calculadora()
{
    float numeroUno;
    float numeroDos;
    int eleccion;

    ingresoOperandos(&numeroUno, &numeroDos);
    menuOperacion(numeroUno, numeroDos,&eleccion);//Elige la opcion deseada, y se la pasa al switch como parametro
    operaciones(numeroUno, numeroDos, eleccion);
    return 0;
}
int ingresoOperandos(float *numeroUno, float *numeroDos)
{
    float primerNumero;
    float segundoNumero;

    printf("Ingrese el primer operando: ");
    scanf("%f",&primerNumero);
    printf("Ingrese el segundo operando: ");
    scanf("%f",&segundoNumero);

    *numeroUno = primerNumero;
    *numeroDos = segundoNumero;

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
    printf("5-FACTORIAL DEL PRIMER NUMERO.(%.2f!)\n", numeroUno);
    printf("6-REALIZAR TODAS LAS OPERACIONES ANTERIORES \n", numeroUno);
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
int factorial(int numeroUno)
{
    int retorno=-1;
    long resultado;
    if(numeroUno<0)
    {
        printf("No se puede calcular el factorial de un numero negativo \n");
    }else
         {
             if(numeroUno==0)
             {
                 resultado = 1;
                 retorno = 0;
             }else
                {
                    int aux = numeroUno;
                    resultado = numeroUno;
                    do{
                        aux --;
                        resultado*=aux;
                    }while(aux>1);
                    retorno = 0;
                }
        printf("El factorial de %d es %ld", numeroUno, resultado);
        }
    return retorno;
}



