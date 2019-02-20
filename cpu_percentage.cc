
//******************************************************************************
// File:          cpu_percentage.cc
// Author:        Wesley Ryder
// Description:   This code operates the cpu at a certain percentage
//                upon execution
//******************************************************************************

#include <iostream>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
using namespace std;


// Variables used to perform cpu usage
int const MAX_ARGC_COUNT      = 2;
int const ARG_POS             = 1;
int const PERCENT_MAX         = 100;
int const PERCENT_MIN         = 1;
int const TIME_DELAY_CONSTANT = 50000;


//******************************************************************************
// Function:      print_percent_error()
// Arguments:     None
// Description:   Simply prints error message
//******************************************************************************
void print_percent_error()
{
  cout << "Usage: ./cpu_percentage <percentage>" << endl;
}

//******************************************************************************
// Function:      print_within_percent_error()
// Arguments:     None
// Description:   Simply prints error message
//******************************************************************************
void print_within_percent_error()
{
  cout << "Usage: ./cpu_percentage <percentage>" <<
    " percentage must be between values 1-100" << endl;
}

//******************************************************************************
// Function:      calc_effective_sleep_time()
// Arguments:     float time_diff
//                float percentage
// Description:   Calculates the effect sleep time
//******************************************************************************
float calc_effective_sleep_time(float time_diff, float percentage)
{
  float total;
  float sleep_time;
  total = time_diff/percentage;
  sleep_time = total - time_diff;
  return sleep_time;
}

//******************************************************************************
// Function:      check_percentage()
// Arguments:     int argc
//                char** argv
// Description:   Check if percentage value is between 1 and 100 and isn't an
//                invalid input (ie, symbols, strings etc)
//******************************************************************************
int check_percentage(int argc, char** argv)
{
  int percentage;

  if (argc == MAX_ARGC_COUNT )
  {
    int num_of_nums = strlen(argv[ARG_POS]);
    string string_of_nums = argv[ARG_POS];
    for(int i = 0; i < num_of_nums; i++)
    {
      if(!isdigit(string_of_nums[i]))
      {
        print_within_percent_error();
        exit (EXIT_FAILURE);
      }
    }
  }
  else
  {
    print_percent_error();
    exit (EXIT_FAILURE);
  }

  percentage = atoi(argv[ARG_POS]);

  if (percentage <= PERCENT_MAX and percentage >= PERCENT_MIN)
    return percentage;
  else
  {
    print_within_percent_error();
    exit (EXIT_FAILURE);
  }
}


//******************************************************************************
// Function:      main()
// Arguments:     int argc
//                char** argv
// Description:   To run the main of the program, sleep the cpu to create a
//                'cpu_usage' program
//******************************************************************************
int main(int argc, char** argv)
{
  float percentage;
  clock_t t1      = 0;
  clock_t t2      = 0;
  size_t time_diff = 0;
  size_t sleep_time = 0;


  percentage = check_percentage(argc, argv);
  percentage = percentage / 100.0;


  while(1)
  {
    t1 = clock();
    while(1)
    {
      t2 = clock();
      time_diff = t2 - t1;
      if( time_diff > TIME_DELAY_CONSTANT)
        break;
    }
    sleep_time = calc_effective_sleep_time(time_diff, percentage);
    usleep(sleep_time);
  }
}
