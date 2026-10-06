#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include <sstream>
#include "analize.h"

int main(int argc, char* argv[])
{
  std::string archivo_entrada = argv[1];
  Analizador analizador(archivo_entrada);
  analizador.Salida();
  bool header_encontrado = analizador.Header();
} 