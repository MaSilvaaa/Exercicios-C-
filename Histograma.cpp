#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <locale>
#include <map>

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
void GerarHistograma(map<string, int>& histograma, string palavra);
string GerarRelatorio(map<string, int> histograma, string arquivo);

int main()
{
    map <string, int> histograma;
    ifstream inFile; // inFile é o arquivo de leitura dos dados
    string entrada, arquivo;

    setlocale(LC_ALL, "");

    while (1)
    {
        histograma.clear();
        cout << "Digite o nome do arquivo que deseja criar o histograma de palavras, ou sair para sair: ";
        cin >> entrada;
        cout << endl;

        if (entrada == "sair")
        {
            break;
        }
        arquivo = entrada + ".txt";

        inFile.open(arquivo, ios::in); // abre o arquivo para leitura
        if (!inFile)
        {
            cerr << "Arquivo " + arquivo + " nao pode ser aberto\n" << endl;
            continue;
        }

        string palavra;
        while (inFile >> palavra)
        {
            GerarHistograma(histograma, palavra);
        }

        cout << GerarRelatorio(histograma, arquivo);
        inFile.close();
    }

    cout << "Programa encerrado!\n" << endl;

    return 0; // o finalizador se encarrega de fechar o arquivo
}

void GerarHistograma(map<string, int>& histograma ,string palavra)
{
  string palSemPont;
  for(char c : palavra)
  {
    if(!ispunct(c) || c == '-')
    {
      palSemPont += tolower(c);
    }
  }
  histograma[palSemPont]++;
}

string GerarRelatorio(map<string, int> histograma, string arquivo)
{
  ofstream outFile;
  int pos_inserir = arquivo.find(".txt");
  arquivo.insert(pos_inserir, "_rel");
  outFile.open(arquivo, ios::trunc);
  if(!outFile)
  {
    return "Nao foi possivel abrir o arquivo " + arquivo + "!!!\n\n";
  }

  for(auto key:histograma)
  {
    outFile << key.first << " aparece " << key.second << "x" << '\n';
  }

  outFile.close();

  return "Relatorio do arquivo " + arquivo + " gerado!\n\n";
}