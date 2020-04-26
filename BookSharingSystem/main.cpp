#include<bits/stdc++.h>
#include<conio.h>
#include<fstream>
#include<iomanip>
#include<string.h>
#include<stdio.h>
#include<iostream>
using namespace std;
class admin;
class user
{
protected:
    string fname,lname,name,password,email,NID,city;
    int yourbook;
public:
    void putname();
    void new_user();
    int sign_in();
    void update();
    void yourbooks();
    void operator++();
    void mybooklist();
    void delete_();
    friend istream & operator>>(istream &,user &);
    friend void copy__(user&,admin&);
    ~user() {}
};

class book:public user
{
protected:
    string bname,aname,print;
public:
    void new_book();
    void searc_h();
    virtual void delete_() {};
    ~book(){}
};

class sell:virtual public book
{
protected:
    int price;
public:
    ~sell(){}
    void sell_book();
    void delete_();
};

class exchange:virtual public book
{
protected:
    string exbname,exaname,exprint;
public:
    ~exchange(){}
    void exchange_book();
    void eunique_book();
    void delete_();
};

class buy:virtual public book
{
protected:
    string bbname,baname;
public:
    ~buy(){};
    void unique_book();
    void find_user();
};

class admin:public sell,public exchange,public buy
{
private:
    string ID,pass;
public:
    admin()
    {
        ID="051198";
        pass="cloud";
    }
    ~admin(){}
    void admin_login();
    void user_display_all();
    void book_display_all();
    void admin_display();
    void display();
    void delete_();
    friend void copy__(user&,admin&);
};

admin a,*aptr;
user u,*uptr;
book *bptr,b;
sell s;
exchange e;
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

/*Register a new user*/
istream & operator>>(istream &in,user &p)
{
    p.name="";
    cout<<"\n\n\n";
    cout<<"\t\t\tEnter your first name:";
    in>>p.fname;
    cout<<"\t\t\tEnter your last name:";
    in>>p.lname;
    p.name=p.fname+" "+p.lname;
    cout<<"\t\t\tEnter your NID number:";
    in>>p.NID;
    cout<<"\t\t\tEnter you e-mail:";
    in>>p.email;
    cout<<"\t\t\tEnter you city:";
    in>>p.city;
    cout<<"\t\t\tEnter your password:";
    in>>p.password;
    return in;
}
void user :: new_user()
{
    system("cls");
    cout<<"\n\t\t******************************************"<<endl;
    cout<<"\t\t\t    ### Sign Up ###"<<endl;
    cout<<"\t\t******************************************"<<endl;
    fstream fu;
    fu.open("user.csv",ios :: out | ios :: app);
    cin>>u;
    fu<<NID<<" ,";
    fu<<password<<" ,";
    fu<<name<<" ,";
    fu<<email<<" ,";
    fu<<city<<" ,";
    fu<<"\n";
    copy__(u,a);
    cout<<"\n\t\tYou have registered successfully!!"<<endl;
    fu.close();
    return;
}

void user :: putname()
{
    system("cls");
    cout<<"\n\n\t\t\t   Welcome "<<name<<endl;
    yourbook=0;
    yourbooks();
    if(yourbook==1)
    {
        cout<<"\t\t\tYou have contributed "<<yourbook<<" book."<<endl;
    }
    else
    {
        cout<<"\t\t\tYou have contributed "<<yourbook<<" books."<<endl;
    }

}
void user :: operator++()
{
    yourbook+=1;
}

/*Count books*/
void user::yourbooks()
{
    fstream fin;
    fin.open("sell.csv", ios :: in);
    string temp,line,word;
    while(fin>>temp)
    {
        getline(fin,line);
        if(NID==temp)
        {
            yourbook++;
        }

    }
    fin.close();
    fin.open("exchange.csv", ios :: in);
    while(fin>>temp)
    {
        getline(fin,line);
        if(NID==temp)
        {
            yourbook++;
        }
    }
    fin.close();
}
void copy__(user& u,admin& a)
{
    a.name=u.name;
    a.NID=u.NID;
    a.password=u.password;
    a.email=u.email;
    a.city=u.city;
    a.yourbook=u.yourbook;
}
/*end*/

