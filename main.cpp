#include <iostream>
#include<string>
#include <fstream>
#include<stdlib.h>
#include<sstream>
#include<math.h>
#include<cmath>
#include<map>
#include"BST.h"
#include"Date.h"
#include"Vector.h"
#include"DataCollector.h"
#include"Time.h"
#include"AmbAirTemp.h"
#include"SolarRadiation.h"

using namespace std;

typedef struct
{
    Date d;
    Time t;
    AmbAirTemp a;
    float speed;
    SolarRadiation sr;
} WeatherLogType;

typedef struct
{
    Date date;
}Key; // A struct which will hold the key of the map

void Layout()
{
    cout<<endl<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
    cout<<"MENU"<<endl;
    cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
    cout<<"Option 1: Display the average wind speed and sample deviation"<<endl;
    cout<<"Option 2: Display the average ambient air temperature and sample deviation for months of year"<<endl;
    cout<<"Option 3: Display the SOLAR RADIATION IN kWh/m2 for months of year"<<endl;
    cout<<"Option 4: Display the WIND SPEED(km/h), AVERAGE AMBIENT AIR TEMP. AND SOLAR RADI.(kWh/m2) for months of year"<<endl;
    cout<<"Option 5: Display the highest solar radiation for a Date"<<endl;
    cout<<"Option 6: EXIT"<<endl;
    cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
}



ostream& operator<<(ostream& osObject, const WeatherLogType obj) // << overloading the << operator for data class
{
    osObject<<obj.d.GetDay()<<"/"<<obj.d.GetMonth()<<"/"<<obj.d.GetYear()<<" "<<obj.t.GetHour()<<":"<<obj.t.GetMinute()<<endl;

    return osObject;
}

bool operator==(const WeatherLogType obj1, const WeatherLogType obj2) // == overloading
{
    bool same = false;

        if(obj1.d.GetYear()==obj2.d.GetYear()&&obj1.d.GetMonth()==obj2.d.GetMonth()&&obj1.d.GetDay()==obj2.d.GetDay()&&obj1.t.GetHour()==obj2.t.GetHour()&&obj1.t.GetMinute()==obj2.t.GetMinute()){
            same = true;
        }
    return same;
}

bool operator==(const Key date1, const Key date2) // == overloading
{
    bool same = false;

        if(date1.date.GetDay()==date2.date.GetDay()&&date1.date.GetMonth()==date2.date.GetMonth()&&date1.date.GetYear()==date2.date.GetYear()){
            same = true;
        }
    return same;
}


bool operator>(const WeatherLogType obj1, const WeatherLogType obj2) // > overloading the > operator for the objects from structs
{
    bool large = false;

        //Used for insertion into the BST
        if(obj1.d.GetYear()>obj2.d.GetYear()){ // Items will be sorted according to name length
            large = true;
        }
        else if(obj1.d.GetYear()==obj2.d.GetYear()&&obj1.d.GetMonth()>obj2.d.GetMonth()){
            large = true;
        }
        else if(obj1.d.GetYear()==obj2.d.GetYear()&&obj1.d.GetMonth()==obj2.d.GetMonth()&&obj1.d.GetDay()>obj2.d.GetDay()){
            large = true;
        }
        else if(obj1.d.GetYear()==obj2.d.GetYear()&&obj1.d.GetMonth()==obj2.d.GetMonth()&&obj1.d.GetDay()==obj2.d.GetDay()&&obj1.t.GetHour()>obj2.t.GetHour()){
            large = true;
        }
        else if(obj1.d.GetYear()==obj2.d.GetYear()&&obj1.d.GetMonth()==obj2.d.GetMonth()&&obj1.d.GetDay()==obj2.d.GetDay()&&obj1.t.GetHour()==obj2.t.GetHour()&&obj1.t.GetMinute()>obj2.t.GetMinute()){
            large = true;
        }
    return large;
}

