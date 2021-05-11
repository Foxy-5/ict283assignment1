#include "date.h"
#include "Time.h"
#include "myvector.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
//---------------------------------------------------------------------
using namespace std;
//declare windlogtype struct
typedef struct {
    date d;
    Time t;
    float speed;
    float solarRad;
    float aAirTemp;
} WindLogType;
//declare all the functions for file reading
void readFile(MyVector<WindLogType> & WindLog);
void printMenu();
void option1(MyVector<WindLogType> & WindLog);
void option2(MyVector<WindLogType> & WindLog);
void option3(MyVector<WindLogType> & WindLog);
void option4(MyVector<WindLogType> & WindLog);
void option5(MyVector<WindLogType> & WindLog);
void menuOption(MyVector<WindLogType> & WindLog);
//void printVector(MyVector<WindLogType> & WindLog); //for testing only!!

int main()
{
    MyVector<WindLogType> WindLog;
    cout << "Loading file please wait a moment\n";
    readFile(WindLog);
    printMenu();
    menuOption(WindLog);
    return 0;
}
//function to read in file and store data into windlog vector
void readFile(MyVector<WindLogType> & WindLog)
{
    ifstream infile;
    string datafile = "data/MetData-31-3.csv";
    infile.open(datafile);
    infile.ignore(500,'\n');
    cout << "Loading file: " << datafile << endl;
    if(infile.is_open())
    {
        while(!infile.eof())
        {
            date tempDate;
            Time tempTime;
            float tempSpeed,tempSolarRad,TempAAirTemp;
            if(infile.peek() == '\n')   //checking for blank lines
            {
                infile.ignore(500,'\n');    //skip line if blank
            }
            else
            {
                infile >> tempDate >> tempTime; //read in and store date and time
                for (int i = 0; i < 10; i++)    //skip 10 columns for speed
                {
                    infile >> tempSpeed;    //store speed
                    infile.ignore(50,',');  //skip the ,
                }
                infile >> tempSolarRad; //store solar radiation
                for (int i = 0;i <6; i++)   //skip 6 columns for air temp
                {
                    infile.ignore(50,',');  //skip ,
                }
                infile >> TempAAirTemp; //store air temp

                WindLogType TempWindLog;    //create temp windlog for storage
                TempWindLog.d = tempDate;   //assign into struct
                TempWindLog.t = tempTime;
                TempWindLog.speed = tempSpeed;
                TempWindLog.solarRad = tempSolarRad;
                TempWindLog.aAirTemp = TempAAirTemp;
                WindLog.push_back(TempWindLog);     //store into windlog vector
                infile.ignore(500,'\n');    //go to next line
            }
        }
    }
}
void printMenu()
{
    cout << "--------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Please select a option 1 - 5\n";
    cout << "1. The average wind speed and average ambient air temperature for a specified month and year. (print on screen only)\n";
    cout << "2. Average wind speed and average ambient air temperature for each month of a specified year. (print on screen only)\n";
    cout << "3. Total solar radiation in kWh/m2 for each month of a specified year. (print on screen only)\n";
    cout << "4. Average wind speed (km/h), average ambient air temperature and total solar radiation in kWh/m2\n"
         << "   for each month of a specified year. (write to a file called WindTempSolar.csv)\n";
    cout << "5. exit the program.\n";
}

void option1(MyVector<WindLogType> & WindLog)
{
    //option to print out average wind speed and average ambient air temperature
    //for a specified month and year.
    float tempSpeed, tempATemp;
    int m, y, count = 0;
    WindLogType tempWindLog;
    cout << fixed << setprecision(1);
    cout << "Enter the month (in integer): ";
    cin >> m;
    cout << "\nEnter the year: ";
    cin >> y;

    for(int i=0;i<WindLog.getCount();i++)   //retrieve data stored in windlog vector
    {
        tempWindLog = WindLog.at(i);
        if(m == tempWindLog.d.getMonth() && y == tempWindLog.d.getYear())   //checking if month and year is stored
        {                                                                   //in the vector
            tempSpeed = tempSpeed + tempWindLog.speed;                      //adding all the speed up
            tempATemp = tempATemp + tempWindLog.aAirTemp;                   //adding all the air temp up
            count++;
        }
    }
    tempSpeed = (tempSpeed/count) * 3.6;    //getting the average speed and convert it
    tempATemp = tempATemp/count;            //getting the average air temp

    if(count != 0)  //check if empty
    {   //print out the required data
        cout << tempWindLog.d.monthConvert(m) << " " << y << ": " << tempSpeed << " km/h, " << tempATemp << " degrees C\n";
    }
    else
    {   //print out if no data is front
        cout << tempWindLog.d.monthConvert(m) << " " << y << ": No Data\n";
}
    }
