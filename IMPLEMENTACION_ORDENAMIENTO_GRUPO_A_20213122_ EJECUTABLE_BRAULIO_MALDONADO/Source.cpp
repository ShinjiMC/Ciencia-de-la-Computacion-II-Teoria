#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace::std;
struct Estudiante {
    string Nombre;
    string Apellidos;
    char Seccion;
    int edad;
    float estatura;
    double nota;
};
typedef struct Estudiante* Et;
Et Crear(string nombre_,string apellidos_,char sec_,int ed_,float estatu_,double not_) {
    Et nuevo = new (struct Estudiante);
    nuevo->Nombre=nombre_;
    nuevo->Apellidos = apellidos_;
    nuevo->Seccion = sec_;
    nuevo->edad = ed_;
    nuevo->estatura = estatu_;
    nuevo->nota = not_;
    return nuevo;
}
void Insertar(Et& lista,string nombre_, string apellidos_, char sec_, int ed_, float estatu_, double not_) {
    if (lista == NULL) {
        lista = Crear(nombre_, apellidos_, sec_, ed_, estatu_, not_);
    }
}
void Mostrar(Et lista) {
    if (lista != NULL) {
        cout << "|"
            << left << setw(10) << lista->Nombre
            << "|"
            << left << setw(30) << lista->Apellidos
            << "|"
            << left << setw(15) << lista->Seccion
            << "|"
            << left << setw(15) << lista->edad
            << "|"
            << left << setw(15) << lista->estatura
            << "|"
            << left << setw(15) << lista->nota
            << "|";
    }
}
void IngresarData(Et*& numeros, int n) {
    string nombre;
    string apellidos;
    char Seccion;
    int edad;
    float estat;
    double notas;
    for (int i = 0; i < n; i++) {
        cout << "-----------------------Estudiante Nro." << i + 1 << "-------------------------------" << endl;
        cout << "Ingrese el nombre del Estudiante: ";
        cin >> nombre;
        cout << "Ingrese el apellido del Estudiante: ";
        cin >> apellidos;
        cout << "Ingrese la letra de la seccion del Estudiante: ";
        cin >> Seccion;
        cout << "Ingrese la edad del Estudiante: ";
        cin >> edad;
        cout << "Ingrese la estatura del Estudiante (en metros): ";
        cin >> estat;
        cout << "Ingrese la nota promedio del Estudiante: ";
        cin >> notas;
        cout << endl;
        Insertar(numeros[i], nombre, apellidos, Seccion, edad, estat, notas);
    }
}

template <typename T>
bool compare1(T x, T y) {
    return x <= y;
}
template <typename T>
bool compare2(T x, T y) {
    return x > y;
}
template <typename T>
bool compare3(T x, T y) {
    return x < y;
}

template <typename T>
void InsertionSort(T*& numeros, int a, int n, bool (*p)(T, T)) {
    T cache;
    int indice;
    for (int i = 1; i < n; i++) {
        cache = numeros[i];
        indice = i;
        while (indice > 0 && p(cache, numeros[indice - 1])) {
            numeros[indice] = numeros[indice - 1];
            indice = indice - 1;
        }
        numeros[indice] = cache;
    }
}
template <typename T>
void merge(T*& num, int const izq, int const centro, int const der, bool (*p)(T, T)) {
    auto const X = centro - izq + 1;
    auto const Y = der - centro;
    auto* izqNumeros = new T[X], * derNumeros = new T[Y];
    for (auto i = 0; i < X; i++) {
        izqNumeros[i] = num[izq + i];
    }
    for (auto j = 0; j < Y; j++) {
        derNumeros[j] = num[centro + 1 + j];
    }
    auto A = 0, B = 0;
    int tam = izq;
    while (A < X && B < Y) {
        if (p(izqNumeros[A], derNumeros[B])) {
            num[tam] = izqNumeros[A];
            A++;
        }
        else {
            num[tam] = derNumeros[B];
            B++;
        }
        tam++;
    }
    while (A < X) {
        num[tam] = izqNumeros[A];
        A++;
        tam++;
    }
    while (B < Y) {
        num[tam] = derNumeros[B];
        B++;
        tam++;
    }
}
template <typename T>
void mergeSort(T*& num, int const Inicio, int const ultimo, bool (*p)(T, T)) {
    if (Inicio >= ultimo) {
        return;
    }
    auto centro = Inicio + (ultimo - Inicio) / 2;
    mergeSort(num, Inicio, centro,p);
    mergeSort(num, centro + 1, ultimo,p);
    merge(num, Inicio, centro, ultimo,p);
}
template <typename T>
void quicksort(T*& A, int izq, int der , bool (*p)(T, T)) {
    int i = izq, j = der;
    T tmp;
    T mid = A[(izq + der) / 2];
    while (i <= j) {
        while (p(A[i], mid)) {
            i++;
        }
        while (p(mid,A[j])) {
            j--;
        }
        if (i <= j) {
            tmp = A[i];
            A[i] = A[j];
            A[j] = tmp;
            i++;
            j--;
        }
    }
    if (izq < j) {
        quicksort(A, izq, j,p);
    }
    if (i < der) {
        quicksort(A, i, der,p);
    }
}


