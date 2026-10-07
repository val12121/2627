#include "analize.h"

void Analizador::analizar()
{
  std::ifstream file(archivo_);
  if (!file.is_open())
  {
    std::cerr << "Error al abrir el archivo: " << archivo_ << std::endl;
    return;
  }

  // std::stringstream buffer;
  // buffer << file.rdbuf();
  // std::string contenido = buffer.str();
  // contenido_ = contenido;
  std::string contenido = "";
  std::string linea = "";

  while (std::getline(file, linea))
  {
    texto_.push_back(linea);
    contenido += linea + "\n";
  }
  contenido_ = contenido;
  file.close();

  this->Header();
  this->Body();
  this->Html();

  this->FindTags();
  this->FindAttributes();
  this->FindComments();
}

void Analizador::Salida()
{
  std::cout << "[ PROGRAMA ]: " << archivo_ << std::endl;
  std::cout << "\n[ ESTRUCTURA ]: " << std::endl;
  std::cout << "-> HEAD: " << (header_encontrado_ ? "true" : "false") << std::endl;
  std::cout << "-> BODY: " << (body_encontrado_ ? "true" : "false") << std::endl;
  std::cout << "-> HTML: " << (html_encontrado_ ? "true" : "false") << std::endl;

  std::cout << "\n[ TAGS ]:" << std::endl;
  for (const auto &tag : Tags_) {
    std::cout << tag << std::endl;
  }
  std::cout << "\n[ ATRIBUTOS ]:" << std::endl;
  for (const auto &atr : Atributos_) {
    std::cout << atr;
  }
  std::cout << "\n[ COMENTARIOS ]:" << std::endl;
  for (const auto &com : Comments_) {
    std::cout << com;
  }
}

bool Analizador::Header()
{
  std::regex header("<head>([\\s\\S]*)</head>");
  std::smatch match;
  if (std::regex_search(contenido_, match, header))
  {
    header_encontrado_ = true;
    return true;
  }
  else
  {
    header_encontrado_ = false;
    return false;
  }
}

bool Analizador::Body()
{
  std::regex body("<body>([\\s\\S]*)</body>");
  std::smatch match;
  if (std::regex_search(contenido_, match, body))
  {
    body_encontrado_ = true;
    return true;
  }
  else
  {
    body_encontrado_ = false;
    return false;
  }
}

bool Analizador::Html()
{
  std::regex html("<html>([\\s\\S]*)</html>");
  std::smatch match;
  if (std::regex_search(contenido_, match, html))
  {
    html_encontrado_ = true;
    return true;
  }
  else
  {
    html_encontrado_ = false;
    return false;
  }
}

void Analizador::FindTags()
{
  std::regex tag_regex("<([A-Za-z][A-Za-z0-9]*)\\s*([^>]*)>");
  std::smatch match;

  for (int i = 0; i < texto_.size(); i++)
  {
    std::string linea = texto_[i];
    std::string texto_linea;
    while (std::regex_search(linea, match, tag_regex))
    {
      texto_linea += "LINE: ";
      texto_linea += std::to_string(i + 1);
      texto_linea += " -> TAG: " + match[1].str();
      Tags_.push_back(texto_linea);
      linea = match.suffix().str();
      texto_linea = "LINE: ";
    }
  }
}

void Analizador::FindAttributes()
{
  std::regex tag_regex("<([A-Za-z][A-Za-z0-9]*)\\s*([^>]*)>");
  std::regex attr_regex("(\\w+)=(\"[^\"]*\")");

  std::smatch tag_match;
  std::smatch attr_match;

  for (int i = 0; i < texto_.size(); i++)
  {
    std::string linea = texto_[i];
    if (std::regex_search(linea, tag_match, tag_regex))
    {
      std::string nombre_tag = tag_match[1].str();
      std::string old_tag = "";
      std::string atributos = tag_match[2].str();
      // Lo que queda del texto que no coincide con el tag
      while (std::regex_search(atributos, attr_match, attr_regex))
      {
        std::string texto_linea;
        if (old_tag != nombre_tag)
        {
          texto_linea += "\n[ LINE " + std::to_string(i + 1) + " ] : " + nombre_tag + "\n";
          old_tag = nombre_tag;
        }
        texto_linea += "ATRIBUTOS: ";
        texto_linea += attr_match[1].str();
        texto_linea += "=";
        texto_linea += attr_match[2].str();
        texto_linea += "\n";

        Atributos_.push_back(texto_linea);
        atributos = attr_match.suffix().str();
      }
    }
  }
}

void Analizador::FindComments()
{
  std::regex inicio_regex("<!--");
  std::regex fin_regex("-->");
  std::string texto_linea;
  std::string comentario;
  bool dentro_comentario = false;
  int linea_inicial = 0;
  for (int i = 0; i < texto_.size(); i++) {
    std::string linea = texto_[i];
    // Buscar inicio del comentario
    if (!dentro_comentario &&
        std::regex_search(linea, inicio_regex)) {
      dentro_comentario = true;
      linea_inicial = i + 1;
      texto_linea = "";
      comentario = "";
    } 
    // Aqui lo que hago es basicamente es que cada linea que venga despues
    // del -->, se almacena en la variable comentario
    if (dentro_comentario == true) {
      comentario += linea + "\n";
    }
    // Buscar final del comentario
    if (dentro_comentario &&
      std::regex_search(linea, fin_regex))
    {
      int linea_fin = i + 1;
      if (linea_fin != linea_inicial) {
        texto_linea += "[ LINE " + std::to_string(linea_inicial) +
        " - " + std::to_string(linea_fin) + " ]" + "\n";
      } else {
        texto_linea += "[ LINE " + std::to_string(linea_inicial) +
        " ]" + "\n";
      } 
      dentro_comentario = false;
      texto_linea += comentario;
      Comments_.push_back(texto_linea);
    }
  }
}