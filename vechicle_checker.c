#include<stdio.h>
#include<stdlib.h>
#include"vehicle_checker.h"
#include <string.h>
char usnm[50],pass[50];
void menu(){
	
    int choice;
     
    while(1){
    printf("\033[36m\n\t\tHi %s. Welcome to Vehicle Registration\n\n",usnm);
    rechoice:
    printf("\033[36m1.Add Vehicle    \t\t\t\t 2.Update Vehicle\n\n");
    printf("3.Remove Vehicle \t\t\t\t 4.Check Vehicle Status\n\n");
    printf("5.Log out        \t\t\t\t 6.Account Details\n\n");
    printf("7.Exit\033[0m\n\n");
    printf("Enter Your Choice: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
    addVehicle();
    break;
    case 2:
    updateVehicle();
    break;
    case 3:
    deleteVehicle();
    break;
    case 4:
    checkVehicle();
    break;
    case 5:
    Account();
    break;
    case 6:
    accountDetail();
    break;
    case 7:
    exit(0);
    break;

    default:
    	system("cls");
    printf("\033[31mInvalid option Try Again.\033[0m\n\n");
    goto rechoice;
    break;
}
}
}
int checkregnum(int reg){
	if(reg<=9999){
		return 1;
	}
	else{
		return 0;
	}
}
int checkPassword(char pass[100]){
    int upperCase=0,symbols=0,numbers=0,letter=0,i;
    
    for(i=0;pass[i]!='\0';i++){
        if(pass[i]>=65&&pass[i]<=90){
            upperCase++;
        }
        else if(pass[i]>=32&&pass[i]<=47||pass[i]>=58&&pass[i]<=64||pass[i]>=91&&pass[i]<=96||pass[i]>=123&&pass[i]<=126){
            symbols++;
        }
        else if(pass[i]>=48&&pass[i]<=57){
            numbers++;
        }
        else{
            letter++;
        }
    }
    if(upperCase>0&&letter>0&&numbers>0&&symbols>0&&strlen(pass)>=8){
        return 1;
    }
    else{
        return 0;
    }
}
int phnumberchecker(long long int ph){
    int digit=0;
    while(ph!=0){
        ph/=10;
        digit++;
    }
    if(digit==10){
        return 1;
    }
    else{
        return 0;
    }
}
char user[50],pass[50];
void login() {
    char ch, yn;
    system("cls");
    printf("\t\tSign in\n");
    char username[100], password[100];
    int found = 0;
    account a;
    FILE *sign;

    sign = fopen("acc.txt", "r");
    if (sign == NULL) {
        printf("\033[31mError Opening File.\033[0m");
        return;
    }

rem:
    printf("Enter Username: ");
    scanf("%s", username);
    strcpy(usnm, username);

    int i = 0;
    printf("Enter Password:");
    while ((ch = _getch()) != 13) {
        if (ch == 8) {
            if (i > 0) {
                i--;
                password[i] = '\0';
                printf("\b \b");
            }
        } else {
            password[i] = ch;
            printf("*");
            i++;
        }
    }
    password[i] = '\0';

    system("cls");
    printf("Do you want to show password?(y/n)");
    scanf(" %c", &yn);
    if (yn == 'y') {
        printf("Password: %s\n", password);
    }
    strcpy(pass, password);

    rewind(sign);
    while (fread(&a, sizeof(account), 1, sign)) {
        if (strcmp(username, a.un) == 0 && strcmp(password, a.password) == 0) {
            found = 1;
            printf("\033[32mLogin Successfully\033[0m\n\n");
            break;
        }
    }
    fclose(sign);

    if (found == 0) {
        printf("\033[31mIncorrect username or password.\033[0m\n");
    recov:
        printf("\033[36m1. Forgot Password?\t\t2. Try again\n3. Cancel\n\033[0m");
        printf("Enter Your choice: ");
        int c;
        scanf("%d", &c);
        switch (c) {
            case 1:
                system("cls");
                printf("\033[36m\t\tRecovery Mode\n\n\033[0m");
                account recovery[100];
                long long int recphn;
                char newp[100], confp[100];
                int found = 0;
                int rec = 0;
				int i;
                printf("Enter Recovery Phone number: ");
                scanf("%lld", &recphn);
                sign = fopen("acc.txt", "r");
                if (sign == NULL) {
                    printf("\033[31mError Opening File.\033[0m");
                    exit(0);
                }
                while (fread(&recovery[rec], sizeof(account), 1, sign)) {
                    if (recovery[rec].recovphn == recphn) {
                        found = 1;
                    new:
                    	i=0;
                        printf("Enter New Password: ");
                        while ((ch = _getch()) != 13) {
        if (ch == 8) {
            if (i > 0) {
                i--;
                newp[i] = '\0';
                printf("\b \b");
            }
        } else {
            newp[i] = ch;
            printf("*");
            i++;
        }
    }
    newp[i] = '\0';
	i=0;
                        printf("\nConfirm password: ");
                        while ((ch = _getch()) != 13) {
        if (ch == 8) {
            if (i > 0) {
                i--;
               confp[i] = '\0';
                printf("\b \b");
            }
        } else {
            confp[i] = ch;
            printf("*");
            i++;
        }
    }
    confp[i] = '\0';
    char choice;
    printf("\nDo you want to show password(y/n)?\n");
    scanf(" %c",&choice);
    if(choice=='y'){
    	printf("New Password:%s\nConfirm Password:%s\n\n",newp,confp);
	}
                        if (strcmp(newp, confp) == 0) {
                            if (checkPassword(confp) == 0) {
                                printf("\033[31mPlease Use letter, UpperCase, symbols and numbers. Try Again: \033[0m");
                                goto new;
                            } else {
                                strcpy(recovery[rec].password, confp);
                            }
                        }
                        else{
                        	printf("\033[31mPassword Doesnot match.\n\n\033[0m");
                        	goto recov;
                        	
						}
                    }
                    rec++;
                }
                fclose(sign);

                if (found == 1) {
                    sign = fopen("acc.txt", "w");
                    if (sign == NULL) {
                        printf("\033[31mError Opening File.\033[0m");
                        exit(0);
                    }
                    for ( i = 0; i < rec; i++) {
                        fwrite(&recovery[i], sizeof(account), 1, sign);
                    }
                    fclose(sign);
                    printf("\033[32mSuccessfully Changed. Please Login to continue...\n\n\033[0m");
                    Account();
                } else {
                    printf("\033[31mThis Recovery PH number Does not Exist.\n\033[0m");
                    Account();
                }
                break;
            case 2:
                system("cls");
                goto rem;
                break;
            case 3:
                system("cls");
                Account();
                break;
            default:
                system("cls");
                printf("\033[31mInvalid option. Please Try Again.\n\033[0m");
                goto recov;
        }
    }
}

