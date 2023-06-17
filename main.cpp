#include <iostream>
#include <fstream>
using namespace std;

// Definição das estruturas de dados para Candidato, Eleitor e Voto
struct Candidato
{
    string nome;
    int numero;
    int votos;
    Candidato *proximo;
};

struct Eleitor
{
    string nome;
    int titulo;
    bool apto;
    Eleitor *proximo;
};

struct Voto
{
    Eleitor *eleitor;
    Candidato *candidato;
    Voto *proximo;
};

// Função para criar um novo Candidato
Candidato *criarCandidato(string nome, int numero)
{
    // Aloca memória para um novo Candidato
    Candidato *novoCandidato = new Candidato;

    // Define os atributos do novo Candidato
    novoCandidato->nome = nome;
    novoCandidato->numero = numero;
    novoCandidato->votos = 0;
    novoCandidato->proximo = nullptr;

    // Retorna o novo Candidato criado
    return novoCandidato;
}

// Função para criar um novo Eleitor
Eleitor *criarEleitor(string nome, int titulo, bool apto)
{
    // Aloca memória para um novo Eleitor
    Eleitor *novoEleitor = new Eleitor;

    // Define os atributos do novo Eleitor
    novoEleitor->nome = nome;
    novoEleitor->titulo = titulo;
    novoEleitor->apto = apto;
    novoEleitor->proximo = nullptr;

    // Retorna o novo Eleitor criado
    return novoEleitor;
}

// Função para criar um novo Voto
Voto *criarVoto(Eleitor *eleitor, Candidato *candidato)
{
    // Aloca memória para um novo Voto
    Voto *novoVoto = new Voto;

    // Define os atributos do novo Voto
    novoVoto->eleitor = eleitor;
    novoVoto->candidato = candidato;
    novoVoto->proximo = nullptr;

    // Retorna o novo Voto criado
    return novoVoto;
}

// Função para inserir um Candidato na lista de candidatos
void inserirCandidato(Candidato **lista, string nome, int numero)
{
    // Cria um novo Candidato
    Candidato *novoCandidato = criarCandidato(nome, numero);

    // Verifica se a lista está vazia
    if (*lista == nullptr)
    {
        // Se estiver vazia, o novo Candidato se torna o primeiro da lista
        *lista = novoCandidato;
    }
    else
    {
        // Caso contrário, percorre a lista até o último Candidato
        Candidato *atual = *lista;
        while (atual->proximo != nullptr)
        {
            atual = atual->proximo;
        }

        // Insere o novo Candidato no final da lista
        atual->proximo = novoCandidato;
    }
}

// Função para remover um Candidato da lista de candidatos
void removerCandidato(Candidato **lista, int numero)
{
    // Verifica se a lista está vazia
    if (*lista == nullptr)
    {
        cout << "A lista de candidatos está vazia." << endl;
        return;
    }

    // Variáveis para percorrer a lista
    Candidato *atual = *lista;
	    Candidato *anterior = nullptr;

    // Percorre a lista em busca do Candidato a ser removido
    while (atual != nullptr && atual->numero != numero)
    {
        anterior = atual;
        atual = atual->proximo;
    }

    // Verifica se o Candidato foi encontrado
    if (atual == nullptr)
    {
        cout << "Candidato não encontrado." << endl;
        return;
    }

    // Remove o Candidato da lista
    if (anterior == nullptr)
    {
        // Caso seja o primeiro da lista
        *lista = atual->proximo;
    }
    else
    {
        // Caso contrário
        anterior->proximo = atual->proximo;
    }

    // Libera a memória alocada pelo Candidato removido
    delete atual;
    cout << "Candidato removido." << endl;
}

// Função para listar os Candidatos da lista
void listarCandidatos(Candidato *lista)
{
    // Verifica se a lista está vazia
    if (lista == nullptr)
    {
        cout << "A lista de candidatos está vazia." << endl;
        return;
    }

    cout << "Lista de candidatos:" << endl;

    // Percorre a lista de Candidatos e exibe suas informações
    Candidato *atual = lista;
    while (atual != nullptr)
    {
        cout << "Nome: " << atual->nome << ", Número: " << atual->numero << ", Votos: " << atual->votos << endl;
        atual = atual->proximo;
    }
}

// Função para salvar os Candidatos em um arquivo
void salvarCandidatos(Candidato *lista)
{
    // Abre o arquivo para escrita
    ofstream arquivo("candidatos.txt");

    // Verifica se o arquivo foi aberto corretamente
    if (!arquivo)
    {
        cout << "Erro ao abrir o arquivo." << endl;
        return;
    }

    // Percorre a lista de Candidatos e escreve suas informações no arquivo
    Candidato *atual = lista;
    while (atual != nullptr)
    {
        arquivo << atual->nome << "," << atual->numero << "," << atual->votos << endl;
        atual = atual->proximo;
    }

    // Fecha o arquivo
    arquivo.close();
    cout << "Candidatos salvos com sucesso." << endl;
}

// Função para carregar os Candidatos a partir de um arquivo
Candidato *carregarCandidatos()
{
    // Abre o arquivo para leitura
    ifstream arquivo("candidatos.txt");

    // Verifica se o arquivo foi aberto corretamente
    if (!arquivo)
    {
        cout << "Erro ao abrir o arquivo." << endl;
        return nullptr;
    }

    Candidato *lista = nullptr;
    string linha;

    // Lê cada linha do arquivo
    while (getline(arquivo, linha))
    {
        string nome;
        int numero;
        int votos;

        // Cria um stringstream para extrair os dados da linha
        stringstream ss(linha);

        // Extrai o nome do candidato até a primeira vírgula
        getline(ss, nome, ',');

        // Extrai o número do candidato
        ss >> numero;

        // Ignora a vírgula após o número
        ss.ignore();

        // Extrai a quantidade de votos do candidato
        ss >> votos;

        // Insere o Candidato
		        inserirCandidato(&lista, nome, numero);

        // Encontra o Candidato na lista pelo número
        Candidato *atual = lista;
        while (atual != nullptr && atual->numero != numero)
        {
            atual = atual->proximo;
        }

        // Atualiza a quantidade de votos do Candidato
        if (atual != nullptr)
        {
            atual->votos = votos;
        }
    }

    // Fecha o arquivo
    arquivo.close();

    // Retorna a lista de Candidatos carregada do arquivo
    return lista;
}

// Função para exibir o menu e interagir com o usuário
void menu()
{
    // Carrega a lista de Candidatos do arquivo
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
