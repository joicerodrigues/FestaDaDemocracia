#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

struct Candidato
{
    string nome;
    int numero;
    int votos;
    Candidato *proximo;
};

Candidato *criarCandidato(string nome, int numero)
{
    Candidato *novoCandidato = new Candidato;
    novoCandidato->nome = nome;
    novoCandidato->numero = numero;
    novoCandidato->votos = 0;
    novoCandidato->proximo = nullptr;
    return novoCandidato;
}

void inserirCandidato(Candidato **lista, string nome, int numero)
{
    Candidato *novoCandidato = criarCandidato(nome, numero);
    if (*lista == nullptr)
    {
        *lista = novoCandidato;
    }
    else
    {
        Candidato *atual = *lista;
        while (atual->proximo != nullptr)
        {
            atual = atual->proximo;
        }
        atual->proximo = novoCandidato;
    }
}

void removerCandidato(Candidato **lista, int numero)
{
    if (*lista == nullptr)
    {
        cout << "A lista de candidatos está vazia." << endl;
        return;
    }

    Candidato *atual = *lista;
    Candidato *anterior = nullptr;

    while (atual != nullptr && atual->numero != numero)
    {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == nullptr)
    {
        cout << "Candidato não encontrado." << endl;
        return;
    }

    if (anterior == nullptr)
    {
        *lista = atual->proximo;
    }
    else
    {
        anterior->proximo = atual->proximo;
    }

    delete atual;
    cout << "Candidato removido." << endl;
}

void listarCandidatos(Candidato *lista)
{
    if (lista == nullptr)
    {
        cout << "A lista de candidatos está vazia." << endl;
        return;
    }

    cout << "Lista de candidatos:" << endl;
    Candidato *atual = lista;
    while (atual != nullptr)
    {
        cout << "Nome: " << atual->nome << ", Número: " << atual->numero << ", Votos: " << atual->votos << endl;
        atual = atual->proximo;
    }
}

void salvarCandidatos(Candidato *lista)
{
    ofstream arquivo("candidatos.txt");

    if (!arquivo)
    {
        cout << "Erro ao abrir o arquivo." << endl;
        return;
    }

    Candidato *atual = lista;
    while (atual != nullptr)
    {
        arquivo << atual->nome << "," << atual->numero << "," << atual->votos << endl;
        atual = atual->proximo;
    }

    arquivo.close();
    cout << "Candidatos salvos com sucesso." << endl;
}

Candidato *carregarCandidatos()
{
    ifstream arquivo("candidatos.txt");

    if (!arquivo)
    {
        cout << "Erro ao abrir o arquivo." << endl;
        return nullptr;
    }

    Candidato *lista = nullptr;
    string linha;
    while (getline(arquivo, linha))
    {
        string nome;
        int numero;
        int votos;

        stringstream ss(linha);
        getline(ss, nome, ',');
        ss >> numero;
		        ss.ignore();
        ss >> votos;

        inserirCandidato(&lista, nome, numero);
        Candidato *atual = lista;
        while (atual != nullptr && atual->numero != numero)
        {
            atual = atual->proximo;
        }
        if (atual != nullptr)
        {
            atual->votos = votos;
        }
    }

    arquivo.close();
    return lista;
}

void menu()
{
    Candidato *listaCandidatos = carregarCandidatos();

    while (true)
    {
        cout << "==== Eleições ====" << endl;
        cout << "1. Inserir candidato" << endl;
        cout << "2. Remover candidato" << endl;
        cout << "3. Listar candidatos" << endl;
        cout << "4. Salvar candidatos" << endl;
        cout << "0. Sair" << endl;
        cout << "==================" << endl;
        cout << "Escolha uma opção: ";

        int opcao;
        cin >> opcao;

        switch (opcao)
        {
            case 1:
            {
                string nome;
                int numero;
                cout << "Digite o nome do candidato: ";
                cin.ignore();
                getline(cin, nome);
                cout << "Digite o número do candidato: ";
                cin >> numero;
                inserirCandidato(&listaCandidatos, nome, numero);
                break;
            }
            case 2:
            {
                int numero;
                cout << "Digite o número do candidato a ser removido: ";
                cin >> numero;
                removerCandidato(&listaCandidatos, numero);
                break;
            }
            case 3:
                listarCandidatos(listaCandidatos);
                break;
            case 4:
                salvarCandidatos(listaCandidatos);
                break;
            case 0:
                salvarCandidatos(listaCandidatos);
                cout << "Encerrando o programa..." << endl;
                return;
            default:
                cout << "Opção inválida. Tente novamente." << endl;
        }
    }
}

int main()
{
    menu();
    return 0;
}

       
