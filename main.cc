#include <iostream>
#include <regex>
#include <string>

int main()
{
  // Target sequence
  std::string target_s = "I am looking for GeeksForGeeks articles ";
  // An object of regex for pattern to be searched
  std::regex expression(" Geeks [a-zA -Z]+");

  // smatch for storing the matches
  std::smatch matches;

  // regex_search () for searching the regex pattern
  // ’expression ’ in the string ’target_s ’.
  regex_search(target_s, matches, expression);

  for (auto match : matches)
    std::cout << match << std::endl;

  return 0;
}