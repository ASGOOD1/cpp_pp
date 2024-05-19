#ifndef CATEG_H_INCLUDED
#define CATEG_H_INCLUDED

string categories[50];
int totalCategori = 0;
void incarca_categorii() {
    ifstream file;
    string cat;
    file.open("categorii.txt");
    while(getline(file>>ws, cat)){
        categories[totalCategori] = cat;
        totalCategori++;
    }
    file.close();
}

void salveaza_categorii() {
    ofstream file;
    file.open("categorii.txt");
    for(int i = 0; i<totalCategori; i++) file<<categories[i]<<endl;
    file.close();
}




#endif