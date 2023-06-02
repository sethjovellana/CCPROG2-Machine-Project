/*
   File: numeric_date_helpers.c
   
   DO NOT CHANGE THE CONTENTS OF THIS FILE.  	
*/
#include <string.h>
#include <stdlib.h>


/*
   Note: You may or may not use this helper function.  In my own MP solution, I used it to 
         convert the dates from strings into integers.  It uses a predefined function
         atol(str) which converts a string containing digits into a long integer.
         Please read about atol() in 
            https://www.ibm.com/docs/en/i/7.2?topic=lf-atol-atoll-convert-character-string-long-long-long-integer

	Purpose: determine a numeric value corresponding to a date in string format
	Returns: returns the date as an integer in the format YYYYMMDD
   @param : str_date is the name of the date string
	Pre-condition: str_date contains a valid date value

   Example Usage:
      numeric_date("1/2/2017")   returns 20170102
      numeric_date("12/8/2016")  returns 20161208
      numeric_date("3/29/2014")  returns 20140329
      numeric_date("10/23/2015") returns 20151023

   You can then compare two dates (in string format) using numeric_date() for example as follows:
     
      if (numeric_date("10/24/2016") > numeric_date("12/23/2014"))
         printf("test...\n");
   
      if (numeric_date("8/8/2020") <= numeric_date("08/08/2020"))
         printf("another test...\n");

      if (numeric_date(date1) >= numeric_date(date2))
         printf("last test...\n");
*/
long int 
numeric_date(char *str_date)
{
   long int day, month, year;     
   char str[11];      
   int i;
   int ctr;
    
   // Step 1: get the month part from the string  
   strcpy(str, str_date);
   i = 0;
   ctr = 0;
   while (str[i] != '/') {  // find the first '/'
       i++;
       ctr++;
   }       
   
   str[i] = '\0';   
   month = atol(str); // capture the month as a long int 
   
   
   // get the day part from the string
   ctr++; // move 1 character past '/'
   strcpy(str, str_date + ctr);
   i = 0;
   while (str[i] != '/') { // find the second '/'
      i++;
      ctr++;
   }  
   
   str[i] = '\0';
   day = atol(str); // capture the day as a long integer       
       
   // get the year part from the string
   ctr++;  // move 1 character past '/'
   strcpy(str, str_date + ctr);  
   year = atol(str);  // capture the year as a long integer      

   return year * 10000 + month * 100 + day;   
}

/* 
	Note   : You may or may not use this helper function.  
   Purpose: extracts the numeric year value from a string date
   Returns: the numeric year value
   @param : date is the name of the date string
	Pre-condition: date is already in the format "MM/DD/YYYY"

   Example Usage:
      int year;
      year = GetYear("04/04/2022");  // will store 2022 as the value of year variable
      printf("%d\n", GetYear("10/24/2016"));  // will print 2016
*/
int
GetYear(char *date)
{
	return atol(date+6);	// date + 6 is the start of the portion of the string that stores the "YYYY".
}


/* 
	Note   : You may or may not use this helper function.  
   Purpose: extracts the numeric month value from a string date
   Returns: the numeric month value
   @param : date is the name of the date string
	Pre-condition: date is already in the format "MM/DD/YYYY"

   Example Usage:
      int month;
      year = GetMonth("04/04/2022");  // will store 4 as the value of month variable
      printf("%d\n", GetYear("10/24/2016"));  // will print 10
*/
int 
GetMonth(char *date)
{
	char temp[3] = "";
	
	temp[0] = date[0];  // extract the 1st digit of the month
	temp[1] = date[1];	// extract the 2nd digit of the month
	return atol(temp);
}


/* 
	Note   : You may or may not use this helper function.  
   Purpose: extracts the numeric day value from a string date
   returns: the numeric day value
   @param : date is the name of the date string
	Pre-condition: date is already in the format "MM/DD/YYYY"

   Example Usage:
      int day;
      year = GetDay("04/08/2022");  // will store 8 as the value of the day variable
      printf("%d\n", GetDay("10/24/2016"));  // will print 8
*/
int 
GetDay(char *date)
{
	char temp[3] = "";
	
	temp[0] = date[3];	// extract the 1st digit of the day
	temp[1] = date[4];	// extract the 2nd digit of the day
	return atol(temp);
}