/*Logging in the system*/
int user :: sign_in()
{
    system("cls");
    cout<<"\n\t\t******************************************"<<endl;
    cout<<"\t\t\t    ### Sign In ###"<<endl;
    cout<<"\t\t******************************************"<<endl;
    getchar();
    int count=3;
    while(count--)
    {
        cout<<"\n\n\n\t\tEnter your NID:";
        getline(cin,NID);
        cout<<"\t\tEnter your password:";
        char ch;
        password="";
        while((ch=_getch())!=13)
        {
            if(ch==8)
            {
                if(password.length()>0)
                {
                    printf("\b \b");
                    password.erase(password.length()-1);
                }
            }
            else
            {
                password.push_back(ch);
                cout<<'*';
            }

        }
        fstream fin;
        fin.open("user.csv", ios :: in);
        string temp,line,word;
        vector<string>row;
        while(fin>>temp)
        {
            row.clear();
            getline(fin,line);
            stringstream ss(line);
            int i=0;
            while(getline(ss,word,','))
            {
                row.push_back(word);
                row[i].erase(row[i].length()-1);
                i++;
            }
            if(NID==temp && password==row[1])
            {
                name=row[2];
                email=row[3];
                city=row[4];
                yourbook=0;
                copy__(u,a);
                fin.close();
                return -1;
            }

        }
        cout<<"\n\t\tNID or password does not match."<<endl;
        printf("\t\tYou have %d tries left.\n",count);
        fin.close();

    }
    return -2;

}
/*end*/

void user::mybooklist()
{
    system("cls");
    cout<<"\n\t\t******************************************"<<endl;
    cout<<"\t\t\t    ### MY BOOKS ###"<<endl;
    cout<<"\t\t******************************************"<<endl;
    fstream fout,fin;
    fout.open("sell.csv",ios::in);
    string tem,lin,wor;
    int k=0;
    vector<string>boo;
    cout<<"\n\n\t**Books in selling list**"<<endl;
    while(fout>>tem)
    {
        boo.clear();
        getline(fout,lin);
        stringstream ss(lin);
        int i=0;
        while(getline(ss,wor,','))
        {
            wor.erase(wor.length()-1);
            boo.push_back(wor);
            i++;
        }
        if(tem==NID)
        {
            cout<<"\t";
            cout<<boo[1]<<" by "<<boo[2]<<" "<<"\n";
            k++;
        }

    }
    fout.close();
    if(k==0)
        cout<<"\t***You have no books in this section***\n";
    cout<<"\n";
    fin.open("exchange.csv");
    k=0;
    cout<<"\t**Books in exchange list**"<<endl;
    while(fin>>tem)
    {
        boo.clear();
        getline(fin,lin);
        stringstream s(lin);
        int i=0;
        while(getline(s,wor,','))
        {
            wor.erase(wor.length()-1);
            boo.push_back(wor);
            i++;
        }
        if(tem==NID)
        {
            cout<<"\t";
            cout<<boo[1]<<" by "<<boo[2]<<" "<<"\n";
            k=1;
        }

    }
    fin.close();
    if(k==0)
        cout<<"\t***You have no books in this section***\n";
    cout<<"\n\tPress 0 to return to main menu\n";
    int e;
    cin>>e;
    if(e==0)
        return;//a.display();
}
/*New book to sell*/
void book :: new_book()
{
    system("cls");
    cout<<"\n\t\t******************************************"<<endl;
    cout<<"\t\t\t  ### Adding a New Book ###"<<endl;
    cout<<"\t\t******************************************"<<endl;
    int c;
    do
    {
        getchar();
        cout<<"\n\n\n";
        cout<<"\t\tEnter the name of the book:";
        getline(cin,bname);
        transform(bname.begin(),bname.end(),bname.begin(), ::tolower);
        cout<<"\t\tEnter the name of the author:";
        getline(cin,aname);
        transform(aname.begin(),aname.end(),aname.begin(), ::tolower);
        cout<<"\t\tIs it paper print or news print?:";
        getline(cin,print);
        transform(print.begin(),print.end(),print.begin(), ::tolower);
        int p;
        cout<<"\t\t01.Sell this book\n\t\t02.Exchange this book\n\t\t";
        cin>>p;
        if(p==1)
            a.sell_book();
        else
            a.exchange_book();
        cout<<"\t\tPress 3 to contribute another book\n\t\tPress 4 to exit\n\t\t";
        cin>>c;
    }
    while(c==3);
    return;
    //a.display();

}
void sell :: sell_book()
{
    cout<<"\t\tEnter Price:";
    cin>>price;
    fstream fs;
    fs.open("sell.csv", ios::out | ios::app);
    fs<<NID<<" ,";
    fs<<bname<<" ,";
    fs<<aname<<" ,";
    fs<<name<<" ,";
    fs<<email<<" ,";
    fs<<price<<" ,";
    fs<<print<<" ,";
    fs<<city<<" ,";
    fs<<"\n";
    fs.close();
    fstream fw,ft;
    fw.open("slist.csv",ios::in);
    string t,l,w;
    vector<string>r;
    int k=0;
    while(getline(fw,t,','))
    {
        r.clear();
        getline(fw,l);
        stringstream s(l);
        getline(s,w,',');
        t.erase(t.length()-1);
        w.erase(w.length()-1);
        if(bname==t && aname==w)
        {
            k=1;
            break;
        }
    }
    fw.close();
    if(k==0)
    {
        ft.open("slist.csv",ios::out|ios::app);
        ft<<bname<<" ,";
        ft<<aname<<" ,";
        ft<<"\n";
        ft.close();
    }
    cout<<"\n\t\t***Your book is up for sell***"<<endl;
}
/*END*/

