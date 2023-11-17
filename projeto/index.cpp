#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

// Registro base que vai receber as informações do arquivo.

struct base
{
    int id;
    string nome;
    string objetivo;
    string musculos;
    int dificuldade;
};

/* A função permite ao usuário decidir se deseja continuar consultando itens. */

bool repete()
{
    int repetir = 0;
    cout << "Deseja repetir o processo?\n";

    while ((repetir != 1) && (repetir != 2))
    {
        cout << "1 - Continuar.\n2 - Sair.\n";

        cin >> repetir;
        cin.ignore();

        if (repetir == 1)
            return true;
        else if (repetir == 2)
            return false;
    }
    return true;
}

// Funcao para inserir novos dados no arquivo.

void inserirArquivo(base *ptrVetorCompleto, int *ptrVetorModificado, int &capacidade, int &tamanho)
{
    ofstream dados("dados.csv", std::ios::out | std::ios::app);
    do
    {
        if (tamanho == capacidade)
        {
            capacidade += 2;
            base *novoVetor = new base[capacidade];
            copy(ptrVetorCompleto, ptrVetorCompleto + tamanho, novoVetor);
            delete[] ptrVetorCompleto;
            ptrVetorCompleto = novoVetor;
        }

        cout << "Inserção de novos dados no arquivo.\n";
        cout << "Digite as informacoes do exercicio conforme solicitado.\n";

        // Escrevendo novos dados no vetor.
        cout << "ID do novo exercicio: ";
        cin >> ptrVetorCompleto[tamanho].id;
        cin.ignore();
        cout << "Nome do novo exercicio: ";
        getline(cin, ptrVetorCompleto[tamanho].nome);
        cout << "Objetivo do novo exercicio: ";
        getline(cin, ptrVetorCompleto[tamanho].objetivo);
        cout << "Musculos do novo exercicio: ";
        getline(cin, ptrVetorCompleto[tamanho].musculos);
        cout << "Dificuldade do novo exercicio: ";
        cin >> ptrVetorCompleto[tamanho].dificuldade;
        cin.ignore();

        // Escrevendo os novos dados no arquivo
        dados << ptrVetorCompleto[tamanho].id << ';';
        dados << ptrVetorCompleto[tamanho].nome << ';';
        dados << ptrVetorCompleto[tamanho].objetivo << ';';
        dados << ptrVetorCompleto[tamanho].musculos << ';';
        dados << ptrVetorCompleto[tamanho].dificuldade << '\n';

        ptrVetorModificado[tamanho] = 1;
        tamanho++;
    } while ((repete()));

    dados.close();
}

/* Função que permite a modificação dos dados de um elemento específico no vetor 'ptrVetorCompleto[]',
baseando-se na escolha do usuário. Dependendo da mesma, os dados do vetor são modificados,
a variável 'ptrVetorModificado[]' marca o índice correspondente.*/

void alterarDado(base *ptrVetorCompleto, int *ptrVetorModificado, int i)
{
    int valorAlterar;

    cout << "O que você deseja alterar?\n1- ID\n2 - Nome\n3 - Objetivo\n4 - Musculos\n5 - Dificuldade\n6 - Tudo\n";

    cin >> valorAlterar;
    cin.ignore();

    if (valorAlterar == 1)
    {
        cout << "Digite o novo valor: ";
        cin >> ptrVetorCompleto[i].id;
        cin.ignore();
        ptrVetorModificado[i] = 1;
    }
    else if (valorAlterar == 2)
    {
        cout << "Digite o novo valor: ";
        getline(cin, ptrVetorCompleto[i].nome);
        ptrVetorModificado[i] = 1;
    }
    else if (valorAlterar == 3)
    {
        cout << "Digite o novo valor: ";
        getline(cin, ptrVetorCompleto[i].objetivo);
        ptrVetorModificado[i] = 1;
    }
    else if (valorAlterar == 4)
    {
        cout << "Digite o novo valor: ";
        getline(cin, ptrVetorCompleto[i].musculos);
        ptrVetorModificado[i] = 1;
    }
    else if (valorAlterar == 5)
    {
        cout << "Digite o novo valor: ";
        cin >> ptrVetorCompleto[i].dificuldade;
        cin.ignore();
        ptrVetorModificado[i] = 1;
    }
    else if (valorAlterar == 6)
    {
        ptrVetorModificado[i] = 1;
        cout << "Insira o novos dados\n";
        cout << "Novo ID exercicio: ";
        cin >> ptrVetorCompleto[i].id;
        cin.ignore();
        cout << "Novo nome do exercicio: ";
        getline(cin, ptrVetorCompleto[i].nome);
        cout << "Novo objetivo do exercicio: ";
        getline(cin, ptrVetorCompleto[i].objetivo);
        cout << "Novos musculos do exercicio: ";
        getline(cin, ptrVetorCompleto[i].musculos);
        cout << "Nova dificuldade do exercicio: ";
        cin >> ptrVetorCompleto[i].dificuldade;
        cin.ignore();
    }
    else
    {
        cout << "Opção inválida, tente novamente." << endl;
    }
}

