/*
 * Description:
 * This program takes input from the user in the form Month Day Year eg. Dec 8 1965 and outputs
 * the day of the week on which that day fell/falls. The program is able to accommodate incorrectly
 * inputted arguments and will gracefully exit with an "Input not valid" error message. 
 *
 * Inputs:
 * argc - the number of inputted arguments
 * argv:
 * argv[0] - program name
 * argv[1] - month of the year
 * argv[2] - day of the year
 * argv[3] - year
 *
 * Outputs:
 * If valid inputs are received:
 * - outputs day of the year
 * If invalid inputs are received
 * - outputs "Input not valid"
 *
 * Caveats
 * This program can only run from years 1901 to 2038
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * The getDayOfYear routine takes the date and outputs the day of the year.
 *
 * Algorithm
 * Convert the month to decimal by comparing it to a list of known months. Check if the month, day
 * and year are valid inputs. Use Zeller’s algorithm to determine the day of the week.
 *
 * Inputs
 * day - the inputted day
 * month - pointer to a character array where the inputted month is found
 * year - the inputted year
 *
 * Outputs
 * If valid inputs are received:
 * - outputs day of the year
 * If invalid inputs are received
 * - outputs "Input not valid"
 *
 * Caveats
 * This program can only run from years 1901 to 2038
 *  
 */

void getDayOfYear(int day, char* month, int year)
{
	char *months [12] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"}; /*All the months of the year*/
	char *days [7] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"}; /*All the days of the week*/
	int noDays[12] = {31,28,31,30,31,30,31,31,30,31,30,31}; /*The number of days in each respective month*/
	
	int i; /*Declared outside the loop for gcc compiler*/
	int monthNo = -1; /*Stores the number of the inputted month*/


	if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) /*Check if the date is a leap year*/
	{
        noDays[1] = 29; /*Change the number of days in February to 29*/
	}

	for(i = 0; i < 12; i++) /*Check which month number has been inputted*/
	{
		if(strcmp(month,months[i]) == 0) /*Compare the input to the stored months*/
		{
			monthNo = i+1; /*Store the month number starting at 1 - 12*/
			break;
		}
	}

	if(day > 0 && day <= noDays[monthNo-1] && monthNo > 0 && monthNo <= 12 && year > 1900 && year < 2039 ) /*Check that the day is between 1 and the number of days in the inputted month. Check of the month number is between 1 and 12. Check if the year is between 1901 and 2038*/
	{
		
		int detDay = (day+=monthNo<3?year--:year-2,23*monthNo/9+day+4+year/4-year/100+year/400)%7; /*Zeller’s algorithm taken from https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week*/
		printf("%s\n",days[detDay]); /*Display the day of the year*/	
	}

	else /*Any input that doesn't match the given criteria*/
	{
		fprintf(stderr,"Input not valid\n"); /*Print Input not valid*/	
		exit(EXIT_FAILURE); /*Exit the program*/
	}
}

/*
 * The main routine controls the execution of the overall program.
 *
 * Algorithm
 * Get input from command line and pass it to getDayOfYear
 *
 * Inputs
 * argc holds the number of command line arguments.
 * argv is a pointer to an array of command line arguments.
 *
 * Outputs
 * "Input not valid" if the number of arguments is not 4
 *
 * Caveats
 * This program can only run from years 1901 to 2038
 *  
 */
int main(int argc, char* argv[]) /*The main method*/
{
	if(argc != 4) /*Check if the input parameters have 3 arguments*/
	{
		fprintf(stderr, "Input not valid\n"); /*Print input not valid*/
		exit(EXIT_FAILURE); /*Exit the program*/
	}
	
	char* month = argv[1]; /*Save the first parameter into variable month*/
	int day = atoi(argv[2]); /*Save the second parameter into variable day*/
	int year = atoi(argv[3]); /*Save the third parameter into variable year*/

	getDayOfYear(day,month,year); /*Call method DayOfYear with given input parameters*/
	
   return 0; /*Return at the end of the main method*/
}