void signup() {
    char ch, yn;
    int i;
    system("cls");
    printf("\033[36m\t\tNew Account\n\033[0m");
    account s;
    FILE *newAcc;

    newAcc = fopen("acc.txt", "a");
    if (newAcc == NULL) {
        printf("\033[31mError Opening File.\033[0m");
        return;
    }

    printf("First Name:");
    scanf("%s", s.fname);
    printf("Last Name: ");
    scanf("%s", s.lname);

    printf("Date of Birth info\n");
    printf("Year(1963-2024): ");
yr:
    scanf("%d", &s.DOBY);
    if (s.DOBY < 1963 || s.DOBY > 2024) {
        printf("\033[31mIncorrect format. Please re-enter(1963-2024): \033[0m");
        goto yr;
    }

    printf("Month: ");
mo:
    scanf("%d", &s.DOBM);
    if (s.DOBM > 12) {
        printf("\033[31mIncorrect format. Please re-enter(0-12): \033[0m");
        goto mo;
    }

    printf("Date: ");
dt:
    scanf("%d", &s.DOBD);
    if (s.DOBD > 30) {
        printf("\033[31mIncorrect format. Please re-enter(0-30): \033[0m");
        goto dt;
    }

    printf("Gender(m for Male, f for Female, o for others):\n");
gen:
    printf("Enter your gender: ");
    scanf(" %c", &s.gender);
    if (s.gender != 'm' && s.gender != 'f' && s.gender != 'o') {
        printf("\033[31mIncorrect format. Please try again.\033[0m");
        goto gen;
    }

    printf("Create a User Name: ");
    scanf("%s", s.un);

    printf("Create a Strong password Using letter, UpperCase, symbols, and numbers: ");
repass:
    i = 0;
    while ((ch = _getch()) != 13) {
        if (ch == 8) {
            if (i > 0) {
                i--;
                s.password[i] = '\0';
                printf("\b \b");
            }
        } else {
            s.password[i] = ch;
            printf("*");
            i++;
        }
    }
    s.password[i] = '\0';

    printf("\nDo you want to show the password?(y/n): ");
    scanf(" %c", &yn);
    if (yn == 'y') {
        printf("Password: %s\n", s.password);
    }

    if (checkPassword(s.password) == 0) {
        printf("\033[31mPlease Use letter, UpperCase, symbols, and numbers. Try Again: \033[0m");
        goto repass;
    }

    printf("Phone Number:+977 ");
reph:
    scanf("%lld", &s.phn);
    if (phnumberchecker(s.phn) == 0) {
        printf("\033[31mIncorrect Format. Please Try Again:+977 \033[0m");
        goto reph;
    }

    printf("Enter Recovery Phone Number:+977 ");
recovph:
    scanf("%lld", &s.recovphn);
    if (phnumberchecker(s.recovphn) == 0) {
        printf("\033[31mIncorrect Format. Please Re-enter:+977 \033[0m");
        goto recovph;
    }

    fwrite(&s, sizeof(account), 1, newAcc);
    fclose(newAcc);
    printf("\033[32mCreated Successfully.\n\033[0m");
    Account();
}

