#include "includes.h"

using namespace std;

#include "products.h"
#include "categories.h"
#include "orders.h"
#include "accounts.h"
#include "menuUI.h"



int main()
{
    incarca_categorii();
    loadAccounts();
    incarca_produse();
    require_login();
    return 0;
}
