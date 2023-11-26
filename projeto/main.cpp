#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <stdlib.h>
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

void redimensionamento(base *&cadastro, int *&alteracoes, int tamanho, int &capacidade)
{
    capacidade += 10;
    base *novoVetor = NULL;
    int *novoVetorModificado = NULL;
    novoVetor = new base[capacidade];
    novoVetorModificado = new int[capacidade]();
    copy(cadastro, cadastro + tamanho, novoVetor);
    copy(alteracoes, alteracoes + tamanho, novoVetorModificado);
    delete[] cadastro;
    delete[] alteracoes;
    cadastro = novoVetor;
    alteracoes = novoVetorModificado;
}

// Procedimento para inserir novos dados no arquivo.
void inserir(base *&cadastro, int *&alteracoes, int &tamanho, int &capacidade)
{
    // Verifica se há espaço suficiente e redimensiona se necessário.
    if (tamanho == (capacidade - 1))
        redimensionamento(cadastro, alteracoes, tamanho, capacidade);

    cout << "Inserção de novos dados no arquivo.\n";
    cout << "Digite as informacoes do exercicio conforme solicitado.\n";

    int novoID, novaDificuldade;
    string novoNome, novoObjetivo, novosMusculos;

    // Escrevendo novos dados em variaveis.
    cout << "ID do novo exercicio (que seja um número inteiro): ";
    cin >> novoID;
    cin.ignore();
    cout << "Nome do novo exercicio: ";
    getline(cin, novoNome);
    cout << "Objetivo do novo exercicio: ";
    getline(cin, novoObjetivo);
    cout << "Musculos do novo exercicio: ";
    getline(cin, novosMusculos);
    cout << "Dificuldade do novo exercicio (que seja um número inteiro): ";
    cin >> novaDificuldade;
    cin.ignore();

    // Escrevendo os novos dados no arquivo
    int i = tamanho;
    cadastro[i].id = novoID;
    cadastro[i].nome = novoNome;
    cadastro[i].objetivo = novoObjetivo;
    cadastro[i].musculos = novosMusculos;
    cadastro[i].dificuldade = novaDificuldade;

    alteracoes[tamanho] = 1;
    tamanho++;

    cout << "Dados inserido com sucesso, arquivo salvo." << endl;
}

// Procedimento que permite a modificação dos dados de um elemento específico no vetor 'cadastro'. Os dados do vetor são modificados, a variável 'alteracoes' marca o índice correspondente.
void alterarDado(base *cadastro, int *alteracoes, int i)
{
    int valorAlterar;

    cout << "O que você deseja alterar?\n1- ID\n2 - Nome\n3 - Objetivo\n4 - Musculos\n5 - Dificuldade\n6 - Tudo\n0 - Voltar para a tela anterior.\n";

    do
    {
        if (!(cin >> valorAlterar))
        {
            cin.clear();
            cin.ignore();
        }

        if (valorAlterar == 1)
        {
            cout << "Digite o novo valor (que seja um número inteiro): ";
            cin >> cadastro[i].id;
            cin.ignore();
            alteracoes[i] = 1;
        }
        else if (valorAlterar == 2)
        {
            cout << "Digite o novo valor: ";
            getline(cin, cadastro[i].nome);
            alteracoes[i] = 1;
        }
        else if (valorAlterar == 3)
        {
            cout << "Digite o novo valor: ";
            getline(cin, cadastro[i].objetivo);
            alteracoes[i] = 1;
        }
        else if (valorAlterar == 4)
        {
            cout << "Digite o novo valor: ";
            getline(cin, cadastro[i].musculos);
            alteracoes[i] = 1;
        }
        else if (valorAlterar == 5)
        {
            cout << "Digite o novo valor (que seja um número inteiro): ";
            cin >> cadastro[i].dificuldade;
            cin.ignore();
            alteracoes[i] = 1;
        }
        else if (valorAlterar == 6)
        {
            alteracoes[i] = 1;
            cout << "Insira o novos dados\n";
            cout << "Novo ID exercicio: ";
            cin >> cadastro[i].id;
            cin.ignore();
            cout << "Novo nome do exercicio: ";
            getline(cin, cadastro[i].nome);
            cout << "Novo objetivo do exercicio: ";
            getline(cin, cadastro[i].objetivo);
            cout << "Novos musculos do exercicio: ";
            getline(cin, cadastro[i].musculos);
            cout << "Nova dificuldade do exercicio: ";
            cin >> cadastro[i].dificuldade;
            cin.ignore();
        }
        else
        {
            cout << "Opção inválida, tente novamente.\n"
                 << endl;
        }
    } while (alteracoes[i] != 1 && valorAlterar != 0);
}

