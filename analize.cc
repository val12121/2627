#include "analize.h"

void Analizador::analizar() {
  std::ifstream file(archivo_);
  if (!file.is_open()) {
    std::cerr << "Error al abrir el archivo: " << archivo_ << std::endl;
    return;
  }

  std::stringstream buffer;
  buffer << file.rdbuf();
  std::string contenido = buffer.str();
  contenido_ = contenido;

  file.close();

  this-> Header();
  this-> Body();
  this-> Html();
}

