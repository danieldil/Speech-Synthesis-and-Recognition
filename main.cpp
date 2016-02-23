#include "voce.h"
#include <QString>
#include <QDebug>
#include <QStringList>
#include <iomanip>
#include <cmath>
#include <stdlib.h>
#include <sstream>
#include "place.h"
#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
using namespace std;
int height = 0;//global variable for height
double latitude = 0;//global variable for latitude
double longitude = 0;//global variable for longitude
vector<string> strings;//global variable for all the strings spoken
bool nine = false;
bool eight = false;
//int setD = 0;
void ELP(){
    const int arraysize = 3;
    place arr[arraysize];
    arr[0].name = "california";
    arr[1].name = "texas";
    arr[2].name = "florida";

    arr[0].percent = rand() % 100;
    arr[1].percent = rand() % 100;
    arr[2].percent = rand() % 100;

    int highestindex = 0;
    if(arr[0].percent < arr[1].percent)
        highestindex = 1;
    if(arr[1].percent < arr[2].percent)
        highestindex = 2;

    boolean land = false;
    boolean been = false;
    int i = 1;

    while(!land){
        if(!been){
        string out = "the aircraft is now landing to " + arr[highestindex].name.toStdString() + " because it has " + QString::number(arr[highestindex].percent).toStdString() + " percent  chance of landing. Should it land? Say Yes or Enter 0 to land enter 9 or say no for other percentages";
     cout<<out<<endl;
     voce::synthesize(out);
     been = true;
        }
        string j = voce::popRecognizedString();
        cout<<j;

        //cin>>i;
     if(i == 0 || j == "yes"){
         land = true;
         cout<<" \nThank you now landing";
         voce::synthesize(" Thank you now landing");
        }
     else if(i == 9|| j == "no"){
         for(int i = 0; i < arraysize; i++){
             qDebug()<< "place: " <<arr[i].name;
             qDebug()<< "percent: "<<arr[i].percent;
             cout<<endl;
      }
    }
  }
}
QString getFirstWord(QString x){
    QStringList list1 = x.split(QRegExp("\\s"));
    x = list1[0];
    return x;
}
QString removeFirstWord(QString x){
    QStringList list1 = x.split(QRegExp("\\s"));
    x = "";
    for(int i = 0; i < list1.count()-1;i++)
    {
        x += list1[i+1]+" ";
    }
    return x;
}
int arr2int(QStringList nums,int arr[]){
    int number = 0;
    for(int i= 0; i< nums.count() ;i++){
        number += arr[i] * pow(10, nums.count() - i - 1);
    }
    return number;
}

void transformNums(QStringList nums){
    int *arr = new int [nums.count()];
    for(int i= 0; i < nums.count(); i++){                                                       //populate the int array
        if(nums[i] == "one"){
            arr[i] = 1;
        }
        else if(nums[i] == "two"){
            arr[i] = 2;
        }
        else if(nums[i] == "three"){
            arr[i] = 3;
        }
        else if(nums[i] == "four"){
            arr[i] = 4;
        }
        else if(nums[i] == "five"){
            arr[i] = 5;
        }
        else if(nums[i] == "six"){
            arr[i] = 6;
        }
        else if(nums[i] == "seven"){
            arr[i] = 7;
        }
        else if(nums[i] == "eight"){
            arr[i] = 8;
        }
        else if(nums[i] == "nine"){
            arr[i] = 9;
        }
    }
    height = arr2int(nums,arr);
    delete [] arr;
}
double transformNums(QStringList nums, string x){
    double *arr = new double [nums.count()];
    for(int i= 0; i < nums.count(); i++){
        if(nums[i] == "one"){
            arr[i] = 1;
        }
        else if(nums[i] == "two"){
            arr[i] = 2;
        }
        else if(nums[i] == "three"){
            arr[i] = 3;
        }
        else if(nums[i] == "four"){
            arr[i] = 4;
        }
        else if(nums[i] == "five"){
            arr[i] = 5;
        }
        else if(nums[i] == "six"){
            arr[i] = 6;
        }
        else if(nums[i] == "seven"){
            arr[i] = 7;
        }
        else if(nums[i] == "eight"){
            arr[i] = 8;
        }
        else if(nums[i] == "nine"){
            arr[i] = 9;
        }
        else if(nums[i] == "zero"){
            arr[i] = 0;
        }
        else{arr[i] = 0;}
    }
    double number = 0;
    for(int i= 0; i< nums.count() ;i++){
        number += arr[i] * pow(10, nums.count() - i - 1);
        //cout<< "arr[i] * pow(10, nums.count() - i - 1) is "<<arr[i] * pow(10, nums.count() - i - 1) <<endl;
        //cout<<"arr[i] is " << arr[i]<<endl;
        //cout<<number<<endl;
    }
    //cout<<number<<endl;
    delete [] arr;
    return number;
}