template <typename T>
void MenuDescendente(T*& list, int n) {
    void(*p)(T*&, int, int, bool (*p)(T, T));
    while (true) {
        string op;
        cout << "************************************************************************" << endl;
        cout << "\t1.Insertion \n\t2.Merge \n\t3.Quick \nIngrese una opcion: ";
        cin >> op;
        if (op == "1") {
            p = InsertionSort<T>;
            (p)(list, 0, n, compare2);
            break;
        }
        else if (op == "2") {
            p = mergeSort<T>;
            (p)(list, 0, n - 1,compare2);
            break;
        }
        else if (op == "3") {
            p = quicksort<T>;
            (p)(list, 0, n - 1,compare2);
            break;
        }
        else {
            cout << "Valor Incorrecto. Vuelva a intenatrlo." << endl;
        }
    }
}
template <typename T>
void MenuAscendente(T*& list, int n) {
    void(*p)(T*&, int, int, bool (*p)(T, T));
    while (true) {
        string op;
        cout << "************************************************************************" << endl;
        cout << "\t1.Insertion \n\t2.Merge \n\t3.Quick \nIngrese una opcion: ";
        cin >> op;
        if (op == "1") {
            p = InsertionSort<T>;
            (p)(list, 0, n, compare1);
            break;
        }
        else if (op == "2") {
            p = mergeSort<T>;
            (p)(list, 0, n - 1, compare1);
            break;
        }
        else if (op == "3") {
            p = quicksort<T>;
            (p)(list, 0, n - 1, compare3);
            break;
        }
        else {
            cout << "Valor Incorrecto. Vuelva a intenatrlo." << endl;
        }
    }
}
template <typename T>
void Menu(T*& list, int n) {
    while (true) {
        cout << "************************************************************************" << endl;
        string op;
        cout << "\t1.Ascendente \n\t2.Descendente \nIngrese una opcion: ";
        cin >> op;
        if (op == "1") {
            MenuAscendente<T>(list, n);
            break;
        }
        else if (op == "2") {
            MenuDescendente<T>(list, n);
            break;
        }
        else {
            cout << "Valor Incorrecto. Vuelva a intenatrlo." << endl;
        }
    }
}

template <typename T>
void For(Et*& numeros, Et*& lista, T aux,T* listaux,int j,int n ) {
    for (int i = 0; i < n; i++) {
        T data = listaux[i];
        if (aux == data) {
            if (lista[i] != NULL) {
                numeros[j] = lista[i];
                lista[i] = NULL;
                i = n;
            }
        }
    }
}

template <typename T>
Et* ReloadET(Et* lista, int n, T* list,T* listaux) {
    Et* numeros = new Et[n];
    for (int i = 0; i < n; i++) {
        numeros[i] = NULL;
    }
    for (int j = 0; j < n; j++) {
        T aux = list[j];
        For<T>(numeros, lista, aux, listaux,j,n);
    }
    return numeros;
}

