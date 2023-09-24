#include <iostream>
#include <jsoncpp/json/json.h>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <set>
#include <locale>
using namespace std;



/**
 * @param file_contents A list of strings, where each string represents the contents of a file.
 * @return The contents of the merged file.
 */

std::vector<std::string> splitString(const std::string& input, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::stringstream ss(input);

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

string mergeFiles(vector<string> file_contents)
{
    map<string, map<string, string>> hash;
    vector<string> tokens;
    int i;
    int j;
    string name;
    string to_s;

    for(auto file : file_contents)
    {
        istringstream iss(file);
        while (getline(iss, to_s))
        {
            i = to_s.find("Name=", 0);
            i = i + 5;
            j = i;
            while(to_s[i] && to_s[i] != ';')
                i++;
            name = to_s.substr(j, i - j);
            if (hash.count(name) == 0)
                hash[name] = map<string, string>();
            tokens = splitString(to_s, ';');
            for (auto token : tokens)
            {
                if (token.find("Name=", 0) != string::npos)
                    continue ;
                i = token.find("=", 0);
                hash[name][token.substr(0, i)] = token.substr(i + 1, token.size());
            }
        }
    }
    string result = "";
    for (auto p : hash)
    {
      result += "Name=" + p.first + ';';
      for (auto b : p.second)
      {
        result += b.first + "=" + b.second + ";";
      }
      result.pop_back();
      result += "\n";
    }
    result.pop_back();
    return (result);
}

/* Ignore and do not change the code below */

void trySolution(string merged_file) {
  Json::Value output_json;
  output_json = Json::Value(merged_file);

  Json::FastWriter fastWriter;
  std::string output_str = fastWriter.write(output_json);
  cout << "" << output_str.c_str();
}

int main () {
  setlocale(LC_ALL, "en_US.UTF-8");
  Json::Reader reader;
  string line;
  Json::Value parsed_json;
  std::getline(std::cin, line, '\n');
  reader.parse(line, parsed_json);

  vector<string> array;
  for (int i = 0 ; i < parsed_json.size() ; i++) {
    array.push_back(parsed_json[i].asString());
  }
  vector<string> file_contents = array;

  string output = mergeFiles(file_contents);
  trySolution(output);
}
/* Ignore and do not change the code above */