/*Show all books for buying*/
void buy::unique_book()
{
    system("cls");
    cout<<"\n\t\t******************************************"<<endl;
    cout<<"\t\t\t    ### Buy a BOOK ###"<<endl;
    cout<<"\t\t******************************************"<<endl;
    fstream fin,fout;
    fin.open("slist.csv",ios::in);
    vector<string>row[50];
    string line,word,temp;
    int j=0;
    cout<<"\n\n";
    while(getline(fin,temp,','))
    {
        row[j].clear();
        getline(fin,line);
        stringstream s(line);
        cout<<"\t\t"<<j+1<<". ";
        getline(s,word,',');
        row[j].push_back(temp);
        row[j].push_back(word);
        transform(temp.begin(),temp.end(),temp.begin(), ::toupper);
        transform(word.begin(),word.end(),word.begin(), ::toupper);
        cout<<temp<<"by "<<word<<"\n";
        j++;
    }
    fin.close();
    cout<<"\n\t***Choose the book you want to buy or press 0 to exit***"<<endl;
    int o;
    cin>>o;
    if(o==0)
    {
        return;
    }
    bbname=row[o-1][0];
    baname=row[o-1][1];
    fout.open("sell.csv",ios::in);
    string tem,lin,wor;
    vector<string>ro;
    int cnt=0;
    cout<<"\t***People who want to sell this book***\n"<<endl;
    while(fout>>tem)
    {
        ro.clear();
        getline(fout,lin);
        stringstream ss(lin);
        int i=0;
        while(getline(ss,wor,','))
        {
            ro.push_back(wor);
            i++;
        }
        if(bbname==ro[1] && baname==ro[2])
        {
            cout<<"\t\t"<<++cnt<<". "<<ro[3]<<endl;
            cout<<"\t\t"<<"   "<<ro[4]<<endl;
            cout<<"\t\t"<<"   "<<ro[5]<<" taka"<<endl;
            cout<<"\t\t"<<"   "<<ro[6]<<endl;
            cout<<"\t\t"<<"   "<<ro[7]<<endl;

        }

    }
    fout.close();
    if(cnt==0)
        cout<<"\t\tUser not found"<<endl;
    cout<<"\t\tPress 0 to return to main menu"<<endl;
    int e;
    cin>>e;
    if(e==0)
        return;//a.display();
}
/*end*/

