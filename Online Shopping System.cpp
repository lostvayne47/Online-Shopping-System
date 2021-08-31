#include<iostream>
#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<fstream>
using namespace std;
class product
{
char colour[10],type[10];
char size,gender;
    float price;
int in,itemno,sp;
public:
void order();
void show();
void delivery();
void modify();
void remove1();
void accept();
void alot();
int getitem()
{
return itemno;
}
static int bag,n,b;
}p1,d;
int product::bag=0;
int product::n=0;
int product::b=0;

void product::accept() //to be received from user.
{
cout << "item no.";
cin >>itemno;
cout << "\nEnter category (Jeans/Shirt/Kurta)";
cin >> type;
cout << "\nEnter gender (M/F)";
cin >> gender;
cout << "\nEnter colour (Purple/Black/White/Blue/Green/Red)";
cin >> colour;
cout << "\nEnter size (S/M/L)";
cin >> size;
}
void product::order()
{
if (size == 'S' || size == 's')
{
sp = 100;
b=b+sp;
bag++;
}
else
{
if (size == 'M' || size == 'm')
{
sp = 200;
b=b+sp;
bag++;
}
else
{
if (size == 'L' || size == 'l')
{
sp = 300;
b=b+sp;
bag++;
}
else
{
cout << "\nSorry that size is not available";
}
}
}
return;
}
void product::show()
{
cout <<"\nitem no    Category    Gender    Colour    Size     price\n";
cout<<itemno<<"           "<<type<<"       "<<gender<<"        "<<colour<<"       "<<size<<"      "<<sp;
return;
}
void product::remove1()
{
        int di; //deleteitem
int fl = 0;
char confirm;
cout << "\nBag items:";
ifstream f("D:\\shop.dat", ios::in | ios::binary);
ofstream file("D:\\temp.dat", ios::out | ios::binary);
cout << "\nEnter item no. of the bag item you want to delete";
cin>>di;
while (!f.eof())
{
while(f.read((char*)&p1, sizeof(p1)))
{
if (p1.getitem()==di)
{
bag--;
b=b-sp;
break;
}
else
{
 file.write((char*)&p1,sizeof(p1));
};
}
}
f.close();
file.close();
remove("D:\\shop.dat");
    rename("D:\\temp.dat", "D:\\shop.dat");
f.open("D:\\shop.dat", ios::in|ios::binary);
cout << "Items in bag:";
while (!f.eof())
{
f.read((char*)&p1, sizeof(p1));
if (f.eof())
break;
p1.show();
}
f.close();
}
void product::alot()
{
b=b-sp;
bag--;
}

void product::modify() //to modify items in bag
{
cout <<"\nitem no    Category    Gender    Colour    Size     price\n";
cout<<itemno<<"           "<<type<<"       "<<gender<<"        "<<colour<<"        "<<size<<"     "<<sp;
char gn= ' ', ca[10] = " ", si=' ', co[10] = " ";
cout << "\nUpdated gender: (Enter '.' to retain old one)"; //retain old one in the sense don't change that
cin >> gn;
cin.ignore();
cout << "Updated category: (Enter '.' to retain old one)";
cin.getline(ca,10);
cout<<"Updated size: (Enter '.' to retain old one)";
cin>>si;
cin.ignore();
cout << "Updated colour: (Enter '.' to retain old one)";
cin.getline(co,10);
if (gn == '.')
gn = gender;
else
   gender=gn;
if (strcmp(ca, ".") != 0)
strcpy(type, ca);
if (si=='.')
si=size;
else
size=si;
if (strcmp(co, ".") != 0)
strcpy(colour, co);
}
class address
{
private:
int pin;
char city[50];
char ad[100];
int price;
public:
void ead()
{ cout << "\nEnter shipping details";
cout << "\nPincode:";
cin >> pin;
cin.ignore();
cout << "\nCity:";
cin.getline(city, 50);
cout << "\nAddress:";
cin.getline(ad, 50);
}
void dad()
{
cout << "\nORDER WILL BE SHIPPED TO " << ad << "\nCITY " << city << "\nPINCODE " << pin;
}

};
void product::delivery()
{
address a;
a.ead();
//price calculation:
int tax;
price=100;
cout<<"------------------------------------------------------------------------";
cout << "\nThe final price is:";
price=price+b;
cout << "\nItem total Cost               Rs" << price << "/-";
tax = price * 0.10;
cout << "\nTax                           Rs" << tax << "/-";
cout << "\nDelivery charge               Rs" << "50/-";
price = price + tax + 50;
cout << "\nSUB TOTAL                     Rs" << price << "/-";
cout << "\n";
cout << "\n\nOrder confirmed."<<bag<<" items will be delivered to you soon.";
cout<<"\n----------------------------------------------------------------------";
//bag items will be displayed here and after that the address
a.dad();
return;
}

int main()
{        char ch1;
int ch;
cout << "----------Welcome to ADOS!----------";
do{
    cout << "\nMenu:";
cout << "\n1.Add items to bag" << "\n2.Modify items in bag" << "\n3.Delete items from bag" << "\n4.Display items from bag" << "\n5.Confirm and place order"<<"\n6.Exit and clear bag\n";
cout<<"\nEnter choice ";
cin >> ch;
cout<<"\n**************************************************\n";
switch(ch)
{
case 1: //insertion: getting the items from user
{
char c;
ofstream fout;
fout.open("d:\\shop.dat", ios::app | ios::binary);
do
{   p1.accept();
p1.order();
fout.write((char*)&p1, sizeof(p1));
cout << "\nContinue adding items to bag?"; //takes all orders at once.
cin >> c;
} while (c == 'y' ||c== 'Y'); //when user enters no they can't order again. they can only modify and delete.
fout.close();
}
break;
case 2:
{   fstream fio("d:\\shop.dat", ios::in | ios::out | ios::binary);
int m, flag = 0;
long pos, pos1;
cout << "\nEnter item no. you wish to modify";
cin >> m;
while (fio.read((char*)&p1, sizeof(p1)))
{ pos = fio.tellg();
pos = pos - sizeof(p1);
if (p1.getitem() == m)
{ p1.alot();
    p1.modify();
p1.order();
fio.seekg(pos);
fio.write((char*)&p1,sizeof(p1));
flag = 1;
fio.close();
break;
}
}
if (flag == 0)
{
cout << "\nThe bag item which you want to modify is not found";
fio.close();
}
fstream fio1("d:\\shop.dat", ios::in | ios::out | ios::binary);
cout<<"\n****************************************************";
cout << "\nBag items after modification";
while (fio1.read((char*)&p1, sizeof(p1)))
{
p1.show();
}
fio1.close();
cout<<"\n****************************************************";
break;
}
case 3: //deletion: removing an item.
{
   p1.remove1();
   break;
}
case 4: //display the bag items here
{
cout << "\n*******Items in your bag*******\n";
ifstream fdisp;
fdisp.open("d:\\shop.dat", ios::in | ios::binary);
while(fdisp.read((char*)&p1,sizeof(p1)))
{
p1.show();
};
fdisp.close();
break;
}
case 5: // delivery part+price calculation
{
d.delivery();
break;
}
case 6:
{
cout<<"\nExiting and clearing bag. Thank you for shopping with us!";
remove("d:\\shop.dat");
            getch();
             break;
}
default:
cout << "Wrong choice";
}
cout << "\nOpen menu?(y/n)";
cin >> ch1;
}while (ch1 == 'Y' || ch1 == 'y');
remove("d:\\shop.dat");
getch();
}
