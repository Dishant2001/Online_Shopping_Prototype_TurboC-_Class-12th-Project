//Online Shopping Prototype using File Stream

#include<fstream.h>
#include<iomanip.h>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<string.h>
#include<dos.h>  // for delay() function
int num;


class member        //definition of class MEMBER
{int phno;
 char name[20];
 char pass[20];
 char address[50];
 public:
 void get()
 {
   cout<<"Enter user name: ";
   gets(name);
   cout<<"Enter phone number: ";
   cin>>phno;
   cout<<"Enter your password: ";
   gets(pass);
   cout<<"Enter your address: ";
   gets(address);
  }
  int retphno()
  { return phno;}
  char*retname()
  { return name;}
  char*retpass()
  { return pass;}
  char*retad()
  { return address;}
};


class product       //definition of class PRODUCT
{ int pno;
  char pname[20];
  char category[20];
  float cost;
  public:
  void get()
  { cout<<"Product No.:";cin>>pno;
    cout<<"Product name:";
    gets(pname);
    cout<<"Cost:";
    cin>>cost;
    cout<<"Category:";
    gets(category);
  }
  void put()
  { cout<<"Product No.:"<<pno<<" ";
    cout<<"Product Name:"<<pname<<"  ";
    cout<<"Rs."<<cost<<"\t";
  }
  char*retcat()
  { return category;}
  char*retname()
  { return pname;}
  int retpno()
  { return pno;}
  float retprice()
  {return cost;}
};
product p; member m;


class cart        //definition of class CART
{ int pno;
  char pname[20];
  char category[20];
  float cost;
  int phno;
 char name[20];
 char address[50];
 public:
 void val()
 { pno=p.retpno();
   strcpy(pname,p.retname());
   strcpy(category,p.retcat());
   phno=m.retphno();
   strcpy(name,m.retname());
   strcpy(address,m.retad());
   cost=p.retprice();
 }
 void display()
 { cout<<"Product No.:"<<pno<<endl;
   cout<<"Product Name:"<<pname<<endl;
   cout<<"Price:"<<cost<<endl;
   cout<<"Customer Name:"<<name<<endl;
   cout<<"Address:"<<address<<endl;
 }
 float retprice()
 { return cost;}
 int retpno()
 { return pno;}
};
cart c;