/*exchange operation*/
void exchange :: exchange_book()
{
    fstream fs;
    fs.open("exchange.csv", ios::out | ios::app);
    fs<<NID<<" ,";
    fs<<bname<<" ,";
    fs<<aname<<" ,";
    fs<<name<<" ,";
    fs<<email<<" ,";
    fs<<print<<" ,";
    fs<<city<<" ,";
    fs<<"\n";
    fs.close();
    cout<<"\n\t\t***Your book is added to the exchange book list***"<<endl;
    fstream fw,ft;
    fw.open("elist.csv",ios::in);
    string t,l,w;
    vector<string>r;
    int k=0;
    while(getline(fw,t,','))
    {
        r.clear();
        getline(fw,l);
        stringstream s(l);
        getline(s,w,',');
        t.erase(t.length()-1);
        w.erase(w.length()-1);
        if(bname==t && aname==w)
        {
            k=1;
            break;
        }
    }
    fw.close();
    if(k!=1)
    {
        ft.open("elist.csv",ios::out|ios::app);
        ft<<bname<<" ,";
        ft<<aname<<" ,";
        ft<<"\n";
        ft.close();
    }

}
void exchange::eunique_book()
{
    system("cls");
    cout<<"\n\t\t******************************************"<<endl;
    cout<<"\t\t\t    ### Exchange a BOOK ###"<<endl;
    cout<<"\t\t******************************************"<<endl;
    cout<<"\n\n";
    fstream fin,fout;
    fin.open("elist.csv",ios::in);
    vector<string>row[50];
    string line,word,temp;
    int j=0;
    while(getline(fin,temp,','))
    {
        row[j].clear();
        getline(fin,line);
        stringstream s(line);
        cout<<"\t\t"<<j+1<<". ";
        getline(s,word,',');
        row[j].push_back(temp);
        row[j].push_back(word);
        j++;
        transform(temp.begin(),temp.end(),temp.begin(), ::toupper);
        transform(word.begin(),word.end(),word.begin(), ::toupper);
        cout<<temp<<"by "<<word<<"\n";
    }
    fin.close();
    cout<<"\t\tChoose the book you like or press 0 to exit: ";
    int o;
    cin>>o;
    if(o==0)
    {
        return;
    }
    exbname=row[o-1][0];
    exaname=row[o-1][1];
    fout.open("exchange.csv",ios::in);
    string tem,lin,wor;
    vector<string>ro;
    cout<<"\t**People who want to exchange this book**"<<endl;
    int cnt=0;
    while(fout>>tem)
    {
        ro.clear();
        getline(fout,lin);
        stringstream ss(lin);
        int i=0;
        while(getline(ss,wor,','))
        {
            ro.push_back(wor);
            i++;
        }
        if(exbname==ro[1] && exaname==ro[2])
        {
            cout<<"\t\t"<<++cnt<<". "<<ro[3]<<endl;
            cout<<"\t\t"<<"   "<<ro[4]<<endl;
            cout<<"\t\t"<<"   "<<ro[5]<<endl;
            cout<<"\t\t"<<"   "<<ro[6]<<endl;
        }

    }
    fout.close();
    if(cnt==0)
         cout<<"\t\tUser not found"<<endl;
    cout<<"\n\tPress 0 to return to main menu"<<endl;
    int e;
    cin>>e;
    if(e==0)
        return;//a.display();
}
/*END*/

/*Admin function*/
void admin::admin_login()
{
    system("cls");
    cout<<"\n\t\t******************************************"<<endl;
    cout<<"\t\t\t### Administrator Sign In ###"<<endl;
    cout<<"\t\t******************************************"<<endl;
    string a,b;
    cout<<"\n\n\t\tEnter your ID:";
    cin>>a;
    cout<<"\t\tEnter your password:";
    char ch;
    b="";
    while((ch=_getch())!=13)
    {
        if(ch==8)
        {
            if(b.length()>0)
            {
                printf("\b \b");
                b.erase(b.length()-1);
            }
        }
        else
        {
            b.push_back(ch);
            cout<<'*';
        }
    }
    if(a==ID && b==pass)
    {
        admin_display();
    }

}
void admin::admin_display()
{
    cout<<"\n\n\t\t\tWelcome Asnuva"<<endl;
    cout<<"\n\t\tPress 1 to see all users\n\t\tPress 2 to see all books\n\t\tPress 3 to remove user\n\t\tPress 4 to Sign Out";
    int r;
    cin>>r;
    switch(r)
    {
    case 1:
        user_display_all();
        break;
    case 2:
        book_display_all();
        break;
    case 3:
        bptr=&a;
        bptr->delete_();
        break;
    case 4:
        break;
    }

}

void admin::user_display_all()
{
    system("cls");
    cout<<"\n\t\t******************************************"<<endl;
    cout<<"\t\t\t    ### ALL USERS ###"<<endl;
    cout<<"\t\t******************************************"<<endl;
    fstream fu;
    fu.open("user.csv",ios::in);
    string temp,line,word;
    vector<string>us;
    int i=0;
    while(fu>>temp)
    {
        us.clear();
        getline(fu,line);
        stringstream d(line);
        while(getline(d,word,','))
        {
            word.erase(word.length()-1);
            us.push_back(word);
            i++;
        }
        cout<<"\t\t";
        cout<<temp<<" ";
        for(int i=2; i<us.size(); i++)
        {
            cout<<us[i]<<" ";
        }
        cout<<endl;
    }
    cout<<"\t\tPress 0 to return to main menu\n";
    int e;
    cin>>e;
    if(e==0)
        admin_display();

}
void admin::book_display_all()
{
    system("cls");
    cout<<"\n\t\t******************************************"<<endl;
    cout<<"\t\t\t    ### ALL BOOKS ###"<<endl;
    cout<<"\t\t******************************************"<<endl;
    fstream fout,fin;
    fout.open("sell.csv",ios::in);
    string tem,lin,wor;
    vector<string>boo;
    cout<<"\n\n\t****Books in selling list****\n"<<endl;
    while(fout>>tem)
    {
        boo.clear();
        getline(fout,lin);
        stringstream ss(lin);
        int i=0;
        while(getline(ss,wor,','))
        {
            wor.erase(wor.length()-1);
            boo.push_back(wor);
            i++;
        }
        cout<<"\t";
        cout<<tem<<" "<<boo[1]<<" BY "<<boo[2]<<" "<<"\n";
    }
    fout.close();
    fin.open("exchange.csv");
    cout<<"\n\t****Books in exchange list****\n"<<endl;
    while(fin>>tem)
    {
        boo.clear();
        getline(fin,lin);
        stringstream s(lin);
        int i=0;
        while(getline(s,wor,','))
        {
            wor.erase(wor.length()-1);
            boo.push_back(wor);
            i++;
        }
        cout<<"\t";
        cout<<tem<<" "<<boo[1]<<" BY "<<boo[2]<<" "<<"\n";
    }
    fin.close();
    cout<<"\tPress 0 to return to main menu\n";
    int e;
    cin>>e;
    if(e==0)
        admin_display();
}

