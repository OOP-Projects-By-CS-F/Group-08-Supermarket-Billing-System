#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<fstream>
#include<stdlib.h>
#include<iomanip>

using namespace std;


//Welcome to the source code of FreshMart <Billing System>



/*
OOP Mini Project 2nd Year (3rd Sem) By:
EN20EL301079 Rushat Dubey
EN20CS301346 Richa Trivedi
EN20CS301345 Richa Deshpande
*/




//Let's Begin



//Global Declaration
fstream fp;    //File Object
char Name[50]; //Customer Name 



//Intro Function
void intro() 
{
    cout << "\n\t\t\t\tFresh Mart <Billing System>";

    cout << "\n\n\tCreated By: ";
    cout << "\n\tRushat Dubey";
    cout << "\n\tRicha Trivedi";
    cout << "\n\tRicha Deshpande";
    cout << "\n\n\n\tPlease enter your Name: ";
    gets(Name);
}



class Database
{
    int pcode;
    char name[50];
    float price, qty, dis;
    public:

    //Creating the Product
    void create_product() 
        {
            cout<<"\nEnter The Product Code: ";
            cin>>pcode;
            cout<<"\nEnter The Product Name: ";
            cin>>name;
            cout<<"\nEnter The Product Price: ";
            cin>>price;
            cout<<"\nEnter The Product Discount: ";
            cin>>dis;
        }


    //Showing the Product
    void show_product() 
        {
            cout<<"\n\nProduct Code: "<<pcode;
            cout<<"\nProduct Name: ";
            puts(name);
            cout<<"Product Price: Rs." <<price;
            cout<<"\nProduct Discount: "<<dis<<"%";
        }

    //Showing only Specific details of the Product *Before* Placing Order
    void list_product()
       {
           cout<<"Product Code: "<<pcode;
           cout<<"    Name: ";
           puts(name);
       }
    //Showing only Specific details of the Product *While* Placing Order
    void order_product()
       {
           cout<<"Database - Product Name: ";
           puts(name);
           cout<<"Database - Product Price/Unit: Rs." <<price;
       }

    
    //
    //Returning the Values
    int retpcode() 
        {
            return pcode;
        }

    float retprice() 
        {
            return price;
        }

    int retdis() 
        {
            return dis;
        }

    char * retname() 
        {
            return name;
        }
};
//End of class Database



//Object Declaration of class Database
Database db;

/*Early Declaration of Staff Menu Function
because it is used in class Files*/ 
void staff_menu();



class Files
{
    public:

    //Function to Create a Product
    void write_product() 
    {
      char c1;
        fp.open("store.dat", ios::out | ios::app);
        db.create_product();
        fp.write((char * ) & db, sizeof(Database));
        fp.close();
        cout<<"\n\nCreated Product successfully, Database updated.";
        cout<<"\n\nDo you want to GO BACK to Staff Menu? (Y/N): ";
        cin>>c1;
        if(c1=='y'|| c1=='Y')
          {
             staff_menu();
          }
        else
          {
             cout<<"\n\n\tRedirecting.";
             cout<<"\n\n\tExited, Thankyou.\n";
             exit(2);
          }
       }


    //Function to Display Product List
    void display_all() 
    {
      char c2;
      cout<<"\n\nFetching List from Database.";
      cout<<"\n\n\t\t<Product List>\n\n";
      fp.open("store.dat", ios:: in );
      while (fp.read((char * ) & db, sizeof(Database))) 
      {
        db.show_product();
      }
      fp.close();
      cout<<"\n\nDo you want to GO BACK to Staff Menu? (Y/N): ";
      cin>>c2;
      if(c2=='y'|| c2=='Y')
      {
        staff_menu();
      }
      else
      {
        cout<<"\n\n\tRedirecting.";
        cout<<"\n\n\tExited, Thankyou.\n";
        exit(2);
      }
    }


    //Function to Display a Specific Product
    void display_sp(int n) 
    {
      char c3;
      int flag = 0;
      fp.open("store.dat", ios:: in );
      while (fp.read((char * ) & db, sizeof(Database))) 
      {
        if (db.retpcode() == n) 
        {
            db.show_product();
            flag = 1;
        }
      }
      fp.close();
      if (flag == 0)
      cout << "\n\nProduct Not Found.";
      cout<<"\n\nDo you want to GO BACK to Staff Menu? (Y/N): ";
      cin>>c3;
      if(c3=='y'|| c3=='Y')
      {
        staff_menu();
      }
      else
      {
        cout<<"\n\n\tRedirecting.";
        cout<<"\n\n\tExited, Thankyou.\n";
        exit(2);
      }
    }


