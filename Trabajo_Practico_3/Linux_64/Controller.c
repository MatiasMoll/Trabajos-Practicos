#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Get.h"
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"
#define MIN_CHAR_NAME 5
#define MAX_CHAR_NAME 20
#define REINTENTOS 2
#define MIN_SUELDO 10000
#define MAX_SUELDO 100000
#define MIN_HOUR 10
#define MAX_HOUR 500
///----------------------------------------------------------------------------------------------------------------------------
/** \brief Recorre la linkedList pasada y devuelve el id maximo.
 *
 * \param pArrayListEmployee LinkedList* Puntero a la linkedList a analizar
 * \return idMax como int
 *
 */
int findMaxId(LinkedList* pArrayListEmployee)
{
    int idMax=0;
    int idAux;
    Employee* pAux;
    for(int i=0; i<ll_len(pArrayListEmployee); i++)
    {
        pAux = ll_get(pArrayListEmployee,i);
        if(pAux != NULL)
        {
            employee_getId(pAux,&idAux);
            if(idAux>idMax)
            {
                idMax = idAux;
            }
        }
    }
    return idMax;
}
/** \brief Devuelve la posicion del id que le pasan como parametro, si no lo logra retorna -1
 *
 * \param pArrayListEmployee LinkedList* Recibe puntero a la LinkedList a analizar
 * \param idABuscar int Recibe id a buscar en la LinkedList
 * \return retorno int [-1]Si pArrayListEmployee es NULL o si el id a buscar es menor a 0
                        [i] posicion donde encontro el id solicitado
 *
 */
int findId(LinkedList* pArrayListEmployee, int idABuscar)
{
    int retorno = -1;
    int idAux;
    Employee* pAux = NULL;
    if(pArrayListEmployee != NULL && idABuscar >=0)
    {
        for(int i=0;i<=ll_len(pArrayListEmployee);i++)
        {
            pAux=ll_get(pArrayListEmployee,i);
            if(pAux!= NULL)
            {
                employee_getId(pAux,&idAux);
                if(idAux == idABuscar)
                {
                    retorno = i;
                }
            }
        }
    }
    return retorno;
}
///------------------------------------------------------------------------------------------------------------------------------
/** \brief Listar empleados contnidos en la pArrayListEmployee
 *
 * \param pArrayListEmployee LinkedList* LinkedList a analizar
 * \return int retorno [-1] Si la linkedList es NULL o
                        [0] Si salio todo ok
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    Employee* pAuxEmp;
    int idA;
    char nombreA[MAX_CHAR_NAME];
    int horasA;
    int sueldoA;
    if(pArrayListEmployee != NULL)
    {
        for(int i=0; i<ll_len(pArrayListEmployee); i++)
        {
            pAuxEmp = ll_get(pArrayListEmployee,i);
            if(pAuxEmp != NULL)
            {
                employee_getId(pAuxEmp,&idA);
                employee_getNombre(pAuxEmp,nombreA);
                employee_getHorasTrabajadas(pAuxEmp,&horasA);
                employee_getSueldo(pAuxEmp,&sueldoA);

                printf("Id: %d Nombre: %s Horas Trabajadas: %d Sueldo: %d\n",idA,nombreA,horasA,sueldoA);
            }
        }
        retorno = 0;
    }
    return retorno;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char* Ruta del archivo a procesar
 * \param pArrayListEmployee LinkedList* LinkedList a llenar con el archivo
 * \return int retorno [-1] Si la LinkedList es NULL o si el path es NULL o
                        [0] Si salio todo ok
 *
 */