void transformL(QStringList L,boolean lat, boolean lon){
    //setD++;
    //either two digits before the decimal or three digits before the decimal
    boolean execute10,execute11 = false;
    if(L.count() == 10){
        execute10 = true;
    }
    if(L.count() == 11){
        execute11 = true;
    }

    if(execute10)
    {
    //qDebug()<<"this is the qstring before everything"<<L;
    boolean minus = false;
    if(L[0] == "minus"){
        minus = true;
    }
    L.removeFirst();
    QStringList bL;
    QStringList aL;
    bL.append(L[0]);
    bL.append(L[1]);
    double b = transformNums(bL,"");
    //qDebug()<<"THE SIZE OF AL before population"<<aL.count();
    aL.append(L[3]);
    aL.append(L[4]);
    aL.append(L[5]);
    aL.append(L[6]);
    aL.append(L[7]);
    L[8].chop(1);
    aL.append(L[8]);
    //qDebug()<<"the L[8] is "<<L[8];
    //qDebug()<<"THE SIZE OF AL after population"<<aL.count();
    double a = transformNums(aL,"");
    //cout<<transformNums(aL,"");
    //cout<<a;
    a = a * .000001;
    //cout<<a;
    double d = a+b;
    //qDebug()<<bL;
    //qDebug()<<aL;
   // cout<<b<<endl;
    //cout<<a<<endl;
    cout.precision(8);
    if(minus){
        d -= d*2;
    }
    cout<<"YOU HAVE SET IT TO "<<d;
    voce::synthesize("it has been set");
    if(lat){
        latitude = d;
    }
    if(lon){
        longitude = d;
    }

  }
    //**********************************************************
    if(execute11)
    {
    //qDebug()<<"this is the qstring before everything"<<L;
    boolean minus = false;
    if(L[0] == "minus"){
        minus = true;
    }
    L.removeFirst();
    QStringList bL;
    QStringList aL;
    bL.append(L[0]);
    bL.append(L[1]);
    bL.append(L[2]);
    double b = transformNums(bL,"");
    //qDebug()<<"THE SIZE OF AL before population"<<aL.count();
    aL.append(L[4]);
    aL.append(L[5]);
    aL.append(L[6]);
    aL.append(L[7]);
    aL.append(L[8]);
    L[9].chop(1);
    aL.append(L[9]);
    //qDebug()<<"the L[8] is "<<L[8];
    //qDebug()<<"THE SIZE OF AL after population"<<aL.count();
    double a = transformNums(aL,"");
    //cout<<transformNums(aL,"");
    //cout<<a;
    a = a * .000001;
    //cout<<a;
    double d = a+b;
    //qDebug()<<bL;
    //qDebug()<<aL;
   // cout<<b<<endl;
    //cout<<a<<endl;
    cout.precision(9);
    if(minus){
        d -= d*2;
    }
    cout<<"YOU HAVE SET IT TO "<<d;
    voce::synthesize("it has been set");
    if(lat){
        latitude = d;
    }
    if(lon){
        longitude = d;
    }

  }

    //**********************************************************
    else{
    cout<<"Invalid input. Format = +/- dd.dddddd";
  }
    if(longitude != 0 && latitude != 0){
        //CALL THE SETDESTINATION ON THE MAP
        cout<<"setDEST()";
    }
}

