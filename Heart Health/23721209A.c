#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

//initialise enum to clearly keep track of the blood pressure risks
enum Pressure {HIGH, PREHIGH, NORMAL, LOW};

//I will use these arrays later to iterate through the exact columns of a row calculated from the user input to decide whether we have sufficient information or not.
//we do not have to know the exact risk percentage, the category is sufficient -> That is why there is only 6 integer categories.
//we know that the first and the last age category have consistent risk category -> That lets us omit additional 8 lines of risks.
int ERICE_men[16][16] = {{5, 5, 5, 5, 5, 5, 5, 5, 4, 4, 4, 4, 5, 5, 5, 5},
                        {5, 5, 5, 5, 5, 5, 5, 5, 4, 4, 4, 4, 5, 5, 5, 5},
                        {5, 5, 5, 5, 5, 5, 5, 5, 4, 4, 4, 4, 5, 5, 5, 5},
                        {4, 4, 4, 4, 4, 4, 4, 4, 3, 3, 3, 3, 4, 4, 4, 4},
                        {4, 4, 4, 4, 5, 5, 5, 5, 3, 3, 3, 3, 4, 4, 4, 4},
                        {4, 4, 4, 4, 4, 4, 5, 5, 3, 3, 3, 3, 4, 4, 4, 4},
                        {4, 4, 4, 4, 4, 4, 4, 4, 3, 3, 3, 3, 4, 4, 4, 4},
                        {2, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 3, 3, 3},
                        {2, 2, 2, 2, 3, 3, 3, 3, 1, 2, 2, 2, 2, 2, 2, 2},
                        {2, 2, 2, 2, 3, 3, 3, 3, 1, 1, 1, 1, 2, 2, 2, 2},
                        {2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2},
                        {1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                        {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1},
                        {0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
                        {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
                        };
int ERICE_women[12][16] = {{5, 5, 5, 5, 5, 5, 5, 5, 4, 4, 4, 4, 5, 5, 5, 5},
                            {4, 4, 4, 4, 5, 5, 5, 5, 3, 3, 3, 3, 4, 4, 4, 4},
                            {4, 4, 4, 4, 5, 5, 5, 5, 3, 3, 3, 3, 4, 4, 4, 4},
                            {4, 4, 4, 4, 5, 5, 5, 5, 3, 3, 3, 3, 4, 4, 4, 4},
                            {4, 4, 4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 4, 4, 4, 4},      
                            {2, 2, 2, 2, 3, 3, 3, 3, 1, 1, 1, 1, 2, 2, 2, 2},
                            {2, 2, 2, 2, 3, 3, 3, 3, 1, 1, 1, 1, 2, 2, 2, 2},
                            {2, 2, 2, 2, 3, 3, 3, 3, 1, 1, 1, 1, 2, 2, 2, 2},
                            {2, 2, 2, 2, 3, 3, 3, 3, 1, 1, 1, 1, 2, 2, 2, 2},
                            {1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1},
                            {1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1},
                            {1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1},
                        };

//a struct for all the medical data we need for this program.
//i am using boolean values for yes/no data to have a more understandable and concise program.
struct medicalData {
    int age;
    int SBP;
    bool male;
    bool female;
    bool diabetic;
    bool smoker;
    double cholesterol;    
};

void BMIcalc(void)
{
    double weight, height;
    system("cls");              //stdlib function that clears the terminal window for a clearer output

    do 
    {
        printf("Enter your weight in kilograms: ");
        scanf("%lf", &weight); 
        if (weight > 300 || weight < 0)
        {
            puts("Are you sure you input your real weight?\n"); 
        }
    }while(weight > 300 || weight < 0);
    //i assume the max weight for this program is 300kg, the user cannot enter less than 0 and more than 300

    do 
    {
        printf("\nEnter your height in metres: ");
        scanf("%lf", &height); 
        if (height > 2.5 || height < 0.5)
        {
            puts("Are you sure you put your real height in metres?"); 
        }
    }while(height > 2.5 || height < 0.5);
    //i assume nobody is taller than 2.5 metres

    double BMI;
    BMI = weight / (height*height);

    //print the line to separate output and make it clearer
    printf("\n");
    for (size_t i = 0; i< 100; i++) printf("=");

    //print the bmi categories and advice for user
    if (BMI < 18.5)
    {
        printf("\n| Your BMI is: %.1lf,\n| which is under 18.5, that means you are Underweight."
        "\n| Being Underweight can cause serious health concerns."
        "\n| Try to gain somewhere in between %.1lf - %.1lf kilograms to achieve normal BMI of 18.5 - 24.9.", BMI,18.5-BMI, 24.9-BMI);
    }
    else if(BMI >= 18.5 && BMI <= 24.9)
    {
        printf("\n| Your BMI is: %.1lf,\n| which is in between 18.5 and 24.9, that means you have a normal BMI."
        "\n| Try to keep your BMI in the normal range to avoid various health risks.", BMI);
    }
    else if(BMI >= 25 && BMI <= 29.9)
    {
        printf("\n| Your BMI is: %.1lf,\n| which is in between 25 and 29.9, that means you are Overweight."
        "\n| Being Overweight can cause serious health concerns."
        "\n| Try to lose somewhere in between %.1lf - %.1lf kilograms to achieve normal BMI of 18.5 - 24.9.", BMI, BMI - 24.9, BMI - 18.5);
    }
    else if(BMI >= 30)
    {
        printf("\n| Your BMI is: %.1lf,\n| which is in over 30, that means you are Obese."
        "\n| Being Obese can cause severe health concerns."
        "\n| Lose somewhere in between %.1lf - %.1lf kilograms to achieve normal BMI of 18.5 - 24.9.", BMI, BMI - 24.9, BMI - 18.5);
    }

    printf("\n| However, the Body Mass Index is only indicative and does not take body composition into account.\n");

    for (size_t i = 0; i< 100; i++) printf("=");
    puts("\n");
}

int bloodPressure (int systolicAvg)
{
    enum Pressure pressure;
    int diastolicAvg = 0;
    int systolTotal = 0;
    int diastolTotal = 0;
    int systolicPressure[5];
    int diastolicPressure[5];

    system("cls");                  //stdlib function that clears the terminal window for a clearer output
    
    for(size_t i = 0; i<5; i++)
    {
        do
        {
            printf("\nInput systolic and diastolic pressure (in mmHg) in the format XXX/XX\n");
            scanf("%d/%d", &systolicPressure[i], &diastolicPressure[i]);
            if (systolicPressure[i]>190 || systolicPressure[i]<70 || diastolicPressure[i]>100 || diastolicPressure[i] < 40)
            {
                puts("The blood pressure entered is not real, try again\n");
            }
            else if (diastolicPressure[i] > systolicPressure[i])
            {
                puts("The systolic blood pressure has to be higher than the diastolic, try again\n");
            }
        } while (systolicPressure[i]>190 || systolicPressure[i]<70 || diastolicPressure[i]>100 || diastolicPressure[i] < 40 || diastolicPressure[i] > systolicPressure[i]);
    }

    for(size_t i = 0; i<5; i++)
    {
        systolTotal += systolicPressure[i];
        diastolTotal += diastolicPressure[i];
    }

    systolicAvg = systolTotal/5;
    diastolicAvg = diastolTotal/5;

    printf("\n");
    for (size_t i = 0; i< 100; i++) printf("=");
    printf("\n| Your levels are %d/%d\n", systolicAvg, diastolicAvg);

    //i could have omitted the enums here and printed out straight category and advice, but wanted to try to implement enums in one way to make the code a bit clearer
    if(systolicAvg < 90 || diastolicAvg < 60)
    {
        pressure = LOW;
    }
    else if((systolicAvg >= 90 && systolicAvg < 120) && (diastolicAvg >= 60 && diastolicAvg<80))
    {
        pressure = NORMAL;
    }
    else if ((systolicAvg >= 120 && systolicAvg < 140) || (diastolicAvg >=80 && diastolicAvg<90))
    {
        pressure = PREHIGH;
    }
    else if(systolicAvg >= 140 || diastolicAvg >= 90)
    {
        pressure = HIGH;
    }

    //print out the category and advice to user using a switch statement based on enum pressure
    switch (pressure)
    {
        case LOW:
            puts("| Your blood pressure is low.\n| Low blood pressure usually isn't a problem, but it can sometimes make you feel faint or dizzy or could be a sign of another health problem.\n| Concider consulting with a doctor to prevent a heart disease risk.");
            break;
        case NORMAL:
            puts("| Your blood pressure is normal.\n| Your blood pressure reading is healthy.\n| At this level you have a much lower risk of heart disease and stroke.\n| Following a healthy lifestyle will help you to keep it in the healthy range.");
            break;
        case PREHIGH:
            puts("| Your blood pressure is pre-high.\n| This is not high blood pressure, but it is a little higher than it should be\n| and means you could go on to develop high blood pressure.");
            break;
        case HIGH:
            puts("| Your blood pressure is high.\n| This is the point where your risk of serious health problems goes up.\n| Concider consulting with a doctor to prevent a heart disease risk.");
            break;
        default:
            puts("| Unexpected error, try again.");
            break;
    }

    for (size_t i = 0; i< 100; i++) printf("=");
    puts("\n");

    return systolicAvg;     //return the average systolic pressure back to main in order to have as least questions asked as possible later in the ERICE risk score
}

void printTheRisk(int riskNumber)
{
    //a function used just to print the risk percentages and categories according to the calculated integers
    printf("\n");                                   //format the output by making a little "box" for the output
    for (size_t i = 0; i< 82; i++) printf("=");
    printf("\n");

    switch (riskNumber)
    {
        case 0:
            puts("| The risk of you having a stroke in next ten years is low, less than 5%.");
            break;
        case 1:
            puts("| The risk of you having a stroke in next ten years is mild, 5% to 9%.");
            break;
        case 2:
            puts("| The risk of you having a stroke in next ten years is moderate, 10% to 14%.");
            break;
        case 3:
            puts("| The risk of you having a stroke in next ten years is moderate-high, 15% to 19%.");
            break;
        case 4:
            puts("| The risk of you having a stroke in next ten years is high, 20% to 29%.");
            break;
        case 5:
            puts("| The risk of you having a stroke in the next ten years is very high, over 30%.");
            break;
    }
    //again, separated output
    for (size_t i = 0; i< 82; i++) printf("=");
    puts("\n");
    
}

int calcRow(int age, int SBP)
{
    //a function to calculate which row of the 16 or 12 rows in the erice chart has to be checked
    //we only need the SBP and age to pinpoint a specific row

    int index =0;       

    //first calculate the age category and return the first row from the top
    if (age >= 60 && age < 70)
    {
        index = 4;
    }
    else if (age >= 50 && age < 60)
    {
        index = 8;
    }
    else if (age < 50)      //women's chart will not be affected by this condition because we know women under 50 have a low risk and that would be already printed to the user
    {                       //so we do not need to worry that the program would want to access an index of an array that is out of range
        index = 12;
    }

    //then add 1/2/3 to the index from the top according to the SBP, 0 is not listed here because that would not change the index, so condition is simply not found
    if (SBP >= 160 && SBP < 180)
    {
        index += 1;
    }
    else if(SBP >= 140 && SBP < 160)
    {
        index += 2;
    }
    else if(SBP < 140)
    {
        index += 3;
    }
    
    return index;
}

void calcColumn(bool x, int columns[])
{
    if (x)
    {
        //if the person is diabetic or non smoker,
        //the upper limit of the column changes to the original number - the difference between the two divided by 2
        columns[1] -= ((columns[1] - columns[0]) / 2);
    }
    else{
        //if the person is not a diabetic or a smoker,
        //the lower column boundry is bumped up by the difference between the two divided by 2
        //for example range 0-16 is difference 16 and divided by two gives us ranges either 8-16 or 0-8 and same further down
        columns[0] += ((columns[1] - columns[0]) / 2);
    }
}

int checkChart(int row, int Column[], int chart[][16])
{
    //check if all the entries in the row and range of columns are same
    //if one element is different immediately exit and return 6
    //if they are same then return the risk number

    for (size_t i = Column[0]; i < (Column[1]-1); i++)
    {
        if (chart[row][i+1] != chart[row][i])
        {
            return 6;
        }
    }
    return chart[row][Column[0]];
}

int check(int row, int columns[], bool male)
{
    //just a simple path divider to decide whether to check the men's or the women's chart 
    if (male)
    {
        return(checkChart(row, columns, ERICE_men));
    }
    else{
        return (checkChart(row, columns, ERICE_women));
    }
}

int cholesterol(double *cholest)
{
    do
    {
        printf("What is your cholesterol level?\nCholesterol level: ");
        scanf("%lf", cholest);
        if ((*cholest < 1) || (*cholest > 15))
        {
            puts("\nNot a valid answer, try again");
        }
    }while(*cholest<1 || *cholest>15);
    //i am assuming that levels below 1 and above 15 are not possible to have, therefore keep the user trying the input
    
    //the function returns the number that has to be added to the starting column to pinpoint one specific column 
    if (*cholest < 5.2)
    {
        return 0;
    }
    else if (*cholest >= 5.2 && *cholest <= 6.4)
    {
        return 1;
    }
    else if(*cholest >= 6.5 && *cholest <= 7.7)
    {
        return 2;
    }
    else{
        return 3;
    }
    //at this point the program knows the exact column and row
    //therefore, it knows the exact risk number
}

void smoking(bool *smoker)
{
    char answer[4];

    do 
    {
        printf("Are you a smoker? (Yes/No)\nAnswer: ");
        scanf("%3s", answer);
        if ((strcasecmp("yes", answer) != 0) && (strcasecmp("no", answer) != 0))
        {
            puts("\nNot a valid answer, try again");
        }
    }while((strcasecmp("yes", answer) != 0) && (strcasecmp("no", answer) != 0));
    //keep prompting the user for answer if it is not yes or no
    //strcasecmp is a better function than strcmp because it is case insensitive, so 'no' and 'No' are taken as the same word

    if (strcasecmp("yes", answer) == 0)
    {
        *smoker = true;
    }
    else
    {
        *smoker = false;
    }
}

void DIA(bool *diabetic)
{
    char answer[4];     //store the yes/no answer from the user

    do 
    {
        printf("Are you a diabetic? (Yes/No)\nAnswer: ");
        scanf("%3s", &answer);
        if ((strcasecmp("yes", answer) != 0) && (strcasecmp("no", answer) != 0))
        {
            puts("\nNot a valid answer, try again");
        }
    }while((strcasecmp("yes", answer) != 0) && (strcasecmp("no", answer) != 0));
    //keep prompting the user for answer if it is not yes or no
    //strcasecmp is a better function than strcmp because it is case insensitive, so 'yes' and 'Yes' are the same and taken as the same word

    if (strcasecmp("yes", answer) == 0)
    {
        *diabetic = true;
    }
    else
    {
        *diabetic = false;
    }
}

void getSBP(int *SBP)
{
    //get users Systolic blood pressure,
    //i am assuming that levels of SBP cannot be below 70 and above 190
    do
    {
        printf("What is your average systolic blood pressure?\nSBP: ");
        scanf("%d", SBP);
        if (*SBP < 70 || *SBP > 190)
        {
            puts("Invalid blood pressure input, try again.");
        }
    }while(*SBP < 70 || *SBP > 190);
}

void getGender(bool *male, bool *female)
{
    char gender[7];

    do
    {
        printf("What is your gender? (Male/Female)\nGender: ");
        scanf("%6s", gender);                                       //use %6s to avoid overflow corrupting the program
        
        if ((strcasecmp("male", gender) != 0) && (strcasecmp("female", gender) != 0))
        {
            puts("\nInvalid gender, please try again.");
            fflush(stdout);
        }
    } while ((strcasecmp("male", gender) != 0) && (strcasecmp("female", gender) != 0));
    //as mentioned above, strcasecmp does not see difference between 'Female' and 'fEmAlE', therefore it takes the meaning of the input better

    if (strcasecmp("male", gender) == 0)
    {
        *male = true;
        *female = false;
    }
    else
    {
        *male = false;
        *female = true;
    }
}

int ERICErisk(struct medicalData Data)
{
    int row;                //to keep track of which row are we checking in the chart
    int Column[2] = {0,16}; //to keep track of the range of columns we are checking in the chart
    int checkInt;           //variable to determine if the fucntion check found a risk number or not

    system("cls");          //stdlib function that clears the terminal window for a clearer output

    //first get the age of the user since this is the category that can help us immediately distinguish the risk category
    do
    {
        printf("How old are you?\nAge: ");
        scanf("%d", &Data.age);
        if (Data.age < 0 || Data.age > 150)
        {
            puts("Are you sure you wrote down your real age?");  
        }
    } while (Data.age < 0 || Data.age > 150);

    //we know that men under 40 and women under 50 have a low risk, conversely both genders above age 80 have high risk
    //immediately return low or high risk number if we come accross these age categories
    if (Data.age < 40)
    {
        return 0;
    }
    else if( Data.age >= 80 )      
    {
        return 5;
    }
    else        
    {
        //if age was not enough to determine the risk, get gender from the user
        //For most part in this function I am using pointers, addresses of the struct and its members
        getGender(&Data.male, &Data.female);
        
        if( Data.female && (Data.age < 50) )
        {
            return 0;
        }

        if(Data.SBP == 0)   //if user used the blood pressure function before, the SBP will be stored and we do not need to ask again, otherwise we do
        {
            getSBP(&Data.SBP);
        }
        else{
            printf("- Your previously calculated Systolic blood pressure is: %d -\n", Data.SBP);
        }

        //calculate the row using age and sbp
        row = calcRow(Data.age, Data.SBP);

        //check if there is a consistent categroy in the row and all columns
        checkInt = check(row, Column, Data.male);
        if (checkInt != 6)      //function check returns 6 if the function found out that it needs more precise information
        {
            return checkInt;
        }

        //ask the user if they are diabetic and calculate the columns accordingly
        DIA(&Data.diabetic);
        calcColumn(Data.diabetic, Column);

        checkInt = check(row, Column, Data.male);
        if (checkInt != 6)
        {
            return checkInt;
        }

        //ask the user if they are a smoker or not 
        smoking(&Data.smoker);
        //calculate the columns but with the negation of the boolean
        //i used this approach because non diabetics appear on the right hand side and non smokers appear on the left hand side of the scaled down chart
        //that means different approaches would have to be used to calculate these two 'identical' conditions
        //so i just negated the smoker answer and that let me use the same function
        calcColumn(!(Data.smoker), Column);

        checkInt = check(row, Column, Data.male);
        if (checkInt != 6)
        {
            return checkInt;
        }

        //last question asked is the cholesterol level that gives back the number that has to be added to the starting column to pinpoint one specific column
        //so we know the row and the column => we have only one value => return it
        if (Data.male)
        {
            return (ERICE_men[row][Column[0]+(cholesterol(&Data.cholesterol))]);
        }
        else{
            return (ERICE_women[row][Column[0]+(cholesterol(&Data.cholesterol))]);
        }
    }
}

int main(void)
{
    struct medicalData Data = {0, 0, 0, 0, 0, 0, 0};        //initialise the empty struct to work with
    int choice = 1;                                         //user menu choice

    puts("Welcome to the Heart Health program,");

    while(choice > 0 && choice < 4)                         //let the user choose which function they want the program to perform
    {
        do
        {
            printf("To calculate your BMI press 1.\nTo have your blood pressure assesed press 2.\n"
            "To figure out your ERICE Risk score category press 3.\nTo end the program press 4.\n"
            "Your choice: ");
            scanf("%d", &choice);
            if (choice <= 0 || choice > 4)
            {
                system("cls");                              //stdlib function that clears the terminal window for a clearer output
                puts(" -Invalid number option, try again.- ");  //warn the user to give a valid menu choice
            }
        } while (choice <= 0 || choice > 4);                //simple do while loop to guardrail the input from the user
        
        //a switch statement that performs the function user wants to
        switch (choice)
        {
            case 1:
                BMIcalc();
                break;
            case 2:
                Data.SBP = bloodPressure(Data.SBP);         //save the bloodpressure value to the current struct for even less questions asked if user wants to calculate ERICE
                break;
            case 3:
                printTheRisk(ERICErisk(Data));
                break;
            default:                                        //Tell the user the program has ended with a nice box and terminate the program
                printf("\n|");
                for (size_t i = 0; i< 14; i++) printf("=");
                printf("|\n| Program end. |\n|");  
                for (size_t i = 0; i< 14; i++) printf("=");
                printf("|");
                break;
        }        
    }
}