/*
As principais classes implementadas na STL que não podem ser usadas são:
Vetor (vector),
Cadeias de caracteres (string),
Lista (list),
Fila (queue),
Pilha (stack),
Mapeamento (map),
Conjunto (set).
*/

#include <iostream>
#include <fstream>

using namespace std;


// struct criada para o candidato
struct Candidato {
    string nome;
    int numero;
    Candidato* proximo;
};

Candidato* criarCandidato(string nome, int numero) {
    Candidato* novoCandidato = new Candidato;
    novoCandidato->nome = nome;
    novoCandidato->numero = numero;
    novoCandidato->proximo = nullptr;
    return novoCandidato;
}

void inserirCandidato(Candidato** lista, string nome, int numero) {
    Candidato* novoCandidato = criarCandidato(nome, numero);
    if (*lista == nullptr) {
        *lista = novoCandidato;
    } else {
        Candidato* atual = *lista;
        while (atual->proximo != nullptr) {
            atual = atual->proximo;
        }
        atual->proximo = novoCandidato;
    }
}

void removerCandidato(Candidato** lista, int numero) {
    if (*lista == nullptr) {
        cout << "A lista de candidatos está vazia." << endl;
        return;
    }

    Candidato* atual = *lista;
    Candidato* anterior = nullptr;

    if (atual->numero == numero) {
        *lista = atual->proximo;
        delete atual;
        cout << "Candidato removido com sucesso." << endl;
        return;
    }

    while (atual != nullptr && atual->numero != numero) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == nullptr) {
        cout << "Candidato não encontrado." << endl;
    } else {
        anterior->proximo = atual->proximo;
        delete atual;
        cout << "Candidato removido com sucesso." << endl;
    }
}

void listarCandidatos(Candidato* lista) {
    if (lista == nullptr) {
        cout << "A lista de candidatos está vazia." << endl;
        return;
    }

    cout << "Lista de candidatos:" << endl;
    Candidato* atual = lista;
    while (atual != nullptr) {
        cout << "Nome: " << atual->nome << ", Número: " << atual->numero << endl;
        atual = atual->proximo;
    }
}

void salvarCandidatos(Candidato* lista) {
    ofstream arquivo("candidatos.txt");
    if (arquivo.is_open()) {
        Candidato* atual = lista;
        while (atual != nullptr) {
            arquivo << atual->nome << " " << atual->numero << endl;
            atual = atual->proximo;
        }
        arquivo.close();
        cout << "Candidatos salvos no arquivo 'candidatos.txt'." << endl;
    } else {
        cout << "Não foi possível abrir o arquivo para salvar os candidatos." << endl;
    }
}

void carregarCandidatos(Candidato** lista) {
    ifstream arquivo("candidatos.txt");
    if (arquivo.is_open()) {
        string nome;
        int numero;
        while (arquivo >> nome >> numero) {
            inserirCandidato(lista, nome, numero);
        }
        arquivo.close();
        cout << "Candidatos carregados do arquivo 'candidatos.txt'." << endl;
    } else {
        cout << "Não foi possível abrir o arquivo para carregar os candidatos." << endl;
    }
}

int main() {
    Candidato* lista;

}
