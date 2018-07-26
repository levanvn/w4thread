#include <iostream>
#include "we4.h"
//#include "sha1.hpp"
#include<bits/stdc++.h>


using namespace std;



int ConnectSQlite::callback(void *NotUsed, int argc, char **argv, char **azColName){
           int i;
           for(i=0; i<argc; i++){
              printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
           }
           printf("\n");
           return 0;
        }
void ConnectSQlite::Open(){
        rc = sqlite3_open("We4.db", &db);
       if( rc ){

          fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
          exit(0);
       }else{
          //fprintf(stderr, "Opened database successfully\n");

       }

}
void ConnectSQlite::RunInsertParamSQL(sqlite3 *db, char *fn, char *ln,int id ){
  if (!db)return;
  // Insert data item into myTable
  szSQL = "insert into user (username, password,city) values (?,?,?)";

  int rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);

  if( rc == SQLITE_OK ) {
    // bind the value
    sqlite3_bind_text(stmt, 1, fn, strlen(fn), 0);
    sqlite3_bind_text(stmt, 2, ln, strlen(ln), 0);
    sqlite3_bind_int(stmt, 3, id);
   // sqlite3_bind_int(stmt, 3, age);

    // commit
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
  }else{

      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      // break the loop if error occur
  }
}
int ConnectSQlite::RunSelectParamSQL(sqlite3 *db,char *us, char *pa){
        int id = 0;
        if (!db)return 0;

        szSQL = "SELECT * FROM  user WHERE username = ? and password = ? ";

        rc = sqlite3_prepare(db, szSQL, strlen(szSQL), &stmt, &pzTest);

       if( rc == SQLITE_OK ) {
            // bind the value
            sqlite3_bind_text(stmt, 1, us, strlen(us), 0);
            sqlite3_bind_text(stmt, 2, pa, strlen(pa), 0);
            // commit
           while(sqlite3_step(stmt) == SQLITE_ROW) {
                stringstream str;
                str << sqlite3_column_text(stmt, 0);
                str >> id ;
            }
            sqlite3_finalize(stmt);


      }else{

          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
          // break the loop if error occur
      }
    return id;

}

void ConnectSQlite::WriteCity(char *name){
    szSQL = "INSERT INTO city(name) VALUES(?)";
    rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
      if( rc == SQLITE_OK ) {
            // bind the value
        sqlite3_bind_text(stmt,1,name,strlen(name),0);
            sqlite3_step(stmt);
            sqlite3_finalize(stmt);

    }else{

          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
          // break the loop if error occur
      }

}

bool ConnectSQlite::CheckCity(char *name){
    int hascity = 0;
    szSQL = "SELECT idc FROM city WHERE name = ? ";
    rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
      if( rc == SQLITE_OK ) {
            // bind the value
        sqlite3_bind_text(stmt,1,name,strlen(name),0);
        // commit
       if(sqlite3_step(stmt) == SQLITE_ROW ){
           stringstream str;
            str << sqlite3_column_text(stmt, 0);
            str >> hascity;

            if(hascity != 0) hascity = 1;
            else hascity = 0;

            sqlite3_finalize(stmt);
        }
    }else{

          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
          // break the loop if error occur
      }
    return hascity;
}
const unsigned char* ConnectSQlite::TranIdtoCity(int id){
     const unsigned char* s;
    szSQL = "SELECT name FROM city WHERE idc = ?";
    rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
    if( rc == SQLITE_OK){
        sqlite3_bind_int(stmt,1,id);
        if(sqlite3_step(stmt) == SQLITE_ROW){
            s = sqlite3_column_text(stmt,0);
        }
    }else{
          fprintf(stderr, "SQL error: %s\n",zErrMsg);
          sqlite3_free(zErrMsg);
    }
    return s;
}

const unsigned char* ConnectSQlite::TranIdtoUser(int id){
     const unsigned char* s;
    szSQL = "SELECT username FROM User WHERE id = ?";
    rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
    if( rc == SQLITE_OK){
        sqlite3_bind_int(stmt,1,id);
        if(sqlite3_step(stmt) == SQLITE_ROW){
            s = sqlite3_column_text(stmt,0);
        }
    }else{
          fprintf(stderr, "SQL error: %s\n",zErrMsg);
          sqlite3_free(zErrMsg);
    }
    return s;
}

