#include <iostream>
using namespace std;

void skrivInfo();
int lasEttTal(int index);
char lasOp();
void ordna(int &a, int &b);
int berakna(char op, int tal1, int tal2);
void skrivResultat(int resultat);

int main() {
  skrivInfo();

  // läs in två olika tal
  int tal1 = lasEttTal(1);
  int tal2 = lasEttTal(2);

  // ordna så att tal 1 är mindre än tal 2
  ordna(tal1, tal2);

  char op = lasOp();

  // beräkna resultatet med givna tal och operator
  int resultat = berakna(op, tal1, tal2);

  // skriv ut resultatet
  skrivResultat(resultat);

  return 0;
}

/**
 * Skriver ut en välkomsthälsning till användaren
 */
void skrivInfo() {
  cout << "Välkommen till inlämningsuppgift 3, räknaren!" << endl;
  cout << "Du kommer nu att få skriva in två tal och en operation." << endl
       << endl;
  ;
}

/**
 * Läser in ett tal från använadren
 * @param index används för att visa vilket av dem två talen som ska skrivas in
 * @return int talet som användaren skrev in
 */
int lasEttTal(int index) {
  cout << "Skriv in tal " << index << ": ";

  int tal;
  cin >> tal;

  return tal;
}

/**
 * Läser in operationen från användaren
 * @return char operationen som användaren skrev in
 */
char lasOp() {
  cout << "Vilken operation vill du använda?" << endl;
  cout << "a) Addition" << endl;
  cout << "m) Multiplikation" << endl;
  cout << "r) Kvadratsumma" << endl;

  char op;
  cin >> op;

  // om det inte är en giltig operator så kommer den fråga om tills det är en
  // giltig
  if (op != 'a' && op != 'm' && op != 'r') {
    cout << "Felaktig inmatning!" << endl;
    return lasOp();
  }

  return op;
}

/**
 * Ordnar två tal så att det första är mindre än det andra
 * @param tal1 Första talet
 * @param tal2 Andra talet
 */
void ordna(int &tal1, int &tal2) {
  if (tal1 > tal2) {
    int temp = tal1;
    tal1 = tal2;
    tal2 = temp;
  }
}

/**
 * Gör en beräkning beroende på vilken operation användaren valt
 * @param op operationen
 * @param tal1 första talet
 * @param tal2 andra talet
 * @return int totalen efter beräkningarna
 */
int berakna(char op, int tal1, int tal2) {
  // 1 om multiplikation, 0 om addition eftersom vi inte kan multiplicera med 0
  // från början då allting blir 0 då
  int total = op == 'm' ? 1 : 0;

  // loopa från första talet till andra talet och beroende på beräkning addera
  // till totalen
  for (int i = tal1; i <= tal2; i++) {
    switch (op) {
    case 'a':
      total += i;
      break;
    case 'm':
      total *= i;
      break;
    case 'r':
      total += i * i;
    }
  }

  return total;
}

/**
 * Skriver ut resultatet till användaren
 * @param resultat Totalen
 */
void skrivResultat(int resultat) {
  cout << "Resultatet är: " << resultat << endl;
}