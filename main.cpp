#include <iostream>
#include <fstream>

using namespace std;

struct Candidato {
    string nome;
    int numero;
    int votos;
};

// Função para inserir um candidato na lista
void cadastrarCandidato(Candidato**& listaDeCandidatos, int&  tamanhoListaDeCandidatos) {
    Candidato* novoCandidato = new Candidato;

    cout << "Digite o nome do candidato: ";
    cin >> novoCandidato->nome;

    cout << "Digite o número do candidato: ";
    cin >> novoCandidato->numero;

    novoCandidato->votos = 0;

    /*
    uma nova lista de candidatos é criada com um 
    tamanho maior que a lista original. Os candidatos 
    da lista original são copiados para a nova lista. 
    Um novo candidato é adicionado à nova lista.
     A memória ocupada pela lista original é liberada. 
     A variável da lista original é atualizada para 
     apontar para a nova lista. O tamanho da lista é 
     incrementado. Resumindo, o bloco de código realiza
     uma expansão da lista de candidatos, adicionando 
     um novo candidato. */
    Candidato** novaListaCandidatos = new Candidato*[ tamanhoListaDeCandidatos + 1];
    for (int i = 0; i <  tamanhoListaDeCandidatos; i++) {
        novaListaCandidatos[i] = listaDeCandidatos[i];
    }
    novaListaCandidatos[ tamanhoListaDeCandidatos] = novoCandidato;

    delete[] listaDeCandidatos;

    listaDeCandidatos = novaListaCandidatos;
     tamanhoListaDeCandidatos++;

    cout << "Candidato cadastrado com sucesso!" << endl;
}

// Função para remover um candidato da lista
void removerCandidato(Candidato**& listaDeCandidatos, int&  tamanhoListaDeCandidatos, int numeroCandidato) {
    int indice = -1;
    for (int i = 0; i <  tamanhoListaDeCandidatos; i++) {
        if (listaCandidatos[i]->numero == numeroCandidato) {
            indice = i;
            break;
        }
    }

    if (indice != -1) {
        delete listaDeCandidatos[indice];

        for (int i = indice; i <  tamanhoListaDeCandidatos - 1; i++) {
            listaDeCandidatos[i] = listaDeCandidatos[i + 1];
        }


        /*
        Nesta linha de código, uma nova matriz de ponteiros 
        para objetos do tipo Candidato é criada com um 
        tamanho menor que a matriz original.
        */
        Candidato** novaListaCandidatos = new Candidato*[ tamanhoListaDeCandidatos - 1];
        for (int i = 0; i <  tamanhoListaDeCandidatos - 1; i++) {
            novaListaCandidatos[i] = listaDeCandidatos[i];
        }

        delete[] listaDeCandidatos;

        listaDeCandidatos = novaListaCandidatos;
         tamanhoListaDeCandidatos--;

        cout << "Candidato removido com sucesso!" << endl;
    } else {
        cout << "Candidato não encontrado." << endl;
    }
}

// Função para listar os candidatos
void listarCandidatos(Candidato** listaDeCandidatos, int  tamanhoListaDeCandidatos) {
    cout << "Lista de candidatos:" << endl;
    for (int i = 0; i <  tamanhoListaDeCandidatos; i++) {
        cout << "Número: " << listaDeCandidatos[i]->numero << ", Nome: " << listaDeCandidatos[i]->nome << ", Votos: " << listaDeCandidatos[i]->votos << endl;
    }
}

// Função para salvar a lista de candidatos em arquivo
void salvarCandidatos(Candidato** listaDeCandidatos, int  tamanhoListaDeCandidatos) {
    ofstream arquivo("candidatos.txt");

    if (arquivo.is_open()) {
        arquivo <<  tamanhoListaDeCandidatos << endl;
        for (int i = 0; i <  tamanhoListaDeCandidatos; i++) {
            arquivo << listaDeCandidatos[i]->nome << endl;
            arquivo << listaDeCandidatos[i]->numero << endl;
            arquivo << listaDeCandidatos[i]->votos << endl;
        }

        arquivo.close();

        cout << "Lista de candidatos salva com sucesso!" << endl;
    } else {
        cout << "Erro ao abrir o arquivo de candidatos." << endl;
    }
}

