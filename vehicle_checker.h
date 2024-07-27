typedef struct 
{
    int registrationNumber;
    char vehicleType;
    char modelName[50];
    char ofname[50];
    char olname[50];
    int year;
    char state[10];
    

} vehicle;

typedef struct 
{
    char fname[20];
    char lname[20];
    int DOBM;
    int DOBD;
    int DOBY;
    char gender;
    char un[100];
    char password[100];
    long long int phn;
    long long int recovphn;
} account;

void Account();
void addVehicle();
void updateVehicle();
void deleteVehicle();
void checkVehicle();
void accountDetail();
void menu();