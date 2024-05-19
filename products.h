#ifndef PRODUCTS_H_INCLUDED
#define PRODUCTS_H_INCLUDED

class Produs {
    string nume;
    int pret;
    int stoc;
    int categorie;
    public:
        Produs(string& nume, int pret, int stoc, int cat) {
            this->nume = nume;
            this->pret = pret;
            this->stoc = stoc;
            this->categorie = cat;
        }
        string getName() {
            return this->nume;
        }
        int getCateg() {
            return this->categorie;
        }
        int getStoc() {
            return this->stoc;
        }
        int getPret() {
            return this->pret;
        }
        void setStoc(int a) {
            this->stoc = a;
        }
        void setCategorie(int a) {
            this->categorie = a;
        }
        Produs& operator-=(int a) {
            this->stoc -= a;
            return *this;
        }
        friend ostream& operator<<(ostream& os, Produs& p) {
            os<<"Nume produs:\t"<<p.getName()<<endl;
            os<<"Pret: \t\t"<<p.getPret()<<" RON"<<endl;
            os<<"Stoc: \t\t"<<p.getStoc()<<endl;
            os<<"---------------------------------------------"<<endl<<endl;
            return os;
        }
        friend bool operator<(Produs p1, Produs p2) {
            if(p1.getName() < p2.getName()) return true;
            return false;
        }
        friend bool operator==(Produs p1, Produs p2) {
            if(p1.getName() == p2.getName()) return true;
            return false;
        }
};
vector<Produs> produse;

void incarca_produse() {
    string name;
    produse.clear();
    int stoc;
    int pret;
    int categorie;
    ifstream file;
    file.open("produse.txt");
    if(!file.is_open()) return;
    while(getline(file>>ws, name)) {
        file>>stoc>>pret>>categorie;
        if(name != "") produse.push_back(Produs(name, pret, stoc, categorie));
    }
    file.close();
}
void salveaza_produse() {

    ofstream file;
    file.open("produse.txt");

    foreach(it, produse) {
        if(it->getPret() != 0 && it->getStoc() != 0) file<<it->getName()<<endl<<it->getStoc()<<" "<<it->getPret()<<" "<<it->getCateg()<<endl;
    }
    file.close();
}

#endif // PRODUCTS_H_INCLUDED
