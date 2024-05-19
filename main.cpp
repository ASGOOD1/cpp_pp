#include "includes.h"

using namespace std;

#include "products.h"
#include "orders.h"
#include "accounts.h"
#include "menuUI.h"



int main()
{
    loadAccounts();
    incarca_produse();
    require_login();
    return 0;
}
