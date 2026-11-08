#include <iostream>
#include <string>
#include <stdexcept>
#include <cstddef>
#include <iterator>

using namespace std;

// Classe template ArrayDyn
template <typename T>
class ArrayDyn {

private:
    T* data;
    size_t capacite;
    size_t taille;

public:

    // 1. Constructeur par defaut
    ArrayDyn() {
        data = nullptr;
        capacite = 0;
        taille = 0;
    }

    // 2. Constructeur avec capacite initiale
    ArrayDyn(size_t cap) {
        capacite = cap;
        taille = 0;

        if (capacite > 0)
            data = new T[capacite];
        else
            data = nullptr;
    }

    // 3. Constructeur de copie
    ArrayDyn(const ArrayDyn& autre) {
        capacite = autre.capacite;
        taille = autre.taille;

        if (capacite > 0) {
            data = new T[capacite];

            for (size_t i = 0; i < taille; i++) {
                data[i] = autre.data[i];
            }
        } else {
            data = nullptr;
        }
    }

    // 4. Operateur d'affectation
    ArrayDyn& operator=(const ArrayDyn& autre) {

        if (this != &autre) {

            T* nouveau = nullptr;

            if (autre.capacite > 0) {
                nouveau = new T[autre.capacite];

                for (size_t i = 0; i < autre.taille; i++) {
                    nouveau[i] = autre.data[i];
                }
            }

            delete[] data;

            data = nouveau;
            capacite = autre.capacite;
            taille = autre.taille;
        }

        return *this;
    }

    // 5. Destructeur
    ~ArrayDyn() {
        delete[] data;
    }

    // 6. Methode push_back
    void push_back(const T& element) {

        // Agrandir le tableau si necessaire
        if (taille == capacite) {

            size_t nouvelleCapacite =
                (capacite == 0) ? 1 : capacite * 2;

            T* nouveau = new T[nouvelleCapacite];

            for (size_t i = 0; i < taille; i++) {
                nouveau[i] = data[i];
            }

            delete[] data;

            data = nouveau;
            capacite = nouvelleCapacite;
        }

        data[taille] = element;
        taille++;
    }

    // 7. Methode pop_back
    void pop_back() {

        if (taille == 0) {
            throw underflow_error("Tableau vide !");
        }

        taille--;
    }

    // 8. Surcharge de l'operateur []
    T& operator[](size_t indice) {

        if (indice >= taille) {
            throw out_of_range("Indice invalide !");
        }

        return data[indice];
    }

    // 9. Classe interne Iterator
    class Iterator {

    private:
        T* ptr;

    public:

        Iterator(T* p = nullptr) {
            ptr = p;
        }

        // Acceder a l'element
        T& operator*() const {
            return *ptr;
        }

        // Incrementer
        Iterator& operator++() {
            ++ptr;
            return *this;
        }

        // Incrementer postfixe
        Iterator operator++(int) {
            Iterator temp = *this;
            ++ptr;
            return temp;
        }

        // Decrementer
        Iterator& operator--() {
            --ptr;
            return *this;
        }

        // Decrementer postfixe
        Iterator operator--(int) {
            Iterator temp = *this;
            --ptr;
            return temp;
        }

        // Comparaison
        bool operator!=(const Iterator& autre) const {
            return ptr != autre.ptr;
        }

        bool operator==(const Iterator& autre) const {
            return ptr == autre.ptr;
        }
    };

    // 10. Methode begin
    Iterator begin() {
        return Iterator(data);
    }

    // 11. Methode end
    Iterator end() {
        return Iterator(data + taille);
    }

    // 12. Afficher la taille
    size_t getTaille() const {
        return taille;
    }
};

// Classe maison pour le test
class Etudiant {

private:
    string nom;
    int age;

public:

    // Constructeur par defaut
    Etudiant() {
        nom = "Inconnu";
        age = 0;
    }

    // Constructeur avec parametres
    Etudiant(string n, int a) {
        nom = n;
        age = a;
    }

    void afficher() const {
        cout << "Nom : " << nom
             << " | Age : " << age << endl;
    }
};

// Programme principal
int main() {

    // TEST 1 : Tableau d'entiers
    cout << " TABLEAU D'ENTIERS " << endl;

    ArrayDyn<int> nombres;

    nombres.push_back(10);
    nombres.push_back(20);
    nombres.push_back(30);
    nombres.push_back(40);

    for (auto& e : nombres) {
        cout << e << " ";
    }

    cout << endl;


    // TEST 2 : Tableau de chaines
    cout << "\n TABLEAU DE STRINGS " << endl;

    ArrayDyn<string> mots;

    mots.push_back("Bonjour");
    mots.push_back("C++");
    mots.push_back("Programmation");

    for (auto& e : mots) {
        cout << e << " ";
    }

    cout << endl;


    // TEST 3 : Tableau d'objets
    cout << "\n TABLEAU D'ETUDIANTS " << endl;

    ArrayDyn<Etudiant> etudiants;

    etudiants.push_back(Etudiant("Hind", 20));
    etudiants.push_back(Etudiant("Reda", 22));
    etudiants.push_back(Etudiant("Youssef", 27));

    for (auto& e : etudiants) {
        e.afficher();
    }


    // TEST 4 : Constructeur de copie
    cout << "\n TEST COPIE " << endl;

    ArrayDyn<int> copie(nombres);

    for (auto& e : copie) {
        cout << e << " ";
    }

    cout << endl;


    // TEST 5 : Operateur d'affectation
    cout << "\n TEST AFFECTATION " << endl;

    ArrayDyn<int> tableau2;

    tableau2 = nombres;

    for (auto& e : tableau2) {
        cout << e << " ";
    }

    cout << endl;


    // TEST 6 : Acces avec []
    cout << "\n TEST OPERATEUR [] " << endl;

    cout << "Premier element : " << nombres[0] << endl;


    // TEST 7 : pop_back
    nombres.pop_back();

    cout << "\nApres pop_back : ";

    for (auto& e : nombres) {
        cout << e << " ";
    }

    cout << endl;

    return 0;
}
