#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// Tips: Anv�nd de globala konstanterna ANTAL_BOKSTAVER och ANTAL_SPRAK
// ist�llet f�r v�rdena 26 och 4 i programmet.
const int ANTAL_BOKSTAVER = 26; // A-Z
const int ANTAL_SPRAK = 4;

// 2d-arrayen TOLK_HJALP inneh�ller bokstavsfrekvensen i %
// f�r fyra spr�k. TOLK_HJALP[0][0] �r frekvensen av
// bokstaven a f�r engelska. TOLK_HJALP[0][25] �r frekvensen av
// bokstaven z f�r engelska.
// Arrayen �r en GLOBAL KONSTANT och skall allts� ej skickas
// som parameter till den funktion som beh�ver den.
const double TOLK_HJALP[ANTAL_SPRAK][ANTAL_BOKSTAVER] = {
    {8.27, 1.48, 2.94, 4.03, 11.78, 2.22, 1.72, 6.77, // engelska
     7.39, 0.12, 0.81, 3.76, 2.85,  6.71, 7.79, 1.54, 0.05,
     5.95, 6.69, 9.07, 2.66, 1.13,  2.14, 0.19, 1.89, 0.03},
    {7.97, 1.40, 3.55, 3.79, 16.89, 1.02, 1.00, 0.75, // franska
     7.08, 0.38, 0.04, 5.51, 2.82,  8.11, 5.19, 2.78, 1.01,
     6.69, 8.35, 7.22, 6.09, 1.35,  0.02, 0.54, 0.30, 0.15},
    {9.50, 1.11, 1.53, 5.30, 8.94, 1.74, 3.57, 3.94, // svenska
     3.98, 0.89, 3.26, 4.93, 3.41, 8.46, 5.01, 1.77, 0.00,
     6.73, 5.56, 9.20, 1.94, 2.42, 0.00, 0.05, 0.45, 0.00},
    {5.12, 1.95, 3.57, 5.07, 16.87, 1.35,  3.00, 5.79, // tyska
     8.63, 0.19, 1.14, 3.68, 3.12,  10.64, 1.74, 0.42, 0.01,
     6.30, 6.99, 5.19, 3.92, 0.77,  1.79,  0.01, 0.69, 1.24}};

string namn_pa_fil();
string inlasning(string filename);

class Text {
private:
  string input;
  int characterCount;
  int histogram[ANTAL_BOKSTAVER];
  double relativeHistogram[ANTAL_BOKSTAVER];

public:
  Text();
  void setText(const string newText);
  bool beraknaHistogramAbs();
  void skrivHistogramAbs();
  void absTillRel();
  void plottaHistogramRel();
  void beraknaHistogram();
  string tolka();
};

int main() {
  Text minText;

  string fileName = namn_pa_fil();
  string text = inlasning(fileName);

  minText.setText(text);

  minText.beraknaHistogram();
  minText.plottaHistogramRel();

  string language = minText.tolka();

  cout << "Det är mest troligt att språket är " << language << endl;

  return 0;
}

string namn_pa_fil() {
  string filename;
  cout << "Ange filnamn: " << endl;
  getline(cin, filename);

  // om filnamnet saknar .txt
  if (filename.rfind(".txt") == string::npos) {
    filename.append(".txt");
  }

  return filename;
}

string inlasning(string filename) {
  ifstream fin(filename.c_str());

  // om filen inte kunde öppnas, stäng programmet
  if (!fin) {
    cout << "Det finns ingen fil med namnet " << filename << endl;
    exit(EXIT_FAILURE);
  }

  char c;
  string text;

  // för varje bokstav, lägg till i text
  while (fin.get(c)) {
    text.push_back(c);
  }

  return text;
}

Text::Text() {
  input = "";
  characterCount = 0;

  // nollställ
  for (int i = 0; i < ANTAL_BOKSTAVER; i++) {
    histogram[i] = 0;
    relativeHistogram[i] = 0;
  }
};

void Text::setText(string newText) { input = newText; };

bool Text::beraknaHistogramAbs() {
  bool foundCharacter = false;

  int inputLength = input.length();

  // för varje bokstav i raden
  for (int i = 0; i < inputLength; i++) {

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
    histogram[index]++;
    characterCount++;
    foundCharacter = true;
  }

  return foundCharacter;
}

void Text::skrivHistogramAbs() {
  cout << "Totala antalet bokstäver: " << characterCount << endl
       << "Bokstavsfördelning" << endl;
  cout << "\nBokstav\tFrekvens\n";

  for (int i = 0; i < ANTAL_BOKSTAVER; i++) {
    char letter = char(i + 'A');
    cout << letter << "\t" << histogram[i] << endl;
  }
}

void Text::absTillRel() {
  for (int i = 0; i < ANTAL_BOKSTAVER; i++) {
    // om det inte finns någon bokstav i textfilen så behövs ingen beräknning
    if (histogram[i] <= 0) {
      continue;
    }

    // hämta procentandelen av alla bokstäver i textfilen
    double percentage = (double)histogram[i] / characterCount * 100;
    relativeHistogram[i] = percentage;
  }

  cout << "Resultat för bokstäverna A-Z" << endl
       << "Totala antalet bokstäver: " << characterCount << endl;
}

void Text::plottaHistogramRel() {
  for (int i = 0; i < ANTAL_BOKSTAVER; i++) {
    if (histogram[i] > 0) {
      // trunkera
      int truncated = relativeHistogram[i] / 0.5 + 0.5;

      cout << char(i + 'A') << " ";

      // skriv ut * för den relativa frekvensen
      for (int j = 0; j < truncated; j++) {
        cout << "*";
      }

      cout << endl;
    }
  }
}

void Text::beraknaHistogram() {
  // om det finns inte finns några bokstäver, strunta i att beräkna relativ
  if (!beraknaHistogramAbs()) {
    return;
  }

  absTillRel();
}

string Text::tolka() {
  double diff[ANTAL_SPRAK], sum[ANTAL_SPRAK];

  // nollställ listorna
  for (int i = 0; i < ANTAL_SPRAK; i++) {
    diff[i] = 0;
    sum[i] = 0;
  }

  // beräkna kvadratsumman
  for (int i = 0; i < ANTAL_BOKSTAVER; i++) {
    for (int j = 0; j < ANTAL_SPRAK; j++) {
      diff[j] = TOLK_HJALP[j][i] - relativeHistogram[i];
      sum[j] += diff[j] * diff[j];
    }
  }

  // list of all languages
  string languages[ANTAL_SPRAK] = {"engelska", "franska", "svenska", "tyska"};

  for (int i = 0; i < ANTAL_SPRAK; i++) {
    cout << languages[i] << " har kvadratsumman " << sum[i] << endl;
  }

  // sätt defaultvärden
  double min = sum[0];
  int langIdx = 0;

  // sortera fram det mest troliga språket
  for (int j = 0; j < ANTAL_SPRAK; j++) {
    if (min > sum[j]) {
      min = sum[j];
      langIdx = j;
    }
  }

  return languages[langIdx];
}