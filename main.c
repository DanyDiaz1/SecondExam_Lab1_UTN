#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pila.h"

typedef struct
{
    char titulo[50];
    char genero[50];
    int ISBN;
    int cantidaddepaginas;
} stLibro;

int generarCodigo ();
stLibro cargarUnLibro ();
int cargarMuchosLibros (stLibro muchosLibros [],int dim);
int buscarXISBN (stLibro muchosLibros [],int validos,int ISBNRecibido);
void mostrarUnArchivo (char genero[]);
int devolverISBNMayor (char genero[]);
int ISBNMayor=0;

int main()
{
    int opcion=0;

    stLibro arregloLibros[50];
    int validos=0;
    int ISBN;
    int flag=0;
    char genero[20];

    do
    {
        printf("Ingrese la operacion que quiere realizar:\n\n");
        printf("1-Cargar un libro\n");
        printf("2-Buscar libro por ISBN\n");
        printf("3-Guardar en varios archivos x genero\n");
        printf("4-Ver archivos de Libros\n");
        printf("5-Mostrar el ISBN del libro con mayor cantidad de paginas\n");

        scanf("%i",&opcion);

        switch(opcion)
        {
        case 1:

            validos=cargarMuchosLibros(arregloLibros,100);

            for(int i=0 ; i<validos ; i++)
            {
                mostrarDatosDelLibro(arregloLibros[i]);
                sleep(1);
            }

            break;

        case 2:

            printf("Ingrese un ISBN: ");
            scanf("%i",&ISBN);

            flag=buscarXISBN(arregloLibros,validos,ISBN);
            if(flag==1)
            {
                printf("El libro se encuentra en el arreglo\n");
            }
            else
            {
                printf("El libro no se encuentra en el arreglo\n");
            }

            break;

        case 3:

            grabarTodosLosLibros(arregloLibros,validos);


            break;

        case 4:

            printf("Que registro de generos quiere ver? ");
            fflush(stdin);
            scanf("%s",&genero);
            strcat(genero,".dat");

            mostrarUnArchivo(genero);

            break;

        case 5:

            printf("Con que archivo quiere operar(Ingrese Genero)? ");
            fflush(stdin);
            scanf("%s",&genero);
            strcat(genero,".dat");

            ISBNMayor=devolverISBNMayor(genero);

            printf("El ISBN del libro con mayor cantidad de paginas es: %i\n",ISBNMayor);

            break;

        case 0:

            printf("El programa se cerrara...\n");

            break;


        default:

            printf("Numero de operacion incorrecto\n");

            break;
        }

        system("pause");
        system("cls");

    }
    while(opcion!=0);

    return 0;
}



/*1. Hacer una función que genere un código numérico. Mínimo 1 y máximo del que
quieran. Hacer una función que verifique si un libro existe en un arreglo buscando
por ISBN. Retornará 1 ó 0. 15 pts.*/

int generarCodigo ()
{
    int ISBN=0;

    srand(time(NULL));

    ISBN=rand()%50+1;

    return ISBN;
}


/*2. Hacer una función que cargue libros en un arreglo utilizando la función anterior.
15 pts. Modularizar todo.*/

stLibro cargarUnLibro ()
{
    stLibro unLibro;

    printf("\nTitulo del Libro: ");
    fflush(stdin);
    gets(unLibro.titulo);
    printf("Genero: ");
    fflush(stdin);
    gets(unLibro.genero);
    unLibro.ISBN=generarCodigo();
    printf("ISBN asignado: %i\n",unLibro.ISBN);
    printf("Cantidad de paginas: ");
    scanf("%i",&unLibro.cantidaddepaginas);

    return unLibro;
}


