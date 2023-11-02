#include <iostream>
#include <fstream>
using namespace std;
//Registro base que vai receber os exercicios do csv.
struct base
{
    int id;
    string nome;
    string objetivo;
    string musculos;
    int dificuldade;
};
/* Funcao que altera os dados desejados. Enquanto a variavel bool tentarNovamente estive ativa a funcao pede informacoes para o usuario,
 caso chegue ao fim, ou encontre valores invalidos ela para de ser executada */
void alterarDado(base ex[], int i, bool &alterou)
{
    bool tentarNovamente = true;
    string valorAlterar;
    cout << "O que voce deseja alterar? " << endl;
    while (tentarNovamente)
    {
        cout << "Digite 'id', 'nome', 'objetivo', 'musculos', 'dificuldade'ou 'tudo': ";
        cin >> valorAlterar;
        if (valorAlterar == "id")
        {
            cin.ignore();
            cout << "Digite o novo valor: ";
            cin >> ex[i].id;
            alterou = true;
        }
        else if (valorAlterar == "nome")
        {
            cin.ignore();
            cout << "Digite o novo valor: ";
            getline(cin, ex[i].nome);
            alterou = true;
        }
        else if (valorAlterar == "objetivo")
        {
            cin.ignore();
            cout << "Digite o novo valor: ";
            getline(cin, ex[i].objetivo);
            alterou = true;
        }
        else if (valorAlterar == "musculos")
        {
            cin.ignore();
            cout << "Digite o novo valor: ";
            getline(cin, ex[i].musculos);
            alterou = true;
        }
        else if (valorAlterar == "dificuldade")
        {
            cout << "Digite o novo valor: ";
            cin >> ex[i].dificuldade;
            alterou = true;
        }
        else if (valorAlterar == "tudo")
        {
            cin.ignore();
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
        {
            cout << "Valor nao reconhecido. Quer tentar novamente? 'sim' para continuar e outro valor qualquer para sair: ";
            string aux;
            cin >> aux;
            if (aux == "sim")
                tentarNovamente = true;
            else
                tentarNovamente = false;
        }
    if(alterou){
        cout << "Mais alguma alteracao? 'sim' para sim e outro valor qualquer para nao: ";
        string aux;
        cin >> aux;
        if (aux == "sim")
            tentarNovamente = true;
        else
            tentarNovamente = false;
        }
    }
}
/* funcao principal, recebe os dados do arquivo csv, executa uma busca no arquivo pelo exercicio informado pelo usuario, caso encontre ela pergunta
se o mesmo quer alterar algo no arquivo, caso afirmativo ela chama a funcao de alteracao e depois salva tudo que foi alterado no arquivo original,
sempre que executar algumna mudanca tem disponivel nessa pasta um backup do csv original, so copiar e colar */
int main()
{
    base ex[100];
    string lixo;
    fstream entrada("dados.csv");
    bool alterou = false;

    if (entrada)
    {
        getline(entrada, lixo, '#');
        for (int i = 1; i <= 99; i++)
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
    {
        cout << "Erro com arquivo.";
    }
    bool continua = true;
    cout << "Busca no arquivo. Atualmente podem ser usados o nome e ou ID do exercicio!" << endl;
    while (continua)
    {
        cout << "Digite 'nome' ou 'id': ";
        string busca;
        cin >> busca;
        if (busca == "nome")
        {
            cout << "Digite o nome completo do exercicio: ";
            string exercicio;
            cin.ignore();
            getline(cin, exercicio);
            bool achou = false;
            int i = 1;
            while (i <= 99 && !achou)
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
                    achou = true;
                    cout << "Deseja alterar algo nesse exercicio? Digite 'sim' ou outro valor qualquer para nao': ";
                    string altera;
                    cin >> altera;
                    continua = false;
                    if (altera == "sim")
                        alterarDado(ex, i, alterou);
                }
                i++;
            }
            if (!achou)
                cout << "Exercicio nao encontrado!" << endl;
        }
        else if (busca == "id")
        {
            cout << "Digite o ID do exercicio: ";
            int idBusca;
            cin >> idBusca;
            bool achou = false;
            for (int i = 1; i <= 99; i++)
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
                    continua = false;
                    cout << "Deseja alterar algo nesse exercicio? Digite 'sim' ou outro valor qualquer para nao': ";
                    string altera;
                    cin >> altera;
                    if (altera == "sim")
                        alterarDado(ex, i, alterou);
                }
            }
            continua = false;
            if (!achou)
                cout << "Exercicio nao encontrado!" << endl;
        }
        else
        {
            cout << "A entrada digitada nao e reconhecida." << endl;
        }
    }
    if(alterou){
        ofstream saida("dados.csv");
        saida << lixo << "#" << endl;
        for (int i = 1; i <= 99; i++)
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
    } else {
        cout << "Arquivo inalterado!";
    }
    return 0;
}