bool operator<(const Key date1, const Key date2) // > overloading
{

    bool large = false;

    //Used for insertion into the BST
        if(date1.date.GetYear()<date2.date.GetYear()){ // Items will be sorted according to name length
            large = true;
        }
        else if(date1.date.GetYear()==date2.date.GetYear()&&date1.date.GetMonth()<date2.date.GetMonth()){
            large = true;
        }
        else if(date1.date.GetYear()==date2.date.GetYear()&&date1.date.GetMonth()==date2.date.GetMonth()&&date1.date.GetDay()<date2.date.GetDay()){
            large = true;
        }

    return large;
}

unsigned Convert(string fix)
{
    unsigned num;
    istringstream convert(fix);
    convert>>num;
    return num;
}


float ConvertF(string fix)
{
    stringstream ss;
    ss<<fix;
    float numF;
    ss>>numF;
    return numF;
}

float TotalSR(const Vector<float> &array)//Calculates the total solar radiation in kWh/m2
{
    float sum = 0;

    for(int i=0;i<array.GetLength();i++)
    {
        sum += array[i]; //Add up all the elements in the array passed as parameter
    }

    sum = (sum/1000)/6; //Converts into kWh/m2 from W/m2
    return sum; //returns the total solar radiation in kWh/m2
}

float CalculateAverage(Vector<float>& tempLog)
{
    float sum = 0;
    for(int i=0; i<tempLog.GetLength(); i++)
    {
        sum = sum + tempLog[i];
    }

    return sum/tempLog.GetLength();
}

float CalculateSD(Vector<float>& tempLog)
{
    float sum = 0;
    float ave = CalculateAverage(tempLog);

    for(int i=0; i<tempLog.GetLength(); i++)
    {
        sum = sum + (tempLog[i]-ave)*(tempLog[i]-ave);
    }

    return sqrt(sum/tempLog.GetLength());

}

void case1(map<Key, BST<WeatherLogType>> WeatherMap)
{
        unsigned month=0;
        unsigned year=0;

         while(month<1 || month>12)
        {
            cout<<endl<<"Please enter the month : "<<endl;
            cin>>month;
        }

        cout<<"Please enter the year: "<<endl;
        cin>>year;

        Date date;

        string strMonth = date.ConvertMonthToString(month);
        cout<<endl<<strMonth<<" "<<year<<": "<<endl;

        DataCollector<WeatherLogType> data1;
        map<Key,BST<WeatherLogType>>::iterator itr;
        BST<WeatherLogType> dataTree;
        Vector<float> spdata; //Array which will hold the wind speed data of given year and month

        Key key;
        Key tempKey;
        key.date.SetYear(year);
        key.date.SetMonth(month);

        for(itr=WeatherMap.begin();itr!=WeatherMap.end();itr++)//Loops throughout the length of weatherlog
        {
              tempKey = itr->first;
              if(tempKey.date.GetYear()==year&&tempKey.date.GetMonth()==month)
              { //If the key matches with the Year and Month of the BST, collect data from that BST
              dataTree = WeatherMap.at(tempKey);
              dataTree.inorderTraversal(DataCollector<WeatherLogType>::vectorCollect);
              }
        }

        for(int i=0;i<data1.size();i++){
            if(!isnan(data1[i].speed)){ //If speed is not NAN
            spdata.pushIn(data1[i].speed*3.6); //If they match, insert data in the end of the array
            }
        }

        if(spdata.GetLength()<5)
        {
            cout<<"No Data"<<endl;
        }
        else
        {
        if(CalculateAverage(spdata)==0)
        {
            cout<<"No Data"<<endl; //If there is no data in the array, display "No data"
        }
        else
        {
            float speedAve = CalculateAverage(spdata); //Calculates the wind speed average of the given year and month
            float speedSD = CalculateSD(spdata); //Calculates the standard deviation of the windspeed of the given year and month

            cout<<"Average speed: "<<speedAve<<"km/h"<<endl; //Displays wind speed average
            cout<<"Sample stdev: "<<speedSD<<endl; //Displays the standard deviation of the windspeed
        }
        }
        data1.deleteData(); //Clears the items in the collector vector which is static for reuse
}