int controller_loadFromText(char* path, LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    FILE* fAux;
    if(path != NULL && pArrayListEmployee != NULL)
    {
        fAux = fopen(path, "r");
        if(fAux != NULL)
        {
            if(!parser_EmployeeFromText(fAux,pArrayListEmployee))
            {
                retorno = 0;
            }
        }
    }
    return retorno;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char* Ruta del archivo a procesar
 * \param pArrayListEmployee LinkedList* LinkedList a llenar con el archivo
 * \return int retorno [-1] Si la LinkedList es NULL o si el path es NULL o
                        [0] Si salio todo ok
 *
 */
int controller_loadFromBinary(char* path, LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    FILE* pFile = NULL;
    if(path != NULL && pArrayListEmployee != NULL)
    {
        pFile = fopen(path, "rb");
        if(pFile != NULL && !parser_EmployeeFromBinary(pFile,pArrayListEmployee))
        {
            retorno = 0;
        }
    }
    return retorno;
}

/** \brief Alta de empleados pide los datos del Employee al usuario y en caso de ser correctos
            lo agrega a la LinkedList
 *
 * \param pArrayListEmployee LinkedList* LinkedList a cargar
 * \return int retorno [-1] Si la linkedList es NULL
                        [0] Si se puede cargar todos los campos del Employee correctamente
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    Employee* pAux;
    char nombreAux[MAX_CHAR_NAME];
    int idMax = 1;
    char idMaxAux[12];
    char horasAux[12];
    char sueldoAux[12];
    if(pArrayListEmployee != NULL)
    {
        if(!GET_Name("Ingrese nombre del empleado: ","\nNombre Invalido\n",MIN_CHAR_NAME,MAX_CHAR_NAME,REINTENTOS,nombreAux) &&
                !GET_Int("Ingrese las horas que trabajo el empleado: ","\nNumero Invalido\n",1,5,MIN_HOUR,MAX_HOUR,REINTENTOS,horasAux)&&
                !GET_Int("Ingrese el sueldo del empleado: ","\nSueldo Invalido\n",3,6,MIN_SUELDO,MAX_SUELDO,REINTENTOS,sueldoAux))
        {
            idMax = idMax + findMaxId(pArrayListEmployee);
            sprintf(idMaxAux,"%d",idMax);
            pAux = employee_newParametros(idMaxAux,nombreAux,horasAux,sueldoAux);
            if(pAux != NULL)
            {
                ll_add(pArrayListEmployee,pAux);
                retorno = 0;
            }

        }
    }
    return retorno;
}

/** \brief Modificar datos de empleado, lista los empleados, pide un id a modificar, mostrando un submenu
            dando posibilidad a cambiar tanto nombre, horas trabajadas o sueldo del empleado
 *
 * \param pArrayListEmployee LinkedList* LinkedList donde estan contenidos los empleados
 * \return int retorno [-1] Si la LinkedList es NULL
                        [0] Si se lograron hacer las modificaciones correctamente
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    Employee* pAux;
    int opcion;
    int posId;
    int idMax=1;
    int idAux;
    char bufferName[4096];
    int bufferHoras;
    int bufferSueldo;
    if(pArrayListEmployee != NULL)
    {
        controller_ListEmployee(pArrayListEmployee);
        idMax+=findMaxId(pArrayListEmployee);
        if(!GET_Edad("Ingrese el ID del empleado a modificar: ","ID Invalido.\n",0,idMax,REINTENTOS,&idAux))
        {
            posId = findId(pArrayListEmployee,idAux);
            if(posId != -1)
            {
                pAux = ll_get(pArrayListEmployee,posId);
                do{
                    printf("\n1)Modificar Nombre\n2)Modificar Horas trabajadas\n3)Modificar Sueldo\n4)Salir\n");
                    GET_Edad("Ingrese la opcion: ","",0,5,REINTENTOS,&opcion);
                    switch(opcion)
                    {
                        case 1:
                            if(!GET_Name("\nIngrese el nuevo nombre: ","\nNombre invalido\n",MIN_CHAR_NAME,MAX_CHAR_NAME,REINTENTOS,bufferName))
                            {
                                if(!employee_setNombre(pAux,bufferName))
                                {
                                    printf("\nNombre modificado exitosamente");
                                }
                            }
                            break;
                        case 2:
                            if(!GET_Edad("\nIngrese horas trabajadas: ","Horas invalida\n",MIN_HOUR,MAX_HOUR,REINTENTOS,&bufferHoras))
                            {
                                if(!employee_setHorasTrabajadas(pAux,bufferHoras))
                                {
                                    printf("\nHoras modificadas exitosamente");
                                }
                            }
                            break;
                        case 3:
                            if(!GET_Edad("\nIngrese el nuevo sueldo: ","\nSueldo Invalido\n",MIN_SUELDO,MAX_SUELDO,REINTENTOS,&bufferSueldo))
                            {
                                if(!employee_setSueldo(pAux,bufferSueldo))
                                {
                                    printf("\nSueldo modificado exitosamente");
                                }
                            }
                            break;
                        default:
                            printf("Opcion Incorrecta\n");
                    }
                }while(opcion!=4);
            retorno = 0;
            }else
                {
                    printf("ID no encontrado.");
                }
        }
    }
    return retorno;
}

/** \brief Baja de empleado, muestra la lista de empleados de la LinkedList, pide el ID del empleado
            a remover (La baja es fisica, tanto del empleado, como del nodo que lo contenia)
 *
 * \param pArrayListEmployee LinkedList* LinkedList que contiene a los empleados
 * \return int retorno[-1] Si la LinkedList es NULL
                        [0] Si la baja es exitosa
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
    Employee* pAux;
    int retorno = -1;
    int posId=-1;
    int idMax=1;
    int idAux;
    if(pArrayListEmployee != NULL)
    {
        controller_ListEmployee(pArrayListEmployee);
        idMax += findMaxId(pArrayListEmployee);
        if(!GET_Edad("Ingrese el ID a borrar: ","ID Invalido",0,idMax,REINTENTOS,&idAux))
        {
            posId = findId(pArrayListEmployee,idAux);
            if(posId != -1)
            {
                pAux=ll_pop(pArrayListEmployee,posId);
                if(pAux!=NULL)
                {
                    employee_delete(pAux);
                    printf("Empleado eliminado correctamente");
                    retorno = 0;
                }
            }
        }
    }
    return retorno;
}



/** \brief Ordenar empleados de la LinkedList mediante una funcion criterio
 *
 * \param pArrayListEmployee LinkedList* LinkedList a ordenar
 * \return int retorno [-1] Si la LinkedList es NULL
                        [0] Si el ordenamiento es exitoso
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    if(pArrayListEmployee != NULL)
    {
        if(!ll_sort(pArrayListEmployee,employee_compararNombre,1))
        {
            retorno = 0;
        }

    }
    return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char* La ruta del archivo que queremos escribir
 * \param pArrayListEmployee LinkedList* LinkedList con la que vamos a llenar el path
 * \return int retorno [-1] Si el path es NULL o si la LinkedList es NULL
                        [0] Si la carga es exitosa
 *
 */
int controller_saveAsText(char* path, LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    int i;
    char nombre[MAX_CHAR_NAME];
    int id;
    int horas;
    int sueldo;
    FILE* pFileAux;
    Employee* pEmpAux;
    if(path!= NULL && pArrayListEmployee != NULL)
    {
        pFileAux = fopen(path,"w");
        if(pFileAux != NULL)
        {
            for(i=0;i<ll_len(pArrayListEmployee);i++)
            {
                pEmpAux = ll_get(pArrayListEmployee,i);
                if(pEmpAux != NULL && !employee_getId(pEmpAux,&id) && !employee_getNombre(pEmpAux,nombre)&&
                    !employee_getHorasTrabajadas(pEmpAux,&horas)&&!employee_getSueldo(pEmpAux,&sueldo))
                {

                    fprintf(pFileAux,"%d,%s,%d,%d\n",id,nombre,horas,sueldo);
                }else
                    {
                        employee_delete(pEmpAux);
                    }
            }
            retorno = 0;
            fclose(pFileAux);
        }
    }
    return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char* La ruta del archivo que queremos escribir
 * \param pArrayListEmployee LinkedList* LinkedList con la que vamos a llenar el path
 * \return int retorno [-1] Si el path es NULL o si la LinkedList es NULL
                        [0] Si la carga es exitosa
 *
 */
int controller_saveAsBinary(char* path, LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    FILE *pFile = NULL;
    Employee* pAux = NULL;
    int i;
    if(path!=NULL && pArrayListEmployee != NULL)
    {
        pFile = fopen(path, "wb");
        if(pFile != NULL)
        {
            for(i=0;i<ll_len(pArrayListEmployee);i++)
            {
                pAux = ll_get(pArrayListEmployee,i);
                fwrite(pAux,sizeof(Employee),1,pFile);
                retorno = 0;
            }


        }
    }
    return retorno;
}
