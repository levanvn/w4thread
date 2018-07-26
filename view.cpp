#include <iostream>
#include "we4.h"
#include <string>
#include "sha1.hpp"
#include<bits/stdc++.h>
#include<pthread.h>
using namespace std;

 pthread_mutex_t frien, mess;

void User::SignUp(){
    cout << "-------Dien cac thong tin de dang ky!-------" << endl;
    username = new (char);
    city = new (char);
    password = new char;

	cout << "Nhap vao username: ";
	cin >> username;
	cout << "Nhap password: ";
	cin >> password;
	password = sha1(password);
    //cout << password;
	cout << "Enter city: ";
	cin >> city;

	ConnectSQlite conn ;
	conn.Open();
    if(!conn.CheckCity(city)) conn.WriteCity(city);
    int idc = conn.TranCitytoId(city);
    conn.RunInsertParamSQL(conn.db,username,password,idc);

}
void  User::SignIn(){
    username = new (char);
    password = new (char);

    cout << "Nhap vao username: ";
	cin >> username;
	cout << "Nhap password: ";
	cin >> password;
	password = sha1(password);
	ConnectSQlite conn ;
	conn.Open();

	if(conn.RunSelectParamSQL(conn.db,username,password) > 0) {
        cout << "Sign in successfuly!\n";
        id = conn.RunSelectParamSQL(conn.db,username,password);
        flag = 1;

	}
	else {
        cout << "Sign in fail!\n";
        flag = 0;
	}
    //conn.SelectUser1();
}
void User::SignOut(){
    flag = 0;
    cout << "-----Ban da dang xuat.-------\n";
}
bool User::isSignIn(){
    ConnectSQlite conn;
    if(flag == 1) return true;
    return false;
}

void User::EditInfoFriend(User u){

    /* 0: Friends
       1: Block
       2: Close Friend

    */
    if (isSignIn()){
        ShowFriend(u.id);
        cout << "Nhap vao ten ban be can chinh sua: ";
        char *frien = new char;

        cin >> frien;
        ConnectSQlite conn;
        conn.Open();
        int id2 = conn.TransNameToId(frien);
        if(id2 > 0){
            cout << "Tinh trang ban be hien tai: ";
            if(conn.CheckBlock(u.id,id2) == 0) cout << "Friends.\n";
            else if(conn.CheckBlock(u.id,id2) == 1) cout << "isBlock.\n";
            else cout << "Close Friend.\n";
            cout << "------Nhap thay doi-----------\n"
                << "1.Block\n"
                << "2.Bo Block \n"
                << "3.Close Friend\n";
                int choose;
                cin >> choose;
            if(choose == 1 ) {
                if(conn.CheckBlock(u.id,id2) == 0 ){

                    conn.UpdateStatusFriend(conn.db,1,u.id,id2);
                    cout <<"---------Block Successfuly---------\n";
                    string s[100];
                    conn.ShowFriend(conn.db,u.id,s);
                }else cout << "----Ban da block nguoi nay------\n ";

            }
            if(choose == 2) {
                if(conn.CheckBlock(u.id,id2) == 1 && conn.CheckWhoBlock(u.id,id2) == u.id){
                    conn.UpdateStatusFriend(conn.db,0,u.id,id2);
                    cout <<"---------Ban da bo Block nguoi nay---------\n";
                } else { cout << "---Ban khong co quyen bo block hoac chua block---\n";}
            }
            if(choose == 3){
                conn.UpdateStatusFriend(conn.db,2,u.id,id2);
                cout << "-----Ban than da duoc them-------\n";
            }
        }else cout << "-----Tai khoan khon ton tai-----\n";
    }else  cout << "----------Ban chua dang nhap.--------\n\n";

}


void User::AddFriend(int id){
    if (isSignIn()){
        cout << "Nhap ten nguoi ban muon them: ";
        char *newfr;
        newfr = new char;
        cin >> newfr;
        ConnectSQlite conn;
        conn.Open();
        int id2 = conn.TransNameToId(newfr);
        //cout << "OK1" << id2;
        if(id2 > 0){
            if(conn.CheckBlock(id,id2) == 0 && !conn.CheckFriend(conn.db,id,id2) ){
                conn.WriteToFriend(conn.db,id,id2);
                ShowFriend(id);
            }else {
                //conn.CheckBlock(id,id2);
                cout << "------You were blocked by her  or You was friend ----------\n\n\n";
                //conn.CheckFriend(conn.db,id,id2);
            }
        }else cout <<  "----Tai khoan khong ton tai-----------\n";
    }else {
        cout << "----------Ban chua dang nhap.--------\n\n";
    }

}

void User::ShowFriend(int id,string s[]){
    if (isSignIn()){
        ConnectSQlite conn;
        conn.Open();
        conn.ShowFriend(conn.db,id,s);

    }else {
        cout << "----------Ban chua dang nhap.--------\n\n";
    }
}

void User::ShowFriendByCity(int id){
    if (isSignIn()){
        ConnectSQlite conn;
        conn.Open();
        conn.ShowFriendByCity(id);

    }else {
        cout << "----------Ban chua dang nhap.--------\n\n";
    }
}

