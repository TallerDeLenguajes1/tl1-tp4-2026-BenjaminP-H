#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/* =========================================================
   ZONA 1: DEFINICIÓN DE ESTRUCTURAS
   ========================================================= */
typedef struct Tarea {
    int TareaID;       // Identificador numérico
    char *Descripcion; // Puntero para memoria dinámica (texto de largo variable)
    int Duracion;      // Valor entre 10 y 100
} Tarea;

typedef struct Nodo {
    Tarea T;              // La carga útil (los datos de la tarea)
    struct Nodo *Siguiente; // El "gancho" que guarda la dirección del próximo nodo //Muy IMPORTANTE    
} Nodo;

//MAS IMPORTANTES!
/* =========================================================
   ZONA 2: PROTOTIPOS (El índice del programa)
   ========================================================= */

//crea una lista vacia para comenzar
Nodo *crearListaVacia();
//crea un nodo de tarea
Nodo *crearTarea(int *TareaID, char Descripcion[], int Duracion);//puntero de id por que hay que cambiar el id sumando constantemente

//Insertar Nodos o Tareas ala lista
void insertarTarea(Nodo **ListaPendiente, Nodo *tareaCreada); //funciona
void insertarTareaAlFinal(Nodo **ListaPendiente, Nodo *tareaCreada);//para mi gusto este es mejor que el anterior

//Mostrar Nodos o Listas Enlazadas
void mostrarListas(Nodo *Listas);

//Quitar Nodos o Tareas de la lista
Nodo *quitarNodo(Nodo **ListaPendiente, int IDBuscado);

//Busquedas de Tareas / Nodos
Nodo *BuscarTareaPorID(Nodo **ListaPendiente, int IDBuscado);
Nodo *BuscarTareaPorDescripcion(Nodo **ListaPendiente, char palabraClave[]);

//Liberar memoria(de la lista) free

void LiberarMemoria(Nodo **Listas);

/* =========================================================
   ZONA 3: CUERPO PRINCIPAL (MAIN)
   ========================================================= */

