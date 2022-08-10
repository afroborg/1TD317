#include <cctype>
#include <cmath>
#include <iostream>
#include <string>
using namespace std;

const int ANTAL_BOKSTAVER = 26; // A-Z

int berakna_histogram_abs(const string input, int frequency[]);
void skriv_histogram_abs(int frequency[], int characterCount);

int main() {
  string input;
  int frequency[ANTAL_BOKSTAVER];

  // sätt alla värden till 0
  for (int i = 0; i < ANTAL_BOKSTAVER; i++) {
    frequency[i] = 0;
  }

  cout << "Ge en rad med text: " << endl;

  // hämta användarens input
  getline(cin, input);

  int totalCharacters = berakna_histogram_abs(input, frequency);
  skriv_histogram_abs(frequency, totalCharacters);

  return 0;
}

int berakna_histogram_abs(const string input, int frequency[]) {
  int totalCharacters = 0;

  // för varje bokstav i raden
  for (int i = 0; i < input.length(); i++) {

    // kontrollera att det är en bokstav mellan a och z
    bool isCharacter = isalpha(input[i]);

    // om det inte är det, skippa den
    if (!isCharacter) {
      continue;
    }

    // konvertera till gemen, för att ha samma form på allt
    char lowercase = tolower(input[i]);

    int index = lowercase - 'a';

    // uppdatera rätt index i listan av alla bokstäver
    frequency[index]++;
    totalCharacters++;
  }

  return totalCharacters;
}

void skriv_histogram_abs(int frequency[], int characterCount) {
  cout << "Resultat för bokstäverna A-Z" << endl;
  cout << "Totala antalet bokstäver: " << characterCount << endl
       << "Bokstavsfördelning:" << endl;

  // för varje bokstav, skriv ut hur många gånger den hittades
  for (int i = 0; i < ANTAL_BOKSTAVER; i++) {
    char letter = char(i + 'A');

    cout << letter << ": " << frequency[i] << endl;
  }
}