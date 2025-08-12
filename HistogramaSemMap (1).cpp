#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <locale>

using namespace std;

/*
Modos de abertura Descrição
ios::in Abre para leitura (default de ifstream).
ios::out Abre para gravação (default de ofstream),
ios::ate Abre e posiciona no final do arquivo.
(Este modo trabalha com leitura e gravação)
ios::app Grava a partir do fim do arquivo
ios::trunc Abre e apaga todo o conteúdo do arquivo
ios::nocreate Erro de abertura se o arquivo não existe
ios::noreplace Erro de abertura se o arquivo existir
ios::binary Abre em binário (default é texto)

*/
const int MAX_PALAVRAS = 2000;

struct PalavraContagem
{
  string palavra;
  int contagem;
};

string LimparPalavra(const string& palavra); //Remover a potnuacao
int BuscarPalavra(const string& palavra); //Ver se a palavra ja existe e agir de acordo
void InserirPalavra(const string& palavra); //Adiciona as palavras no  histograma
void GerarRelatorio(const string& nomeArquivo); //Gera o reatorio

PalavraContagem histograma[MAX_PALAVRAS];
int numPalavras = 0;

int main() {
    while (true) {
        string entrada;
        cout << "Digite o nome do arquivo ou \"sair\" para encerrar: ";
        cin >> entrada;
        if (entrada == "sair") break;

        string nomeArquivo = entrada + ".txt";

        ifstream inFile(nomeArquivo);
        if (!inFile) {
            cerr << "Arquivo " << nomeArquivo << " nao pode ser aberto\n";
            continue;
        }

        numPalavras = 0;

        string palavra;
        while (inFile >> palavra) {
            palavra = LimparPalavra(palavra);
            if (!palavra.empty()) {
                InserirPalavra(palavra);
            }
        }
        inFile.close();

        GerarRelatorio(nomeArquivo);
    }

    cout << "Programa encerrado!" << endl;
    return 0;
}

string LimparPalavra(const string& palavra)
{
  string resultado;

  for(char c:palavra)
  {
    if(!ispunct(c) || c == '-')
    {
      resultado += tolower(c);
    }
  }

  return resultado;
}

int BuscarPalavra(const string& palavra) {
    for (int i = 0; i < numPalavras; i++) {
        if (histograma[i].palavra == palavra) {
            return i;
        }
    }
    return -1;
}

void InserirPalavra(const string& palavra)
{
  int pos = BuscarPalavra(palavra);
  if(pos != -1)
  {
    histograma[pos].contagem++;
  }
  else
  {
    if(numPalavras < MAX_PALAVRAS)
    {
      histograma[numPalavras].palavra = palavra;
      histograma[numPalavras].contagem = 1;
      numPalavras++;
    }
    else
    {
      cerr << "Limite de palavras atingido!!!" << endl;
    }
  }
}

void GerarRelatorio(const string& nomeArquivo) {
    string nomeRelatorio = nomeArquivo;
    int posInserir = nomeRelatorio.find(".txt");
    if (posInserir != string::npos) {
        nomeRelatorio.insert(posInserir, "_rel");
    } else {
        nomeRelatorio += "_rel.txt";
    }

    ofstream outFile(nomeRelatorio);
    if (!outFile) {
        cerr << "Nao foi possivel abrir o arquivo " << nomeRelatorio << endl;
        return;
    }

    for (int i = 0; i < numPalavras; i++) {
        outFile << histograma[i].palavra << " aparece " << histograma[i].contagem << "x\n";
    }
    outFile.close();

    cout << "Relatorio do arquivo " << nomeRelatorio << " gerado!\n\n";
}