int main()
{
     // Inicializamos las cabezas de las listas en NULL
    Nodo *ListaPendiente = crearListaVacia();
    Nodo *ListaTerminada = crearListaVacia();

    int TareaID = 1000;
    char Descripcion[50];
    int Duracion;
    int opcion = 1;
    int IDBuscado;
    int opcionBusqueda;

    srand(time(NULL)); // Semilla para que rand() cambie siempre

    while (opcion != 0)
    {
        printf("Eliga una de las siguientes opciones a realizar:\n");
        printf("1. Ingresar una nueva tarea\n");
        printf("2. Marcar una tarea como realizada\n");
        printf("3. Mostrar todas las tareas pendientes y realizadas\n");
        printf("4. Buscar Tarea por Descripcion o ID\n");// acab debo indicar si la tarea existe o no y si esta mostrar si esta en la lista de pendiente o realizada
        printf("0. Salir\n");
        scanf("%d", &opcion);

        if (opcion <= 5)
        {
           
            switch (opcion)
            {
            case 1:
                printf("\n--- Carga de Nueva Tarea ---\n");
                printf("Descripcion de la Tarea: ");
                fflush(stdin);//Limpio el buffer
                gets(Descripcion);//consultar si puedo usar fgets
                
                Duracion = 10 + rand() % 91; //entre 10 y 100
                // 1. Fabricamos el nodo con los datos de la tarea

                Nodo *tareaCreada = crearTarea(&TareaID, Descripcion, Duracion);
                // 2. Insertamos el nodo en la lista
                insertarTareaAlFinal(&ListaPendiente, tareaCreada);
                printf("Tarea %d cargada con exito.\n", tareaCreada->T.TareaID);
                break;
    
            case 2:
                printf("\n--- Marcar Tarea como Realizada ---\n");
                printf("ID de la Tarea Realizada: ");
                scanf("%d", &IDBuscado);
                // 1. Buscamos y desenganchamos de 'Pendientes'
                Nodo *tareaRealizada = quitarNodo(&ListaPendiente,IDBuscado);

                if (tareaRealizada !=  NULL)
                {
                     // 2. Enganchamos el mismo nodo en 'Realizadas'
                    insertarTareaAlFinal(&ListaTerminada, tareaRealizada);
                    printf("Tarea %d movida con exito a Realizadas.\n", IDBuscado);
                }else
                {
                    printf("Tarea %d no encontrada.\n", IDBuscado);
                }
                break;

            case 3:
                printf("\n======= TAREAS PENDIENTES =======");
                mostrarListas(ListaPendiente);
                printf("\n======= TAREAS REALIZADAS =======");
                mostrarListas(ListaTerminada);
                break;
            case 4:
                printf("\n--- Buscar Tarea por Descripcion o ID ---\n");
                printf("1. Buscar por Descripcion\n");
                printf("2. Buscar por ID\n");
                scanf("%d", &opcionBusqueda);
                if (opcionBusqueda == 1)
                {
                    printf("Descripcion de la Tarea: ");
                    fflush(stdin);//Limpio el buffer
                    gets(Descripcion);
                    Nodo *tareaBuscada = BuscarTareaPorDescripcion(&ListaPendiente, Descripcion);
                    if (tareaBuscada)
                    {
                        printf("\n[Tarea Encontrada en PENDIENTES]\n");
                        mostrarListas(tareaBuscada);
                    }else
                    {
                        tareaBuscada = BuscarTareaPorDescripcion(&ListaTerminada, Descripcion);
                        if (tareaBuscada)
                        {
                            printf("\n[Tarea Encontrada en REALIZADAS]\n");
                            mostrarListas(tareaBuscada);
                        }else
                        {
                            printf("\n[Tarea no encontrada con esa descripcion]\n");
                        }
                    }
                      
                }else if (opcionBusqueda == 2)
                {
                    printf("ID de la Tarea: ");
                    scanf("%d", &IDBuscado);
                    Nodo *tareaBuscada = BuscarTareaPorID(&ListaPendiente, IDBuscado);
                    if (tareaBuscada)
                    {
                        printf("\n[Tarea Encontrada en PENDIENTES]\n");
                        mostrarListas(tareaBuscada);
                    }else
                    {
                        tareaBuscada = BuscarTareaPorID(&ListaTerminada, IDBuscado);
                        if (tareaBuscada)
                        {
                            printf("\n[Tarea Encontrada en REALIZADAS]\n");
                            mostrarListas(tareaBuscada);
                        }else
                        {
                            printf("\n[Tarea no encontrada con ese ID]\n");
                        }
                    }
                }else
                {
                    printf("Opcion no valida");
                }

                break;
            case 0:
                // SIEMPRE liberar memoria antes de salir
                    printf("\nLiberando memoria de tareas pendientes...\n");
                    LiberarMemoria(&ListaPendiente);
                    
                    printf("Liberando memoria de tareas terminadas...\n");
                    LiberarMemoria(&ListaTerminada);
                    
                    printf("Programa finalizado. ¡Hasta luego!\n");
                break;
            }
        }

    }
    
    return 0;
}
/* =========================================================
   ZONA 4: FUNCIONES DE MEMORIA Y LISTAS
   ========================================================= */
// Devuelve NULL para decir que la lista arranca limpia
Nodo *crearListaVacia()
{
    return NULL;
}
// PASO DE DATOS: Aquí pides memoria para el "contenedor" (Nodo) 
// y para el "contenido" (Descripcion).
Nodo *crearTarea(int *TareaID, char Descripcion[], int Duracion)
{
    //reservo memoria para el nodo nuevo
    Nodo * tareaCreada = (Nodo *) malloc(sizeof(Nodo));

    //Cargamos el ID y lo aumentamo para la próxima vez
    tareaCreada->T.TareaID = *TareaID;
    (*TareaID)++;//sumo 1 al id // Modifica el valor en el main usando el puntero

    //Cargo la duración de la tarea
    tareaCreada->T.Duracion = Duracion;

    //strlen(Descripcion): Mide cuántas letras tiene el nombre que escribió el usuario (por ejemplo, "Lavar auto" tiene 10).
    //+ 1: Reserva un espacio extra para el carácter invisible \0 que le dice a C dónde termina el texto.
    
    // Apartamos el espacio justo para el texto + el caracter final \0

    tareaCreada->T.Descripcion = (char *)malloc(sizeof(char) * (strlen(Descripcion) + 1));


    strcpy(tareaCreada->T.Descripcion, Descripcion);//guarda la descripcion de la tarea

    tareaCreada->Siguiente = NULL; // Todo nodo nuevo nace "suelto"

    return tareaCreada;
}