void case2(map<Key, BST<WeatherLogType>> WeatherMap)
{
        unsigned year=0;
        cout<<endl<<"Please enter the year: "<<endl;
        cin>>year;

        DataCollector<WeatherLogType> data2;
        map<Key,BST<WeatherLogType>>::iterator itr;
        BST<WeatherLogType> dataTree;
        Vector<WeatherLogType> yeardata; //An array which will hold the data of a given year

        Key key;
        Key tempKey;
        key.date.SetYear(year);

        for(itr=WeatherMap.begin();itr!=WeatherMap.end();itr++)
        { //Loops throughout the length of weatherlog
            tempKey = itr->first;
               if(tempKey.date.GetYear()==year)
               { //If key matches with the Year of a BST, collect data from that BST
                   dataTree = WeatherMap.at(tempKey);
                   dataTree.inorderTraversal(DataCollector<WeatherLogType>::vectorCollect);
               }
        }

        for(int i=0;i<data2.size();i++)
        {
            if(!isnan(data2[i].a.GetAmbAirTemp())) //If temperature value is not NAN
            {
            yeardata.pushIn(data2[i]); //Insert the data of the whole year in a vector
            }
        }

        cout<<endl<<year<<": "<<endl; //Display the year

        if(yeardata.GetLength()<5)
        {
            cout<<"No Data"<<endl;
        }
        else
        {
        for(int i=1;i<=12;i++) //Loop through each month
        {
            Vector<float> tempdata; //Array which will hold the data for each month
            Date date;
            string month = date.ConvertMonthToString(i);

            for(int j=0;j<yeardata.GetLength();j++)
                {
                if(yeardata[j].d.GetMonth()==i)
                {
                    tempdata.pushIn(yeardata[j].a.GetAmbAirTemp()); //If the month data matches the one being looped, insert the temperature data into the end of the array
                }
            }

            if(tempdata.GetLength()<5)
            {
                cout<<month<<": No Data"<<endl;
            }
            else
            {
            if(CalculateAverage(tempdata)==0)
            {
                cout<<month<<": No Data"<<endl; //Display "No Data" when there is no data for a specific month
            }
            else
            {
            float tempave = CalculateAverage(tempdata); //Calculates the average of the temperature of each month
            float tempSD = CalculateSD(tempdata); //Calculates the standard deviation of the temperature of each month

            cout<<month<<": Average: "<<tempave<<" degree C, "<<"Stdev: "<<tempSD<<endl; //Display the results
            }
            }
        }
        }
        data2.deleteData(); //Clears collector vector which is static for reuse
}


void case3(map<Key, BST<WeatherLogType>> WeatherMap)
{
        unsigned year=0;
        cout<<endl<<"Please enter the year: "<<endl;
        cin>>year;

        DataCollector<WeatherLogType> data3;
        map<Key,BST<WeatherLogType>>::iterator itr;
        BST<WeatherLogType> dataTree;
        Vector<WeatherLogType> yeardata; //An array which will hold the data of a given year

        Key key;
        Key tempKey;
        key.date.SetYear(year);

        for(itr=WeatherMap.begin();itr!=WeatherMap.end();itr++) //Loops throughout the length of weatherlog
            {
                tempKey = itr->first;
                if(tempKey.date.GetYear()==year) //If key matches with the Year of a BST, collect data from that BST
                {
                    dataTree = WeatherMap.at(tempKey);
                    dataTree.inorderTraversal(DataCollector<WeatherLogType>::vectorCollect);
                }
            }

        for(int i=0;i<data3.size();i++)
        {
            yeardata.pushIn(data3[i]); //Insert the data of the whole year in a vector
        }

        cout<<endl<<year<<": "<<endl; //Display the year

        float srTotal;

        if(yeardata.GetLength()<5)
        {
            cout<<"No Data"<<endl;
        }

        else
        {
        for(int i=1;i<=12;i++)
        {
            Vector<float> srdata; //Array which will hold solar radiation data of each month being looped
            for(int j=0;j<yeardata.GetLength();j++){
                if(yeardata[j].d.GetMonth()==i&&yeardata[j].sr.GetSolarRadi()>=100)//If month value matches and solar radiation is bigger than 100
                {
                    if(!isnan(yeardata[j].sr.GetSolarRadi()))//If solar radiation is not NAN
                    {
                    srdata.pushIn(yeardata[j].sr.GetSolarRadi()); //If the month matches the one being looped and solar radiation is larger than 100, insert into the end of the array
                    }
                }
            }

            Date date;
            string srMonth = date.ConvertMonthToString(i); //Convert month number into string

            if(TotalSR(srdata)==0)
            {
                cout<<srMonth<<": "<<"No Data"<<endl; //Display "No Data" if there is no that for specific month
            }

            else
            {
            srTotal = TotalSR(srdata); //Calculate the total solar radiation of each month in kWh/m2
            cout<<srMonth<<": "<<srTotal<<" kWh/m2"<<endl; //Display the results
            }
        }
        }
        data3.deleteData(); //Clears collector vector which is static for reuse
}

