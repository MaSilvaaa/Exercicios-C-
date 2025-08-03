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
void ContarEspecs(string str, int *numEsp,int *numVog, int *numArt);
bool EhVogal(char c);
bool EhEspaco(char c);
bool EhArtigoDef(string pal);
string GerarRelatorio(int numEsp, int numVog, int numArt, int numLin, string arquivo);

int main()
{
  int numLinhas, numEsp, numVog, numArt;
  ifstream inFile; // inFile é o arquivo de leitura dos dados
  string entrada, arquivo;

  setlocale(LC_ALL,"");

  while(1)
  {
    numLinhas = 0, numEsp = 0, numVog = 0, numArt = 0;
    cout << "Digite o nome do arquivo que deseja editar, ou sair para sair: ";
    cin >> entrada;
    cout << endl;

    if(entrada == "sair")
    {
      break;
    }
    arquivo = entrada + ".txt";
  
    inFile.open(arquivo, ios::in); // abre o arquivo para leitura
    if (! inFile)
      { 
        cerr << "Arquivo " + arquivo + " nao pode ser aberto\n" << endl;
        return -1;
      }
    string linha;

    while(getline(inFile, linha))
    {
      cout << linha << endl;
      ContarEspecs(linha, &numEsp, &numVog, &numArt);
      numLinhas++;
    }
    cout << '\n' << GerarRelatorio(numEsp, numVog, numArt, numLinhas, arquivo) << '\n' << endl;

    inFile.close();
  } 

  cout << "Programa encerrado!\n" << endl;

  return 0; // o finalizador se encarrega de fechar o arquivo
}

void ContarEspecs(string str, int *numEsp, int *numVog, int *numArt)
{
  for(char c: str)
  {
    if(EhEspaco(c))
    {
      (*numEsp)++;
    }
    if(EhVogal(c))
    {
      (*numVog)++;
    }
  }

  stringstream ss(str);
  string palavra;
  while(ss >> palavra)
  {
    if(EhArtigoDef(palavra))
    {
      (*numArt)++;
    }
  }
}

bool EhVogal(char c)
{
  if(tolower(c) == 'a' || tolower(c) == 'e' || tolower(c) == 'i' || tolower(c) == 'o' || tolower(c) == 'u')
    return true;
  return false;
}

bool EhEspaco(char c)
{
  return c == ' ';
}

bool EhArtigoDef(string pal)
{
  string palMinuscula;

  for(char c:pal)
  {
    if(c == ',' || c == '.')
      continue;
    palMinuscula += tolower(c);
  }
  return(palMinuscula == "a" || palMinuscula == "o" || palMinuscula == "os" || palMinuscula == "as");
}

string GerarRelatorio(int numEsp, int numVog, int numArt, int numLin, string arquivo)
{
    ofstream OutFile;
    
    int pos_inserir = arquivo.find(".txt");
    arquivo.insert(pos_inserir, "_rel");
    OutFile.open(arquivo, ios::trunc);

    if(!OutFile)
    {
      return "Arquivo " + arquivo + "nao pode ser aberto!";
    }

    OutFile << "\nNumero de espaços: " << numEsp << endl;
    OutFile << "Numero de artigos definidos: " << numArt << endl;
    OutFile << "Numero de vogais: " << numVog << endl;
    OutFile << "Numero de linhas: " << numLin;
    OutFile << '\n' << endl;

    OutFile.close();

    return "Relatorio criado, nome: " + arquivo;
}