void insertarTarea(Nodo **ListaPendiente, Nodo *tareaCreada)
{
    tareaCreada->Siguiente = *ListaPendiente;
    *ListaPendiente = tareaCreada;
}

void insertarTareaAlFinal(Nodo **ListaPendiente, Nodo *tareaCreada)
{
    if (*ListaPendiente== NULL)
    {
        *ListaPendiente = tareaCreada;
        
    }else{
        Nodo *aux = *ListaPendiente;
    
        while (aux->Siguiente)
        {
            aux = aux->Siguiente;;
        }
        aux->Siguiente = tareaCreada;

    }
}
// RECORRIDO DE LECTURA: Usas un auxiliar para no perder el 'Start'
void mostrarListas(Nodo *Listas)
{
    // 1. Creamos un puntero auxiliar 'aux' que apunte al inicio
    // No usamos doble puntero porque no vamos a cambiar el inicio        
    Nodo *aux = Listas;
    // 2. Si aux es NULL, significa que la lista no tiene nodos
    if (aux == NULL)
    {
        printf("La lista esta vacia\n");
    }else{
        // 3. Mientras aux NO sea NULL, hay un vagon para leer
        while (aux != NULL)
        {
            printf("\n----------------------------");
            printf("\n Tarea ID:   %d", aux->T.TareaID);
            printf("\n Descripcion: %s", aux->T.Descripcion);
            printf("\n Duracion:    %d", aux->T.Duracion);
            printf("\n----------------------------\n");
            // 4. ¡Paso fundamental!: Movemos el dedo al siguiente nodo
            // Si no haces esto, te quedas siempre en la primera tarea
            aux = aux->Siguiente; // Salto al siguiente
        }
    }
    
}

//Muevo tareas entre lista
// RECORRIDO DE BÚSQUEDA Y EXTRACCIÓN: 
// Necesitas 'anterior' para que, al sacar uno, los otros dos se den la mano.
Nodo *quitarNodo(Nodo **ListaPendiente, int IDBuscado)
{
    Nodo *aux = *ListaPendiente;
    Nodo *anterior = NULL; 

    while (aux != NULL && aux->T.TareaID != IDBuscado)
    {
        anterior = aux;
        aux = aux->Siguiente;
    }
    // Si lo encontramos (aux no es NULL)
    if (aux != NULL)
    {
        if (anterior == NULL)
        {   
            // Si anterior es NULL, significa que el nodo a eliminar es el primero
            *ListaPendiente = aux->Siguiente;
        }else{
            // Si anterior no es NULL, significa que el nodo a eliminar no es el primero
            anterior->Siguiente = aux->Siguiente; // Hago el puente
        }

        aux->Siguiente = NULL; //Lo aislamos completamente
        return aux; // Retornamos el nodo eliminado para re-engancharlo luego
    }
    return NULL;
}
// Buscamos en una lista específica por ID
Nodo *BuscarTareaPorID(Nodo **ListaPendiente, int IDBuscado)
{
    Nodo *aux = *ListaPendiente;
    while (aux != NULL && aux->T.TareaID != IDBuscado)
    {
        aux = aux->Siguiente;
    }
    return aux; // Devuelve el nodo o NULL
}

// Buscamos en una lista específica por palabra clave
Nodo *BuscarTareaPorDescripcion(Nodo **ListaPendiente, char palabraClave[])
{
    Nodo *aux = *ListaPendiente;
    while (aux != NULL)
    {
        // strstr busca si 'palabra' está contenida en la descripción
        if (strstr(aux->T.Descripcion, palabraClave) != NULL)
        {
            return aux;//Encontro la Coincidencia
        }
        aux = aux->Siguiente;
    }
    return NULL;
}

void LiberarMemoria(Nodo **Listas)
{
    Nodo *aux = *Listas;
    Nodo *proximo;

    while (aux != NULL)
    {
        proximo = aux->Siguiente; // 1. Guardo el siguiente antes de borrar

        // 2. Libero la memoria de la descripción (char *)
         if (aux->T.Descripcion != NULL)
         {
            free(aux->T.Descripcion);
         }

         // 3. Libero la memoria del nodo
         free(aux);

         // 4. Avanzo al siguiente
         aux = proximo;
    }
    *Listas = NULL; //Dejo la lista limpia
}