void option2(MyVector<WindLogType> & WindLog)
{
    //option to print out average wind speed and average ambient air temperature for each month
    //of a specific year
    int y = 0;
    double convertedSpeed;
    cout << fixed << setprecision(1);

    cout << "\nEnter the year: ";
    cin >> y;

    for(int m=1;m<13;m++)   //for loop for month
    {
        float totalSpeed = 0;
        float totalTemp = 0;
        float avgSpeed = 0;
        float avgTemp = 0;

        MyVector<float> SpeedVector;
        MyVector<float> TemperatureVector;

        for(int i=0;i<WindLog.getCount();i++)   //retrieve data from vector
        {
            if(WindLog.at(i).d.getMonth() == m && WindLog.at(i).d.getYear() == y)   //checking for month and year in vector
            {   //storing the data needed
                SpeedVector.push_back(WindLog.at(i).speed);
                TemperatureVector.push_back(WindLog.at(i).aAirTemp);
                totalSpeed = totalSpeed + WindLog.at(i).speed;
                totalTemp = totalTemp + WindLog.at(i).aAirTemp;
            }
        }
        date tempdate;
        if(!SpeedVector.isEmpty() == 1 && !TemperatureVector.isEmpty() == 1)    //checking if data is empty
        {
            avgSpeed = totalSpeed / SpeedVector.getCount();     //getting average speed
            avgTemp = totalTemp / TemperatureVector.getCount(); //getting average temperature
            convertedSpeed = avgSpeed * 3.6;                    //convert the speed to km/h
            //print out the data
            cout << tempdate.monthConvert(m) << ": " << convertedSpeed << " km/h, "
                    << avgTemp << " degrees C\n";
        }
        else
        {   //print out no data found
            cout << tempdate.monthConvert(m) << ": No Data\n";
        }
    }
}
void option3(MyVector<WindLogType> & WindLog)
{
    int y;
    cout << "Please enter the year: ";
    cin >> y;

    for(int m = 1;m<13;m++) //loop for all months
    {
        float totalSolar = 0;
        float convertSolar = 0;
        MyVector<float> tempSolar;

        for(int i=0;i<WindLog.getCount();i++)   //retrieve data
        {
            if(WindLog.at(i).d.getMonth() == m && WindLog.at(i).d.getYear() == y) //checking for month and year
            {
                if(WindLog.at(i).solarRad >= 100)                       //checking if solar radiation is more than 100
                {
                    tempSolar.push_back(WindLog.at(i).solarRad);        //store all the solar radiation data in vector
                    totalSolar = totalSolar + WindLog.at(i).solarRad;   //add up all the solar radiation in the vector
                }
            }
        }
        date tempdate;
        if(!tempSolar.isEmpty() == 1)   //checking if data is stored in vector
        {
            convertSolar = totalSolar / 6000;   //converting solar radiation to kWh/m2
            //print out the data required
            cout << tempdate.monthConvert(m) << ": " << fixed << setprecision(1) << convertSolar << " kWh/m^2\n";
        }
        else
        {   //print out no data found
            cout << tempdate.monthConvert(m) << ": No Data\n";
        }
    }
}
void option4(MyVector<WindLogType> & WindLog)
{
    int y;
    cout << "Please enter the year: ";
    cin >> y;
    ofstream outfile;
    outfile.open("WindTempSolar.csv");
    int NoOfEmptydata = 0;
    outfile << y << endl;
    for(int m=1;m<13;m++)   //loop for all the months
    {
        float totalSpeed = 0;
        float totalTemp = 0;
        float avgSpeed = 0;
        float convertedSpeed = 0;
        float avgTemp = 0;
        float totalSolar = 0;
        float convertSolar = 0;

        MyVector<float> tempSolar;
        MyVector<float> SpeedVector;
        MyVector<float> TemperatureVector;
        for(int i=0;i<WindLog.getCount();i++)   //retrieve the stored data
        {
            if(WindLog.at(i).d.getMonth() == m && WindLog.at(i).d.getYear() == y) //checking for month and year
            {
                SpeedVector.push_back(WindLog.at(i).speed);             //storing of all speed into a vector
                TemperatureVector.push_back(WindLog.at(i).aAirTemp);    //storing of all temperature into a vector
                totalSpeed = totalSpeed + WindLog.at(i).speed;          //getting the total speed
                totalTemp = totalTemp + WindLog.at(i).aAirTemp;         //getting the total temperature
                if(WindLog.at(i).solarRad >= 100)                       //filter out solar radiation for greater than 100
                {
                    tempSolar.push_back(WindLog.at(i).solarRad);        //storing of solar radiation
                    totalSolar = totalSolar + WindLog.at(i).solarRad;   //getting the total solar radiation
                }
            }
        }
        date tempdate;
        //checking if all data are present
        if(!SpeedVector.isEmpty() == 1 && !TemperatureVector.isEmpty() == 1 && !tempSolar.isEmpty() == 1)
        {
            avgSpeed = totalSpeed / SpeedVector.getCount();             //getting the average speed
            avgTemp = totalTemp / TemperatureVector.getCount();         //getting the average temperature
            convertedSpeed = avgSpeed * 3.6;                            //converting the average speed
            convertSolar = totalSolar / 6000;                           //converting the total solar radiation
            outfile << fixed << setprecision(1);
            //store the required data into the output file
            outfile << tempdate.monthConvert(m) << "," << convertedSpeed << "," << avgTemp << "," << convertSolar << endl;
        }
        else
        {
            outfile << tempdate.monthConvert(m) << ",No Data\n";        //if no data found for that month print no data
            NoOfEmptydata++;                                            //counter for fully no data year
        }
    }
    outfile.close();                    //close the output file
    if(NoOfEmptydata == 12)             //checking if year has no data
    {   //write over the output file with no data
        ofstream outfile;
        outfile.open("WindTempSolar.csv");
        outfile << y << endl;
        outfile << "NO DATA\n";
        outfile.close();
    }
    cout << "Data have been written to WindTempSolar.csv\n";
}
void option5()
{   //option to exit program
    cout << "End of program\n";
    exit(0);    //closes the program
}
void menuOption(MyVector<WindLogType> & WindLog)
{   //prompt for user input in what options they require
    cout << "Please enter (1-5): ";
    int option = 0;
    cin >> option;
    while(option < 1 || option > 5 || cin.fail())   //checking for valid input 1-5 only
    {
        cout << "Invalid option please try again\n";
        cin.clear();
        cin.ignore(255,'\n');
        cin >> option;
    }
    if(option == 1)
    {
        option1(WindLog);
    }
    else if(option == 2)
    {
        option2(WindLog);
    }
    else if(option == 3)
    {
        option3(WindLog);
    }
    else if(option == 4)
    {
        option4(WindLog);
    }
    else
    {
        option5();
    }
}
//Function only used for testing (checking if storage is working as intended)
/*
void printVector(MyVector<WindLogType> & WindLog)
{
    WindLogType tempLog;
    for(int i=0;i<WindLog.getCount();i++)
    {
        tempLog = WindLog.at(i);
        cout << tempLog.d.getDay() << "/" << tempLog.d.getMonth() << "/" << tempLog.d.getYear() << " "
             << tempLog.t.GetHour() << ":" << tempLog.t.GetMinute() << "," << tempLog.speed << ","
             << tempLog.solarRad << "," << tempLog.aAirTemp << endl;
    }
}
*/
