#include <bits/stdc++.h>
#include "we4.h"

using namespace std;
sem_t sem;
User us = User();
int main(){
while(1){


            cout << "-------Chon chuc nang: ------\n"
                "1.Dang ky\n"
                "2.Dang nhap\n"
                "3.Hien thi tin nhan\n"
                "4.Hien thi chi tiet tin nhan\n"
                "5.Hien thi  tin nhan nhan duc\n"
                "6.Hien thi tin nhan da gui\n"
                "7.Gui tin nhan\n"
                "8.Them ban be\n"
                "9.Hien thi ban be\n"
                "10.Hien thi ban be theo thanh pho\n"
                "11.Chinh sua thong tin ban be\n"
                "12.Dang xuat\n"
                "-----------------------\n";

        int choose;
        cin >> choose;

        string s[100];
        switch(choose){
            case 1:
                us.SignUp();
                break;
            case 2:
                us.SignIn();
                break;
        /*
            case 3:
                us.ShowMess(us.id);
                break;
            case 4:
                us.ShowMessDetail(us.id);
                break;
            case 5:
                us.ShowMessRec(us.id);
                break;
            case 6:
                us.ShowMessSen(us.id);
                break;
            case 7:
                us.SendMess(us.id);
                break;
        */
            case 3:{
               // extern sem_t sem;
                //cout <<"main: " <<  &sem;
                sem_init(&sem, 0,1);
               // extern sem_t mutex;
                void *arg = &us.id;
                //cout << " OK.\n";
                pthread_t t1,t2;
                pthread_create(&t1,NULL,threadsendmess,arg);

               // sleep(1);
                pthread_create(&t2,NULL,threadshowmess,arg);
                pthread_join(t1,NULL);
                pthread_join(t2,NULL);
              //  sleep(2);
                }
                break;
            case 4:
                us.AddFriend(us.id);
                break;
            case 9:
                us.ShowFriend(us.id,s);
                break;
            case 10:
                us.ShowFriendByCity(us.id);
            case 11:
                us.EditInfoFriend(us);
              //  us.BlockFriend(us.id);
                break;
            case 12:
                 us.SignOut();
                break;

            default:
                cout << "Xin moi nhap lai\n";
                break;

        }
}
return 0;
}
