#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
using namespace std;

// Exception : pile pleine
class StackOverflow : public exception {
public:
    const char* what() const noexcept override {
        return "Erreur : la pile est pleine !";
    }
};

// Exception : pile vide
class StackUnderflow : public exception {
public:
    const char* what() const noexcept override {
        return "Erreur : la pile est vide !";
    }
};

// Classe Stack générique
template <typename T>
class Stack {
private:
    unique_ptr<T[]> data;
    size_t capacity;
    size_t top;

public:

    // Constructeur avec capacité par défaut
    Stack(size_t capacite = 10) {
        capacity = capacite;
        top = 0;
        data = make_unique<T[]>(capacity);
    }

    // Constructeur avec des itérateurs
    template <typename Iterator>
    Stack(Iterator begin, Iterator end) {
        capacity = 0;
        top = 0;

        // Compter les éléments
        for (Iterator it = begin; it != end; ++it) {
            capacity++;
        }

        data = make_unique<T[]>(capacity);

        // Copier les éléments dans la pile
        for (Iterator it = begin; it != end; ++it) {
            push(*it);
        }
    }

    // Ajouter un élément
    void push(const T& valeur) {
        if (top == capacity) {
            throw StackOverflow();
        }

        data[top] = valeur;
        top++;
    }

    // Retirer le dernier élément
    void pop() {
        if (empty()) {
            throw StackUnderflow();
        }

        top--;
    }

    // Consulter le dernier élément
    const T& peek() const {
        if (empty()) {
            throw StackUnderflow();
        }

        return data[top - 1];
    }

    // Vérifier si la pile est vide
    bool empty() const {
        return top == 0;
    }

    // Afficher les éléments de la pile
    void afficher() const {
        cout << "Contenu de la pile : ";

        for (size_t i = 0; i < top; i++) {
            cout << data[i] << " ";
        }

        cout << endl;
    }

    // Retourner le nombre d'éléments
    size_t taille() const {
        return top;
    }
};

int main() {

    cout << " TEST DE LA PILE D'ENTIERS " << endl;

    Stack<int> pile(3);

    pile.push(10);
    pile.push(20);
    pile.push(30);

    pile.afficher();

    cout << "Dernier element : " << pile.peek() << endl;

    cout << "\n TEST DE STACKOVERFLOW " << endl;

    try {
        pile.push(40);
    }
    catch (const StackOverflow& e) {
        cout << e.what() << endl;
    }

    cout << "\n TEST DE POP " << endl;

    pile.pop();

    pile.afficher();

    cout << "Dernier element : " << pile.peek() << endl;

    cout << "\n TEST DE STACKUNDERFLOW " << endl;

    pile.pop();
    pile.pop();

    try {
        pile.pop();
    }
    catch (const StackUnderflow& e) {
        cout << e.what() << endl;
    }

    cout << "\n TEST AVEC UNE COLLECTION " << endl;

    int valeurs[] = {1, 2, 3, 4, 5};

    Stack<int> pile2(valeurs, valeurs + 5);

    pile2.afficher();

    cout << "Taille de la pile : " << pile2.taille() << endl;

    cout << "\n TEST AVEC DES CHAINES " << endl;

    Stack<string> pile3(3);

    pile3.push("Bonjour");
    pile3.push("C++");
    pile3.push("Templates");

    pile3.afficher();

    cout << "Dernier element : " << pile3.peek() << endl;

    cout << "\n TEST AVEC UN GRAND NOMBRE D'ELEMENTS " << endl;

    Stack<int> grandePile(100000);

    for (int i = 1; i <= 100000; i++) {
        grandePile.push(i);
    }

    cout << "Nombre d'elements ajoutes : "
         << grandePile.taille() << endl;

    cout << "Dernier element : " << grandePile.peek() << endl;

    cout << "\nFin du programme." << endl;

    return 0;
}