    //Function to Modify a Product
    void modify_product() 
    {
      char c4;
      int no, found = 0;
      cout<<"\n\n\tEnter The Product Code: ";
      cin>>no;
      fp.open("store.dat", ios:: in | ios::out);
      while (fp.read((char * ) & db, sizeof(Database)) && found == 0) 
      {
        if (db.retpcode() == no) 
        {
            db.show_product();
            cout<<"\n\n>> Enter The New Details of Product." << endl;
            db.create_product();
            int pos = -1 * sizeof(db);
            fp.seekp(pos, ios::cur);
            fp.write((char * ) & db, sizeof(Database));
            cout<<"\n\nProduct modified, Database updated.";
            found = 1;
        }
      }
      fp.close();
      if (found == 0)
      cout<<"\n\nProduct Not Found.";
      cout<<"\n\nDo you want to GO BACK to Staff Menu? (Y/N): ";
      cin>>c4;
      if(c4=='y'|| c4=='Y')
      {
        staff_menu();
      }
      else
      {
        cout<<"\n\n\tRedirecting.";
        cout<<"\n\n\tExited, Thankyou.\n";
        exit(2);
      }
    }


    //Function to Delete a Product 
    void delete_product() 
    {
      char c5;
      int no;
      cout<<"\n\n\tEnter The Product Code: ";
      cin>>no;
      fp.open("store.dat", ios:: in | ios::out);
      fstream fp2;
      fp2.open("temp.dat", ios::out);
      fp.seekg(0, ios::beg);
      while (fp.read((char * ) & db, sizeof(Database))) 
      {
        if (db.retpcode() != no) 
        {
            fp2.write((char * ) & db, sizeof(Database));
        }
      }
      fp2.close();
      fp.close();
      remove("store.dat");
      rename("temp.dat", "store.dat");
      cout << "\n\nProduct Deleted, Database updated.";
      cout<<"\n\nDo you want to GO BACK to Staff Menu? (Y/N): ";
      cin>>c5;
      if(c5=='y'|| c5=='Y')
      {
        staff_menu();
      }
      else
      {
        cout<<"\n\n\tRedirecting.";
        cout<<"\n\n\tExited, Thankyou.\n";
        exit(2);
      }
    }


    //Function to display List during Placing Order
    void list_disp()
    {
      cout<<"\n\n\t\t<Product List>\n\n";
      fp.open("store.dat", ios:: in );
      while (fp.read((char * ) & db, sizeof(Database))) 
      {
        db.list_product();
      }
      fp.close();
    }

};
//End of class Files         




