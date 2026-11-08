
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <cassert>
using namespace std;

//  Concept Sortable
template <typename T>
concept Sortable = requires(T a, T b) {
    { a < b } -> convertible_to<bool>;
};

//  Foncteur de tri croissant
struct Asc {
    template <typename T>
    bool operator()(const T& a, const T& b) const {
        return a < b;
    }
};

//  Foncteur de tri decroissant
struct Desc {
    template <typename T>
    bool operator()(const T& a, const T& b) const {
        return a > b;
    }
};

//  Fonction quickSort
template <typename T, typename Comp = less<T>>
void quickSort(vector<T>& v, Comp comp = Comp()) {
    sort(v.begin(), v.end(), comp);
}

//  Structure utilisateur
struct Etudiant {
    string nom;
    int age;

    bool operator<(const Etudiant& autre) const {
        return age < autre.age;
    }
};

//  Affichage d'un vecteur
template <typename T>
void afficher(const vector<T>& v) {
    for (const T& element : v) {
        cout << element << " ";
    }
    cout << endl;
}

// Affichage  pour Etudiant
void afficherEtudiants(const vector<Etudiant>& v) {
    for (const Etudiant& e : v) {
        cout << e.nom << " (" << e.age << ") ";
    }
    cout << endl;
}

// Tests unitaires simples
template <typename T, typename Comp>
bool estTrie(const vector<T>& v, Comp comp) {
    return is_sorted(v.begin(), v.end(), comp);
}

int main() {

    cout << " TRI GENERIQUE" << endl;

    // Test 1 : vector<int>
    vector<int> nombres = {8, 3, 5, 1, 9, 2};

    quickSort(nombres, Asc());

    cout << "\nTri croissant des entiers : ";
    afficher(nombres);

    assert(estTrie(nombres, Asc()));
    cout << "Test 1 reussi !" << endl;

    // Test 2 : vector<int> decroissant
    quickSort(nombres, Desc());

    cout << "Tri decroissant des entiers : ";
    afficher(nombres);

    assert(estTrie(nombres, Desc()));
    cout << "Test 2 reussi !" << endl;

    // Test 3 : vector<string>
    vector<string> noms = {
        "Sara", "Ahmed", "Youssef", "Ali"
    };

    quickSort(noms, Asc());

    cout << "\nTri des chaines : ";
    afficher(noms);

    assert(estTrie(noms, Asc()));
    cout << "Test 3 reussi !" << endl;

    // Test 4 : structure Etudiant
    vector<Etudiant> etudiants = {
        {"Sara", 22},
        {"Ali", 19},
        {"Youssef", 24},
        {"Ahmed", 20}
    };

    quickSort(etudiants, Asc());

    cout << "\nTri des etudiants par age : ";
    afficherEtudiants(etudiants);

    assert(estTrie(etudiants, Asc()));
    cout << "Test 4 reussi !" << endl;

    cout << "\nTous les tests sont reussis !" << endl;

    return 0;
}
