#include <iostream>
#include <fstream>
using namespace std;
const int tamanho = 99;

// Registro base que vai receber os exercicios do csv.

struct base
{
    int id;
    string nome;
    string objetivo;
    string musculos;
    int dificuldade;
};

/* Funcao que altera os dados desejados. Solicita ao usuario alguns valores e pode alterar na matriz copiada do arquivo,
 caso assim seja desejado. */

void alterarDado(base ex[], int i, bool &alterou)
{
    string valorAlterar;
    cout << "O que voce deseja alterar? " << endl;
    cout << "Digite 'id', 'nome', 'objetivo', 'musculos', 'dificuldade'ou 'tudo': ";
    cin >> valorAlterar;
    cin.ignore();
    if (valorAlterar == "id")
    {
        cout << "Digite o novo valor: ";
        cin >> ex[i].id;
        cin.ignore();
        alterou = true;
    }
    else if (valorAlterar == "nome")
    {
        cout << "Digite o novo valor: ";
        getline(cin, ex[i].nome);
        alterou = true;
    }
    else if (valorAlterar == "objetivo")
    {
        cout << "Digite o novo valor: ";
        getline(cin, ex[i].objetivo);
        alterou = true;
    }
    else if (valorAlterar == "musculos")
    {
        cout << "Digite o novo valor: ";
        getline(cin, ex[i].musculos);
        alterou = true;
    }
    else if (valorAlterar == "dificuldade")
    {
        cout << "Digite o novo valor: ";
        cin >> ex[i].dificuldade;
        cin.ignore();
        alterou = true;
    }
    else if (valorAlterar == "tudo")
    {
        cout << "Insira o novos dados no mesmo formato do arquivo, separando os itens por um ';': ";
        alterou = true;
        cin >> ex[i].id;
        cin.ignore();
        getline(cin, ex[i].nome, ';');
        getline(cin, ex[i].objetivo, ';');
        getline(cin, ex[i].musculos, ';');
        cin >> ex[i].dificuldade;
        cin.ignore();
    }
    else
        cout << "Valor nao reconhecido." << endl;
}

/*Funcao que vai pegar os dados que estao no arquivo e vai coloca-los em uma matriz 'ex' que vai ser usada nas outras funcoes para realizar as
operacoes cabiveis. */

void receberArquivo(base ex[], string &cabecalho)
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
    }
    else
        cout << "Erro com o arquivo!";

    entrada.close();
}

/*Essa funcao vai buscar se o exercicio que o usuario que consultar esta presente no arquivo, pode tambem chamar a funcao de alteracao
caso assim seja desejado.*/

void buscaArquivo(base ex[], bool &alterou)
{
    cout << "Busca no arquivo. Atualmente podem ser usados o nome e ou ID do exercicio!" << endl;
    bool continua = true, achou = false; // booleanos de controle para decidir quando cada loop funciona ou nao de acordo com o usuario.
    int itemAlterar = -1;                // variavel que sera atribuida o indice do item que o usuario deseja consultar caso seja encontrado o mesmo.
    while (continua)
    {
        cout << "Digite 'nome' ou 'id': ";
        string busca;
        cin >> busca;
        cin.ignore();
        if (busca == "nome")
        {
            achou = false;
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
                    i++;
                }
                i++;
            }
        }
        else if (busca == "id")
        {
            achou = false;
            cout << "Digite o ID do exercicio: ";
            int idBusca;
            cin >> idBusca;
            cin.ignore();
            if(idBusca >= 1)
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
            {
                cout << "O id deve ser um numero inteiro maior que 0!" << endl;
            }
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
        {
            cout << "Exercicio nao encontrado!" << endl;
        }

        cout << "Quer consultar ou alterar mais algum outro item? Digite 'sim' para continuar e qualquer outro valor para sair! " << endl;
        string repetir;
        cin >> repetir;

        if (repetir == "sim")
            continua = true;
        else
            continua = false;
    }
}

/*Funcao que pega os dados da matriz 'ex' que foi usada pra manipular os valores e salva as alteracoes no arquivo original*/

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
/* Funcao principal, usada pra chamar as outras funcoes do codigo e no fim faz uma verificacao se deve chamar a funcao de escrever no
arquivo caso ele tenha sido alterado, caso negativo apenas exibe uma mensagem. */
int main()
{
    base ex[100];
    string cabecalho = "";
    bool alterou = false;
    receberArquivo(ex, cabecalho);
    buscaArquivo(ex, alterou);
    if (alterou)
    {
        escreverDados(ex, cabecalho);
    }
    else
    {
        cout << "Arquivo inalterado!";
    }
    return 0;
}