//Object Declaration of class Files
Files fe;



   //Function to Place Order and Generate Bill
   void place_order() 
   {

     int order_arr[50], quan[50], c = 0;
     float amt, damt, total = 0;
     char ch = 'Y';
     cout<<"\n\n\n\tHi there, this is our <Product List>";
     cout<<"\n\tPress any key to view.";
     getch();
     fe.list_disp();
     cout<<"\n\n\n\t\t<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<";
     cout<<"\n\t\tDear "<<Name<<", now Place your Order :)";
     cout<<"\n\t\t<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<";

     do 
     {
        cout<<"\n\nEnter The Product Code: ";
        cin>>order_arr[c];
        fp.open("store.dat", ios:: in );
        while (fp.read((char * ) & db, sizeof(Database))) 
          {
            if (db.retpcode() == order_arr[c]) 
              {
                db.order_product();
              }
          }
        fp.close();
        cout<<"\n\nEnter Quantity in Number : ";
        cin>>quan[c];
        c++;
        cout<<"\n>>>>> Do You Want To Add more Products ? (Y/N): ";
        cin>>ch;
     } 
     while (ch == 'y' || ch == 'Y');

     cout<<"\n\n\t\t*** Thank You For Placing The Order, "<<Name<<" ***";
     cout<<"\n\n\n\t\tPress any key to see your INVOICE (Bill)";
     getch();

     cout << "\n\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ BILL $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n";
     cout << "\nCode\t Name\t  Quantity \tPrice \tAmount \t    Our Price \n ";

     for (int x = 0; x < c; x++) 
     {
        fp.open("store.dat", ios:: in );
        fp.read((char * ) & db, sizeof(Database));
        while (!fp.eof()) 
        {
            if (db.retpcode() == order_arr[x]) 
            {
                amt = db.retprice() * quan[x];
                damt = amt - (amt * db.retdis() / 100);
                cout << "\n" << order_arr[x] << "\t" << db.retname() <<
                    "\t   " << quan[x] << "\t\t" << db.retprice() << "\t" << amt << "\t\t" << damt;
                total += damt;
            }
            fp.read((char * ) & db, sizeof(Database));
        }

        fp.close();
     }

     cout << "\n\n\t\t\t\t\tTotal Amount = " << total;


     //Applying Discout from Coupon Code
     char check;
     char coup;
     float pay=0;
     cout << "\n\n\tDo you have any Coupon Code? (Y/N): ";
     cin>>check;

     if(check=='y' || check=='Y')
     {
        cout << "\n\tEnter your Coupon Code: ";
        cin>>coup;

        if(coup=='F' || coup=='f')
        {
            pay = total - (total * 5 / 100);
            cout << "\n\n\tCoupon Code 'F' %5 Discount applied successfully ";
            cout << "\n\n\t\t\t\t# Now you just have to Pay: Rs " << pay;
        }

        else if(coup=='T' || coup=='t')
        {
            pay = total - (total * 10 / 100);
            cout << "\n\n\tCoupon Code 'T' %10 Discount applied successfully.";
            cout << "\n\n\t\t\t\t# Now you just have to Pay: Rs " << pay;
        }

        else
        {
            cout << "\n\n\tINVALID Coupon Code.";
            cout << "\n\n\t\t\t\t\t# You have to Pay: Rs " << total;
        }
     }

     else 
     {
        cout << "\n\n\t\t\t\t\t# You have to Pay: Rs " << total;
     }
     getch();

     cout << "\n\n\nThankyou, wait for 5 seconds we have a Surprise for you :)";
     cout << "\nPress any key to view your Surprise.";
     getch();


     //Generating New Coupon Code for next order
     if(total<=5000)
     {
        cout<<"\n\n\n\n\n>>>>Congratulations! you have won a new Coupon: ' F ' ";
        cout<<"\nDon't forget to redeem this Coupon and get extra %5 off on your next order.";
     }

     else if(total>5000)
     {
        cout<<"\n\n\n\n\n>>>>Congratulations! you have won a new Coupon: ' T ' ";
        cout<<"\nDon't forget to redeem this Coupon and get extra %10 off on your next order.";
     }

     cout<<"\n\n\n\t\tThankyou for shopping with us, "<<Name;
     cout<<"\n\t\tVisit Again to FRESH Mart.";
     getch();
    }
    //End of Place Order Function





    //Staff Menu Function
    void staff_menu() 
    {
      char ch2;
      cout << "\n\n\n\n\t\t<<<< Staff Login >>>>";
        cout << "\n\nLogin Successful, Access Granted to "<<Name;
        cout << "\n\n\tPress 1.Create Product";
        cout << "\n\n\tPress 2.Display Product List";
        cout << "\n\n\tPress 3.Search Product";
        cout << "\n\n\tPress 4.Modify Product";
        cout << "\n\n\tPress 5.Delete Product";
        cout << "\n\n\tPress 6.Exit";
        cout << "\n\n\tPlease Enter Your Choice (1-6) ";
        ch2 = getche();
        switch (ch2) 
        {
          case '1':
          fe.write_product();
          break;
          case '2':
          fe.display_all();
          break;
          case '3':
          int num;
          cout << "\n\n\tPlease Enter The Product Code: ";
          cin >> num;
          cout << "\n\tSearching the Product from Database.....";
          fe.display_sp(num);
          break;
          case '4':
          fe.modify_product();
          break;
          case '5':
          fe.delete_product();
          break;
          case '6':
          cout<<"\n\n\tRedirecting.";
          break;
          default:
          cout << "\a";
          staff_menu();
        }
    }
    //End of Staff Menu Function 



//Main Function of the Program
int main() 
{
    char ch;

    intro();

    do 
    {
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nHey "<<Name<<" ,Welcome to Fresh Mart.";
        cout << "\n\n\t>Press 1. Generate Bill";
        cout << "\n\n\t>Press 2. Staff Login";
        cout << "\n\n\t>Press 3. Exit";
        cout << "\n\n\tPlease Select Your Option (1-3) ";
        ch = getche();
        cout << "\n\n\n\n\n\n\n";

        switch (ch) 
        {
        case '1':
            place_order();
            getch();
            break;
        case '2':
            {

                int pass,Pass=3456;

                cout<<"\n\nEnter Password: ";
                cin>>pass;
                
                if(Pass==pass)
                {
                    staff_menu();
                }
                else
                {
                    cout<<"\n ! Wrong Password";
                    cout<<"\n Exiting Code.";
                }   
            }   
        case '3':
            cout<<"\n\n\tExited, Thankyou.\n";
            exit(4);
        default:
            cout << "\a";
        }
    } while (ch != '3');
}





