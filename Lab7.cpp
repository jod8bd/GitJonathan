/*
* File:   Lab7.cpp
* Author: Jonathan Davis
* Created on October 13, 2016, 10:43 AM
*/
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
class Signal{
  private:
  int length;                 //Declare private methods for the signal class
  double max;
  double *data;
  double average();
  void maximum();
  public:
  Signal();                   //Declare public methods for the signal class
  Signal(int num);
  Signal(char* name);
  ~Signal();
  void menu();
  void operation(int choice);
  void offset(double oFFset);
  void scale(double scaler);
  void normal();
  void center();
  void sig_Info();
  void save_File(char* name);
};
Signal::Signal(){         //This is the default constructor that initialize the
  length = 0;             //members of the constructor.
  max = 0;
  data = NULL;
}
Signal::Signal(int num){             //The constructor takes in an integer value
  Signal();
  char file[50] = {'\0'};                 //Declare variables for the
  int i;                                  //constructor
  sprintf(file, "Raw_data_%d.txt", num);
  FILE *filE = fopen(file, "r");          //Open chosen file
  if (filE == NULL){                      //Check if file opens
    cout << "Error! File couldn't be open!";
    exit(1);
  }
  fscanf(filE, "%d %lf", &length, &max);    //Stores the values from file to
  data = new double [length];               //corresponding members of the
  while (!feof(filE)){                      //constructor.
    fscanf(filE, "%lf\n", &data[i++]);
  }
}
Signal::Signal(char* name){      //The constructor takes in an character pointer
  Signal();
  char file[50] = {'\0'};                 //Declare variables for the
  int i = 0;                              //constructor
  int num = 0;
  sprintf(file, "%s.txt", name);          //Concatenate name with file type
  FILE *filE = fopen(file, "r");          //Open chosen file
  if (filE == NULL){                      //Check if file opens
    cout << "Error! File couldn't be open!";
    exit(1);
  }
  fscanf(filE, "%d %lf", &length, &max);  //Stores the values from file to
  data = new double [length];             //corresponding members of the
  while (!feof(filE)){                    //constructor.
    fscanf(filE, "%lf\n", &data[i++]);
  }
}
Signal::~Signal(){                        //Destructor that frees data pointer
  if (data){                              //Conditional statement that checks
    delete[] data;                        //to see if pointer is empty.
  }
}
double Signal::average(){                 //This method sums up all the data
  int i = 0;                              //in the pointer, divide it by the
  double total = 0, avg;                  //length, and return the double
  while (i < length){                     //variable avg.
    total += data[i];
    i++;
  }
  avg = total / length;
  return avg;
}
void Signal::maximum(){                   //This method finds the maximum
  int i = 0;                              //value of the various values in the
  double mAx = 0;                         //data pointer and assign the max
  while (i < length){                     //value to the member of the
    if (data[i] > mAx){                   //constructor.
      mAx = data[i];
    }
    i++;
  }
  max = mAx;
}
void Signal::menu(){                      //The menu of operations for the user
  cout << "Choose an option:\n"           //to choose from.
          "1. Signal Info\n"
          "2. Offset\n"
          "3. Scale\n"
          "4. Normalize\n"
          "5. Center\n"
          "6. Save Signal\n";
}
void Signal::operation(int choice){        //This method carries out the desired
  double oFFset, scaler;                 //operation annotation using an
  char file[50] = "Raw_data_13";         //switch statement
  switch (choice) {
    case 1:
      sig_Info();
      break;
    case 2:
      cout << "How much do you want to offset your signal?:";
      cin >> oFFset;
      offset(oFFset);
      maximum();
      break;
    case 3:
      cout << "How much do you want to scale your signal by?:";
      cin >> scaler;
      scale(scaler);
      maximum();
      break;
    case 4:
      normal();
      maximum();
      break;
    case 5:
      center();
      maximum();
      break;
    case 6:
      save_File(file);
      break;
    default:
      cerr << "Invalid option, try again!" << endl;
      break;
  }
}
void Signal::offset(double oFFset){     //Takes in an double variable and adds
  int i = 0;                          //the variable to the values in the data
  while (i < length){                 //pointer.
    data[i] += oFFset;
    i++;
  }
}
void Signal::scale(double scaler){      //Takes in an double variable and multiply
  int i = 0; //initialize variables   //the variable to the values in the data
  while (i < length){                 //pointer.
    data[i] *= scaler;
    i++;
  }
}
void Signal::normal(){                  //Takes the max and divides it by the
  int i = 0; //initialize variables   //values in the data pointer.
  while (i < length){
    data[i] /= max;
    i++;
  }
}
void Signal::center(){                  //Takes the average and subtracts it by
  int i = 0; //initialize variables   //the values in the data pointer
  double avg = average();
  while (i < length){
    data[i] -= avg;
    i++;
  }
}
void Signal::sig_Info(){                    //Prints the length of the signal,
  cout << "Length: " << length << endl;   //the maximum, and the average
  cout << "Maximum: " << max << endl;
  cout << "Average: " << average() << endl;
}
void Signal::save_File(char* name){         //This method takes in an string and
  char fIle[50] = {'\0'};                 //concatenate the string to the file
  int i = 0;                              //type
  sprintf(fIle, "%s.txt", name);
  FILE* file = fopen(fIle, "w");
  if (file == NULL) { //Check if file opens
    printf("Error! File couldn't be open!");
    exit(1);
  }
  fprintf(file, "%d %lf\n", length, max); //Write data to file
  while (i < length){
    fprintf(file, "%lf\n", data[i]);
    i++;
  }
  fclose(file);
  cout << "You have just saved the signal to the file " << fIle;//Prompts on success.
}
int main(int argc, char** argv){
  char input[50] = {'\0'};
  int file_num, choice = 0;
  if (argc < 2){                                      //Checks for command line
    cout << "Please enter the file name:";          //arguments
    cin >> input;
    Signal signal1(input);
    while (choice != 6){
      signal1.menu();
      cin >> choice;
      signal1.operation(choice);
    }
  } else if (argv[1][0] == '-' && argv[1][1] == 'n'){ //Check for fie number
    file_num = atoi(argv[2]);
    Signal signal1(file_num);                       //Creates an object
    while (choice != 6){
      signal1.menu();
      cin >> choice;
      signal1.operation(choice);
    }
  } else if (argv[1][0] == '-' && argv[1][1] == 'f'){ //Check for file name
    Signal signal1(argv[2]);                        //Creates an object
    while (choice != 6){
      signal1.menu();
      cin >> choice;
      signal1.operation(choice);
    }
  } else{                              //Handles invalid command line commands
    std::cout << "Invalid argument.\n The program either take -n followed by an number of -f followed by a filename.\n Or no arguments at all!";
    return (1);
  }
  return 0;
}