void Account(){
    int choice;
    printf("\t\tVehicle Registration Management\n\n");
    rechoice: ;
    printf("1.Sign Up\t\t\t\t\t2.Login\n\n3.Exit\n\n");
    printf("Enter Choice: ");
    scanf("%d",&choice);
    switch (choice)
    {
    case 1:
        signup();
        break;
    case 2:
    login();
   break;
   case 3:
   exit(0);
   break;
    default:
        printf("\033[31mIncorrect option.Re-Enter your choice.\n\033[0m");
        goto rechoice;
        break;
}
}
void accountDetail(){
	system("cls");
    printf("\033[36m\t\tAccount Detail\n\n\033[0m");
    account act;
    FILE *acc;
    acc=fopen("acc.txt","r");
    while (fread(&act,sizeof(account),1,acc))
    {
        if(strcmp(act.un,usnm)==0){
            printf("\t\tHi %s %s, Your Details\n\n",act.fname,act.lname);
            printf("Name:%s %s\n",act.fname,act.lname);
            printf("DOB:%d/%d/%d\n",act.DOBD,act.DOBM,act.DOBY);
            printf("Phone number:%lld\n\n",act.phn);
        }
    }  
}
void addVehicle(){
	
    system("cls");
    vehicle v;
    FILE *addv;

    addv = fopen("vehicles.txt", "a");  
    if (addv == NULL) {
        printf("\033[31mError opening file for writing.\n\033[0m");
        exit(0);
    }

    char add = 'y';
    while (add == 'y') {
        reg:
        printf("\t\tRegistration Details\n");
        printf("\n");
        printf("Enter Registration number: ");
        re:
        scanf("%d", &v.registrationNumber);
        int flag=checkregnum(v.registrationNumber);
		if(flag==0){
			printf("\033[31mPlease Input valid number:\033[0m");
			goto re;
		}
        vehicle check;
        FILE *checker;
        checker = fopen("vehicles.txt", "r");
        if (checker == NULL) {
            printf("\033[31mError opening file for reading.\n\033[0m");
            fclose(addv);
            menu();
        }
        while (fread(&check, sizeof(vehicle), 1, checker)) {
            if (v.registrationNumber == check.registrationNumber) {
                printf("\033[31mThe Number %d has already been registered. Please input a valid number.\n\n\n\033[0m", v.registrationNumber);
                goto reg;
            }  
        }
        fclose(checker);
        printf("Enter Vehicle type(A-K): ");
        scanf(" %c", &v.vehicleType);
        if(v.vehicleType<65 ||v.vehicleType>75){
        	printf("\033[31mInvalid Type.Try again.\n\033[0m");
        	menu();
		}
        printf("Enter Vehicle model: ");
        scanf("%s", v.modelName);
        printf("Enter Year of Manufacture: ");
        scanf("%d", &v.year);
        if(v.year>2024){
        	printf("\033[31mEnter a valid Date.\n\033[0m");
        	menu();
		}
        printf("Enter First Name: ");
        scanf("%s", v.ofname);
        printf("Enter Last Name: ");
        scanf("%s", v.olname);
        printf("Enter state name: ");
        scanf("%s", v.state);
        if (fwrite(&v, sizeof(vehicle), 1, addv) != 1) {
            printf("\033[31mError writing to file.\n\033[0m");
        } else {
            printf("\033[32mSuccessfully Added.\n\033[0m");
        }
        printf("Do you want to add another vehicle (y/n): ");
        scanf(" %c", &add);
    }

    fclose(addv);
}
void checkVehicle(){
	system("cls");
    int regNum;
    int found=0;
    vehicle v;
    FILE *check;
    check=fopen("vehicles.txt","r");
    reen:
    printf("Enter your Registration Number: ");
    scanf("%d",&regNum);
    int flag=checkregnum(regNum);
		if(flag==0){
			printf("\033[31mPlease Input valid number.\n\033[0m");
			goto reen;
		}
    while (fread(&v,sizeof(vehicle),1,check))
    {	
        if(v.registrationNumber==regNum){
            found=1;
        printf("\033[36m\n\t\tYour Details\n\n");
        printf("Registration Number:%d\n",v.registrationNumber);
        printf("Owner Name: %s %s\n",v.ofname,v.olname);
        printf("Vehicle Type: %c\n",v.vehicleType);
        printf("State:%s\n",v.state);
        printf("Model:%s\n",v.modelName);
        printf("Year of Manufacture:%d\n\n\033[0m",v.year);
        }
    }
    if(found==0){
        printf("\033[31mNo any vehicle Registered in this number.\n\n\033[0m");
    }
}
void updateVehicle(){
	system("cls");
    FILE *upd;
    upd=fopen("vehicles.txt","r");
    vehicle vehicles[100];
    int reg,choice;
    int num=0;
    int found=0;
    char oldfname[50];
    char oldlname[50];
    regn:
    printf("Enter Your Registration Number: ");
    scanf("%d",&reg);
    int flag=checkregnum(reg);
		if(flag==0){
			printf("\033[31mPlease Input valid number.\n\033[0m");
			goto regn;
		}
    while (fread(&vehicles[num],sizeof(vehicle),1,upd)){
    	system("cls");
        if(vehicles[num].registrationNumber==reg){
            found=1;
            char omodel[100];
            printf("\033[36m\t\tWhat Do You Want To Change?");
            change: ;
            printf("\n\n");
            printf("1.Owner \t\t\t\t 2.Model\n\n");
            printf("3.Go Back\n\n\033[0m");
            printf("Enter Your Choice: ");
            scanf("%d",&choice);
            switch (choice)
            {
            case 1:
            	system("cls");
                printf("\t\tPrevious Owner Details\n\n");
                printf("Enter first Name: ");
                scanf("%s",oldfname);
                printf("Enter Last Name:");
                scanf("%s",oldlname);
                if(strcmp(oldfname,vehicles[num].ofname)==0&&strcmp(oldlname,vehicles[num].olname)==0){
                printf("New Owner\n");
                printf("Enter First Name:");
                scanf("%s",vehicles[num].ofname);
                printf("Enter Last Name:");
                scanf("%s",vehicles[num].olname);
                }
                else{
                	system("cls");
                    printf("\033[31mIncorrect Name.Try Again\n\033[0m");
                    menu();
                }
                break;
                case 2:
                	system("cls");          
                printf("Enter Previous Model Name: ");
                scanf("%s",omodel);
                if(strcmp(omodel,vehicles[num].modelName)==0){
                    printf("Enter New Model: ");
                    scanf("%s",vehicles[num].modelName);
                    printf("Enter Year of Manufacture: ");
                    scanf("%d",&vehicles[num].year);
                    printf("Enter Vehicle TYpe: ");
                    scanf(" %c",&vehicles[num].vehicleType);
                    printf("Enter State: ");
                    scanf("%s",vehicles[num].state);
                }
                else{
                	system("cls");
                    printf("\033[31mInvalid.Try Again.\n\033[0m");
                   menu();
                }
                break;
				case 3:
				menu(); 
            default:
            printf("\033[31mInvalid option Try Again.\n\033[0m");
            goto change;
                break;
            }
        }     
        num++;
    }
    if(!found){
        printf("\033[31mThis Number Doesnot exist please input a valid number.\n\033[0m");
        
    }
    else{
    printf("\033[32mChanged Successfully\033[0m"); 	
	}
    fclose(upd);
    upd=fopen("vehicles.txt","w");
    int i;
    if(!upd){
        printf("Couldnot open.");
    }
    for(i=0;i<num;i++){
        fwrite(&vehicles[i],sizeof(vehicle),1,upd);
    }
    fclose(upd);
    
    
    }
    void deleteVehicle(){
    	system("cls");
    	char repass[50];
        FILE *delv;
        int num=0,found=0;
        char choice=' ';
        delv=fopen("vehicles.txt","r+");
        vehicle vehicles[100];
        int reg;
        printf("Enter Your Registration number to delete:");
        scanf("%d", &reg);
        int flag=checkregnum(reg);
		if(flag==0){
			printf("\033[31mPlease Input valid number:\033[0m");
			menu();
		}
        while(fread(&vehicles[num],sizeof(vehicle),1,delv)){
            if(vehicles[num].registrationNumber==reg){
            	found=1;
                printf("\033[36m\t\tYour Details\n\n");
                printf("Owner Name:%s %s\n",vehicles[num].ofname,vehicles[num].olname);
                printf("Regeistration Number:%d\n",vehicles[num].registrationNumber);
                printf("Vehicle Type:%c\n",vehicles[num].vehicleType);
                printf("Year of Manufacture:%d\n",vehicles[num].year);
                printf("Model:%s\n\033[0m",vehicles[num].modelName);
                del:
                printf("Re-Enter Your Password to Delete: ");
                scanf("%s",repass);
                if(strcmp(pass,repass)==0){
                printf("Are You Sure You Want to delete?(y/n): ");
                scanf(" %c",&choice);
                if(choice=='y'){
                    num-=1;
                	printf("\033[32mSuccessfully Deleted.\033[0m");
                }
                 else{
                menu();
                 }	
				}
                
                else{
                	printf("%s",pass);
                    printf("\033[31mIncorret Password.Try Again.\n\033[0m");
                    menu();
                }
            }
            num++;
        }
        if(!found){
        	printf("\033[31mNo any vehicle registered.Please input valid number.\n\n\033[0m");
		}
        fclose(delv);
        delv=fopen("vehicles.txt","w");
        if(delv==NULL){
            printf("\033[31mError Opening File.\033[0m");
        }
        int i;
        for(i=0;i<num;i++){
            fwrite(&vehicles[i],sizeof(vehicles),1,delv);
        }
    }