int ConnectSQlite::TransNameToId(char *frien){
    int id2 = -1;
    szSQL = "SELECT id FROM User WHERE username = ?";
    rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);

    if( rc == SQLITE_OK ){
        sqlite3_bind_text(stmt,1,frien,strlen(frien),0);
        if(sqlite3_step(stmt) == SQLITE_ROW) {
            stringstream str;
            str << sqlite3_column_text(stmt, 0);
            str >> id2 ;

        }
        sqlite3_finalize(stmt);
    }else{
          fprintf(stderr, "SQL error: %s\n",zErrMsg);
          sqlite3_free(zErrMsg);
    }
    return id2;

}

int ConnectSQlite::TranCitytoId(char *name){

    int id2 = -1;
    szSQL = "SELECT idc FROM city WHERE name = ?";
    rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);

    if( rc == SQLITE_OK ){
        sqlite3_bind_text(stmt,1,name,strlen(name),0);
        if(sqlite3_step(stmt) == SQLITE_ROW) {
            stringstream str;
            str << sqlite3_column_text(stmt, 0);
            str >> id2 ;

        }
        sqlite3_finalize(stmt);
    }else{
          fprintf(stderr, "SQL error: %s\n",zErrMsg);
          sqlite3_free(zErrMsg);
    }
    return id2;
}



void ConnectSQlite::WriteToFriend(sqlite3 *db,int id1, int id2){
    if (!db)return ;
     szSQL = "INSERT INTO Friend VALUES (?,?,?,?,?)";
     rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
     if( rc == SQLITE_OK ) {
            // bind the value
        int isblock = 0;
        time_t hientai = time(0);
        char *dt = ctime(&hientai);
        sqlite3_bind_int(stmt,1,id1);
        sqlite3_bind_int(stmt,2,id2);
        sqlite3_bind_text(stmt,3,dt,strlen(dt),0);
        sqlite3_bind_int(stmt,4,isblock);
        sqlite3_bind_int(stmt,4,0);
        // commit
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);

    }else{

          fprintf(stderr, "Write Friend SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
          // break the loop if error occur
      }
}

void ConnectSQlite::ShowFriendByTime(int id){


}

