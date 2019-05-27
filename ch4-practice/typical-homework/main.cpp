#include <iostream>
#include <cstdio>
#include <cstring>
#include <string.h>
#include <algorithm>
#include <vector>

#define EPS 1e-5
#define maxs 105
//105 students

#define maxid 105
//15 digits

using namespace std;


//int n;
//int removed[maxs] = {0};

int subject[6];
//subject[1] pass subject 1 --> subject[2] pass subject 2
int lastid = 0;

typedef struct Students
{
    bool removed;
    char sid[maxid];
    int cid;
    char name[maxid];

    int chinese;
    int math;
    int english;
    int coding;

//    int rank;
    int totscore;

    bool operator < (const Students& s) const{
        return totscore > s.totscore;
    }
    Students()
    {
        memset(this,0,sizeof(Students));
    }
}students;

typedef struct Klass
{
    int totstu;

    int score[4];
    int pass[4];

    Klass()
    {
        memset(this,0,sizeof(Klass));
    }

}klass;

//vector<klass> kl(maxs);

klass kl[maxs + 5];
vector<students> stu;


bool valid(students fresh)
{
    vector<students>::iterator it;
    for(it = stu.begin(); it != stu.end(); it++)
    {
        if(! (*it).removed )
        {
            if(strcmp((*it).sid, fresh.sid) == 0)
                return 0;
        }

    }
    return 1;
}

void add()
{
    for(;;)
    {
        students fresh;
        printf("Please enter the SID, CID, name and four scores. Enter 0 to finish.\n");
        scanf("%s",fresh.sid);

        if(strcmp(fresh.sid, "0") == 0)
            break;

        scanf("%d%s%d%d%d%d",&fresh.cid,fresh.name,&fresh.chinese,&fresh.math,&fresh.english,&fresh.coding);

        if(valid(fresh))
        {
            fresh.totscore = fresh.chinese + fresh.math + fresh.english + fresh.coding;
            fresh.removed = 0;

            int k = fresh.cid;
            kl[k].score[0] += fresh.chinese;
            kl[k].score[1] += fresh.math;
            kl[k].score[2] += fresh.english;
            kl[k].score[3] += fresh.coding;

            if(fresh.chinese >= 60)   kl[k].pass[0]++;
            if(fresh.math >= 60)  kl[k].pass[1]++;
            if(fresh.english >= 60)   kl[k].pass[2]++;
            if(fresh.coding >= 60)    kl[k].pass[3]++;

            kl[k].totstu++;
            stu.push_back(fresh);
        }
        else
            printf("Duplicated SID.\n");
    }
}
//add() finished!

int getrank(students cur)
{
    int r = 0;

    vector<students>::iterator it;
    for(it = stu.begin(); ((*it).sid != cur.sid) && it != stu.end(); it++)
    {
        if(!((*it).removed) && (*it).totscore > cur.totscore)
            r++;
    }
    return r+1;
}
//rank() finished
//求学生排名的方法，遍历所有的学生，每遇到一个比自己成绩高的，rank++

void DQ(int isq)
{
    for(;;)
    {
        char choose[maxs];
        printf("Please enter SID or name. Enter 0 to finish.\n");
        scanf("%s",choose);

        if(strcmp(choose,"0") == 0)
            break;

        int cal = 0;
        vector<students>::iterator it;
        for(it = stu.begin(); it != stu.end(); it++)
        {
            if(!(*it).removed)
            {
//                cout << stu[i].sid << "-->" << choose << endl;
//                cout << stu[i].name << "-->" << choose << endl;
                if(strcmp((*it).sid,choose) == 0 || strcmp((*it).name,choose) == 0 )
                {
                    if(isq)
                        //printf("%d %s %d %s %d %d %d %d %d %.2f\n", stu[i].rank, stu[i].sid, stu[i].cid, stu[i].name,stu[i].chinese,stu[i].math,stu[i].english,stu[i].coding,stu[i].totscore,stu[i].totscore/4.0+EPS);
                        printf("%d %s %d %s %d %d %d %d %d %.2f\n",getrank(*it),(*it).sid, (*it).cid, (*it).name,(*it).chinese,(*it).math,(*it).english,(*it).coding,(*it).totscore,(*it).totscore/4.0+EPS);
                    else
                    {
                        (*it).removed = 1;

                        //removed students also infect klass
                        int rid = (*it).cid;

                        kl[rid].totstu--;
                        kl[rid].score[0] -= (*it).chinese;
                        kl[rid].score[1] -= (*it).math;
                        kl[rid].score[2] -= (*it).english;
                        kl[rid].score[3] -= (*it).coding;

                        if((*it).chinese >= 60) kl[rid].pass[0]--;
                        if((*it).math >= 60) kl[rid].pass[1]--;
                        if((*it).english >= 60) kl[rid].pass[2]--;
                        if((*it).coding >= 60) kl[rid].pass[3]--;

                        cal++;
                    }
                }
//                if(!isq)
//                    printf("%d student(s) removed.\n",cal);
            }
        }

        if(!isq)
            printf("%d student(s) removed.\n",cal);

    }
}
//DQ test finished!

void overall_stat(int check)
{
    memset(subject, 0, sizeof(subject));
    vector<students>::iterator it;
    for(it = stu.begin(); it != stu.end(); it++)
    {
        if(!(*it).removed && (check == 0 || (*it).cid == check))
        {
            int k = 0;
            if((*it).chinese >= 60) k++;
            if((*it).math >= 60) k++;
            if((*it).english >= 60) k++;
            if((*it).coding >= 60) k++;

            subject[k]++;
        }
    }
//    for(int i = 0; i < 6; i++)
//        printf("pass %d : %d ", i , subject[i]);
}
//test finished