void Select(Et*& numeros, int n) {
    while (true) {
        string op;
        cout << "---------------------------------------------------------------------------------" << endl;
        cout << "\t1.Ordenar por Nombres \n\t2.Ordenar por Apellidos \n\t3.Ordenar por Seccion\n\t4. Ordenar por edades \n\t5. Ordenar por estatura\n\t6. Ordenar por Notas\n\t7.Salir \nIngrese una opcion: ";
        cin >> op;
        if (op == "1") {
            string* list = new string[n];
            string* listaux = new string[n];
            for (int i = 0; i < n; i++) {
                list[i] = numeros[i]->Nombre;
                listaux[i] = numeros[i]->Nombre;
            }
            cout << endl;
            Menu<string>(list, n);
            cout << endl;
            numeros = ReloadET<string>(numeros, n, list,listaux);
            delete[]list;
            break;
        }
        else if (op == "2") {
            string* list = new string[n];
            string* listaux = new string[n];
            for (int i = 0; i < n; i++) {
                list[i] = numeros[i]->Apellidos;
                listaux[i] = numeros[i]->Apellidos;
            }
            cout << endl;
            Menu<string>(list, n);
            cout << endl;
            numeros = ReloadET<string>(numeros, n, list,listaux);
            delete[]list;
            break;
        }
        else if (op == "3") {
            char* list = new char[n];
            char* listaux = new char[n];
            for (int i = 0; i < n; i++) {
                list[i] = numeros[i]->Seccion;
                listaux[i] = numeros[i]->Seccion;
            }
            cout << endl;
            Menu<char>(list, n);
            cout << endl;
            numeros = ReloadET<char>(numeros, n, list, listaux);
            delete[]list;
            break;
        }
        else if (op == "4") {
            int* list = new int[n];
            int* listaux = new int[n];
            for (int i = 0; i < n; i++) {
                list[i] = numeros[i]->edad;
                listaux[i] = numeros[i]->edad;
            }
            cout << endl;
            Menu<int>(list, n);
            cout << endl;
            numeros = ReloadET<int>(numeros, n, list, listaux);
            delete[]list;
            break;
        }
        else if (op == "5") {
            float* list = new float[n];
            float* listaux = new float[n];
            for (int i = 0; i < n; i++) {
                list[i] = numeros[i]->estatura;
                listaux[i] = numeros[i]->estatura;
            }
            cout << endl;
            Menu<float>(list, n);
            cout << endl;
            numeros = ReloadET<float>(numeros, n, list, listaux);
            delete[]list;
            break;
        }
        else if (op == "6") {
            double* list = new double[n];
            double* listaux = new double[n];
            for (int i = 0; i < n; i++) {
                list[i] = numeros[i]->nota;
                listaux[i] = numeros[i]->nota;
            }
            cout << endl;
            Menu<double>(list, n);
            cout << endl;
            numeros = ReloadET<double>(numeros, n, list, listaux);
            delete[]list;
            break;
        }
        else if (op == "7") {
            cout << endl;
            break;
        }
        else {
            cout << "Valor Incorrecto. Vuelva a intenatrlo." << endl;
        }
    }
}



int main() {
    int n;
    cout << "Ingrese la cantidad de estudiantes a registrar: ";
    cin >> n;
    Et* numeros = new Et[n];
    for (int i = 0; i < n; i++) {
        numeros[i] = NULL;
    }
    /*string nombres[5] = {"Braulio","Julio","Alejandro","Armando","Pablo"};
    string apellidos[5] = { "Maldonado Casilla","Bazan Machaca","Velasco Vilca","Mamani Ranilla","Mamani Vilca" };
    char Seccion[5] = { 'A','A','B','B','A' };
    int edad[5] = { 14,15,14,16,15 };
    float estat[5] = { 1.56,1.75,1.67,1.80,1.67 };
    double notas[5] = { 13.0009,14.9999,13.001,15.009,14.8796001 };
    for (int i = 0; i < n; i++) {
        Insertar(numeros[i], nombres[i], apellidos[i], Seccion[i], edad[i], estat[i], notas[i]);
    }*/
    IngresarData(numeros, n);
    cout << "---------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < n; i++) {
        Mostrar(numeros[i]);
        cout << endl;
    }
    cout << "---------------------------------------------------------------------------------" << endl;
    while (true) {
        string op;
        cout << "------------------------------------MENU--------------------------------------" << endl;
        cout << "\t1.Ordenar Datos \n\t2.Mostrar\n\t3.Salir \nIngrese una opcion: ";
        cin >> op;
        if (op == "1") {
            Select(numeros, n);
            cout << "---------------------------------------------------------------------------------" << endl;
        }
        else if (op == "2") {
            cout << "---------------------------------------------------------------------------------" << endl;
            for (int i = 0; i < n; i++) {
                Mostrar(numeros[i]);
                cout << endl;
            }
            cout << "---------------------------------------------------------------------------------" << endl;
        }
        else if (op == "3") {
            cout << "Saliendo..." << endl;
            break;
        }
        else {
            cout << "Valor Incorrecto. Vuelva a intenatrlo." << endl;
        }
    }
    delete[]numeros;
    return 0;
}