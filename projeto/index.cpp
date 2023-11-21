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

    while ((repetir != 1) && (repetir != 2)) // Enquanto for diferente de uma entrada esperada o loop continua.
    {
        cout << "1 - Continuar.\n2 - Sair.\n";

        cin >> repetir;
        cin.ignore();

        if (repetir == 1)
            return true;
        else if (repetir == 2)
            return false;
        else
            cout << "Entrada não reconhecida, tente novamente.\n";
    }
    return true;
}

// Procedimento para inserir novos dados no arquivo.

void inserir_CSV(base *&cadastro, int *&itens_alterados, int &capacidade, int &tamanho)
{
    ofstream dados("dados.csv", ios::app); // Arquivo aberto no modo app para escrever apenas no final do mesmo.
    do
    {
        if (tamanho == (capacidade - 1)) // Realocação dinâmica padrão quando o arquivo estiver em sua capacidade máxima.
        {
            capacidade += 10;
            base *novoVetor = NULL;
            int *novoVetorModificado = NULL;
            novoVetor = new base[capacidade];
            novoVetorModificado = new int[capacidade];
            copy(cadastro, cadastro + tamanho, novoVetor);
            copy(itens_alterados, itens_alterados + tamanho, novoVetorModificado);
            delete[] cadastro;
            delete[] itens_alterados;
            cadastro = novoVetor;
            itens_alterados = novoVetorModificado;
        }

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
        dados << endl;
        dados << novoID << ';';
        dados << novoNome << ';';
        dados << novoObjetivo << ';';
        dados << novosMusculos << ';';
        dados << novaDificuldade;

        itens_alterados[tamanho] = 1;
        tamanho++;
    } while (repete());

    dados.close();

    cout << "Dados inserido com sucesso, arquivo salvo." << endl;
}

/* Procedimento que permite a modificação dos dados de um elemento específico no vetor 'cadastro[]',
baseando-se na escolha do usuário. Dependendo da mesma, os dados do vetor são modificados,
a variável 'itens_alterados[]' marca o índice correspondente.*/

void alterarDado(base *cadastro, int *itens_alterados, int i)
{
    int valorAlterar;

    cout << "O que você deseja alterar?\n1- ID\n2 - Nome\n3 - Objetivo\n4 - Musculos\n5 - Dificuldade\n6 - Tudo\n";

    cin >> valorAlterar;
    cin.ignore();

    if (valorAlterar == 1)
    {
        cout << "Digite o novo valor (que seja um número inteiro): ";
        cin >> cadastro[i].id;
        cin.ignore();
        itens_alterados[i] = 1;
    }
    else if (valorAlterar == 2)
    {
        cout << "Digite o novo valor: ";
        getline(cin, cadastro[i].nome);
        itens_alterados[i] = 1;
    }
    else if (valorAlterar == 3)
    {
        cout << "Digite o novo valor: ";
        getline(cin, cadastro[i].objetivo);
        itens_alterados[i] = 1;
    }
    else if (valorAlterar == 4)
    {
        cout << "Digite o novo valor: ";
        getline(cin, cadastro[i].musculos);
        itens_alterados[i] = 1;
    }
    else if (valorAlterar == 5)
    {
        cout << "Digite o novo valor (que seja um número inteiro): ";
        cin >> cadastro[i].dificuldade;
        cin.ignore();
        itens_alterados[i] = 1;
    }
    else if (valorAlterar == 6)
    {
        itens_alterados[i] = 1;
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
        cout << "Opção inválida, tente novamente." << endl;
    }
}

/* Função que lê um arquivo chamado "dados.csv" e carrega os dados para um vetor de estruturas 'cadastro[]'.
Retorna um booleano indicando se o carregamento do arquivo foi bem-sucedido ou não.*/

bool ler_CSV(base *&cadastro, int *&itens_alterados, int &tamanho, int &capacidade)
{
    string cabecalho;
    ifstream entrada("dados.csv");
    if (entrada)
    {
        getline(entrada, cabecalho, '#');
        while (entrada >> cadastro[tamanho].id) // Usado para verificar se o fim do arquivo foi antingido, enquanto nao for o programa vai ler mais entradas.
        {
            if (tamanho == (capacidade - 1))
            {
                capacidade += 10;
                base *novoVetor = NULL;
                int *novoVetorModificado = NULL;
                novoVetor = new base[capacidade];
                novoVetorModificado = new int[capacidade];
                copy(cadastro, cadastro + tamanho, novoVetor);
                copy(itens_alterados, itens_alterados + tamanho, novoVetorModificado);
                delete[] cadastro;
                delete[] itens_alterados;
                cadastro = novoVetor;
                itens_alterados = novoVetorModificado;
            }
            entrada.ignore();
            getline(entrada, cadastro[tamanho].nome, ';');
            getline(entrada, cadastro[tamanho].objetivo, ';');
            getline(entrada, cadastro[tamanho].musculos, ';');
            entrada >> cadastro[tamanho].dificuldade;
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

bool buscaArquivo(base *cadastro, int *itens_alterados, int tamanho)
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
                if (cadastro[i].nome == exercicio)
                {
                    cout << "Exercicio encontrado, os seguintes dados estao cadastrados: \n"
                         << endl;
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
                if (cadastro[i].id == idBusca)
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
                alterarDado(cadastro, itens_alterados, itemAlterar);
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

// Procedimento que salva as modificações do vetor 'cadastro', usado pra manipular os valores e salva as açterações no arquivo

void escrever_CSV(base *cadastro, int *itens_alterados, int tamanho, int capacidade)
{

    bool foiModificado = false;
    int entrada;
    int i = 0;

    while (i < capacidade && !foiModificado)
    {
        if (itens_alterados[i] == 1)
            foiModificado = true;
        i++;
    }
    if (!foiModificado)
        cout << "Nenhuma alteração feita no arquivo.";
    else
    {
        ofstream saida("dados.csv");
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
            else if (entrada == 2)
            {
                for (int i = 0; i < tamanho; i++)
                {
                    if (itens_alterados[i] == 1)
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
}

// Função principal, usada pra chamar as demais funcoes e procedimentos do codigo, verificando se certas condições são atendidas.

int main()
{
    int tamanho = 0, capacidade = 75;
    base *cadastro = NULL;
    int *itens_alterados = NULL;
    cadastro = new base[capacidade];
    itens_alterados = new int[capacidade];

    for (int i = 0; i < capacidade; i++)
    {
        itens_alterados[i] = 0;
    }

    if (ler_CSV(cadastro, itens_alterados, tamanho, capacidade))
    {
        int modo;
        cout << "O que deseja fazer no arquivo?\n";
        do
        {
            cout << "1 - Buscar e alterar.\n2 - Inserir novos dados.\n";
            if(!(cin >> modo))
            {
                cin.clear();
                cin.ignore();
            }
            switch(modo)
            {
            case 1:
                if (buscaArquivo(cadastro, itens_alterados, tamanho))
                    escrever_CSV(cadastro, itens_alterados, tamanho, capacidade);
                break;
            case 2:
                inserir_CSV(cadastro, itens_alterados, tamanho, capacidade);
                break;
            default:
                cout << "Entrada nao reconhecida.\n";
                break;
            }
        } while (modo != 1 && modo != 2);
    }

    delete[] cadastro;
    delete[] itens_alterados;

    return 0;
}