void admin::delete_()
{
    system("cls");
    cout<<"\n\t\t******************************************"<<endl;
    cout<<"\t\t\t### Delete User as Administrator ###"<<endl;
    cout<<"\t\t******************************************"<<endl;
    int k=0;
    string m,n;
    cout<<"\n\n\tEnter the NID:";
    cin>>m;
    cout<<"\tEnter the password:";
    cin>>n;
    fstream fup1,fup2;
    fup1.open("user.csv", ios::in);
    fup2.open("temp.csv", ios::out | ios::app);
    string temp,line,word;
    vector<string>row;
    while(fup1>>temp)
    {
        row.clear();
        getline(fup1,line);
        stringstream ss(line);
        int i=0;
        row[0]=temp;
        i++;
        while(getline(ss,word,','))
        {
            row.push_back(word);
            row[i].erase(row[i].length()-1);
            i++;
        }
        if(m==row[0] && n==row[2])
        {
            k=1;
            continue;
        }
        else
        {
            int r=row.size();
            for(int i=0; i<r; i++)
            {
                if(i==1)
                    continue;
                fup2<<row[i]<<" ,";
            }
            fup2<<"\n";
        }

    }
    if(k!=1)
        cout<<"User not found"<<endl;
    else
        cout<<"User Deleted"<<endl;
    fup1.close();
    fup2.close();
    remove("user.csv");
    rename("temp.csv", "user.csv");
    fup1.open("exchange.csv", ios::in);
    fup2.open("temp.csv", ios::out | ios::app);
    while(fup1>>temp)
    {
        row.clear();
        getline(fup1, line);
        stringstream ss(line);
        int i=0;
        row[0]=temp;
        i++;
        while(getline(ss,word,','))
        {
            row.push_back(word);
            row[i].erase(row[i].length()-1);
            i++;
        }
        if(m==row[0])
        {
            continue;
        }
        else
        {
            int r=row.size();
            for(int i=0; i<r; i++)
            {
                if(i==1)
                    continue;
                fup2<<row[i]<<" ,";
            }
            fup2<<"\n";
        }

    }
    fup1.close();
    fup2.close();
    remove("exchange.csv");
    rename("temp.csv", "exchange.csv");
    fup1.open("sell.csv", ios::in);
    fup2.open("temp.csv", ios::out | ios::app);
    while(fup1>>temp)
    {
        row.clear();
        getline(fup1, line);
        stringstream ss(line);
        int i=0;
        row[0]=temp;
        while(getline(ss,word,','))
        {
            row.push_back(word);
            row[i].erase(row[i].length()-1);
            i++;
        }
        if(m==row[0])
        {
            continue;
        }
        else
        {
            int r=row.size();
            for(int i=0; i<r; i++)
            {
                if(i==1)
                    continue;
                fup2<<row[i]<<" ,";
            }
            fup2<<"\n";
        }

    }
    fup1.close();
    fup2.close();
    remove("sell.csv");
    rename("temp.csv", "sell.csv");
    cout<<"\t\tPress 0 to return to main menu\n";
    int e;
    cin>>e;
    if(e==0)
        admin_display();
}
/*End*/

