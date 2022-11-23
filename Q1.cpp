#include<conio.h>
#include<string.h>
#include<iostream>
#include <iomanip>   
#include<fstream>
#include<ctime>
#include<windows.h> 
using namespace std;
class EarnedMoney{
    private:
        int carType;
        int busType;
        int trcukType;
        int bikeType;
        int cycleType;
        int total;
    public:
        EarnedMoney(){
            carType=0;
            busType=0;
            trcukType=0;
            bikeType=0;
            cycleType=0;
            total=0;
        }
        void setEarnedMoney(int car,int bus,int trcuk,int bike,int cycle,int tot){
            carType=car;
            busType=bus;
            trcukType=trcuk;
            bikeType=bike;
            cycleType=cycle;
            total=tot;
        }
        void showEarnedMoney(){
            cout<<"\n--------------------------------------------------------------\n";
            cout<<setw(10)<<"Car|"<<setw(10)<<"Bus|"<<setw(10)<<"Truck|"<<setw(10)<<"Bike|"<<setw(10)<<"Cycle|"<<setw(10)<<"Total|";
            cout<<"\n--------------------------------------------------------------\n";
            cout<<setw(9)<<carType<<"|"<<setw(9)<<busType<<"|"<<setw(9)<<trcukType<<"|"<<setw(9)<<bikeType<<"|"<<setw(9)<<cycleType<<"|"<<setw(9)<<total<<"|";
            cout<<"\n--------------------------------------------------------------\n";
        }
        void getAllEarnedMoney();
        friend void addTwoMoney(EarnedMoney,EarnedMoney&);
};
void EarnedMoney:: getAllEarnedMoney(){
    ifstream fin;
    fin.open("aaEarnedMonry.txt",ios_base::in|ios_base::binary);
    if(!fin){
        cout<<"\nFile Not Found";
    }
    else{
        fin.read((char*)this,sizeof(*this));
        //this->showEarnedMoney();
    }
}
void addTwoMoney(EarnedMoney oldMoney,EarnedMoney &newMoney){
    newMoney.carType+=oldMoney.carType;
    newMoney.busType+=oldMoney.busType;
    newMoney.trcukType+=oldMoney.trcukType;
    newMoney.bikeType+=oldMoney.bikeType;
    newMoney.cycleType+=oldMoney.cycleType;
    newMoney.total+=oldMoney.total;
}
class VehicleType{
    private:
        char vehicleTypeName[50];
    public:
        VehicleType(){
            strcpy(vehicleTypeName,"Vehicle");
        }
        void setVehivleType(EarnedMoney &earnedMoney){
            while(1){
                cout<<"\nSelect Vehicle Type:";
                cout<<"\n1. Car  2. Bus  3. Truck  4. Bike  5. Cycle\n";
                int vehicleType;
                cin>>vehicleType;
                if(vehicleType==1){
                    strcpy(this->vehicleTypeName,"Car");
                    earnedMoney.setEarnedMoney(100,0,0,0,0,100);
                    break;
                }
                else if(vehicleType==2){
                    strcpy(vehicleTypeName,"Bus");
                    earnedMoney.setEarnedMoney(0,200,0,0,0,200);
                    break;
                }
                else if(vehicleType==3){
                    strcpy(vehicleTypeName,"Truck");
                    earnedMoney.setEarnedMoney(0,0,400,0,0,400);
                    break;
                }
                else if(vehicleType==4){
                    strcpy(vehicleTypeName,"Bike");
                    earnedMoney.setEarnedMoney(0,0,0,50,0,50);
                    break;
                }
                else if(vehicleType==5){
                    strcpy(vehicleTypeName,"Cycle");
                    earnedMoney.setEarnedMoney(0,0,0,0,20,20);
                    break;
                }
                else{
                    cout<<"\nInvalid Choice:";
                }
            }
        }
        void showVehicleType(){cout<<vehicleTypeName<<"  ";}
};

