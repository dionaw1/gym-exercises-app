#include <iostream>
#include <fstream>
using namespace std;
const int tamanho = 99;

// Registro base que vai receber as informações do arquivo.

struct base
{
    int id;
    string nome;
    string objetivo;
    string musculos;
    int dificuldade;
};

// Função que vai ser usada para controlar a repetição de alguns laços.

bool repete()
{

    cout << "\nDeseja consultar outro item? Digite 'sim' para continuar ou qualquer outra tecla para sair: ";

    string repetir;
    cin >> repetir;

    if (repetir == "sim")
        return true;
    else
        return false;
}

// Função que altera os dados. Solicita ao usuario valores e pode alterar no vetor de registros.

void alterarDado(base vetorCompleto[], int vetorModificado[], int i)
{
    string valorAlterar;

    cout << "\nO que você deseja alterar?\nOpções: 'id', 'nome', 'objetivo', 'musculos', 'dificuldade' ou 'tudo': ";

    cin >> valorAlterar;
    cin.ignore();

    if (valorAlterar == "id")
    {
        cout << "Digite o novo valor: ";
        cin >> vetorCompleto[i].id;
        cin.ignore();
        vetorModificado[i] = 1;
    }
    else if (valorAlterar == "nome")
    {
        cout << "Digite o novo valor: ";
        getline(cin, vetorCompleto[i].nome);
        vetorModificado[i] = 1;
    }
    else if (valorAlterar == "objetivo")
    {
        cout << "Digite o novo valor: ";
        getline(cin, vetorCompleto[i].objetivo);
        vetorModificado[i] = 1;
    }
    else if (valorAlterar == "musculos")
    {
        cout << "Digite o novo valor: ";
        getline(cin, vetorCompleto[i].musculos);
        vetorModificado[i] = 1;
    }
    else if (valorAlterar == "dificuldade")
    {
        cout << "Digite o novo valor: ";
        cin >> vetorCompleto[i].dificuldade;
        cin.ignore();
        vetorModificado[i] = 1;
    }
    else if (valorAlterar == "tudo")
    {
        vetorModificado[i] = 1;

        cout << "Insira o novos dados no mesmo formato do arquivo, separando os itens por um ';': ";

        cin >> vetorCompleto[i].id;
        cin.ignore();

        getline(cin, vetorCompleto[i].nome, ';');

        getline(cin, vetorCompleto[i].objetivo, ';');

        getline(cin, vetorCompleto[i].musculos, ';');

        cin >> vetorCompleto[i].dificuldade;
        cin.ignore();
    }
    else
    {
        cout << "Opção inválida, tente novamente." << endl;
    }
}

// Função que lê as informações no arquivo e repassa para um vetor 'vetorCompleto' que vai ser usado em outras funções.