void deletar_exercicio(int *alteracoes, int i)
{
    cout << "Tem certeza que quer deletar esse exercicio, essa acao nao pode ser desfeita.\n";
    int opcao_deletar = -1;
    do
    {
        cout << "1 - Deletar mesmo assim.\n2 - Cancelar operacao.\n";
        if (!(cin >> opcao_deletar))
        {
            cin.clear();
            cin.ignore();
        }
        switch (opcao_deletar)
        {
        case 1:
            alteracoes[i] = 2;
            cout << "Exercicio deletado com sucesso. Salve o arquivo para aplicar as alteracoes\n";
            break;
        case 2:
            break;
        default:
            cout << "Entrada invalida.\n";
            break;
        }
    } while (opcao_deletar != 1 && opcao_deletar != 2);
}

// Função que lê um arquivo .csv e carrega os dados para um vetor de estruturas 'cadastro'. Retorna um booleano indicando se o carregamento do arquivo foi bem-sucedido ou não.
bool ler_CSV(base *&cadastro, int *&alteracoes, int &tamanho, int &capacidade, string &cabecalho)
{
    ifstream entrada("dados.csv");
    if (entrada)
    {
        getline(entrada, cabecalho, '#');
        while (entrada >> cadastro[tamanho].id) // Usado para verificar se o fim do arquivo foi antingido, enquanto nao for o programa vai ler mais entradas.
        {
            if (tamanho == (capacidade - 1))
                redimensionamento(cadastro, alteracoes, tamanho, capacidade);

            entrada.ignore();
            getline(entrada, cadastro[tamanho].nome, ';');
            getline(entrada, cadastro[tamanho].objetivo, ';');
            getline(entrada, cadastro[tamanho].musculos, ';');
            entrada >> cadastro[tamanho].dificuldade;
            entrada.ignore();
            tamanho++;
        }
        entrada.close();
        return true;
    }
    else
        return false;
}

// Procedimento que busca se o exercício que o usuário deseja consultar está presente no arquivo, tambem e responsavel por chamar outros procedimentos caso o usuario queira alterar ou deletar algum exercicio.
void buscaArquivo(base *cadastro, int *alteracoes, int tamanho)
{
    bool achou = false;
    int itemAlterar = -1;
    int busca;

    cout << "*\nBuscar no arquivo.\nAtualmente o programa suporta dois tipos de busca:\n";

    do
    {
        cout << "1 - Busca por Nome.\n2 - Busca por ID.\n0 - Voltar para a tela anterior.\n";

        if (!(cin >> busca))
        {
            cin.clear();
            cin.ignore();
        }

        // Busca por nome.
        if (busca == 1)
        {
            cout << "Digite o nome completo do exercicio: ";
            string exercicio;
            getline(cin, exercicio);
            int i = 0;
            while (i <= tamanho && !achou)
            {
                if (cadastro[i].nome == exercicio && alteracoes[i] != 2)
                {
                    cout << "Exercicio encontrado, os seguintes dados estao cadastrados: \n";
                    cout << endl;
                    cout << cadastro[i].id;
                    cout << " -- ";
                    cout << cadastro[i].nome;
                    cout << " -- ";
                    cout << cadastro[i].objetivo;
                    cout << " -- ";
                    cout << cadastro[i].musculos;
                    cout << " -- ";
                    cout << cadastro[i].dificuldade;
                    cout << endl;

                    itemAlterar = i;
                    achou = true;
                }
                i++;
            }
            if (!achou)
            {
                cout << "Exercicio nao encontrado\n";
            }
        }

        // Busca por ID.
        else if (busca == 2)
        {
            do
            {
                cout << "Digite o ID do exercicio:\n";
                int idBusca;
                if (!(cin >> idBusca))
                {
                    cin.clear();
                    cin.ignore();
                    cout << "Entrada invalida.\n";
                }
                else
                {
                    int i = 0;
                    while (i <= tamanho && !achou)
                    {
                        if (cadastro[i].id == idBusca && alteracoes[i] != 2)
                        {
                            cout << "Exercicio encontrado, os seguintes dados estao cadastrados: \n";
                            cout << "\nID: ";
                            cout << cadastro[i].id;
                            cout << "\nNome: ";
                            cout << cadastro[i].nome;
                            cout << "\nObjetivo: ";
                            cout << cadastro[i].objetivo;
                            cout << "\nMusculos: ";
                            cout << cadastro[i].musculos;
                            cout << "\nDificuldade: ";
                            cout << cadastro[i].dificuldade;
                            cout << endl;

                            achou = true;
                            itemAlterar = i;
                        }
                        i++;
                    }
                    if (!achou)
                    {
                        cout << "Exercicio nao encontrado\n";
                    }
                }
            } while (!achou);
        }
        else if (busca != 1 && busca != 2 && busca != 0)
            cout << "Entrada nao reconhecida.\n";

    } while (busca != 1 && busca != 2 && busca != 0);

    if (achou)
    {
        cout << "\n*\nQuer alterar algo neste exercicio?\n";
        int altera;
        do
        {
            cout << "1 - Alterar.\n2 - Deletar exercicio.\n3 - Nao alterar.\n";
            cin >> altera;
        } while (altera != 1 && altera != 2 && altera != 3);
        switch (altera)
        {
        case 1:
            alterarDado(cadastro, alteracoes, itemAlterar);
            break;
        case 2:
            deletar_exercicio(alteracoes, itemAlterar);
            break;
        case 3:
            break;
        default:
            cout << "Entrada nao reconhecida.\n";
            break;
        }
    }

    else if (!achou && busca != 0)
        cout << "Exercicio nao encontrado!\n"
             << endl;
}