void admin::display()
{
    while(1)
    {
        u.putname();
        int c;
        cout<<"\t    ----------------------------------------------------"<<endl;
        cout<<"\n\t\t\tChoose what you want to do(1-8)"<<endl;
        cout<<"\t  --------------------------------------------------------"<<endl;
        cout<<"\t\t01.Search for a book\n\t\t02.Add a new book\n\t\t03.Buy a book\n\t\t04.Exchange book\n\t\t05.Delete\n\t\t06.Update your profile\n\t\t07.See Your Books\n\t\t08.Sign Out\n\t\t";
        cin>>c;
        if(c==1)
            searc_h();
        else if(c==2)
            new_book();
        else if(c==3)
            unique_book();
        else if(c==4)
            eunique_book();
        else if(c==5)
        {
            system("cls");
            cout<<"\n\n\n\t\t01.Delete a book\n\t\t02.Delete your account\n\t\t";
            int n;
            cin>>n;
            //Runtime Polymorphism
            if(n==1)
            {
                cout<<"\t\tPress 1 if the book is on sells list\n\t\tPress 2 if it is on exchange list\n\t\t";
                int j;
                cin>>j;
                if(j==1)
                {
                    bptr=&s;
                    bptr->delete_();
                }
                else
                {
                    bptr=&e;
                    bptr->delete_();
                }

            }
            else
            {
                user::delete_();
                return;

            }
        }
        else if(c==6)
        {
            update();
        }
        else if(c==7)
            u.mybooklist();
        else if(c==8)
        {
            break;
        }
    }
}

/*Search For Books*/
void book::searc_h()
{
    system("cls");
    cout<<"\n\t\t******************************************"<<endl;
    cout<<"\t\t\t  ### Search For a BOOK ###"<<endl;
    cout<<"\t\t******************************************"<<endl;
    cout<<"\n\n\n";
    fstream fin;
    int cnt=0,d=5,cntt=0;
    getchar();
    do
    {
        cout<<"\t\tEnter the books name:";
        getline(cin,bname);
        transform(bname.begin(),bname.end(),bname.begin(), ::tolower);
        cout<<"\t\tEnter the author's name:";
        getline(cin,aname);
        transform(aname.begin(),aname.end(),aname.begin(), ::tolower);
        fin.open("sell.csv", ios :: in);
        string temp,line,word;
        vector<string>row;
        cout<<"\tPeople who want to sell this book:\n"<<endl;
        while(fin>>temp)
        {
            row.clear();
            getline(fin,line);
            stringstream ss(line);
            int i=0;
            while(getline(ss,word,','))
            {
                row.push_back(word);
                row[i].erase(row[i].length()-1);
                i++;
            }

            if(bname==row[1] && aname==row[2])
            {
                cout<<"\t\t"<<++cnt<<". "<<row[3]<<endl;
                cout<<"\t\t"<<"   "<<row[4]<<endl;
                cout<<"\t\t"<<"   "<<row[5]<<" Taka"<<endl;
                cout<<"\t\t"<<"   "<<row[6]<<endl;
                cout<<"\t\t"<<"   "<<row[7]<<endl;

            }

        }
        if(cnt==0)
            cout<<"\t\tBook not found"<<endl;
        fin.close();
        fin.open("exchange.csv", ios :: in);
        string tempp,lline,wordd;
        vector<string>roww;
        cout<<"\n\n\tPeople who want to exchange this book:\n"<<endl;
        while(fin>>tempp)
        {
            roww.clear();
            getline(fin,lline);
            stringstream ss(lline);
            int i=0;
            while(getline(ss,wordd,','))
            {
                roww.push_back(wordd);
                roww[i].erase(roww[i].length()-1);
                i++;
            }
            if(bname==roww[1] && aname==roww[2])
            {
                cout<<"\t\t"<<++cntt<<". "<<roww[3]<<endl;
                cout<<"\t\t"<<"   "<<roww[4]<<endl;
                cout<<"\t\t"<<"   "<<roww[5]<<endl;
                cout<<"\t\t"<<"   "<<roww[6]<<endl;
            }

        }
        if(cntt==0)
            cout<<"\t\tBook not found"<<endl;
        fin.close();
        cout<<"\n\n\t\tPress 5 if you want to search for another book\n\t\tpress 6 to exit"<<endl;
        cin>>d;
    }
    while(d==5);
    return;//a.display();

}