void case4(map<Key, BST<WeatherLogType>> WeatherMap)
{
        unsigned year=0;
        cout<<endl<<"Please enter the year: "<<endl;
        cin>>year;
        cout<<endl<<year<<": "<<endl; //Display the year

        DataCollector<WeatherLogType> data4;
        map<Key,BST<WeatherLogType>>::iterator itr;
        BST<WeatherLogType> dataTree;
        Vector<WeatherLogType> yeardata; //An array which will hold the data of a given year

        Key key;
        Key tempKey;
        key.date.SetYear(year);

        for(itr=WeatherMap.begin();itr!=WeatherMap.end();itr++)
        { //Loops throughout the length of weatherlog
                tempKey = itr->first;
                if(tempKey.date.GetYear()==year)
                { //If key matches with the Year of a BST, collect data from that BST
                    dataTree = WeatherMap.at(tempKey);
                    dataTree.inorderTraversal(DataCollector<WeatherLogType>::vectorCollect);
                }
        }

        for(int i=0;i<data4.size();i++)
        {
            yeardata.pushIn(data4[i]); //Insert the data of the whole year in a vector
        }

        ofstream ofile("WindTempSolar.csv"); //csv file which data will be put in
         // write the file headers
        ofile << "Year/month" <<","<< "Average wind speed(Stdev win speed)"<<"," << "Average Ambient temperature(Stdev Amb temp)"<<","<< "Solar Radiation" << endl;
        ofile <<year<<endl;
        if(yeardata.GetLength()<5)
        {
            cout<<"No Data"<<endl; //Displays "No Data" if the given year contains no data
            ofile<<"No Data"<<endl;
        }

        else
        {
            for(int i=1; i<=12; i++)
            { //Loops through each month
                Vector<WeatherLogType> monthdata; //Array which will hold data of the month being looped
                Vector<float> speeddata; //Array which will hold wind speed data of the month being looped
                Vector<float> srdata; //Array which will hold solar radiation data of the month being looped
                Vector<float> tempdata; //Array which will hold temperature data of the month being looped

                Date date;
                string tempMonth = date.ConvertMonthToString(i); //Converts month number into string

                for(int k=0;k<yeardata.GetLength();k++)
                { //Loops throught out the year array
                    if(yeardata[k].d.GetMonth()==i)
                    {
                        monthdata.pushIn(yeardata[k]); //If the month in the year array matches with the one being looped, insert month data in the array
                    }
                }

                if(monthdata.GetLength()<5)
                {
                    cout<<""; //Does not display anything when the month contains no data
                    ofile<<"";
                }

                else
                {
                for(int j=0; j<monthdata.GetLength(); j++)
                {
                    if(!isnan(monthdata[j].speed)) //If speed data is not NAN
                    {
                    speeddata.pushIn(monthdata[j].speed*3.6); //Inserts the wind speed data of the month being looped in the array
                    }

                    if(monthdata[j].sr.GetSolarRadi()>=100 && !isnan(monthdata[j].sr.GetSolarRadi()))//If solar radiation data is bigger than 100 and is not NAN
                    {
                        srdata.pushIn(monthdata[j].sr.GetSolarRadi()); //Inserts the solar radiation data of the month being looped in the array
                    }

                    if(!isnan(monthdata[j].a.GetAmbAirTemp())) //If temperature data is not NAN
                    {
                    tempdata.pushIn(monthdata[j].a.GetAmbAirTemp()); //Inserts the temperature data of the month being looped in the array
                    }
                }

                cout<<tempMonth<<",";
                ofile<<tempMonth<<",";

                float spave = CalculateAverage(speeddata); //Calculates the average wind speed
                float spsd = CalculateSD(speeddata); //Calculates the standard deviation of the wind speed
                if(spave==0)
                {
                    cout<<","; //Prints a comma when wind speed does not contain data
                    ofile<<",";
                }

                else
                {
                    cout<<spave<<"("<<spsd<<"),";
                    ofile<<spave<<"("<<spsd<<")"<<",";
                }

                float tempave = CalculateAverage(tempdata); //Calculates the average temperature
                float tempsd = CalculateSD(tempdata); //Calculates the standard deviation of the temperature

                if(tempave==0)
                {
                    cout<<","; //Prints a comma when temperature does not contain data
                    ofile<<",";
                }

                else
                {
                    cout<<tempave<<"("<<tempsd<<"),";
                    ofile<<tempave<<"("<<tempsd<<")"<<",";
                }

                float totalsr = TotalSR(srdata); //Calculates the total solar radiation
                if(totalsr==0)
                {
                    cout<<""<<endl; //Prints a comma when solar radiation does not contain data
                    ofile<<""<<endl;
                }
                else
                {
                    cout<<totalsr<<endl;
                    ofile<<totalsr<<endl;
                }
                }
            }
        }
        data4.deleteData(); //Clears the collector vector which is static for reuse
        ofile.close();
}