// Função para carregar a lista de candidatos do arquivo
void carregarCandidatos(Candidato**& listaDeCandidatos, int&  tamanhoListaDeCandidatos) {
    ifstream arquivo("candidatos.txt");

    if (arquivo.is_open()) {
        arquivo >>  tamanhoListaDeCandidatos;

        /*
        a variável listaDeCandidatos está sendo 
        atualizada para referenciar um novo array 
        de ponteiros para objetos Candidato, com 
        um tamanho específico indicado pela variável 
         tamanhoListaDeCandidatos
        */
        listaDeCandidatos = new Candidato*[ tamanhoListaDeCandidatos];

        for (int i = 0; i <  tamanhoListaDeCandidatos; i++) {
            listaDeCandidatos[i] = new Candidato;
            arquivo >> listaDeCandidatos[i]->nome;
            arquivo >> listaDeCandidatos[i]->numero;
            arquivo >> listaDeCandidatos[i]->votos;
        }

        arquivo.close();

        cout << "Lista de candidatos carregada com sucesso!" << endl;
    } else {
        cout << "Erro ao abrir o arquivo de candidatos." << endl;
    }
}

struct Eleitor {
    string nome;
    int titulo;
};

// Função para inserir um eleitor na lista
void cadastrarEleitor(Eleitor**& listaEleitores, int& tamanhoListaEleitores) {
    /*
    um novo objeto Eleitor está sendo criado 
    dinamicamente usando new e seu endereço 
    de memória está sendo armazenado no ponteiro 
    novoEleitor.
    */
    Eleitor* novoEleitor = new Eleitor;

    cout << "Digite o nome do eleitor: ";
    cin >> novoEleitor->nome;

    cout << "Digite o número do título do eleitor: ";
    cin >> novoEleitor->titulo;

    /*
    um novo array dinâmico de ponteiros para Eleitor 
    está sendo criado, com um tamanho maior do que o 
    array original. O endereço de memória desse novo 
    array é armazenado no ponteiro novaListaEleitores.um novo array dinâmico de ponteiros para Eleitor está sendo criado, com um tamanho maior do que o array original. O endereço de memória desse novo array é armazenado no ponteiro novaListaEleitores.
    */
    Eleitor** novaListaEleitores = new Eleitor*[tamanhoListaEleitores + 1];
    for (int i = 0; i < tamanhoListaEleitores; i++) {
        novaListaEleitores[i] = listaEleitores[i];
    }
    novaListaEleitores[tamanhoListaEleitores] = novoEleitor;

    delete[] listaEleitores;

    listaEleitores = novaListaEleitores;
    tamanhoListaEleitores++;

    cout << "Eleitor cadastrado com sucesso!" << endl;
}

// Função para verificar se um eleitor está apto a votar
bool checarEleitorApto(Eleitor** listaEleitores, int tamanhoListaEleitores, int tituloEleitor) {
    for (int i = 0; i < tamanhoListaEleitores; i++) {
        if (listaEleitores[i]->titulo == tituloEleitor) {
            return true;
        }
    }
    return false;
}

// Função para salvar a lista de eleitores em arquivo
void salvarEleitores(Eleitor** listaEleitores, int tamanhoListaEleitores) {
    ofstream arquivo("eleitores.txt");

    if (arquivo.is_open()) {
        arquivo << tamanhoListaEleitores << endl;
        for (int i = 0; i < tamanhoListaEleitores; i++) {
            arquivo << listaEleitores[i]->nome << endl;
            arquivo << listaEleitores[i]->titulo << endl;
        }

        arquivo.close();

        cout << "Lista de eleitores salva com sucesso!" << endl;
    } else {
        cout << "Erro ao abrir o arquivo de eleitores." << endl;
    }
}

// Função para carregar a lista de eleitores do arquivo
void carregarEleitores(Eleitor**& listaEleitores, int& tamanhoListaEleitores) {
    ifstream arquivo("eleitores.txt");

    if (arquivo.is_open()) {
        arquivo >> tamanhoListaEleitores;

        /*
        corre a realocação de memória para o array 
        listaEleitores. Um novo array é criado, 
        com um tamanho maior ou menor, dependendo 
        do valor de tamanhoListaEleitores. Em seguida, 
        o ponteiro listaEleitores é atualizado para 
        apontar para o novo array recém-alocado. 
        Essa operação permite ajustar o tamanho da 
        lista de eleitores, adicionando ou removendo 
        elementos conforme necessário.
        */
        listaEleitores = new Eleitor*[tamanhoListaEleitores];

        for (int i = 0; i < tamanhoListaEleitores; i++) {
            listaEleitores[i] = new Eleitor;
            arquivo >> listaEleitores[i]->nome;
            arquivo >> listaEleitores[i]->titulo;
        }

        arquivo.close();

        cout << "Lista de eleitores carregada com sucesso!" << endl;
    } else {
        cout << "Erro ao abrir o arquivo de eleitores." << endl;
    }
}



