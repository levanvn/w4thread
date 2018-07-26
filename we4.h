#include <iostream>
#include <sqlite3.h>
#include<bits/stdc++.h>
#include <termios.h>
#include <unistd.h>
//#include <stdio.h>
#include <bits/stdc++.h>
#include <pthread.h>
#include <semaphore.h>

using namespace std;
class User{
	public:

		int  id;
		char *username;
		char *password;
		char *city;
		int flag ; //danh dau dang nhap

	public :
        User(){};
		void SignUp();
        void SignIn();
        bool isSignIn(); // kiem tra da dang nhap chua
        void SignOut();
        bool Check(User u);
        void ShowMess(int);
        void ShowMessDetail(int);
        void SendMess(int);
        void AddFriend(int);
        void ShowFriend(int);
        void ShowFriend(int,string s[]);
        void ShowFriendByCity(int);
        void ShowMessRec(int);
        void ShowMessSen(int);
        void BlockFriend(int);
        void EditInfoFriend(User u);
        void (*signal(int sig, void (*func)(int)))(int);

};

class ConnectSQlite{
    public:
        sqlite3 *db;
        char *zErrMsg = 0;
        int rc;
        const char *szSQL;
        const char *pzTest;
        sqlite3_stmt *stmt;
        list<string> answer;
   // int countRow; //dem so hang o cau lenh select
    public :
        static int callback(void *,int,char **,char **);
        void Open();
        void WriteCity(char *);
        bool CheckCity(char *);
        int TranCitytoId(char *);
        const unsigned char* TranIdtoCity(int );
        const unsigned char* TranIdtoUser(int );
        void RunInsertParamSQL(sqlite3 *db,char *, char *,int );
        int RunSelectParamSQL(sqlite3 *db, char *fn, char *ln);
        int TransNameToId(char *frien);
        void SelectMessenger(sqlite3 *db, int id);
        void ShowMessDetail(sqlite3 *db,int id1,int id2);
        int CheckBlock(int id1, int id2);
        void WriteToMess(sqlite3 *db,int id1, int id2,char *mes,char *time);
        bool CheckFriend(sqlite3 *db, int id1,int id2);
        void WriteToFriend(sqlite3 *db,int id1, int id2);
        void ShowFriend(sqlite3 *db,int id1,string a[]);
        void UpdateStatusFriend(sqlite3 *db,int , int ,int);
        int CheckWhoBlock(int, int);
        void ShowFriendByTime(int id);
        void ShowFriendByCity(int id);
        void ShowMessSen(int);
        void ShowMessRec(int);
};

//void EditInfoFriend(User u);
int getch(void);
void* threadsendmess(void* arg);
void* threadshowmess(void* arg);


