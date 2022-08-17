#include <cmath>
#include <fstream>
#include <iostream>
using namespace std;

const int MAX_PERSONER = 10;
const int MAX_TRANSAKTIONER = 30;

class Transaktion {
private:
  string datum;
  string typ;
  string namn;
  double belopp;
  int antal_kompisar;
  string kompisar[MAX_PERSONER];

public:
  Transaktion();
  ~Transaktion();
  string hamtaNamn();
  double hamtaBelopp();
  int hamtaAntalKompisar();
  bool finnsKompis(const string &namnet);
  bool lasIn(istream &is);
  void skrivUt(ostream &os);
  void skrivTitel(ostream &os);
};

class Person {
private:
  string namn;
  double betalat_andras; // ligger ute med totalt
  double skyldig;        // skyldig totalt

public:
  Person();
  Person(const string &namn, double betalat_andras, double skyldig);
  string hamtaNamn();
  double hamtaBetalat();
  double hamtaSkyldig();
  void skrivUt(ostream &os);
};

class PersonLista {
private:
  int antal_personer;
  Person personer[MAX_PERSONER];

public:
  PersonLista();
  ~PersonLista();
  void laggTill(Person ny_person);
  void skrivUtOchFixa(ostream &os);
  double summaSkyldig();
  double summaBetalat();
  bool finnsPerson(const string &namn);
};

class TransaktionsLista {
private:
  int antal_transaktioner;
  Transaktion transaktioner[MAX_TRANSAKTIONER];

public:
  TransaktionsLista();
  ~TransaktionsLista();
  void lasIn(istream &is);
  void skrivUt(ostream &os);
  void laggTill(Transaktion &t);
  double totalKostnad();
  double liggerUteMed(const string &namnet);
  double arSkyldig(const string &namnet);
  PersonLista fixaPersoner();
};

int main() {
  cout << "Startar med att läsa från en fil." << endl;

  TransaktionsLista transaktioner;

  std::ifstream is("resa2.txt");

  transaktioner.lasIn(is);

  int operation = 1;
  while (operation != 0) {
    cout << endl;
    cout << "Välj i menyn nedan:" << endl;
    cout << "0. Avsluta. Alla transaktioner sparas på fil." << endl;
    cout << "1. Skriv ut information om alla transaktioner." << endl;
    cout << "2. Läs in en transaktion från tangentbordet." << endl;
    cout << "3. Beräkna totala kostnaden." << endl;
    cout << "4. Hur mycket är en viss person skyldig?" << endl;
    cout << "5. Hur mycket ligger en viss person ute med?" << endl;
    cout << "6. Lista alla personer mm och FIXA" << endl;

    cin >> operation;
    cout << endl;

    switch (operation) {
    case 1: {
      transaktioner.skrivUt(cout);
      break;
    }
    case 2: {
      Transaktion transaktion;
      cout << "Ange transaktion i följande format" << endl;
      transaktion.skrivTitel(cout);
      transaktion.lasIn(cin);
      transaktioner.laggTill(transaktion);
      break;
    }
    case 3: {
      cout << "Den totala kostnanden för resan var "
           << transaktioner.totalKostnad() << endl;
      break;
    }
    case 4: {
      cout << "Ange personen: ";
      string namn;
      cin >> namn;
      double ar_skyldig = transaktioner.arSkyldig(namn);
      if (ar_skyldig == 0.)
        cout << "Kan inte hitta personen " << namn << endl;
      else
        cout << namn << " är skyldig " << ar_skyldig << endl;
      break;
    }
    case 5: {
      cout << "Ange personen: ";
      string namn;
      cin >> namn;
      double ligger_ute_med = transaktioner.liggerUteMed(namn);
      if (ligger_ute_med == 0.)
        cout << "Kan inte hitta personen " << namn << endl;
      else
        cout << namn << " ligger ute med " << ligger_ute_med << endl;
      break;
    }
    case 6: {
      cout << "Nu skapar vi en personarray och reder ut det hela!" << endl;
      PersonLista lista = transaktioner.fixaPersoner();
      lista.skrivUtOchFixa(cout);
      break;
    }
    }
  }

  std::ofstream os("transaktioner.txt");
  transaktioner.skrivUt(os);

  return 0;
}

Transaktion::Transaktion() {
  datum = "";
  typ = "";
  namn = "";
  belopp = 0.0;
  antal_kompisar = 0;
  for (int i = 0; i < MAX_PERSONER; i++) {
    kompisar[i] = "";
  }
}

Transaktion::~Transaktion() {}

string Transaktion::hamtaNamn() { return namn; }

double Transaktion::hamtaBelopp() { return belopp; }

int Transaktion::hamtaAntalKompisar() { return antal_kompisar; }

bool Transaktion::finnsKompis(const string &namnet) {
  for (int i = 0; i < MAX_PERSONER; i++) {
    if (!(kompisar[i].find(namnet) == string::npos)) {
      return true;
    }
  }

  return false;
}

bool Transaktion::lasIn(istream &is) {
  is >> datum >> typ >> namn >> belopp >> antal_kompisar;

  for (int i = 0; i < MAX_PERSONER; i++) {
    kompisar[i] = "";
  }

  for (int i = 0; i < antal_kompisar; i++) {
    is >> kompisar[i];
  }

  return !is.eof();
}

