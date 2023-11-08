#include <iostream>
#include <fstream>
using namespace std;
const int tamanho = 99;
bool alterou;

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

    cout << "Quer consultar outro item? Digite 'sim' para continuar e qualquer outro valor para sair! " << endl;

    string repetir;
    cin >> repetir;

    if (repetir == "sim")
        return true;
    else
        return false;
}

// Função que altera os dados. Solicita ao usuario valores e pode alterar no vetor de registros.

bool alterarDado(base ex[], int i, bool &alterou)
{
    string valorAlterar;
    cout << "O que você deseja alterar? Digite uma das seguintes opções:\n'id' - 'nome' - 'objetivo' - 'musculos' - 'dificuldade' - 'tudo'\n";
    cin >> valorAlterar;
    cin.ignore();
    if (valorAlterar == "id")
    {
        cout << "Digite o novo valor: ";
        cin >> ex[i].id;
        cin.ignore();
        alterou = true;
        return true;
    }
    else if (valorAlterar == "nome")
    {
        cout << "Digite o novo valor: ";
        getline(cin, ex[i].nome);
        alterou = true;
        return true;
    }
    else if (valorAlterar == "objetivo")
    {
        cout << "Digite o novo valor: ";
        getline(cin, ex[i].objetivo);
        alterou = true;
        return true;
    }
    else if (valorAlterar == "musculos")
    {
        cout << "Digite o novo valor: ";
        getline(cin, ex[i].musculos);
        alterou = true;
        return true;
    }
    else if (valorAlterar == "dificuldade")
    {
        cout << "Digite o novo valor: ";
        cin >> ex[i].dificuldade;
        cin.ignore();
        alterou = true;
        return true;
    }
    else if (valorAlterar == "tudo")
    {
        cout << "Insira o novos dados no mesmo formato do arquivo, separando os itens por um ';': ";
        cin >> ex[i].id;
        cin.ignore();
        getline(cin, ex[i].nome, ';');
        getline(cin, ex[i].objetivo, ';');
        getline(cin, ex[i].musculos, ';');
        cin >> ex[i].dificuldade;
        cin.ignore();
        alterou = true;
        return true;
    }
    else
    {
        cout << "Valor inserido não reconhecido." << endl;
        alterou = false;
        return false;
    }
}

//Função que lê as informações no arquivo e repassa para um vetor 'ex' que vai ser usado em outras funções.

bool receberArquivo(base ex[], string &cabecalho)
{
    fstream entrada("dados.csv");
    if (entrada)
    {
        getline(entrada, cabecalho, '#');
        for (int i = 1; i <= tamanho; i++)
        {
            entrada >> ex[i].id;
            entrada.ignore();
            getline(entrada, ex[i].nome, ';');
            getline(entrada, ex[i].objetivo, ';');
            getline(entrada, ex[i].musculos, ';');
            entrada >> ex[i].dificuldade;
            entrada.ignore();
        }
        entrada.close();
        return true;
    }
    else
    {
        cout << "Erro com o arquivo!";
        return false;
    }
}

//Função que busca se o exercício que o usuario que consultar está presente no arquivo.

void buscaArquivo(base ex[])
{
    cout << "Busca no arquivo. Atualmente podem ser usados o nome e ou ID do exercicio!" << endl;
    bool continua = true;
    bool achou = false;
    int itemAlterar = -1;
    while (continua)
    {
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
                if (ex[i].nome == exercicio)
                {
                    cout << "Exercicio encontrado, os seguintes dados estao cadastrados: " << endl;
                    cout << ex[i].id;
                    cout << " -- ";
                    cout << ex[i].nome;
                    cout << " -- ";
                    cout << ex[i].objetivo;
                    cout << " -- ";
                    cout << ex[i].musculos;
                    cout << " -- ";
                    cout << ex[i].dificuldade;
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
                    if (ex[i].id == idBusca)
                    {
                        cout << "Exercicio encontrado, os seguintes dados estao cadastrados: " << endl;
                        cout << ex[i].id;
                        cout << " -- ";
                        cout << ex[i].nome;
                        cout << " -- ";
                        cout << ex[i].objetivo;
                        cout << " -- ";
                        cout << ex[i].musculos;
                        cout << " -- ";
                        cout << ex[i].dificuldade;
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
                alterarDado(ex, itemAlterar, alterou);
        }

        else
            cout << "Exercicio nao encontrado!" << endl;

        if (repete())
            continua = true;
        else
            continua = false;
    }
}

//Função que salva as modificações do vetor 'ex', usado pra manipular os valores e salva as açterações no arquivo

void escreverDados(base ex[], string &cabecalho)
{
    cout << "Arquivo alterado com sucesso!" << endl;
    ofstream saida("dados.csv");
    saida << cabecalho << "#" << endl;
    for (int i = 1; i <= tamanho; i++)
    {
        saida << ex[i].id;
        saida << ";";
        saida << ex[i].nome;
        saida << ";";
        saida << ex[i].objetivo;
        saida << ";";
        saida << ex[i].musculos;
        saida << ";";
        saida << ex[i].dificuldade;
        saida << endl;
    }
    saida.close();
}
// Função principal, usada pra chamar as outras funcoes do codigo, verificando se certas condições são atendidas.

int main()
{
    base ex[100];
    string cabecalho = "";
    if (receberArquivo(ex, cabecalho))
    {
        buscaArquivo(ex);
        if (alterou)
            escreverDados(ex, cabecalho);
        else
            cout << "Arquivo inalterado!";
    }
    return 0;
}