// Procedimento que salva as modificações do vetor 'cadastro', usado pra manipular os valores e salva as açterações no arquivo
void escrever_CSV(base *cadastro, int *alteracoes, int tamanho, string cabecalho)
{

    bool foiModificado = false;
    int entrada;
    int i = 0;

    while (i < tamanho && !foiModificado)
    {
        if (alteracoes[i] == 1 || alteracoes[i] == 2)
            foiModificado = true;
        i++;
    }

    ofstream saida("dados.csv");
    cout << "Deseja salvar todos os dados no arquivo ou apenas aqueles modificados?\n";

    do
    {
        cout << "1 - Todos os dados.\n2 - Apenas os modificados.\n";
        cin >> entrada;
        cin.ignore();

        if (entrada == 1)
        {
            saida << cabecalho << '#' << endl;
            for (int i = 0; i < tamanho; i++)
            {
                if (alteracoes[i] != 2)
                {
                    saida << cadastro[i].id;
                    saida << ";";
                    saida << cadastro[i].nome;
                    saida << ";";
                    saida << cadastro[i].objetivo;
                    saida << ";";
                    saida << cadastro[i].musculos;
                    saida << ";";
                    saida << cadastro[i].dificuldade;
                    saida << endl;
                }
            }
        }
        else if (entrada == 2)
        {
            saida << cabecalho << '#' << endl;
            for (int i = 0; i < tamanho; i++)
            {
                if (alteracoes[i] == 1)
                {
                    saida << cadastro[i].id;
                    saida << ";";
                    saida << cadastro[i].nome;
                    saida << ";";
                    saida << cadastro[i].objetivo;
                    saida << ";";
                    saida << cadastro[i].musculos;
                    saida << ";";
                    saida << cadastro[i].dificuldade;
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

// Função principal, usada pra chamar as demais funcoes e procedimentos do codigo, verificando se certas condições são atendidas.
int main()
{
    string cabecalho = "";
    int tamanho = 0, capacidade = 75; 

    base *cadastro = NULL; //
    cadastro = new base[capacidade];

    int *alteracoes = NULL; 
    alteracoes = new int[capacidade]();

    cout << "Qual o formato do arquivo a ser lido?\n";
    int opcao_leitura = -1;
    do
    {
        cout << "1 - Arquivo .csv.\n2 - Arquivo .bin.\n";
        if (!(cin >> opcao_leitura))
        {
            cin.clear();
            cin.ignore();
        }
        if (opcao_leitura == 1)
        {
            if (ler_CSV(cadastro, alteracoes, tamanho, capacidade, cabecalho))
                cout << "Arquivo carregado com sucesso.\n";
            else
            {
                cout << "Erro ao tentar carregar o arquivo.\n";
                return 1;
            }
        }
        else if (opcao_leitura == 2)
        {
            //Opcao para ler o de um arquivo binario...
        }
        else
            cout << "Opcao invalida.\n";
    } while (opcao_leitura != 1 && opcao_leitura != 2);

    int modo;
    cout << "O que deseja fazer no arquivo?\n";
    do
    {
        cout << "*\n1 - Consultar (alterar e deletar).\n2 - Inserir novos dados.\n3 - Salvar alteracoes no arquivo '.csv'. (Salve para efetivar as alteracoes no arquivo)\n0 - Sair do programa.\n";
        if (!(cin >> modo))
        {
            cin.clear();
            cin.ignore();
            system("cls");
            modo = -1;
        }
        if (modo == 1)
        {
            buscaArquivo(cadastro, alteracoes, tamanho);
        }
        else if (modo == 2)
        {
            inserir(cadastro, alteracoes, tamanho, capacidade);
        }
        else if (modo == 3)
        {
            cout << "Como deseja salvar o arquivo?\n";
            int opcao_salvar = -1;
            do
            {
                cout << "1 - Salvar como .csv.\n2 - Salvar como .bin\n";
                if (!(cin >> opcao_salvar))
                {
                    cin.clear();
                    cin.ignore();
                }
                if (opcao_salvar == 1)
                {
                    escrever_CSV(cadastro, alteracoes, tamanho, cabecalho);
                }
                else if (opcao_salvar == 2)
                {
                    //Opcao para salvar o arquivo em binario...
                }
                else
                    cout << "Opcao invalida\n";
            } while (opcao_salvar != 1 && opcao_salvar != 2);
        }
        else if (modo == 0)
        {
            cout << "Programa encerrado.\n";
            return 0;
        }
        else
        {
            cout << "Entrada nao reconhecida.\n";
        }
    } while (modo != 0);

    delete[] cadastro;
    delete[] alteracoes;

    return 0;
}