// Função para registrar um voto
void registrarVoto(Candidato** listaDeCandidatos, int  tamanhoListaDeCandidatos, Eleitor** listaEleitores, int tamanhoListaEleitores, Voto**& listaVotos, int& tamanhoListaVotos) {
    int tituloEleitor;
    cout << "Digite o número do título do eleitor: ";
    cin >> tituloEleitor;

    if (checarEleitorApto(listaEleitores, tamanhoListaEleitores, tituloEleitor)) {
        cout << "Lista de candidatos:" << endl;
        for (int i = 0; i <  tamanhoListaDeCandidatos; i++) {
            cout << "Número: " << listaDeCandidatos[i]->numero << ", Nome: " << listaDeCandidatos[i]->nome << endl;
        }

        int numeroCandidato;
        cout << "Digite o número do candidato escolhido: ";
        cin >> numeroCandidato;

        bool candidatoEncontrado = false;
        for (int i = 0; i <  tamanhoListaDeCandidatos; i++) {
            if (listaCandidatos[i]->numero == numeroCandidato) {
                listaDeCandidatos[i]->votos++;
                candidatoEncontrado = true;
                break;
            }
        }

        if (candidatoEncontrado) {
            Voto* novoVoto = new Voto;
            novoVoto->numeroCandidato = numeroCandidato;

            Voto** novaListaVotos = new Voto*[tamanhoListaVotos + 1];
            for (int i = 0; i < tamanhoListaVotos; i++) {
                novaListaVotos[i] = listaVotos[i];
            }
            novaListaVotos[tamanhoListaVotos] = novoVoto;

            delete[] listaVotos;

            listaVotos = novaListaVotos;
            tamanhoListaVotos++;

            cout << "Voto registrado com sucesso!" << endl;
        } else {
            cout << "Candidato não encontrado." << endl;
        }
    } else {
        cout << "Eleitor não apto para votar." << endl;
    }
}

// Função para gerar o relatório
void gerarRelatorio(Candidato** listaDeCandidatos, int  tamanhoListaDeCandidatos, Voto** listaVotos, int tamanhoListaVotos, Eleitor** listaEleitores, int tamanhoListaEleitores) {
    cout << "Relatório de votação:" << endl;
    cout << "-----------------------" << endl;
    cout << "Total de votos registrados: " << tamanhoListaVotos << endl;

    cout << "Votos por candidato:" << endl;
    for (int i = 0; i <  tamanhoListaDeCandidatos; i++) {
        cout << "Número: " << listaDeCandidatos[i]->numero << ", Nome: " << listaDeCandidatos[i]->nome << ", Votos: " << listaDeCandidatos[i]->votos << endl;
    }

    int eleitoresFaltantes = 0;
    for (int i = 0; i < tamanhoListaEleitores; i++) {
        bool eleitorVotou = false;
        for (int j = 0; j < tamanhoListaVotos; j++) {
            if (listaEleitores[i]->titulo == listaVotos[j]->numeroCandidato) {
                eleitorVotou = true;
                break;
            }
        }

        if (!eleitorVotou) {
            eleitoresFaltantes++;
        }
    }

    cout << "Eleitores que faltaram: " << eleitoresFaltantes << endl;
}