void case5(map<Key, BST<WeatherLogType>> WeatherMap)
{
        unsigned day=0;
        unsigned month=0;
        unsigned year=0;
        float largest = 0; //Temporary value to hold the largest solar radiation value

        cout<<endl<<"Please enter the DAY: "<<endl;
        cin>>day;
        cout<<"Please enter the MONTH: "<<endl;
        cin>>month;
        cout<<"Please enter the YEAR: "<<endl;
        cin>>year;

        DataCollector<WeatherLogType> data5;
        map<Key,BST<WeatherLogType>>::iterator itr;
        BST<WeatherLogType> dataTree;
        Vector<WeatherLogType> daydata; //An array which will hold the data of a given year

        Key key;
        Key tempKey;
        key.date = Date(day,month,year);

        for(itr=WeatherMap.begin();itr!=WeatherMap.end();itr++) //Loops throughout the length of weatherlog
        {
                tempKey = itr->first;
                if(tempKey.date.GetYear()==year&&tempKey.date.GetMonth()==month&&tempKey.date.GetDay()==day) //If the Date matches with a BST, collect data from that BST
                {
                    dataTree = WeatherMap.at(tempKey);
                    dataTree.inorderTraversal(DataCollector<WeatherLogType>::vectorCollect);
                }
        }
        if(data5.size()<5){
                cout<<"No data"<<endl;
        }
        else{
        for(int i=0;i<data5.size();i++){
            if(data5[i].sr.GetSolarRadi()>=100&&!isnan(data5[i].sr.GetSolarRadi())) //If solar radiation is bigger than 100 and is not NAN
            {
            daydata.pushIn(data5[i]); //Insert the data of the whole year in a vector
            }
        }

            for(int i=0;i<daydata.GetLength();i++)
            {
                if(daydata[i].sr.GetSolarRadi()>largest) //If it is bigger than temporary largest value, assign that to largest
                {
                    largest = daydata[i].sr.GetSolarRadi();
                }
            }

            cout<<endl<<"Date: "<<day<<"/"<<month<<"/"<<year<<endl;
            cout<<"Highest solar radiation of the day: "<<largest<<"W/m2"<<endl;
            cout<<"Time: "<<endl;

            for(int i=0;i<daydata.GetLength();i++)
            {
                if(daydata[i].sr.GetSolarRadi()==largest) //If there are more than one value, prints out all of them
                {
                    cout<<daydata[i].t.GetHour()<<":"<<daydata[i].t.GetMinute()<<endl;
                }
            }
        }
        data5.deleteData(); //Clears the collector vector which is static for reuse
}