void stat()
{
    int check;
    printf("Please enter class ID, 0 for the whole statistics.\n");
    scanf("%d",&check);


    if(check != 0)
    {
        printf("Chinese\n");
        printf("Average Score: %.2f\n",(double)kl[check].score[0]/(double)kl[check].totstu+EPS);
        printf("Number of passed students: %d\n",kl[check].pass[0]);
        printf("Number of failed students: %d\n",kl[check].totstu-kl[check].pass[0]);
        printf("\n");

        printf("Mathematics\n");
        printf("Average Score: %.2f\n",(double)kl[check].score[1]/(double)kl[check].totstu+EPS);
        printf("Number of passed students: %d\n",kl[check].pass[1]);
        printf("Number of failed students: %d\n",kl[check].totstu-kl[check].pass[1]);
        printf("\n");

        printf("English\n");
        printf("Average Score: %.2f\n",(double)kl[check].score[2]/(double)kl[check].totstu+EPS);
        printf("Number of passed students: %d\n",kl[check].pass[2]);
        printf("Number of failed students: %d\n",kl[check].totstu-kl[check].pass[2]);
        printf("\n");

        printf("Programming\n");
        printf("Average Score: %.2f\n",(double)kl[check].score[3]/(double)kl[check].totstu+EPS);
        printf("Number of passed students: %d\n",kl[check].pass[3]);
        printf("Number of failed students: %d\n",kl[check].totstu-kl[check].pass[3]);
        printf("\n");
    }
    else
    {
        int s1=0, s2=0, s3=0, s4=0;
        int p1=0, p2=0, p3=0, p4=0;

        int m = 0;
        vector<students>::iterator it;
        for(it = stu.begin(); it != stu.end(); it++)
        {
            if(!(*it).removed )
            {
                m++;
                s1 += (*it).chinese;
                s2 += (*it).math;
                s3 += (*it).english;
                s4 += (*it).coding;

                if((*it).chinese >= 60)    p1++;
                if((*it).math >= 60)   p2++;
                if((*it).english >= 60)    p3++;
                if((*it).coding >= 60)     p4++;
            }
        }

        printf("Chinese\n");
        printf("Average Score: %.2f\n",(double)s1/(double)m+EPS);
        printf("Number of passed students: %d\n",p1);
        printf("Number of failed students: %d\n",m-p1);
        printf("\n");

        printf("Mathematics\n");
        printf("Average Score: %.2f\n",(double)s2/(double)m+EPS);
        printf("Number of passed students: %d\n",p2);
        printf("Number of failed students: %d\n",m-p2);
        printf("\n");

        printf("English\n");
        printf("Average Score: %.2f\n",(double)s3/(double)m+EPS);
        printf("Number of passed students: %d\n",p3);
        printf("Number of failed students: %d\n",m-p3);
        printf("\n");

        printf("Programming\n");
        printf("Average Score: %.2f\n",(double)s4/(double)m+EPS);
        printf("Number of passed students: %d\n",p4);
        printf("Number of failed students: %d\n",m-p4);
        printf("\n");

    }

    overall_stat(check);
    printf("Overall:\n");
    printf("Number of students who passed all subjects: %d\n",subject[4]);
    printf("Number of students who passed 3 or more subjects: %d\n",subject[3]+subject[4]);
    printf("Number of students who passed 2 or more subjects: %d\n",subject[2]+subject[3]+subject[4]);
    printf("Number of students who passed 1 or more subjects: %d\n",subject[1]+subject[2]+subject[3]+subject[4]);
    printf("Number of students who failed all subjects: %d\n",subject[0]);
    printf("\n");
}

void print_menu()
{
    printf("Welcome to Student Performance Management System (SPMS).\n");
    printf("\n");
    printf("1 - Add\n");
    printf("2 - Remove\n");
    printf("3 - Query\n");
    printf("4 - Show ranking\n");
    printf("5 - Show Statistics\n");
    printf("0 - Exit\n");
    printf("\n");
}

//void printdata(int n)
//{
//    for(int i = 0; i < n; i++)
//    {
//        printf("%s %d %s %d %d %d %d %d rank: %d\n",stu[i].sid,stu[i].cid,stu[i].name,stu[i].chinese,stu[i].math,stu[i].english,stu[i].coding,stu[i].totscore,stu[i].rank);
//    }
//}



int main()
{
    for( ; ; )
    {
        int choice;
        print_menu();
        scanf("%d",&choice);



        if(choice == 0)
            break;
        if(choice == 1)
        {
            add();
//        cout << stucnt;
//            getrank(cnt);
//            getklass(cnt);
//            cout << cnt << " students "<< endl;
        }

//        for(int i = 0; i < cnt; i++)
//            printf("students %s ",stu[i].name);
//        printf("\n removed: ");
//        for(int i = 0; i < cnt; i++)
//            printf("%d ",removed[i]);

//        sort(stu,stu+cnt);

//        printdata(cnt);
//        printf("\n");


//        printf("enter check : ");
//        int check;
//        scanf("%d",&check);
//        overall_stat(cnt,check,subject);

        if(choice == 2)
            DQ(0);
        if(choice == 3)
            DQ(1);

        if(choice == 4)
            printf("Showing the ranklist hurts students' self-esteem. Don't do that.\n");
        if(choice == 5)
            stat();

    }
}