void User::ShowFriend(int id){
    if (isSignIn()){

        ConnectSQlite conn;
        conn.Open();
        string s[100];
        conn.ShowFriend(conn.db,id,s);

    }else {
        cout << "----------Ban chua dang nhap.--------\n\n";
    }
}

void User::ShowMess(int id){
    //cout << id;
   // cout << this->id << " " << this->flag;
    if (isSignIn()){
        ConnectSQlite conn;
        conn.Open();

        conn.SelectMessenger(conn.db,id);
    }else {
        cout << "----------Ban chua dang nhap.--------\n\n";
    }



}
void User::ShowMessRec(int id){
     if (isSignIn()){
        ConnectSQlite conn;
        conn.Open();
        conn.ShowMessRec(id);
     }else {
        cout << "----------Ban chua dang nhap.--------\n\n";
     }
}

void User::ShowMessSen(int id){
     if (isSignIn()){
        ConnectSQlite conn;
        conn.Open();
        conn.ShowMessSen(id);
     }else {
        cout << "----------Ban chua dang nhap.--------\n\n";
     }
}

void User::ShowMessDetail(int id1){
    if (isSignIn()){
        int id2;
        cout << "Chon nguoi dung: ";
        char *frien;
        frien = new char;
        cin >> frien;
        ConnectSQlite conn;
        conn.Open();
        id2 = conn.TransNameToId(frien);

        if(id2 > 0)
        conn.ShowMessDetail(conn.db,id1,id2);
        else cout <<  "----Tai khoan khong ton tai-----------\n";

        cout << "Nhan Ctrl + R de gui tiep tin nhan,esc de thoat\n";
        //char esc;
      //  cin.ignore();
        //esc = getch();

            char ctrlL;
            cin.ignore();
            ctrlL = getch();
            if( ctrlL == 18 ){
                 time_t hientai = time(0);
                 char *dt, *mess = new char;
                 dt = ctime(&hientai);
                 cout << "Nhap Tin nhan: \n";
                 cin >> mess;
                 conn.WriteToMess(conn.db,id1,id2,mess,dt);
                 conn.ShowMessDetail(conn.db,id1,id2);
            }


    }else {
        cout << "----------Ban chua dang nhap.--------\n\n";
    }

}


void User::SendMess(int id){
    if (isSignIn()){
        int id2;
        ConnectSQlite conn;
        conn.Open();
        //sleep(1);
        cout << "1.Nhap nguoi dung\n "
             << "2.Nhan Ctrl + L de hien thi danh sach\n";


        int choose; char choo;
        cin >> choose;
        string s [100];
        char *username = new char;

        if(choose == 1){
            cout << "Nhap ten ban be: ";
            cin >> username;
        }
         if(choose == 2) {

            cout << "Press Ctrl + L to continue.\n";
            cin.ignore();
            choo = getch();

            if(choo == 12){

                ShowFriend(id,s);
                cout << "Chon so thu tu\n";
                int chon;
                cin >> chon;
                //username = s[chon-1];
                memcpy(username, s[chon-1].c_str(), sizeof(s[chon-1]));
                //cout << s[chon-1].c_str() << "  " << username <<  "   " << s[chon-1].length()<<" ok\n";

            }else cout << choo;
        }
        //username = name.c_str();
        id2 = conn.TransNameToId(username);
        //cout << id2;
        if(id2 > 0){
            char *mess,*dt;
            mess = new char;
            dt =new char;
            if(conn.CheckBlock(id,id2)){
                        cout << conn.CheckBlock(id,id2) ;
                        cout << "---------You is blocked by her--------\n";
            }else{
                cout << "Nhap Tin nhan: \n";
                cin >> mess;
                 time_t hientai = time(0);
                 dt = ctime(&hientai);
                 conn.WriteToMess(conn.db,id,id2,mess,dt);
                 conn.ShowMessDetail(conn.db,id,id2);

            }
        }else cout <<  "----Tai khoan khong ton tai-----------\n";

/*
        ConnectSQlite conn;
        conn.Open();
        id2 = conn.TransNameToId(frien);
        //cout << id2;
        if(id2 > 0){
            char *mess,*dt;
            mess = new char;
            dt =new char;
            if(!conn.CheckBlock(id,id2)){
                        cout << "---------You is blocked by her--------\n";
            }else{
                cout << "Nhap Tin nhan: \n";
                cin >> mess;
                 time_t hientai = time(0);
                 dt = ctime(&hientai);
                 conn.WriteToMess(conn.db,id,id2,mess,dt);
                 conn.ShowMessDetail(conn.db,id,id2);

            }
        }else cout <<  "----Tai khoan khong ton tai-----------\n";

    }else {
        cout << "----------Ban chua dang nhap.--------\n\n";
    } */
}
}

extern sem_t sem;

void* threadsendmess(void* arg)
{  
    int *id = (int*) arg;
    sem_wait(&sem);
    extern User us;
    
    us.SendMess(*id);
    sem_post(&sem);

}

void* threadshowmess(void* arg)
{   
    sem_wait(&sem);
    extern User us;
    int *id = (int *) arg;
    us.ShowMessDetail(*id);
    sem_post(&sem);
}