/* Função que lê um arquivo chamado "dados.csv" e carrega os dados para um vetor de estruturas 'ptrVetorCompleto[]'.
Retorna um booleano indicando se o carregamento do arquivo foi bem-sucedido ou não.*/

bool receberArquivo(base *&ptrVetorCompleto, int &tamanho, int &capacidade)
{
    string cabecalho;
    fstream entrada("dados.csv");
    if (entrada)
    {
        getline(entrada, cabecalho, '#');
        while (!entrada.eof())
        {
            if (tamanho == capacidade)
            {
                capacidade *= 2;
                base *novoVetor = new base[capacidade];
                copy(ptrVetorCompleto, ptrVetorCompleto + tamanho, novoVetor);
                delete[] ptrVetorCompleto;
                ptrVetorCompleto = novoVetor;
            }
            entrada >> ptrVetorCompleto[tamanho].id;
            entrada.ignore();
            getline(entrada, ptrVetorCompleto[tamanho].nome, ';');
            getline(entrada, ptrVetorCompleto[tamanho].objetivo, ';');
            getline(entrada, ptrVetorCompleto[tamanho].musculos, ';');
            entrada >> ptrVetorCompleto[tamanho].dificuldade;
            entrada.ignore();
            tamanho++;
        }
        entrada.close();
        cout << "Arquivo carregado com sucesso!" << endl;
        return true;
    }
    else
    
    {
        cout << "Erro ao carregar o arquivo.";
        return false;
    }
}

/* Função que busca se o exercício que o usuário deseja consultar está presente no arquivo.
Retorna um tipo bool para verificar possíveis erros que podem ocorrer dependendo da entrada do usuário.
Por exemplo, se um texto do tipo string for inserido no campo de ID, que deveria ser um número inteiro, isso pode gerar um erro que encerrará
o código prematuramente e imprimirá textos indesejados. Nesta disciplina, ainda não foram introduzidos métodos de verificação do tipo de dado inserido em uma variável.
Portanto, optei por seguir dessa maneira.*/

bool buscaArquivo(base *ptrVetorCompleto, int *ptrVetorModificado, int tamanho)
{
    bool continua = true;
    while (continua)
    {
        bool achou = false;
        int itemAlterar = -1;
        int busca;

        cout << "Buscar no arquivo.\nAtualmente o programa suporta dois tipos de busca:\n1 - Busca por Nome.\n2 - Busca por ID." << endl;
        cin >> busca;
        cin.ignore();

        // Busca por nome.

        if (busca == 1)
        {
            cout << "Digite o nome completo do exercicio: ";
            string exercicio;
            getline(cin, exercicio);
            int i = 0;
            while (i <= tamanho && !achou)
            {
                if (ptrVetorCompleto[i].nome == exercicio)
                {
                    cout << "Exercicio encontrado, os seguintes dados estao cadastrados: \n"
                         << endl;
                    cout << ptrVetorCompleto[i].id;
                    cout << " -- ";
                    cout << ptrVetorCompleto[i].nome;
                    cout << " -- ";
                    cout << ptrVetorCompleto[i].objetivo;
                    cout << " -- ";
                    cout << ptrVetorCompleto[i].musculos;
                    cout << " -- ";
                    cout << ptrVetorCompleto[i].dificuldade;
                    cout << endl;

                    itemAlterar = i;
                    achou = true;
                }
                i++;
            }
        }

        // Busca por ID.
        else if (busca == 2)
        {
            cout << "Digite o ID do exercicio: ";
            int idBusca;
            cin >> idBusca;
            cin.ignore();

            int i = 0;
            while (i <= tamanho && !achou)
            {
                if (ptrVetorCompleto[i].id == idBusca)
                {
                    cout << "Exercicio encontrado, os seguintes dados estao cadastrados: \n";
                    cout << "\nID: ";
                    cout << ptrVetorCompleto[i].id;
                    cout << "\nNome: ";
                    cout << ptrVetorCompleto[i].nome;
                    cout << "\nObjetivo: ";
                    cout << ptrVetorCompleto[i].objetivo;
                    cout << "\nMusculos: ";
                    cout << ptrVetorCompleto[i].musculos;
                    cout << "\nDificuldade: ";
                    cout << ptrVetorCompleto[i].dificuldade;
                    cout << endl;

                    achou = true;
                    itemAlterar = i;
                }
                i++;
            }
        }
        // Caso inserido um argumento invalido.
        else if (busca != 1 && busca != 2)
        {
            cout << "Entrada nao reconhecida.\n";
            return false;
        }

        if (achou)
        {
            cout << "\nDeseja alterar algo nesse exercicio?\n";
            int altera;
            do
            {
                cout << "1 - Alterar.\n2 - Nao alterar.\n";
                cin >> altera;
            } while (altera != 1 && altera != 2);
            if (altera == 1)
                alterarDado(ptrVetorCompleto, ptrVetorModificado, itemAlterar);
        }

        else
            cout << "Exercicio nao encontrado!" << endl;

        if (repete())
            continua = true;
        else
            continua = false;
    }
    return true;
}

