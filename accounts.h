#ifndef ACCOUNTS_H_INCLUDED
#define ACCOUNTS_H_INCLUDED

class Cont {
    string username;
    string password;
    public:
        map<Produs, int> cos;
        vector<Comanda> comenzi;
        Cont();
        Cont(string& username, string& pwd) {
            this->username = username;
            this->password = pwd;
        }
        void setName(string user) {
            this->username = user;
        }
        void setPWD(string user) {
            this->password = user;
        }
        string getName() {
            return this->username;
        }
        string getPWD() {
            return this->password;
        }
        void add_item(Produs& p, int a) {
            if(this->cos.find(p) != this->cos.end()) {
                this->cos[p] += a;
            }
            else
                this->cos[p] = a;
        }
        int get_cart_item(Produs& p) {
            if(this->cos.find(p) == this->cos.end())
                return 0;
            else return this->cos[p];
        }
        void delete_item(const Produs& p) {
            if(this->cos.find(p) == this->cos.end())
                return;
            cos.erase(p);
        }
        void add_comanda(const Comanda &c) {
            this->comenzi.push_back(c);
        }

};
vector<Cont> conturi;

void meniu(Cont& c);

void saveAccounts() {
    ofstream file;
    file.open("conturi.txt");
    for(auto it = conturi.begin(); it!=conturi.end(); ++it) {
        file<<it->getName()<<" "<<it->getPWD()<<endl;
    }
    file.close();
}
void loadAccounts() {
    ifstream file;
    string nume, pwd;
    file.open("conturi.txt");
    while(file>>nume) {
        file>>pwd;
        conturi.push_back(Cont(nume, pwd));
    }
    file.close();

}
void create_account(int type, string nume = string()) {
    switch(type){
        case 1: {
            string username;
            bool contulExista = false;
            cout<<"Insert username: ";
            cin>>username;
            for(auto it = conturi.begin(); it!=conturi.end(); ++it) {
                if(it->getName() == username) {
                    contulExista = true;
                    break;
                }
            }
            if(contulExista) system("cls"), cout<<"Numele de utilizator deja exista!\n", create_account(1);
            else {
                create_account(2, username);
            }
            break;
        }
        case 2: {
            string pwd;
            cout<<endl;
            cout<<"Insert password: ";
            cin>>pwd;
            Cont curent(nume, pwd);
            conturi.push_back(curent);
            saveAccounts();
            system("cls");
            string dir = "conturi/" + nume;
            const char* dir2 = dir.c_str();
            mkdir(dir2);
            meniu(curent);

            break;


        }

    }
}


void save_orders(Cont& c) {
    ofstream file;
    string dir1 = "conturi/" + c.getName() + "/comenzi.txt";
    const char* dir = dir1.c_str();
    file.open(dir);
    for(auto cmd : c.comenzi) {
        for(unsigned int it = 0; it<cmd.preturi.size(); it++) {
            file<<cmd.nume_produs[it]<<endl;
            file<<cmd.preturi[it]<<" "<<cmd.bucati[it]<<endl;
        }
        file<<"�"<<endl;
    }
    file.close();
}
void load_orders(Cont& c) {
    ifstream file;
    string dir1 = "conturi/" + c.getName() + "/comenzi.txt";
    const char* dir = dir1.c_str();
    file.open(dir);
    string name;
    Comanda* cmd = new Comanda();
    while(getline(file>>ws, name)) {
        int pret, buc;
        if(name == "�") {
            getline(file>>ws, name);
            c.comenzi.push_back(*cmd);
            delete cmd;
            cmd = new Comanda();
        }
        file>>pret>>buc;
        cmd->add_prod(name, pret, buc);
    }
    file.close();
}

void require_login() {

    int option = 0;
    cout<<"1. Sign up\n";
    if(conturi.size() == 0) option = 1;
    cout<<"2. Log in\n";
    while(option < 1 || option > 2)
        cin>>option;
    if(option == 1)

        system("cls"), create_account(1);
    else {
        system("cls");
        string username, pwd;
        cout<<"Insereaza numele de utilizator: ";
        cin>>username;
        cout<<"\nInsereaza parola: ";
        cin>>pwd;
        for(auto it = conturi.begin(); it!=conturi.end(); ++it) {
            if(it->getName() == username && it->getPWD() == pwd) {

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

#endif // ACCOUNTS_H_INCLUDED
