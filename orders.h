#ifndef ORDERS_H_INCLUDED
#define ORDERS_H_INCLUDED



class Comanda {

    int totalPlataComanda;
    public:
        vector<string> nume_produs;
        vector<int> preturi;
        vector<int> bucati;
        Comanda() {
            this->nume_produs.clear();
            this->preturi.clear();
            this->bucati.clear();
            this->totalPlataComanda = 0;
        }
        void add_prod(string nume, int pret, int buc) {
            this->nume_produs.push_back(nume);
            this->preturi.push_back(pret);
            this->bucati.push_back(buc);
            this->totalPlataComanda += pret*buc;
        }
        friend ostream& operator<<(ostream& os, Comanda& c) {
            for(unsigned int it = 0; it<c.preturi.size(); it++) {
                os<<"Nume produs:\t"<< c.nume_produs[it] <<endl;
                os<<"Pret: \t\t"<<c.preturi[it]<<" RON"<<endl;
                os<<"Bucati: \t"<<c.bucati[it]<<endl;
                os<<"Total: \t\t"<<c.preturi[it]*c.bucati[it]<<" RON"<<endl<<endl;
            }
            return os;
        }
        int getTotal() {
            return this->totalPlataComanda;
        }

};



#endif // ORDERS_H_INCLUDED