// Função que salva as modificações do vetor 'ptrVetorCompleto', usado pra manipular os valores e salva as açterações no arquivo

void escreverDados(base *ptrVetorCompleto, int *ptrVetorModificado, int tamanho, int capacidade)
{

    bool foiModificado = false;
    int entrada;
    int i = 0;

    while (i < capacidade && !foiModificado)
    {
        if (ptrVetorModificado[i] == 1)
            foiModificado = true;
        i++;
    }
    if (!foiModificado)
        cout << "Nenhuma alteração feita no arquivo.";
    else
    {
        ofstream saida("saida.dat");
        cout << "Deseja salvar todos os dados no arquivo ou apenas aqueles modificados?\n";

        do
        {
            cout << "1 - Todos os dados.\n2 - Apenas os modificados.\n";
            cin >> entrada;
            cin.ignore();

            if (entrada == 1)
            {
                for (int i = 0; i < tamanho; i++)
                {
                    saida << ptrVetorCompleto[i].id;
                    saida << ";";
                    saida << ptrVetorCompleto[i].nome;
                    saida << ";";
                    saida << ptrVetorCompleto[i].objetivo;
                    saida << ";";
                    saida << ptrVetorCompleto[i].musculos;
                    saida << ";";
                    saida << ptrVetorCompleto[i].dificuldade;
                    saida << endl;
                }
            }
            else if (entrada == 2)
            {
                for (int i = 0; i < tamanho; i++)
                {
                    if (ptrVetorModificado[i] == 1)
                    {
                        saida << ptrVetorCompleto[i].id;
                        saida << ";";
                        saida << ptrVetorCompleto[i].nome;
                        saida << ";";
                        saida << ptrVetorCompleto[i].objetivo;
                        saida << ";";
                        saida << ptrVetorCompleto[i].musculos;
                        saida << ";";
                        saida << ptrVetorCompleto[i].dificuldade;
                        saida << endl;
                    }
                }
            }
            else
                cout << "Opção inválida, tente novamente." << endl;

        } while (entrada != 1 && entrada != 2);

        cout << "Arquivo alterado com sucesso!" << endl;

        saida.close();
    }
}

// Função principal, usada pra chamar as outras funcoes do codigo, verificando se certas condições são atendidas.

int main()
{
    int tamanho = 0, capacidade = 100;
    base *ptrVetorCompleto = new base[capacidade];
    int *ptrVetorModificado = new int[capacidade];

    for (int i = 0; i < capacidade; i++)
    {
        ptrVetorModificado[i] = 0;
    }

    if (receberArquivo(ptrVetorCompleto, tamanho, capacidade))
    {
        int modo;
        cout << "O que deseja fazer no arquivo?\n";
        do
        {
            cout << "1 - Buscar e alterar.\n2 - Inserir novos dados.\n";
            cin >> modo;
            if (modo == 1)
            {
                if (buscaArquivo(ptrVetorCompleto, ptrVetorModificado, tamanho))
                    escreverDados(ptrVetorCompleto, ptrVetorModificado, tamanho, capacidade);
            }
            else if (modo == 2)
            {
                inserirArquivo(ptrVetorCompleto, ptrVetorModificado, tamanho, capacidade);
                escreverDados(ptrVetorCompleto, ptrVetorModificado, tamanho, capacidade);
            }
        } while (modo != 1 && modo != 2);
    }
    else
    {
        cout << "Erro ao receber arquivo!" << endl;
    }

    delete[] ptrVetorCompleto;
    delete[] ptrVetorModificado;

    return 0;
}