/*Delete User Account*/
void user::delete_()
{
    system("cls");
    cout<<"\n\t\t******************************************"<<endl;
    cout<<"\t\t\t  ### Delete My Account ###"<<endl;
    cout<<"\t\t******************************************"<<endl;
    int k=0;
    fstream fup1,fup2;
    fup1.open("user.csv", ios::in);
    fup2.open("temp.csv", ios::out | ios::app);
    string temp,line,word;
    vector<string>row;
    while(fup1>>temp)
    {
        row.clear();
        getline(fup1, line);
        stringstream ss(line);
        int i=0;
        while(getline(ss,word,','))
        {
            row.push_back(word);
            row[i].erase(row[i].length()-1);
            i++;
        }
        if(NID==temp && password==row[1])
        {
            k=1;
            continue;
        }
        else
        {
            int r=row.size();
            fup2<<temp<<" ,";
            for(int i=1; i<r-1; i++)
            {
                fup2<<row[i]<<" ,";
            }
            fup2<<row[r-1]<<"\n";
        }


    }
    if(k!=1)
        cout<<"User not found"<<endl;
    else
        cout<<"User Deleted"<<endl;
    fup1.close();
    fup2.close();
    remove("user.csv");
    rename("temp.csv", "user.csv");
    fup1.open("exchange.csv", ios::in);
    fup2.open("temp.csv", ios::out | ios::app);
    while(fup1>>temp)
    {
        row.clear();
        getline(fup1, line);
        stringstream ss(line);
        int i=0;
        while(getline(ss,word,','))
        {
            row.push_back(word);
            row[i].erase(row[i].length()-1);
            i++;
        }
        if(NID==temp)
        {
            continue;
        }
        else
        {
            int r=row.size();
            fup2<<temp<<" ,";
            for(int i=1; i<r-1; i++)
            {
                fup2<<row[i]<<" ,";
            }
            fup2<<row[r-1]<<"\n";
        }


    }
    fup1.close();
    fup2.close();
    remove("exchange.csv");
    rename("temp.csv", "exchange.csv");
    fup1.open("sell.csv", ios::in);
    fup2.open("temp.csv", ios::out | ios::app);
    while(fup1>>temp)
    {
        row.clear();
        getline(fup1, line);
        stringstream ss(line);
        int i=0;
        while(getline(ss,word,','))
        {
            row.push_back(word);
            row[i].erase(row[i].length()-1);
            i++;
        }
        if(NID==temp)
        {
            continue;
        }
        else
        {
            int r=row.size();
            fup2<<temp<<" ,";
            for(int i=1; i<r-1; i++)
            {
                fup2<<row[i]<<" ,";
            }
            fup2<<row[r-1]<<"\n";
        }


    }
    fup1.close();
    fup2.close();
    remove("sell.csv");
    rename("temp.csv", "sell.csv");
    cout<<"\t\tPress 0 to return to main menu\n";
    int e;
    cin>>e;
    if(e==0)
        return;//a.display();
}

/*Delete Books in Sells list*/
void sell::delete_()
{
    system("cls");
    cout<<"\n\t\t******************************************"<<endl;
    cout<<"\t\t   ### Delete Book From Sells List ###"<<endl;
    cout<<"\t\t******************************************"<<endl;
    fstream fs,ft;
    fs.open("sell.csv",ios::in);
    ft.open("temp.csv",ios::out | ios::app);
    int k1=0;
    getchar();
    cout<<"\n\n\t\tEnter book's name:";
    getline(cin,bname);
    transform(bname.begin(),bname.end(),bname.begin(), ::tolower);
    cout<<"\t\tEnter author's name:";
    getline(cin,aname);
    transform(aname.begin(),aname.end(),aname.begin(), ::tolower);
    string temp,line,word;
    vector<string>row;
    while(fs>>temp)
    {
        row.clear();
        getline(fs, line);
        stringstream ss(line);
        int i=0;
        while(getline(ss,word,','))
        {
            row.push_back(word);
            row[i].erase(row[i].length()-1);
            i++;
        }
        if(a.NID==temp && bname==row[1] && aname==row[2])
        {
            k1=1;
            continue;
        }
        else
        {
            int r=row.size();
            ft<<temp<<" ,";
            for(int i=1; i<r-1; i++)
            {
                ft<<row[i]<<" ,";
            }
            ft<<row[r-1]<<"\n";
        }


    }
    fs.close();
    ft.close();
    remove("sell.csv");
    rename("temp.csv", "sell.csv");
    if(k1!=1)
        cout<<"\t\tBook not found"<<endl;
    else
        cout<<"\t\tBook Removed."<<endl;
    cout<<"\t\tPress 0 to return to main menu\n";
    int e;
    cin>>e;
    if(e==0)
        return;//a.display();
}

