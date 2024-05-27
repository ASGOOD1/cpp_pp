#ifndef MENUUI_H_INCLUDED
#define MENUUI_H_INCLUDED


void cautare(int option, Cont& c);
int calculeaza_cos(Cont& c) {
    if(c.cos.size() == 0) return 0;
    int suma = 0;
    for(auto p : c.cos) {
        auto prod = find(produse.begin(), produse.end(), p.first);
        suma += prod->getPret() * p.second;
    }
    return suma;
}
void editare_categ(int s, Cont& c) {
    system("cls");
    switch(s) {
        case 1: {
            for(int i = 0; i<totalCategori; i++) {
                cout<<i<<". "<<categories[i]<<endl;
            }
            int n;
            cout<<"Insereaza categoria pe care vrei sa o editezi: ";
            cin>>n;
            while(n<0 || n>=totalCategori) cin>>n;
            string cat;
            cout<<endl<<"Introdu noul nume pentru categorie: ";
            getline(cin>>ws, cat);
            categories[n] = cat;
            salveaza_categorii();
            system("cls");
            cout<<"Categoria a fost modificata cu succes."<<endl;
            meniu(c);
            break;
        }
        case 2: {
            string cat;
            cout<<endl<<"Introdu numele categoriei noi: ";
            getline(cin>>ws, cat);
            for(int i = 0; i<totalCategori; i++) {
                cout<<i<<". "<<categories[i]<<endl;
            }
            categories[totalCategori] = cat;
            totalCategori++;
            salveaza_categorii();
            system("cls");
            cout<<"Categoria a fost adaugata cu succes."<<endl;
            meniu(c);
            break;
        }
    }
}
void cart_model(int select, Cont& c) {
    switch(select) {
        case 1: {
            string nume;
            bool deleted = false;
            cout<<"Introdu numele produsului: ";
            getline(cin>>ws, nume);
            for(auto it : c.cos) {
                auto prod = find(produse.begin(), produse.end(), it.first);
                if(prod->getName().find(nume) != string::npos) {
                    c.delete_item(it.first);
                    deleted = true;
                    break;
                }
            }
            if(!deleted) {
                system("cls");
                cout<<"Produsul nu se afla la tine in cos."<<endl;
                meniu(c);
            }
            else {
                system("cls");
                cout<<"Produsul a fost sters din cosul tau de cumparaturi."<<endl;
                meniu(c);
            }
            break;
        }
        case 2: {
            Comanda cmd;
            for(auto it : c.cos) {
                auto prod = find(produse.begin(), produse.end(), it.first);
                cmd.add_prod(prod->getName(), prod->getPret(), it.second);
                prod->setStoc(prod->getStoc() - it.second);
            }
            c.cos.clear();
            salveaza_produse();
            incarca_produse();
            c.add_comanda(cmd);

            save_orders(c);
            system("cls");
            cout<<"Comanda a fost plasata."<<endl;
            meniu(c);
            break;
        }
    }
}
void meniuAdmin(Cont& c) {
    cout<<"Hello, "<<c.getName()<<endl;
    cout<<"1. Vezi toate produse"<<endl;
    cout<<"2. Adauga produs"<<endl;
    cout<<"3. Sterge produs"<<endl;
    cout<<"4. Cauta produs"<<endl;
    cout<<"5. Vezi cos de cumparaturi ("<<calculeaza_cos(c)<<")"<<endl;
    cout<<"6. Vezi comenzile tale"<<endl;
    cout<<"7. Modificare categorii"<<endl;
    cout<<"8. Modificare produse"<<endl;
    cout<<"9. Vezi toate comenzile"<<endl;
    cout<<"10. Exit"<<endl;
    int option = 0;
    while((option < 1 || option > 10) && option != 20) cin>>option;
    switch(option) {
        case 1: {
            if(produse.size() == 0)  {
                system("cls");
                cout<<"Nu exista produse in stoc."<<endl;
                meniu(c);
            }
            system("cls");
            foreach(it, produse) {
                cout<<*it;
            }
            meniu(c);
            break;
        }
        case 2: {
            system("cls");

            string numeprod;
            cout<<"Insereaza numele produsului: ";
            getline(cin>>ws, numeprod);
            foreach(it, produse){
                if(numeprod == it->getName()) {
                    system("cls");
                    cout<<"Acel produs exista deja in stoc."<<endl;
                    meniu(c);
                    break;
                }
            }

            cout<<endl<<"Insereaza pretul produsului: ";
            int pret;
            cin>>pret;
            if(pret < 1) {
                system("cls");
                cout<<"Pret invalid."<<endl;
                meniu(c);
            }

            cout<<endl<<"Insereaza stocul produsului: ";
            int stoc;
            cin>>stoc;

            if(stoc < 1) {
                system("cls");
                cout<<"Stoc invalid."<<endl;
                meniu(c);
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
            meniu(c);
            break;
        }
        case 3: {
            system("cls");

            string numeprod;
            cout<<"Insereaza numele produsului: ";
            getline(cin>>ws, numeprod);
            bool exista = false;
            foreach(it, produse){
                if(numeprod == it->getName()) {
                    system("cls");
                    cout<<"Produsul "<<numeprod<<" a fost sters."<<endl;
                    c.delete_item(*it);
                    produse.erase(it);
                    salveaza_produse();
                    incarca_produse();
                    exista = true;
                    meniu(c);
                    break;
                }
            }
            if(exista == false) {
                system("cls");
                cout<<"Produsul "<<numeprod<<" nu a fost gasit."<<endl;
                meniu(c);
            }

            break;
        }
        case 4: {
            system("cls");
            cout<<"1. Cautare dupa nume"<<endl;
            cout<<"2. Cautare dupa interval de pret"<<endl;
            cout<<"3. Cautare dupa interval si nume"<<endl;
            cout<<"4. Cautare dupa categorie"<<endl;
            int option = 0;
            while(option < 1 || option > 4) cin>>option;
            cautare(option, c);
            break;
        }
        case 5: {
            system("cls");
            int count = 0;
            cout<<"------------- COS DE CUMPARATURI ------------"<<endl;
            for(auto it : c.cos) {
                cout<<"_____________________________________________"<<endl;
                auto prod = find(produse.begin(), produse.end(), it.first);
                cout<<"Nume produs: \t\t"<<prod->getName()<<endl;
                cout<<"Pret/buc.: \t\t"<<prod->getPret()<<endl;
                cout<<"Nr. buc.: \t\t"<<it.second<<endl;
                cout<<"Total: \t\t\t"<<it.second * prod->getPret()<<" RON"<<endl;
                cout<<endl;
                count++;
            }
            if(count != 0) {
                cout<<"Comanda are o valoare totala de: "<<calculeaza_cos(c)<<" RON";
                cout<<endl<<"---------------------------------------------"<<endl;
                cout<<"1. Stergere produs din cos"<<endl;
                cout<<"2. Plasare comanda"<<endl;
                cout<<"3. Meniu principal"<<endl;
                int select = 0;
                while(select < 1 || select > 3) cin>>select;
                if(select == 3) system("cls"), meniu(c);
                cart_model(select, c);
            }
            else {
                cout<<"Cosul este gol.";
                cout<<endl<<"---------------------------------------------"<<endl;
                meniu(c);
            }
            break;
        }
        case 6: {
            system("cls");
            if(c.comenzi.size() == 0) cout<<"Nu ai nicio comanda plasata."<<endl, meniu(c);
            int index = 1;

            for(auto cmd : c.comenzi) {
                cout<<"___________________ COMANDA "<<index<<" _______________"<<endl;
                cout<<cmd;
                cout<<"\t\t\t Total de plata: "<<cmd.getTotal()<<" RON"<<endl;
                cout<<"_____________________________________________"<<endl<<endl;
                index++;
            }
            meniu(c);
            break;
        }

        case 7: {
            system("cls");
            cout<<"1. Modificare categorie"<<endl;
            cout<<"2. Adaugare categorie"<<endl;
            int select = 0;
            while(select < 1 || select > 2)cin>>select;
            editare_categ(select, c);
            break;

        }

        case 8: {
            system("cls");
            int index = 1, x;
            cout<<"Insereaza produsul pe care vrei sa-l modifici:"<<endl;
            foreach(it, produse) {
                cout<<"|"<<index<<"|"<<endl;
                cout<<*it;
                index++;
            }
            x=0;
            while(x < 1||x>int(produse.size())) cin>>x;

            if(c.cos.size() > 0) {
                for(auto it : c.cos) {
                    if(produse[x-1] == it.first) {
                        system("cls");
                        cout<<"Nu poti edita un produs pe care-l ai in cos."<<endl;
                        meniu(c);
                        break;
                    }
                }
            }
            int r = x-1;
            x = 0;
            system("cls");
            cout<<"Ai ales sa modifici produsul:"<<endl;
            cout<<produse[x-1];
            cout<<"1. Modifica nume"<<endl;
            cout<<"2. Modifica pret"<<endl;
            cout<<"3. Modifica stoc"<<endl;
            cout<<"4. Modifica categorie"<<endl;
            while(x<1||x>4)cin>>x;
            system("cls");
            switch(x) {
                case 1: {
                    string nume;
                    cout<<"Introdu noul nume al produsului: ";
                    getline(cin>>ws, nume);
                    produse[r].setName(nume);
                    salveaza_produse();
                    incarca_produse();
                    cout<<"Numele produsului a fost modificat."<<endl;
                    meniu(c);

                    break;
                }
                case 2: {
                    int pret = -1;
                    cout<<"Introdu noul pret al produsului: ";
                    while(pret<0) cin>>pret;
                    produse[r].setPret(pret);
                    salveaza_produse();
                    incarca_produse();
                    system("cls");
                    cout<<"Pretul produsului a fost modificat."<<endl;
                    meniu(c);

                    break;
                }
                case 3: {

                    system("cls");
                    int stoc = -1;
                    cout<<"Introdu noul stoc al produsului: ";
                    while(stoc<0)cin>>stoc;
                    produse[r].setStoc(stoc);
                    salveaza_produse();
                    incarca_produse();
                    system("cls");
                    cout<<"Stocul produsului a fost modificat."<<endl;
                    meniu(c);
                    break;
                }
                case 4: {
                    int ctg = -1;
                    system("cls");
                    for(int i = 0; i<totalCategori; i++) cout<<i<<". "<<categories[i]<<endl;
                    cout<<"Introdu noua categorie al produsului: ";
                    while(ctg < 0 || ctg >= totalCategori) cin>>ctg;
                    produse[r].setCategorie(ctg);
                    salveaza_produse();
                    incarca_produse();
                    system("cls");
                    cout<<"Categoria produsului a fost modificata."<<endl;
                    meniu(c);

                    break;
                }
            }
            break;

        }
        case 9: {
            system("cls");
            string nameee;
            foreach(it, conturi) {
                int ind = 1;
                ifstream file;
                string dir1 = "conturi/" + it->getName() + "/comenzi.txt";
                const char* dir = dir1.c_str();
                file.open(dir);
                cout<<"___________________ "<<"Comenzile lui "<<it->getName()<<"___________________"<<endl;
                cout<<"= = = = = = = = = = = = Comanda #1 = = = = = = = = = = = ="<<endl;
                while(getline(file>>ws, nameee)) {
                    int pret, buc;
                    if(nameee == "œ") {
                        ind++;
                        if(!getline(file>>ws, nameee)) break;
                        
                        cout<<"= = = = = = = = = = = = Comanda #"<<ind<<" = = = = = = = = = = = ="<<endl;
                    }
                    file>>pret>>buc;

                    cout<<"Nume produs:\t"<< nameee <<endl;
                    cout<<"Pret: \t\t"<<pret<<" RON"<<endl;
                    cout<<"Bucati: \t"<<buc<<endl;
                    cout<<"Total: \t\t"<<pret*buc<<" RON"<<endl<<endl;
                }
                cout<<"________________________________________________________"<<endl;
                file.close();
            }
            meniu(c);
        }
        case 10: {
            exit(1);
            break;
        }
        case 20: {
            system("cls");
            c.setAdmin(!c.getAdmin());
            saveAccounts();
            meniu(c);
            break;
        }
    }
}
void meniuUser(Cont& c) {
    cout<<"Hello, "<<c.getName()<<endl;
    cout<<"1. Vezi toate produse"<<endl;
    cout<<"2. Cauta produs"<<endl;
    cout<<"3. Vezi cos de cumparaturi ("<<calculeaza_cos(c)<<")"<<endl;
    cout<<"4. Vezi comenzile tale"<<endl;
    cout<<"5. Exit"<<endl;
    int option = 0;
    while((option < 1 || option > 5) && option != 20) cin>>option;
    switch(option) {
        case 1: {
            if(produse.size() == 0)  {
                system("cls");
                cout<<"Nu exista produse in stoc."<<endl;
                meniu(c);
            }
            system("cls");
            foreach(it, produse) {
                cout<<*it;
            }
            meniu(c);
            break;
        }

        case 2: {
            system("cls");
            cout<<"1. Cautare dupa nume"<<endl;
            cout<<"2. Cautare dupa interval de pret"<<endl;
            cout<<"3. Cautare dupa interval si nume"<<endl;
            cout<<"4. Cautare dupa categorie"<<endl;
            int option = 0;
            while(option < 1 || option > 4) cin>>option;
            cautare(option, c);
            break;
        }
        case 3: {
            system("cls");
            int count = 0;
            cout<<"------------- COS DE CUMPARATURI ------------"<<endl;
            for(auto it : c.cos) {
                cout<<"_____________________________________________"<<endl;
                auto prod = find(produse.begin(), produse.end(), it.first);
                cout<<"Nume produs: \t\t"<<prod->getName()<<endl;
                cout<<"Pret/buc.: \t\t"<<prod->getPret()<<endl;
                cout<<"Nr. buc.: \t\t"<<it.second<<endl;
                cout<<"Total: \t\t\t"<<it.second * prod->getPret()<<" RON"<<endl;
                cout<<endl;
                count++;
            }
            if(count != 0) {
                cout<<"Comanda are o valoare totala de: "<<calculeaza_cos(c)<<" RON";
                cout<<endl<<"---------------------------------------------"<<endl;
                cout<<"1. Stergere produs din cos"<<endl;
                cout<<"2. Plasare comanda"<<endl;
                cout<<"3. Meniu principal"<<endl;
                int select = 0;
                while(select < 1 || select > 3) cin>>select;
                if(select == 3) system("cls"), meniu(c);
                cart_model(select, c);
            }
            else {
                cout<<"Cosul este gol.";
                cout<<endl<<"---------------------------------------------"<<endl;
                meniu(c);
            }
            break;
        }
        case 4: {
            system("cls");
            if(c.comenzi.size() == 0) cout<<"Nu ai nicio comanda plasata."<<endl, meniu(c);
            int index = 1;

            for(auto cmd : c.comenzi) {
                cout<<"___________________ COMANDA "<<index<<" _______________"<<endl;
                cout<<cmd;
                cout<<"\t\t\t Total de plata: "<<cmd.getTotal()<<" RON"<<endl;
                cout<<"_____________________________________________"<<endl<<endl;
                index++;
            }
            meniu(c);
            break;
        }
        case 5: {
            exit(1);
            break;
        }
        case 20: {
            system("cls");
            c.setAdmin(!c.getAdmin());
            saveAccounts();
            meniu(c);
            break;
        }
    }
}
void meniu(Cont& c) {
    if(c.getAdmin()) meniuAdmin(c);
    else meniuUser(c);
}
void cautare(int option, Cont& c)
{
    system("cls");

    auto produs_singular = produse.begin();
    int count = 0;
    switch(option) {
        case 1: {
            string nume;
            cout<<"Insereaza numele produsului: ";
            getline(cin>>ws, nume);
            system("cls");
            foreach(it, produse) {
                if(it->getName().find(nume) != string::npos) {
                    cout<<*it;
                    produs_singular = it;
                    count++;
                }
            }
            if(count == 0)
                cout<<"Niciun produs nu a fost gasit."<<endl;
            if(count == 1) {
                cout<<"Doresti sa adaugi acest produs in cos?"<<endl<<"1. Da"<<endl<<"2. Nu"<<endl;
                int chose = 0;
                while(chose != 1 && chose != 2) cin>>chose;
                switch(chose) {
                    case 1: {
                        cout<<endl<<"Cate doresti sa cumperi?: ";
                        int numar;
                        cin>>numar;
                        if(numar > produs_singular->getStoc()) system("cls"), cout<<"Nu exista atat stoc."<<endl, meniu(c);
                        if(numar+c.get_cart_item(*produs_singular) > produs_singular->getStoc()) system("cls"), cout<<"Nu exista atat stoc."<<endl, meniu(c);
                        else {
                            c.add_item(*produs_singular, numar);
                            system("cls");
                            cout<<"Produsul a fost adaugat cu succes in cos."<<endl;
                            meniu(c);
                        }
                    }
                    default: {
                        system("cls");
                    }
                }
            }
            meniu(c);
            break;
        }
        case 2: {
            int min, max;
            cout<<"Insereaza pretul minim: ";
            cin>>min;
            cout<<"Insereaza pretul maxim: ";
            cin>>max;
            system("cls");
            foreach(it, produse) {
                if(it->getPret()>= min && it->getPret()<=max) {
                    cout<<*it;
                    produs_singular = it;
                    count++;
                }
            }
            if(count == 0)
                cout<<"Niciun produs nu a fost gasit."<<endl;
            if(count == 1) {
                cout<<"Doresti sa adaugi acest produs in cos?"<<endl<<"1. Da"<<endl<<"2. Nu"<<endl;
                int chose = 0;
                while(chose != 1 && chose != 2) cin>>chose;
                switch(chose) {
                    case 1: {
                        cout<<endl<<"Cate doresti sa cumperi?: ";
                        int numar;
                        cin>>numar;
                        if(numar > produs_singular->getStoc()) system("cls"), cout<<"Nu exista atat stoc."<<endl, meniu(c);
                        if(numar+c.get_cart_item(*produs_singular) > produs_singular->getStoc()) system("cls"), cout<<"Nu exista atat stoc."<<endl, meniu(c);
                        else {
                            c.add_item(*produs_singular, numar);
                            system("cls");
                            cout<<"Produsul a fost adaugat cu succes in cos."<<endl;
                            meniu(c);
                        }
                    }
                    default: {
                        system("cls");
                    }
                }
            }
            meniu(c);
            break;
        }
        case 3: {
            string nume;
            cout<<"Insereaza numele produsului: ";
            getline(cin>>ws, nume);
            int min, max;
            cout<<"Insereaza pretul minim: ";
            cin>>min;
            cout<<"Insereaza pretul maxim: ";
            cin>>max;
            system("cls");
            foreach(it, produse) {
                if(it->getPret()>= min && it->getPret()<=max && it->getName().find(nume) != string::npos) {
                    cout<<*it;
                    produs_singular = it;
                    count++;
                }
            }
            if(count == 0)
                cout<<"Niciun produs nu a fost gasit."<<endl;
            if(count == 1) {
                cout<<"Doresti sa adaugi acest produs in cos?"<<endl<<"1. Da"<<endl<<"2. Nu"<<endl;
                int chose = 0;
                while(chose != 1 && chose != 2) cin>>chose;
                switch(chose) {
                    case 1: {
                        cout<<endl<<"Cate doresti sa cumperi?: ";
                        int numar;
                        cin>>numar;
                        if(numar > produs_singular->getStoc()) system("cls"), cout<<"Nu exista atat stoc."<<endl, meniu(c);
                        if(numar+c.get_cart_item(*produs_singular) > produs_singular->getStoc()) system("cls"), cout<<"Nu exista atat stoc."<<endl, meniu(c);
                        else {
                            c.add_item(*produs_singular, numar);
                            system("cls");
                            cout<<"Produsul a fost adaugat cu succes in cos."<<endl;
                            meniu(c);
                        }
                    }
                    default: {
                        system("cls");
                    }
                }
            }
            meniu(c);
            break;
        }
        case 4: {
            int cat=-1;
            cout<<endl<<"Insereaza categoria:"<<endl;
            for(int i = 0; i<totalCategori; i++) {
                cout<<i<<". "<<categories[i]<<endl;
            }
            while(cat < 0 || cat >= totalCategori) cin >>cat;
            system("cls");
            foreach(it, produse) {
                if(it->getCateg() == cat) {
                    cout<<*it;
                    produs_singular = it;
                    count++;
                }
            }
            if(count == 0)
                cout<<"Niciun produs nu a fost gasit."<<endl;
            if(count == 1) {
                cout<<"Doresti sa adaugi acest produs in cos?"<<endl<<"1. Da"<<endl<<"2. Nu"<<endl;
                int chose = 0;
                while(chose != 1 && chose != 2) cin>>chose;
                switch(chose) {
                    case 1: {
                        cout<<endl<<"Cate doresti sa cumperi?: ";
                        int numar;
                        cin>>numar;
                        if(numar > produs_singular->getStoc()) system("cls"), cout<<"Nu exista atat stoc."<<endl, meniu(c);
                        if(numar+c.get_cart_item(*produs_singular) > produs_singular->getStoc()) system("cls"), cout<<"Nu exista atat stoc."<<endl, meniu(c);
                        else {
                            c.add_item(*produs_singular, numar);
                            system("cls");
                            cout<<"Produsul a fost adaugat cu succes in cos."<<endl;
                            meniu(c);
                        }
                    }
                    default: {
                        system("cls");
                    }
                }
            }
            meniu(c);
            break;
        }
    }
}

#endif // MENUUI_H_INCLUDED