void manipCommand(QString qs){
    //first step search for the word 2
    //after the word 'to' will be the number except the last word
    //the last word is the measure
    boolean to = false;
    QStringList qsl = qs.split(QRegExp("\\s"));
    QStringList nums;
    for(int i = 0; i < qsl.count(); i++){
        if(qsl[i] == "to"){
         to = true;
         continue;
        }
        else if(i == qsl.count() -1 ){
         to = false;
         continue;
        }
        else if(to){
            nums += qsl[i];
            //qDebug()<<qsl[i];
        }
    }
    transformNums(nums);

}
void manipReport(QString str){
    QStringList list1 = str.split(QRegExp("\\s"));             //split it by every space and store each word into QStringList
    if(list1[1] == "height"){
    int xx = height;
    std::stringstream ss;   //convert the int height to a string
        ss << xx;
        string str1;
            ss >> str1;

    string j = "        The height is " + str1 + " feet ";
    cout<<j;
    voce::synthesize(j);
    }
    if(list1[1] == "latitude"){
    double xx = latitude;
    std::stringstream ss;   //convert the int height to a string
        ss << setprecision(8) << xx;
        string str1;
            ss >> str1;

    string j = "        The latitude is " + str1 + " feet ";
    cout<<j;
    voce::synthesize(j);
    }
    if(list1[1] == "longitude"){
    double xx = longitude;
    std::stringstream ss;   //convert the int height to a string
        ss << setprecision(8) << xx;
        string str1;
            ss>> str1;

    string j = "        The longitude is " + str1 + " feet ";
    cout<<j;
    voce::synthesize(j);
    }
    if(list1[1] == "destination"){
    double xx = longitude;
    std::stringstream ss;   //convert the int height to a string
        ss << setprecision(8) << xx;
        string str1;
            ss>> str1;

    string j = "        The longitude is " + str1 + " feet ";
    cout<<j;
    voce::synthesize(j);
    xx = latitude;
    std::stringstream ss1;   //convert the int height to a string
        ss1 << setprecision(8) << xx;
        str1;
            ss1 >> str1;

    j = "        The latitude is " + str1 + " feet ";
    cout<<j;
    voce::synthesize(j);
    }

}
void manipSet(QString str){
    boolean latitude = false;
    boolean longitude = false;
    str = removeFirstWord(str);
    QStringList qsl = str.split(QRegExp("\\s"));
    if(qsl[0] == "latitude"){latitude = true;}
    if(qsl[0] == "longitude"){longitude = true;}
    QString L = "";
    for(int i = 0; i<qsl.count()-2;i++)
    {
        L += qsl[i+2]+" ";
        if(i == qsl.count()-3)
        {
            L.chop(2);
            L +=".";
        }
    }
    transformL(L.split(QRegExp("\\s")),latitude,longitude);
  //  transformL(L.split(QRegExp("\\s")),!latitude,!longitude);
}

string Out(QStringList strL){
    //this function we will be recieving the QSlist and making the sentence past tense
    //returns the string in past tense and std string format.

    //DELETE THE LAST LETTER OF A QSTRING with this if statement
    if(strL[0][strL[0].count()-1] == 'e'){
        strL[0].chop(1);
    }
    //create the past tense output
    QString x = "       Roger that " + strL[0] + "ing";
    for(int i = 1; i < strL.count(); i++){
        x += (" " + strL[i]);
    }
    return x.toStdString();
}
void manipString(QString x){
    QString word = getFirstWord(x);
    if      (word == "emergency"){ELP();}
    else if (word == "change"||word == "fly"||word == "ascend"||word == "descend"){
        QStringList list1 = x.split(QRegExp("\\s"));             //split it by every space and store each word into QStringList
        string pTense = Out(list1);
        cout<<pTense<<endl;
        voce::synthesize(pTense);
        manipCommand(x);
    }
    else if (word == "report"){
        manipReport(x);
    }
    else if(word == "set"){manipSet(x);}
    else{
        cout<<"invalid input";
    }
}
int main(int argc, char **argv)
{
    system("color F0");
    voce::init("C:/voce-0.9.1/lib", true, true,"file:/C:/voce-0.9.1/samples/recognitionTest/c++/grammar", "digits");

    bool quit = false;
    while (!quit)
    {
#ifdef WIN32
        ::Sleep(200);
#else
        usleep(200);
#endif
        //TO CHANGE FROM TEXT INPUT TO SPEECH INPUT
        //1. CHANGE THE 3RD PARAMETER TO TRUE IN THE INIT()
        //2. COMMENT OUT THE GETLINE CALL
        //3. uncomment the while recognizer que and the x = poprecognized string.
        //4. line 28 of the elp function uses the voice
          vector<string> strings;
          while(voce::getRecognizerQueueSize() > 0)
            {
                string x = "null";                                           //instantiate a string
               cout<<"\nListening"<<endl;
               x = voce::popRecognizedString();
             //getline(cin, x);                                                //get input
                cout << "You said: " << x << endl;
                strings.push_back(x);
                if(x == "quit" || x == "thank you"){quit = true;}

                QString qstr = QString::fromStdString(x);                    //convert string to QString
                manipString(qstr);
            }
        }
    voce::destroy();
    return 0;
}