/*Delete books in exchange list*/
void exchange::delete_()
{
    system("cls");
    cout<<"\n\t\t******************************************"<<endl;
    cout<<"\t\t\t### Delete Book from Exchange List ###"<<endl;
    cout<<"\t\t******************************************"<<endl;
    fstream fs,ft;
    fs.open("exchange.csv",ios::in);
    ft.open("temp.csv",ios::out | ios::app);
    int k1=0;
    getchar();
    cout<<"\n\t\tEnter book's name:";
    getline(cin,bname);
    transform(bname.begin(),bname.end(),bname.begin(), ::tolower);
    cout<<"\n\t\tEnter author's name:";
    getline(cin,aname);
    transform(aname.begin(),aname.end(),aname.begin(), ::tolower);
    string temp,line,word;
    vector<string>row;
    while(fs>>temp)
    {
        row.clear();
        getline(fs, line);
        stringstream ss(line);
        int i=0;
        while(getline(ss,word,','))
        {
            row.push_back(word);
            row[i].erase(row[i].length()-1);
            i++;
        }
        if(a.NID==temp && bname==row[1] && aname==row[2])
        {
            k1=1;
            continue;
        }
        else
        {
            int r=row.size();
            ft<<temp<<" ,";
            for(int i=1; i<r-1; i++)
            {
                ft<<row[i]<<" ,";
            }
            ft<<row[r-1]<<"\n";
        }


    }
    fs.close();
    ft.close();
    remove("exchange.csv");
    rename("temp.csv", "exchange.csv");
    if(k1!=1)
        cout<<"\t\tBook not found"<<endl;
    else
        cout<<"\t\tBook Removed."<<endl;
    cout<<"\t\tPress 0 to return to main menu\n";
    int e;
    cin>>e;
    if(e==0)
        return;//a.display();

}

/*Update User Profile*/
void user::update()
{
    system("cls");
    cout<<"\n\t\t******************************************"<<endl;
    cout<<"\t\t\t  ### Update My Account ###"<<endl;
    cout<<"\t\t******************************************"<<endl;
    cout<<"\n\n\t\tPress 1 to change password\n\t\tPress 2 to update email\n\t\t";
    int t,k=0;
    cin>>t;
    fstream fup1,fup2;
    fup1.open("user.csv", ios::in);
    fup2.open("temp.csv", ios::out | ios::app);
    string temp,line,word;
    vector<string>row;
    cout<<"\n\n\n";
    while(fup1>>temp)
    {
        row.clear();
        getline(fup1, line);
        stringstream ss(line);
        int i=0;
        while(getline(ss,word,','))
        {
            row.push_back(word);
            row[i].erase(row[i].length()-1);
            i++;
        }
        if(NID==temp && password==row[1])
        {
            int r=row.size();
            string neww;
            k=1;
            if(t==1)
            {
                cout<<"\t\tEnter the password:";
                cin>>neww;
                row[1]=neww;
            }
            else
            {
                cout<<"\t\tEnter the new e-mail:";
                cin>>neww;
                row[3]=neww;
            }
            fup2<<temp<<" ,";
            for(int i=1; i<r-1; i++)
            {
                fup2<<row[i]<<" ,";
            }
            fup2<<row[r-1]<<"\n";
        }
        else
        {
            int r=row.size();
            fup2<<temp<<" ,";
            for(int i=1; i<r-1; i++)
            {
                fup2<<row[i]<<" ,";
            }
            fup2<<row[r-1]<<"\n";
        }


    }
    fup1.close();
    fup2.close();
    remove("user.csv");
    rename("temp.csv", "user.csv");
    if(k!=1)
        cout<<"User not found!"<<endl;
    else
        cout<<"\t\tUpdate Successful"<<endl;
    cout<<"\t\tPress 0 to return to main menu\n";
    int e;
    cin>>e;
    if(e==0)
        return;//a.display();
}

int main()
{
    while(1)
    {
        cout<<"\n\t\t------------------------------------------"<<endl;
        cout<<"\t\t\t*** Book Sharing System ***"<<endl;
        cout<<"\t\t------------------------------------------"<<endl;
        cout<<"\n\n\t\t01.Sign In"<<endl;
        cout<<"\t\t02.Sign In as Administrator"<<endl;
        cout<<"\t\t03.Sign Up"<<endl;
        cout<<"\n\n\n\n\t\t\t\t\tMade By\n\t\t\t\t\tAsnuva Tanvin\n\t\t\t\t\t1707005\n\t\t\t\t\tKUET"<<endl;
        int c;
        cin>>c;
        if(c==1)
        {
            int v;
            v=u.sign_in();
            if(v==-1)
                a.display();
            else
                return 0;

        }
        else if(c==2)
        {
            a.admin_login();
            a.admin_display();
        }
        else
        {
            u.new_user();
            a.display();
        }
    }
    return 0;

}