void Transaktion::skrivUt(ostream &os) {
  os << datum << "\t" << typ << "\t" << namn << "\t" << belopp << "\t"
     << antal_kompisar << "\t";

  // lägg till varje kompis med en tabb emellan
  for (int i = 0; i < antal_kompisar; i++) {
    os << kompisar[i] << "\t";
  }

  os << endl;
}

void Transaktion::skrivTitel(ostream &os) {
  // skriv ut titeln med tabbar emellan varje kolumn
  os << "Datum\tTyp\tNamn\tBelopp\tAntal\tLista över kompisar" << endl;
}

Person::Person() {
  namn = "";
  betalat_andras = 0.0;
  skyldig = 0.0;
}

Person::Person(const string &namn, double betalat_andras, double skyldig) {
  this->namn = namn;
  this->betalat_andras = betalat_andras;
  this->skyldig = skyldig;
}

string Person::hamtaNamn() { return namn; }

double Person::hamtaBetalat() { return betalat_andras; }

double Person::hamtaSkyldig() { return skyldig; }

void Person::skrivUt(ostream &os) {
  os << namn << " ligger ute med " << betalat_andras << " och är skyldig "
     << skyldig;

  // om personen betalat mer än den är skyldig
  if (betalat_andras > skyldig) {
    os << ". Skall ha " << betalat_andras - skyldig << " från potten!" << endl;
    return;
  }

  os << ". Skall lägga " << skyldig - betalat_andras << " till potten!" << endl;
}

PersonLista::PersonLista() { antal_personer = 0; }

PersonLista::~PersonLista() {}

void PersonLista::laggTill(Person ny_person) {
  personer[antal_personer] = ny_person;
  antal_personer++;
}

void PersonLista::skrivUtOchFixa(ostream &os) {
  for (int i = 0; i < antal_personer; i++) {
    personer[i].skrivUt(os);
  }

  // felmarginal för att kolla om summaSkylkdig = summaBetalat
  double felmarginal = 0.000000001;

  if (fabs(summaSkyldig() - summaBetalat()) < felmarginal) {
    os << "Summan i potten stämmer!" << endl;
    return;
  }

  os << "Någon har tagit ut ellet betalat för mycket!" << endl;
}

double PersonLista::summaSkyldig() {
  // Summan av alla skyldigheter
  double total = 0.0;

  for (int i = 0; i < antal_personer; i++) {
    // hämta alla personers skyldighet
    total += personer[i].hamtaSkyldig();
  }

  // returnera totalen
  return total;
}

double PersonLista::summaBetalat() {
  // Summan av alla betalningar
  double total = 0.0;

  for (int i = 0; i < antal_personer; i++) {
    total += personer[i].hamtaBetalat();
  }

  return total;
}

bool PersonLista::finnsPerson(const string &namn) {
  for (int i = 0; i < antal_personer; i++) {
    // om man hittar namnet
    if (!(personer[i].hamtaNamn().find(namn) == string::npos)) {
      return true;
    }
  }
  return false;
}

TransaktionsLista::TransaktionsLista() { antal_transaktioner = 0; }

TransaktionsLista::~TransaktionsLista() {}

void TransaktionsLista::lasIn(istream &is) {
  Transaktion t;

  while (t.lasIn(is)) {
    laggTill(t);
  }
}

void TransaktionsLista::skrivUt(ostream &os) {
  os << "Antal transaktioner = " << antal_transaktioner << endl;
  os << "Datum\tTyp\tNamn\tBelopp\tAntal\tLista över kompisar" << endl;

  for (int i = 0; i < antal_transaktioner; i++) {
    transaktioner[i].skrivUt(os);
  }
}

void TransaktionsLista::laggTill(Transaktion &t) {
  transaktioner[antal_transaktioner] = t;
  antal_transaktioner++;
}

double TransaktionsLista::totalKostnad() {
  double total = 0.0;

  for (int i = 0; i < antal_transaktioner; i++) {
    total += transaktioner[i].hamtaBelopp();
  }

  return total;
}

double TransaktionsLista::liggerUteMed(const string &namnet) {
  double total = 0.0;

  for (int i = 0; i < antal_transaktioner; i++) {
    // om det inte är personen, skippa
    if (transaktioner[i].hamtaNamn() != namnet) {
      continue;
    }

    double antalKompisar = transaktioner[i].hamtaAntalKompisar() + 1;
    double belopp = transaktioner[i].hamtaBelopp();

    total += belopp * (1.0 - 1.0 / antalKompisar);
  }
  return total;
}

double TransaktionsLista::arSkyldig(const string &namnet) {
  double total = 0.0;

  for (int i = 0; i < antal_transaktioner; i++) {
    // om kompisen inte finns
    if (!transaktioner[i].finnsKompis(namnet)) {
      continue;
    }

    double belopp = transaktioner[i].hamtaBelopp();
    double kompisar = transaktioner[i].hamtaAntalKompisar() + 1;

    total += (belopp / kompisar);
  }
  return total;
}

PersonLista TransaktionsLista::fixaPersoner() {
  PersonLista personList;
  string personNamn;
  double personBetalat;
  double personSkyldig;

  for (int i = 0; i < antal_transaktioner; i++) {
    // om personen finns, skippa
    if (personList.finnsPerson(transaktioner[i].hamtaNamn())) {
      continue;
    }

    // annars skapa personen
    personNamn = transaktioner[i].hamtaNamn();
    personBetalat = liggerUteMed(personNamn);
    personSkyldig = arSkyldig(personNamn);

    Person nyPerson(personNamn, personBetalat, personSkyldig);
    personList.laggTill(nyPerson);
  }
  return personList;
}