bool receberArquivo(base vetorCompleto[])
{
    string cabecalho;
    fstream entrada("dados.csv");
    if (entrada)
    {
        getline(entrada, cabecalho, '#');
        for (int i = 1; i <= tamanho; i++)
        {
            entrada >> vetorCompleto[i].id;
            entrada.ignore();
            getline(entrada, vetorCompleto[i].nome, ';');
            getline(entrada, vetorCompleto[i].objetivo, ';');
            getline(entrada, vetorCompleto[i].musculos, ';');
            entrada >> vetorCompleto[i].dificuldade;
            entrada.ignore();
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

// Função que busca se o exercício que o usuario que consultar está presente no arquivo.

void buscaArquivo(base vetorCompleto[], int vetorModificado[])
{
    bool continua = true;
    while (continua)
    {
        cout << "Buscar no arquivo. Use 'nome' ou 'id' do exercício." << endl;

        bool achou = false;

        int itemAlterar = -1;
        cout << "Digite 'nome' ou 'id': ";
        string busca;
        cin >> busca;
        cin.ignore();

        if (busca == "nome")
        {
            cout << "Digite o nome completo do exercicio: ";
            string exercicio;
            getline(cin, exercicio);
            int i = 1;
            while (i <= tamanho && !achou)
            {
                if (vetorCompleto[i].nome == exercicio)
                {
                    cout << "Exercicio encontrado, os seguintes dados estao cadastrados: \n" << endl;
                    cout << vetorCompleto[i].id;
                    cout << " -- ";
                    cout << vetorCompleto[i].nome;
                    cout << " -- ";
                    cout << vetorCompleto[i].objetivo;
                    cout << " -- ";
                    cout << vetorCompleto[i].musculos;
                    cout << " -- ";
                    cout << vetorCompleto[i].dificuldade;
                    cout << endl;

                    itemAlterar = i;
                    achou = true;
                }
                i++;
            }
        }
        else if (busca == "id")
        {
            cout << "Digite o ID do exercicio: ";
            int idBusca;
            cin >> idBusca;
            cin.ignore();
            if (idBusca >= 1)
            {
                int i = 1;
                while (i <= tamanho && !achou)
                {
                    if (vetorCompleto[i].id == idBusca)
                    {
                        cout << "Exercicio encontrado, os seguintes dados estao cadastrados: \n" << endl;
                        cout << vetorCompleto[i].id;
                        cout << " -- ";
                        cout << vetorCompleto[i].nome;
                        cout << " -- ";
                        cout << vetorCompleto[i].objetivo;
                        cout << " -- ";
                        cout << vetorCompleto[i].musculos;
                        cout << " -- ";
                        cout << vetorCompleto[i].dificuldade;
                        cout << endl;

                        achou = true;
                        itemAlterar = i;
                    }
                    i++;
                }
            }
            else
                cout << "O id deve ser um numero inteiro maior que 0!" << endl;
        }
        else
            cout << "A entrada digitada nao e reconhecida." << endl;

        if (achou)
        {
            cout << "Deseja alterar algo nesse exercicio? Digite 'sim' ou outro valor qualquer para nao': ";
            string altera;
            getline(cin, altera);
            if (altera == "sim")
                alterarDado(vetorCompleto, vetorModificado, itemAlterar);
        }

        else
            cout << "Exercicio nao encontrado!" << endl;

        if (repete())
            continua = true;
        else
            continua = false;
    }
}

// Função que salva as modificações do vetor 'vetorCompleto', usado pra manipular os valores e salva as açterações no arquivo

void escreverDados(base vetorCompleto[], int vetorModificado[])
{

    bool foiModificado = false;
    string entrada;

    for (int i = 0; i < 100; i++)
    {
        if (vetorModificado[i] == 1)
            foiModificado = true;
    }
    if (!foiModificado)
        cout << "Nenhuma alteração feita no arquivo.";
    else
    {
        ofstream saida("saida.csv");
        cout << "\nDeseja salvar todos os dados no arquivo ou apenas aqueles modificados?\nDigite 'todos' para salvar todos os dados ou 'modificados' para apenas as alterações: ";

        do
        {
            cout << "Digite 'todos' para todos os dados ou 'modificados' para apenas salvar os que foram alterados: ";
            cin >> entrada;
            cin.ignore();

            if (entrada == "todos")
            {
                for (int i = 1; i <= tamanho; i++)
                {
                    saida << vetorCompleto[i].id;
                    saida << ";";
                    saida << vetorCompleto[i].nome;
                    saida << ";";
                    saida << vetorCompleto[i].objetivo;
                    saida << ";";
                    saida << vetorCompleto[i].musculos;
                    saida << ";";
                    saida << vetorCompleto[i].dificuldade;
                    saida << endl;
                }
            }
            else if (entrada == "modificados")
            {
                for (int i = 1; i <= tamanho; i++)
                {
                    if (vetorModificado[i] == 1)
                    {
                        saida << vetorCompleto[i].id;
                        saida << ";";
                        saida << vetorCompleto[i].nome;
                        saida << ";";
                        saida << vetorCompleto[i].objetivo;
                        saida << ";";
                        saida << vetorCompleto[i].musculos;
                        saida << ";";
                        saida << vetorCompleto[i].dificuldade;
                        saida << endl;
                    }
                }
            }
            else
                cout << "Opção inválida, tente novamente." << endl;

        } while (entrada != "todos" && entrada != "modificados");

        cout << "Arquivo alterado com sucesso!" << endl;

        saida.close();
    }
}
// Função principal, usada pra chamar as outras funcoes do codigo, verificando se certas condições são atendidas.

int main()
{
    base vetorCompleto[100];
    int vetorModificado[100];

    for (int i = 0; i < 100; i++)
    {
        vetorModificado[i] = 0;
    }

    if (receberArquivo(vetorCompleto))
    {
        buscaArquivo(vetorCompleto, vetorModificado);
        escreverDados(vetorCompleto, vetorModificado);
    }
    else
    {
        cout << "Erro ao receber arquivo!" << endl;
    }

    return 0;
}