void readFile(map<Key,BST<WeatherLogType>>& WeatherMap)
{
    string dump;
    const string folder ="./data/";
    ifstream listOffiles;
    listOffiles.open("./data/met_index.txt");

    if(!listOffiles)
    {
        cout<<"Error with file";
        exit(-1);
    }
    else
    {        while(!listOffiles.eof())
        {

            string docName;
            getline(listOffiles,docName,'\n');
            cout<<docName;
            string path =  folder +  docName;
            ifstream infile;
            infile.open(path);

    if(!infile)
    {
        cout<<"Error with file";
        exit(-1);
    }
    else
    {
        getline(infile,dump);
        while(!infile.eof())
        {
            unsigned day;
            unsigned month;
            unsigned year;
            string line;
            unsigned hour;
            unsigned minute;
            float AirTemp;
            unsigned speed;
            unsigned SR;


            /* DAY */
            getline(infile,line,'/');
            day = Convert(line);
            /* MONTH */
            getline(infile,line,'/');
            month = Convert(line);
            /* YEAR */
            getline(infile,line,' ');
            year = Convert(line);
            /* HOUR */
            getline(infile,line,':');
            hour = Convert(line);
            /* MINUTE */
            getline(infile,line,',');
            minute = Convert(line);

            for(int k=0;k<9;k++){ //Ignores non neceessary data between minute and wind speed
                infile.ignore(9,',');
            }
            /* S */
            getline(infile,line,',');
            speed = Convert(line);
            for(int i=0;i<line.length();i++){
                if(isdigit(line[i])==false){ //Sets speed as NAN if not a digit
                    speed = NAN;
                }
            }
            /* SR */
            getline(infile,line,',');
            SR = Convert(line);
            for(int i=0;i<line.length();i++){
                if(isdigit(line[i])==false){ //Sets solar radiation as NAN if not a digit
                    SR = NAN;
                }
            }

            for(int i=0;i<5;i++){ //Ignores non necessary data between solar radiation and temperature
            getline(infile,line,',');
            }
            /* T */
            getline(infile,line,'\n');
            AirTemp = ConvertF(line);
                if(isdigit(line[0])==false){ //Sets temperature as NAN if not a digit
                    AirTemp = NAN;
                }

            if(infile.eof()){ //Breaks the loop when end of the file is reached
                break;
            }
            //temporary object to store each line got from file and
            // to dump in the fixed object vector object weatherLog passed by parameter
            WeatherLogType record;
            record.speed = speed;
            record.t = Time(hour,minute);
            record.d = Date(day,month,year);
            record.a = AmbAirTemp(AirTemp);
            record.sr = SolarRadiation(SR);

            Key key; //Key object
            key.date = Date(day,month,year);//Assign the values read from the file to the key object

            if(WeatherMap.find(key)==WeatherMap.end()/*returns the end of the map if not found*/)
            {
                BST<WeatherLogType> ValueAsBst;
                ValueAsBst.insertNode(record);
                WeatherMap.insert(pair<Key,BST<WeatherLogType>>(key,ValueAsBst));
            }
            else // If the date is found as a key in the map
            {
            WeatherMap[key].insertNode(record); // Insert into the existing value which is a bst
            }

    }//end of while
        infile.close();
    }//end of else
        cout<<" File read"<<endl;
    } //end of while in listOFfiles
    }//end of elselistOFfiles
        listOffiles.close();
    }//end of read file read files

int main()
{
    map<Key ,BST<WeatherLogType>> WeatherMap; //key: year, value: BST BST<Vector<WeatherLogType>>
    //read the file and pass the object weatherLog to be loaded

    readFile(WeatherMap);

    int menu = 0;

    while(menu>1 || menu<5)
    {
        Layout();

        cout<<"Please, enter the menu option:"<<endl;
        cin>>menu;

        switch (menu)
        {

        case 1:
          case1(WeatherMap);
        break;

        case 2:
            case2(WeatherMap);
        break;

        case 3:
            case3(WeatherMap);
        break;

        case 4:
            case4(WeatherMap);
        break;

        case 5:
            case5(WeatherMap);
        break;

        case 6:
            cout<<"You quit! Thank you";
            exit(0);

        }//end of switch

    }//end of while

    return 0;

}//end of main