class Vehicle:public VehicleType{
    private:
        int vehicleNo;
        char driversName[30];
        char description[100];
        char lastUpdatedBy[50];
        float stayTime;
        EarnedMoney earnedMoney;
    public:
        Vehicle(){
            vehicleNo=0;
            strcpy(driversName,"default");
            strcpy(description,"default");
            strcpy(lastUpdatedBy,"default");
            
        }
        void setVehicle(){
            cout<<"\nEnter The Vehicle Number: ";
            cin>>vehicleNo;
            cin.ignore();
            
            cout<<"\nEnter Drivers Name: ";
            cin.getline(driversName,30);
            
            cout<<"\nEnter The Vehicle Description: ";
            cin.getline(description,100);
            
            
            cout<<"\nSystem last updated by: ";
            cin.getline(lastUpdatedBy,50);
            
            setVehivleType(earnedMoney);
            
        }
        
        void showVehicle(){
        	cout<<"\n\tVEHICLE DETAILS ARE:"<<endl;
            cout<<"\nVehicle Number:"<<vehicleNo;
			cout<<"\nDivers Name:"<<driversName;
            cout<<"\nDescription:"<<description;
            cout<<"\nVehicle Type:";showVehicleType();
            cout<<"\nSystem Updated By:"<<lastUpdatedBy<<endl;
            //earnedMoney.showEarnedMoney();
        }
        void addVehicle();
        void getAllVehicleList();
        void searchVehicle(int vno);
};
void Vehicle:: addVehicle(){
    ofstream fout;
    fout.open("aaVehivleData.txt",ios_base::app|ios_base::binary);
    getch();
    fout.write((char*)this,sizeof(*this));
    fout.close();

    EarnedMoney em;
    em.getAllEarnedMoney();
    addTwoMoney(em,this->earnedMoney);
    fout.open("aaEarnedMonry.txt",ios_base::out|ios_base::binary);
    fout.write((char*)(&this->earnedMoney),sizeof(this->earnedMoney));
    fout.close();
    cout<<"\nRecord Added Successfully\n";
}
void Vehicle:: getAllVehicleList(){
    ifstream fin;
    int nor=0;
    fin.open("aaVehivleData.txt",ios_base::in|ios_base::binary);
    if(!fin){
        cout<<"\nFile Not Found";
    }
    else{
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof()){
            this->showVehicle();
            nor++;
            fin.read((char*)this,sizeof(*this));
        }
        fin.close();
        if(nor==0){
            cout<<"\nFile Has No Record:";
        }
    }
}
void Vehicle:: searchVehicle(int vno){
    ifstream fin;
    int nor=0;
    fin.open("aaVehivleData.txt",ios_base::in|ios_base::binary);
    if(!fin){
        cout<<"\nFile Not Found";
    }
    else{
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof()){
            if(this->vehicleNo==vno){
                this->showVehicle();
                nor=1;
                break;
            }
            fin.read((char*)this,sizeof(*this));
        }
        fin.close();
        if(nor==0){
            cout<<"\nRecord Not Found:";
        }
    }
}

int menu(){
    int ch;
    cout<<"\n\tWelcome to Vehicle Parking System\n";
    cout<<"\n1. Add Vehicle";
    cout<<"\n2. Search Vehicle";
    cout<<"\n3. List All Vehicle";
    cout<<"\n4. Check Earned Money";
    cout<<"\n5. Exit";
    cout<<"\n\nEnter Your Choice: ";
    cin>>ch;
    return(ch);
}
void Intro(){
    char intro[200]="\t\tOOP Theory Project\n\t\tSubmitted By - Joydeep Saha\n\t\tSubmitted to - Abinas Panda";
    for(int i=0;i<strlen (intro);i++){
        cout<<intro[i];
        Sleep(100);
    }
    Sleep(2000);
}

int main(){
    system("CLS");
    Intro();
    Vehicle vehicle;
    EarnedMoney earnedMoney;
    int breakInfiniteloop=0,vno;
    while(1){
        system("CLS");
        switch(menu()){
            case 1:
                vehicle.setVehicle();
                vehicle.addVehicle();
                getch();
                break;
            case 2:
                cout<<"\nEnter The Vehicle Number To Searched: ";
                cin>>vno;
                vehicle.searchVehicle(vno);
                getch();
                break;
            case 3:
                vehicle.getAllVehicleList();
                getch();
                break;
            case 4:
                earnedMoney.getAllEarnedMoney();
                earnedMoney.showEarnedMoney();
                getch();
                break;
            case 5:
                breakInfiniteloop=1;
                break;
            default:
                cout<<"\nInvalid Choice \nPress any key to continue";
                getch();
        }//end of switch
        if(breakInfiniteloop==1){
            break;
        }
    }//end of infinite loop1

    return(0);
}