void main()
{
  clrscr();
  int op,ph=-1,check=0,pno;ifstream fin;fstream mem,shopcart;ofstream temp;char pass[20],user[20],un[20],ad[20];
  int flag=1;

  while(op!=5)
  {
    cout<<setw(50)<<"AMAZON SHOPPPING"<<endl<<endl;
    cout<<"1. Sign Up"<<endl;
    cout<<"2. Log In"<<endl;
    cout<<"3. Shop"<<endl;                          //MENU
    cout<<"4. Cart"<<endl;
    cout<<"5. Exit"<<endl<<endl;
    cout<<"6. Administrator Login"<<endl<<endl;
    cout<<"Enter choice:";
    cin>>op;
    switch(op)
    {
      case 1:{ clrscr();
	       cout<<"SIGN UP"<<endl; //signing up
	       mem.open("member.dat",ios::binary|ios::end|ios::in|ios::out|ios::app);
	       m.get();
	       mem.write((char*)&m,sizeof(member));
	       mem.close();
	       cout<<"Account created"<<endl;
	       cout<<"Press Enter to go to Menu"<<endl;
	       mem.close();
	       getch();
	       clrscr();
	       break;
	     }
      case 2:{ clrscr();
	       int t=0;
	       cout<<"LOGIN"<<endl;           //logging up
	       cout<<"Enter Username:";
	       gets(user);
	       cout<<"Enter Password:";
	       gets(pass);
	       mem.open("member.dat",ios::binary|ios::in|ios::out);
	       while(!mem.eof())
	       { mem.read((char*)&m,sizeof(member));
		 if(strcmp(user,m.retname())==0&&strcmpi(pass,m.retpass())==0)
		 { ph=m.retphno();strcpy(un,m.retname());strcpy(ad,m.retad());
		   cout<<"Login Successful"<<endl;t=1;break;
		 }//obtaining details of user for manipulation of cart
	       }
	       if(t==0)
	       { cout<<"Invalid Entries"<<endl;}
	       cout<<"Press Enter to go to Menu";
	       getch();clrscr();
	       break;
	     }
      case 3:{ clrscr();
	       if(ph!=-1)//checking whether user has logged in or not
	      { fin.open("product.dat",ios::binary);
	       while(!fin.eof())
	       { fin.read((char*)&p,sizeof(product));
		 p.put();
	       } fin.close();
	       cout<<endl<<endl;
	       cout<<"1.Buy"<<endl;
	       cout<<"2.Go to Menu"<<endl;
	       cout<<"Enter your choice\n ";
	       int choice;
	       cin>>choice;
	       switch(choice)
	       { case 1:{ clrscr();
			  cout<<"Enter Product No.:";
			  cin>>pno;
			  fin.open("product.dat",ios::binary);
			  while(!fin.eof())
			  {
			    fin.read((char*)&p,sizeof(product));
			    if(p.retpno()==pno)
			   {flag=0;p.put();break;}
			  }
			  if(flag==1)
			  { cout<<"NO such product"; getch();clrscr();break;}
			  cout<<endl;
			  int qty;
			  cout<<"Enter Quantity:";
			  cin>>qty;
			  cout<<"Total Amount:"<<qty*p.retprice();
			  cout<<endl;
			  cout<<"1.Buy Now"<<endl;
			  cout<<"2.Add to Cart"<<endl;
			  cout<<"3.Go to Menu"<<endl;
			  int choice2;
			  cin>>choice2;
			  switch(choice2)
			  { case 1:{ cout<<"Your order will be delivered. Thankyou for ordering"<<endl;
				      getch();clrscr(); break;}
			    case 2:{ clrscr();check=1;//indicating product is added to cart
				     shopcart.open("Cart.dat",ios::binary|ios::in|ios::out|ios::app);
				     c.val();
				     shopcart.write((char*)&c,sizeof(cart));
				     shopcart.close();
				     break;
				   }
			    case 3:clrscr();break;
			    default:{cout<<"Invalid Choice"; break;}
			  }break;
			 }
	       case 2:{clrscr();break;}
	       default:{cout<<"Invalid Choice";clrscr();break;}
	       }break;
	      }
	      else // when ph=-1
	      { cout<<"LOG IN!!";getch();break;}
	     }

      case 4:{ clrscr();
	       if(check==1) // there is any product in the cart or not
	       {shopcart.open("Cart.dat",ios::binary|ios::in|ios::out);
	       while(!shopcart.eof())
	       { shopcart.read((char*)&c,sizeof(cart));
		 if(c.retpno()==pno)
		 { c.display();}
	       }shopcart.close();
	       cout<<"Enter Quantity:";
	       int qty;
	       cin>>qty;
	       cout<<"Total Amount:"<<qty*c.retprice()<<endl;
	       cout<<"1.Buy"<<endl;
	       cout<<"2.Delete"<<endl;
	       int choice3;
	       cin>>choice3;
	       switch(choice3)
	       { case 1:{clrscr();
			 cout<<"your order has been placed";check=0;getch();break;
			}
		 case 2:{clrscr();
			 shopcart.open("Cart.dat",ios::binary|ios::in|ios::out);
			 temp.open("Temp.dat",ios::binary);
			 while(!shopcart.eof())
			 { shopcart.read((char*)&c,sizeof(cart));
			   if(c.retpno()!=pno)
			   { temp.write((char*)&c,sizeof(cart));
			   }
			 }
			 shopcart.close();temp.close();
			 remove("Cart.dat");             //deletion of file CART
			 rename("Temp.dat","Cart.dat");
			 clrscr();
			 break;
			}
		 default:{cout<<"Invalid choice";
			  clrscr();
			  break;
			 }
	       }
	      }
	      else{ cout<<"No product in the cart"; getch();clrscr();break;}
	      clrscr();break;
	     }
      case 5:exit(0);
    }
    fin.close();mem.close();
    if(op==6)
    { char p[10]; int op2,n;ofstream fout;product q;
      cout<<"Enter Password:";
      gets(p);
      if(strcmp(p,"amazon")==0)
      { clrscr();
	cout<<"Welcome Admin!!"<<endl;
	cout<<"1. Enter Products"<<endl;
	cout<<"2. Delete Products"<<endl;
	cout<<"3. Go to Menu"<<endl;
	cout<<"Enter option:";
	cin>>op2;
	switch(op2)
	{
	   case 1:{ clrscr();
		    fout.open("product.dat",ios::binary|ios::app);
		    cout<<"Enter no. of products to be entered:";
		    cin>>n;
		    cout<<"Enter products"<<endl;
		    for(int i=0;i<n;++i)
		    { q.get();
		      fout.write((char*)&q,sizeof(product));
		      cout<<endl;
		    }
		    cout<<"Added"; fout.close();
		    getch(); clrscr();break;
		  }
	   case 2:{ clrscr();
		    temp.open("Temp2.dat",ios::binary);
		    fin.open("product.dat",ios::binary);
		    int prono;
		    cout<<"Enter product number to be deleted:";
		    cin>>prono;
		    while(!fin.eof())
		    { fin.read((char*)&q,sizeof(product));
		      if(prono!=q.retpno())
		      { temp.write((char*)&q,sizeof(product));}
		    }
		    temp.close();fin.close();
		    remove("product.dat");
		    rename("Temp2.dat","product.dat");
		    cout<<"Deleted";
		    getch();clrscr();break;
		  }
	 case 3:{ clrscr();break;}
	 default:{ cout<<"Invalid choice";getch();clrscr();break;}
       }
      }
    else
     { clrscr();
      for(int i=0;i<5;++i)
       { cout<<"Abort!!!";
	 delay(500);
	 clrscr();
	 delay(500);
       }
      exit(0);
     }
    }
  }
  getch();
}