int cargarMuchosLibros (stLibro muchosLibros [],int dim)
{
    char continuar='s';
    int flag=0;
    int validos=0;
    stLibro libroAux;

    while(flag==0 && continuar=='s')
    {
        muchosLibros[validos]=cargarUnLibro();
        flag=1;
        printf("Desea cargar otro libro? [s/n]: ");
        fflush(stdin);
        scanf("%c",&continuar);
        validos++;
    }

    while(validos<dim && continuar=='s')
    {
        libroAux=cargarUnLibro();
        for(int i=0 ; i<validos ; i++)
        {
            while(muchosLibros[i].ISBN==libroAux.ISBN)
            {
                libroAux.ISBN=generarCodigo();
            }
        }
        muchosLibros[validos]=libroAux;

        printf("\nDesea cargar otro libro? [s/n]: ");
        fflush(stdin);
        scanf("%c",&continuar);

        validos++;
    }


    /*while(validos<dim && continuar=='s')
    {
        muchosLibros[validos]=cargarUnLibro();

        printf("Desea cargar otro libro? [s/n]: ");
        fflush(stdin);
        scanf("%c",&continuar);
        validos++;
    }*/

    //Con este codigo comentado se pueden cargar libros, pero se pueden repetir los ISBN

    return validos;
}

int buscarXISBN (stLibro muchosLibros [],int validos,int ISBNRecibido)
{
    int flag=0;

    for(int i=0 ; i<validos ; i++)
    {
        if(muchosLibros[i].ISBN==ISBNRecibido)
        {
            flag=1;
        }
    }

    return flag;
}

//strcat copia el contenido de la segunda string en el final de la primera string

/*3. Hacer una función que grabe en un archivo todos los libros de un determinado
género enviado por parámetro. El nombre del archivo deberá ser el género. Hacer
una función que pase todos los libros del arreglo a varios archivos utilizando la
función anterior. 20 pts.*/

void grabarLibroXGenero (stLibro unLibro,char genero[])
{
    strcat(genero,".dat");
    FILE *archiLibros;

    archiLibros=fopen(genero,"ab");
    if(archiLibros!=NULL)
    {
        fwrite(&unLibro,sizeof(stLibro),1,archiLibros);
        fclose(archiLibros);
    }
}

void grabarTodosLosLibros (stLibro muchosLibros[],int validos)
{
    for(int i=0 ; i<validos ; i++)
    {
        grabarLibroXGenero(muchosLibros[i],muchosLibros[i].genero);
    }
}


/*4. Hacer una función para mostrar un archivo. 10 pts.*/

void mostrarDatosDelLibro (stLibro unLibro)
{
    printf("\nTitulo: %s\n",unLibro.titulo);
    printf("Genero: %s\n",unLibro.genero);
    printf("ISBN: %i\n",unLibro.ISBN);
    printf("Cantidad de paginas: %i\n",unLibro.cantidaddepaginas);

}

void mostrarUnArchivo (char genero[])
{
    printf("\n[Mostrando Archivo %s]\n",genero);
    FILE *archiLibros;
    stLibro unLibro;

    archiLibros=fopen(genero,"rb");
    if(archiLibros!=NULL)
    {
        while(fread(&unLibro,sizeof(stLibro),1,archiLibros)>0)
        {
            mostrarDatosDelLibro(unLibro);
            sleep(1);
        }
        fclose(archiLibros);
    }
    else
    {
        printf("El archivo no existe o esta dañado\n");
    }
}


/*5. Hacer un función que devuelva el ISBN del libro con mayor cantidad de hojas del
archivo. 20pts*/


int devolverISBNMayor (char genero[])
{
    FILE *archiLibros;
    stLibro unLibro;
    int libroConMasPaginas=0;
    int ISBNMayor=0;

    archiLibros=fopen(genero,"rb");
    if(archiLibros!=NULL)
    {
        while(fread(&unLibro,sizeof(stLibro),1,archiLibros)>0)
        {
            if(unLibro.cantidaddepaginas>libroConMasPaginas)
            {
                libroConMasPaginas=unLibro.cantidaddepaginas;
                ISBNMayor=unLibro.ISBN;
            }
        }
        fclose(archiLibros);
    }
    else
    {
        printf("El archivo no existe o esta dañado\n");
    }

    return ISBNMayor;
}