void ConnectSQlite::ShowFriendByCity(int id){
    szSQL = "SELECT city.idc,User.id FROM city, User,Friend WHERE (Friend.id1 = ? or Friend.id2 = ?) and (User.id = Friend.id1 or User.id = Friend.id2)  and User.city = city.idc and User.id != ?";
    rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
    if( rc == SQLITE_OK ) {
            // bind the value
        sqlite3_bind_int(stmt,1,id);
        sqlite3_bind_int(stmt,2,id);
        sqlite3_bind_int(stmt,3,id);
        // commit
        int a[100][100];
        int b[100],c[100];
        memset(b,0,sizeof(b));
        memset(a,0,sizeof(a));
        int coun = 0;
        while(sqlite3_step(stmt) == SQLITE_ROW) {
            int idc,idn;
            stringstream str,st;
            str << sqlite3_column_text(stmt, 0);
            str >> idc;
            if(a[idc][0] ==0 ){c[coun] = idc; coun++;}
            st << sqlite3_column_text(stmt, 1);
            st >> idn;
           // cout << idc << "  " << idn << endl;
            a[idc][b[idc]] = idn;
            //cout << idc << " " << b[idc] << "  " << a[idc][b[idc]] << endl;
            b[idc]++;

        }
        for(int i = 0; i< coun;i++) {
            cout << TranIdtoCity(c[i]) << endl ;
            for(int j =0; j< b[c[i]]; j++) {
                cout << "  " <<  j+1 << "."  << TranIdtoUser(a[c[i]][j]) << endl;

            }
            cout << endl;
        }
        sqlite3_finalize(stmt);

            cout <<"-------------------------------------\n";
    }else{

          fprintf(stderr, "City SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
          // break the loop if error occur
      }

}
void ConnectSQlite::ShowFriend(sqlite3 *db,int id1,string s[]){
    cout << "-------List Friends-----------\n";
    if (!db)return ;
    szSQL = "SELECT DISTINCT user.username FROM"
                "(SELECT * FROM friend where (id1 = ? OR id2 = ?) AND RelationshipStatus != 1 )  as A LEFT JOIN user ON (A.id2 = user.id OR A.id1 = user.id)";
    rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
    if( rc == SQLITE_OK ) {
            // bind the value
        sqlite3_bind_int(stmt,1,id1);
        sqlite3_bind_int(stmt,2,id1);
        // commit

        int i = 0,t =1;

        while(sqlite3_step(stmt) == SQLITE_ROW) {
           s[i] = string((const char *) sqlite3_column_text(stmt, 0)) ;
           cout <<t << "." <<  s[i] << endl;
           i++; t++;
        }
        sqlite3_finalize(stmt);

            cout <<"-------------------------------------\n";
    }else{

          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
          // break the loop if error occur
      }
}

int ConnectSQlite::CheckBlock(int id1, int id2){
    int isblock = 0;
     if (!db)return 0;
     szSQL = "SELECT RelationshipStatus FROM Friend WHERE (id1 = ? AND id2 = ?) OR (id1 = ? AND id2 = ?)";
     rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
      if( rc == SQLITE_OK ) {
            // bind the value
        sqlite3_bind_int(stmt,1,id1);
        sqlite3_bind_int(stmt,2,id2);
        sqlite3_bind_int(stmt,3,id2);
        sqlite3_bind_int(stmt,4,id1);

        // commit
        //sqlite3_step(stmt);
       if(sqlite3_step(stmt) == SQLITE_ROW ){
           stringstream str;
            str << sqlite3_column_text(stmt, 0);
            str >> isblock ;
            sqlite3_finalize(stmt);
        }
    }else{

          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
          // break the loop if error occur
      }
      return isblock;
}

int ConnectSQlite::CheckWhoBlock(int id1,int id2){
    int whoblock = 0;
    szSQL = "SELECT whoblock FROM Friend WHERE (id1 = ? AND id2 = ?) OR (id1 = ? AND id2 = ?)";
    rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
    if( rc == SQLITE_OK ) {
            // bind the value
        sqlite3_bind_int(stmt,1,id1);
        sqlite3_bind_int(stmt,2,id2);
        sqlite3_bind_int(stmt,4,id1);
        sqlite3_bind_int(stmt,3,id2);
        //sqlite3_step(stmt);
       if(sqlite3_step(stmt) == SQLITE_ROW ){
           stringstream str;
            str << sqlite3_column_text(stmt, 0);
            str >> whoblock ;
            sqlite3_finalize(stmt);
        }
    }else{

          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
          // break the loop if error occur
      }
      return whoblock;
}

bool ConnectSQlite::CheckFriend(sqlite3 *db, int id1,int id2){
    int isFriend = 0;
    szSQL = "SELECT * FROM Friend WHERE ( id1 = ? AND id2 = ?) OR ( id1 = ? AND id2 = ?)";
    rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
      if( rc == SQLITE_OK ) {
            // bind the value
        sqlite3_bind_int(stmt,1,id1);
        sqlite3_bind_int(stmt,2,id2);
        sqlite3_bind_int(stmt,3,id2);
        sqlite3_bind_int(stmt,4,id1);
        // commit
       if(sqlite3_step(stmt) == SQLITE_ROW ){
           stringstream str;
            str << sqlite3_column_text(stmt, 0);
            str >> isFriend;

            if(isFriend != 0) isFriend = 1;
            else isFriend = 0;

            sqlite3_finalize(stmt);
        }
    }else{

          fprintf(stderr, "Check Friend SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
          // break the loop if error occur
      }
      return isFriend;
}

void ConnectSQlite::UpdateStatusFriend(sqlite3 *db,int status,int id1, int id2){
     if (!db)return ;
     int who = 0;
     if (status == 1) who = id1;

     szSQL = "UPDATE Friend SET RelationshipStatus = ? , whoblock = ? WHERE (id1 = ? AND id2 = ?) OR (id1 = ? AND id2 = ?)";
     rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
     if( rc == SQLITE_OK ) {
            // bind the value
        sqlite3_bind_int(stmt,1,status);
        sqlite3_bind_int(stmt,2,who);
        sqlite3_bind_int(stmt,3,id1);
        sqlite3_bind_int(stmt,4,id2);
        sqlite3_bind_int(stmt,5,id2);
        sqlite3_bind_int(stmt,6,id1);
        // commit
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);

    }else{

          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
          // break the loop if error occur
      }
}

void ConnectSQlite::WriteToMess(sqlite3 *db,int id1, int id2,char *mes,char *time){
         szSQL = "INSERT INTO messenger VALUES (?,?,?,?,1)";
         rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
         if( rc == SQLITE_OK ) {
                // bind the value
            sqlite3_bind_int(stmt,1,id1);
            sqlite3_bind_int(stmt,2,id2);
            sqlite3_bind_text(stmt,3,mes,strlen(mes),0);
            sqlite3_bind_text(stmt,4,time,strlen(time),0);
            // commit
            sqlite3_step(stmt);
            sqlite3_finalize(stmt);

        }else{

              fprintf(stderr, "writetomess SQL error: %s\n", zErrMsg);
              sqlite3_free(zErrMsg);
              // break the loop if error occur
          }

}


void ConnectSQlite::SelectMessenger(sqlite3 *db, int id){
    if (!db)return ;
    szSQL = "SELECT DISTINCT user.username FROM"
                "(SELECT * FROM messenger where idsen = ? ) as A LEFT JOIN user ON A.idrec = user.id";
    rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
    if( rc == SQLITE_OK ) {
            // bind the value
        sqlite3_bind_int(stmt,1,id);
        // commit
        while(sqlite3_step(stmt) == SQLITE_ROW) {
            answer.push_back(string((const char *) sqlite3_column_text(stmt, 0)));
        }
        sqlite3_finalize(stmt);
        cout <<"-----Danh sach tin nhan-------\n" ;
        for( list<std::string>::const_iterator it = answer.begin(); it != answer.end(); it++)
            cout << *it << endl;

    }else{

          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
          // break the loop if error occur
      }
}


void ConnectSQlite::ShowMessDetail(sqlite3 *db,int id1,int id2){
    if (!db)return ;
    cout << "--------Detail--------\n";
    szSQL = "SELECT * FROM (SELECT * FROM messenger WHERE (idsen = ? OR idsen = ?) AND (idrec = ? OR idrec =?) ) AS B LEFT JOIN  user ON user.id = B.idsen";
    rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
    // cout << id1 << id2;
    if( rc == SQLITE_OK ) {
            // bind the value
        sqlite3_bind_int(stmt,1,id1);
        sqlite3_bind_int(stmt,2,id2);
        sqlite3_bind_int(stmt,3,id1);
        sqlite3_bind_int(stmt,4,id2);
        // commit
        while(sqlite3_step(stmt) == SQLITE_ROW) {

                cout << "   " << string((const char *) sqlite3_column_text(stmt, 5)) << ": " <<  endl;
                cout << "       "<< string((const char *) sqlite3_column_text(stmt, 2)) << "-" ;
                cout << string((const char *) sqlite3_column_text(stmt, 3)) << endl ;

        }
        sqlite3_finalize(stmt);

    }else{

          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
          // break the loop if error occur
      }
}

void ConnectSQlite::ShowMessRec(int id1){
    if (!db)return ;
    cout << "-------Nhan--------\n";
    szSQL = "select u.username, m.contend,m.time from messenger m,User u where m.idrec = ? and u.id = m.idsen";
    rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
    // cout << id1 << id2;
    if( rc == SQLITE_OK ) {
            // bind the value
        sqlite3_bind_int(stmt,1,id1);
        // commit
        while(sqlite3_step(stmt) == SQLITE_ROW) {

                cout << "   " << string((const char *) sqlite3_column_text(stmt, 0)) << ": " <<  endl;
                cout << "       "<< string((const char *) sqlite3_column_text(stmt, 1)) << "-" ;
                cout << string((const char *) sqlite3_column_text(stmt, 2)) << endl ;

        }
        sqlite3_finalize(stmt);

    }else{

          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
          // break the loop if error occur
      }
}

void ConnectSQlite::ShowMessSen(int id1){
    if (!db)return ;
    cout << "-------Gui--------\n";
    szSQL = "select u.username, m.contend,m.time from messenger m,User u where m.idsen = ? and u.id = m.idrec";
    rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
    // cout << id1 << id2;
    if( rc == SQLITE_OK ) {
            // bind the value
        sqlite3_bind_int(stmt,1,id1);
        // commit
        while(sqlite3_step(stmt) == SQLITE_ROW) {

                cout << "   " << string((const char *) sqlite3_column_text(stmt, 0)) << ": " <<  endl;
                cout << "       "<< string((const char *) sqlite3_column_text(stmt, 1)) << "-" ;
                cout << string((const char *) sqlite3_column_text(stmt, 2)) << endl ;

        }
        sqlite3_finalize(stmt);

    }else{

          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
          // break the loop if error occur
      }
}

int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}
