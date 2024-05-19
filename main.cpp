#include "includes.h"

using namespace std;

#include "products.h"
#include "categories.h"
#include "orders.h"
#include "accounts.h"
#include "menuUI.h"


int main(int argc, char* argv[])
{
    incarca_categorii();
    loadAccounts();
    incarca_produse();
    if(argc == 1) require_login();
    else { 
        if(strcmp(argv[1], "login") == 0) {
            string user;
            string pass;
            if(argc < 4 || argc > 4) cout<<argv[0]<<" help";
            else{
                user.assign(argv[2]);
                pass.assign(argv[3]);
                for(auto it = conturi.begin(); it!=conturi.end(); ++it) {
                    if(it->getName() == user && it->getPWD() == pass) {

                        system("cls");
                        load_orders(*it);
                        meniu(*it);
                        break;
                    }
                }
                system("cls");
                cout<<"Numele de utilizator sau parola au fost gresite!"<<endl;
                require_login();
            }
        }
        else if(strcmp(argv[1], "signup") == 0) {
            string user;
            string pass;
            if(argc < 4 || argc > 4) cout<<argv[0]<<" help";
            else{
                user.assign(argv[2]);
                pass.assign(argv[3]);
                bool contulExista = false;
                for(auto it = conturi.begin(); it!=conturi.end(); ++it) {
                    if(it->getName() == user) {
                        contulExista = true;
                        break;
                    }
                }
                if(contulExista) cout<<"Numele de utilizator deja exista!\n";
                else {
                    Cont curent(user, pass);
                    conturi.push_back(curent);
                    saveAccounts();
                    system("cls");
                    string dir = "conturi/" + string(argv[2]);
                    const char* dir2 = dir.c_str();
                    mkdir(dir2);
                    meniu(curent);
                }
            }
        }
        else if(strcmp(argv[1], "add_produs") == 0) {
            system("cls");

            string numeprod;
            cout<<"Insereaza numele produsului: ";
            getline(cin>>ws, numeprod);
            foreach(it, produse){
                if(numeprod == it->getName()) {
                    system("cls");
                    cout<<"Acel produs exista deja in stoc."<<endl;
                    break;
                }
            }

            cout<<endl<<"Insereaza pretul produsului: ";
            int pret;
            cin>>pret;
            if(pret < 1) {
                system("cls");
                cout<<"Pret invalid."<<endl;
            }

            cout<<endl<<"Insereaza stocul produsului: ";
            int stoc;
            cin>>stoc;

            if(stoc < 1) {
                system("cls");
                cout<<"Stoc invalid."<<endl;
            }

            cout<<endl<<"Insereaza categoria:"<<endl;
            int cat=-1;
            cout<<endl<<"Insereaza categoria:"<<endl;
            for(int i = 0; i<totalCategori; i++) {
                cout<<i<<". "<<categories[i]<<endl;
            }
            while(cat < 0 || cat >= totalCategori) cin >>cat;

            produse.push_back(Produs(numeprod, pret, stoc, cat));

            salveaza_produse();
            system("cls");
            cout<<"Produsul "<<numeprod<<" a fost adaugat cu succes."<<endl;
        }
        else if(strcmp(argv[1], "help") == 0) {
            cout<<argv[0]<<" login [USERNAME] [PAROLA] - pentru a te loga intr-un cont"<<endl;
            cout<<argv[0]<<" signup [USERNAME] [PAROLA] - pentru a creea un cont"<<endl;
            cout<<argv[0]<<" add_produs - pentru a adauga un produs"<<endl;
            cout<<argv[0]<<" help - pentru a vedea comenzile"<<endl;
        }
        else {
            cout<<"Foloseste "<<argv[0]<<" help pentru a vedea comenzile"<<endl;
        }
    }
    return 0;
}