// Função para salvar o relatório em arquivo
void salvarRelatorio(Candidato** listaDeCandidatos, int  tamanhoListaDeCandidatos, Voto** listaVotos, int tamanhoListaVotos, Eleitor** listaEleitores, int tamanhoListaEleitores) {
    ofstream arquivo("relatorio.txt");

    if (arquivo.is_open()) {
        arquivo << "Relatório de votação:" << endl;
        arquivo << "-----------------------" << endl;
        arquivo << "Total de votos registrados: " << tamanhoListaVotos << endl;

        arquivo << "Votos por candidato:" << endl;
        for (int i = 0; i <  tamanhoListaDeCandidatos; i++) {
            arquivo << "Número: " << listaDeCandidatos[i]->numero << ", Nome: " << listaDeCandidatos[i]->nome << ", Votos: " << listaDeCandidatos[i]->votos << endl;
        }

        int eleitoresFaltantes = 0;
        for (int i = 0; i < tamanhoListaEleitores; i++) {
            bool eleitorVotou = false;
            for (int j = 0; j < tamanhoListaVotos; j++) {
                if (listaEleitores[i]->titulo == listaVotos[j]->numeroCandidato) {
                    eleitorVotou = true;
                    break;
                }
            }

            if (!eleitorVotou) {
                eleitoresFaltantes++;
            }
        }

        arquivo << "Eleitores que faltaram: " << eleitoresFaltantes << endl;

        arquivo.close();

        cout << "Relatório salvo com sucesso!" << endl;
    } else {
        cout << "Erro ao abrir o arquivo de relatório." << endl;
    }
}

int main() {
    Candidato** listaDeCandidatos = nullptr;
    int  tamanhoListaDeCandidatos = 0;

    Eleitor** listaEleitores = nullptr;
    int tamanhoListaEleitores = 0;

    Voto** listaVotos = nullptr;
    int tamanhoListaVotos = 0;

    // Carregar dados do arquivo (se existirem)
    carregarCandidatos(listaCandidatos,  tamanhoListaDeCandidatos);
    carregarEleitores(listaEleitores, tamanhoListaEleitores);

    int opcao;
    do {
        cout << "==== Sistema de Votação ====" << endl;
        cout << "1. Cadastrar candidato" << endl;
        cout << "2. Remover candidato" << endl;
        cout << "3. Listar candidatos" << endl;
        cout << "4. Cadastrar eleitor" << endl;
        cout << "5. Registrar voto" << endl;
        cout << "6. Gerar relatório" << endl;
        cout << "7. Salvar candidatos em arquivo" << endl;
        cout << "8. Salvar eleitores em arquivo" << endl;
        cout << "9. Salvar relatório em arquivo" << endl;
        cout << "0. Sair" << endl;
        cout << "Digite sua opção: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                cadastrarCandidato(listaCandidatos,  tamanhoListaDeCandidatos);
                break;
            case 2:
                int numeroCandidato;
                cout << "Digite o número do candidato a ser removido: ";
                cin >> numeroCandidato;
                removerCandidato(listaCandidatos,  tamanhoListaDeCandidatos, numeroCandidato);
                break;
            case 3:
                listarCandidatos(listaCandidatos,  tamanhoListaDeCandidatos);
                break;
            case 4:
                cadastrarEleitor(listaEleitores, tamanhoListaEleitores);
                break;
            case 5:
                registrarVoto(listaCandidatos,  tamanhoListaDeCandidatos, listaEleitores, tamanhoListaEleitores, listaVotos, tamanhoListaVotos);
                break;
            case 6:
                gerarRelatorio(listaCandidatos,  tamanhoListaDeCandidatos, listaVotos, tamanhoListaVotos, listaEleitores, tamanhoListaEleitores);
                break;
            case 7:
                salvarCandidatos(listaCandidatos,  tamanhoListaDeCandidatos);
                break;
            case 8:
                salvarEleitores(listaEleitores, tamanhoListaEleitores);
                break;
            case 9:
                salvarRelatorio(listaCandidatos,  tamanhoListaDeCandidatos, listaVotos, tamanhoListaVotos, listaEleitores, tamanhoListaEleitores);
                break;
            case 0:
                // Sair do programa
                break;
            default:
                cout << "Opção inválida. Digite novamente." << endl;
        }
    } while (opcao != 0);

    // Liberar memória alocada
    for (int i = 0; i < tamanhoListaDeCandidatos; i++) {
        delete listaDeCandidatos[i];
    }
    delete[] listaDeCandidatos;

    for (int i = 0; i < tamanhoListaEleitores; i++) {
        delete listaEleitores[i];
    }
    delete[] listaEleitores;

    for (int i = 0; i < tamanhoListaVotos; i++) {
        delete listaVotos[i];
    }
    delete[] listaVotos;

    return 0;
}