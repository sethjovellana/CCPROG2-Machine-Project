/*
    Do not forget to encode your name, section and date of submission.  A deduction of
	0.5 point will be applied for not complying with this instruction!

    LASTNAME1, FIRSTNAME1: JOVELLANA, REUBEN SETH        SECTION: S24
    LASTNAME2, FIRSTNAME2:                               SECTION:
    
    DATE SUBMITTED     : 14 JUNE 2022
	
	Make sure that you do the following:

	1. COMPILE your C source code with -Wall directive.
	
	       Example: CCPROG2> gcc -Wall 02-C10.c -o 02-C10.exe	   
  
   	   where 02 is an example group number and C10 is the Challenge number.
  
  	   You must replace 02 with your own group number!
  
	2. RUN the program's exe file in the command line. Unlike the previous challenges you should NOT use 
	   I/O redirection.
	   
	   		Example: CCPROG2> 02-C10	   

	   Your program should produce two text files named as:
	      a. 02-PORTFOLIO.txt 
		  b. 02-MYTEST.txt
	   based on the two function calls in the main() function. The output files should NOT be created inside
	   the accompanying SHD folder; it should be in the same folder where you have your C source file.
	  
    3. COMPARE your program's 02-PORTFOLIO.txt output file with the accompanying C10-EXPECTED.txt file 
	   using bbtest.c.
    
	   	In case you do not have bbtest.exe, produce it first by compiling bbtest.c as shown below:
		
		 	Example: CCPROG2> gcc -Wall bbtest.c -o bbtest.exe
		 	
	    Thereafter, run bbtest.exe with I/O redirection as shown below:
		
			Example: CCPROG2> bbtest C10-EXPECTED.txt 02-PORTFOLIO.txt > 02-C10-BBTEST.txt
			
		The output redirected file 02-C10-BBTEST.txt contains the results of the comparison.  If you see 
		Differences = 0 towards the end of the file, then it means that your program's output matches the
		expected output.  Otherwise, if you see a Differences value higher than 0, then there's a strong 
		probability that you either have a logical error in your program, or you did NOT follow the
		MP specifications (including the directions in this file).
		
		Debug your C source file, and redo the steps above until you get Differences = 0.
		
		Take note, however, that Differences = 0 does NOT necessarily mean that your solutions is 100% logically
		correct.  The bbtest.exe only tests if two files have the same contents.  It is not meant to test the logic
		of your C program.
	
	4. TEST your solution using the stock historical data for other companies.  Create your own portfolio
	   text file and use them for testing. You'll have to figure out how to verify the correctness of your 
	   program's output using your own portfolio files.	
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*
	TO DO: replace GROUPNUMBER in the #include below with your own group number.  For example if you are group 2,
	you should have #include "02-C6.h".  Group numbers from 1 to 9 should have a leading zero in the filename.
*/
#include "50-C6.h"

// Do NOT edit/delete the next #include directive
#include "numeric_date_helpers.c"  // read and understand the contents of this file

/* Do NOT include other files. */ 

/* 
	Do NOT define any constant in this file.  
    Do NOT declare any typedef that you need below this comment.
	You should encode #define and typedef declarations in your GROUPNUMBER-C6.h header file.
*/



/* 
	HARD REQUIREMENTS: NON-COMPLIANCE WILL MAKE YOUR SOLUTION INCORRECT or CAUSE POINT DEDUCTIONS!
	
	1. You are required to use TEXT FILE PROCESSING commands fopen(), fclose(), fscanf() and fprintf()
	   on top of previous topics in solving Challenge #10.
	2. You are required to implement and use a binary search algorithm for searching using buy date
	   as search key.	
	3. You are NOT allowed to use library functions that were NOT discussed 
	   in our online class.
	4. Apply divide-and-conquer technique by segregating your program's logic into functions.
	   A solution where all the logic are found only in the main() function 
	   will result to a 2-point deduction!
	5. Document your functions with SENSIBLE comments. 	Each function definition must
	   be PRECEDED by an online documentation (in the form comments) describing
	   concisely the following:
			a. What is the purpose of the function?
			b. What is the nature of the functions return value (write "void" if
		   	   the function is of type void)
			c. What is the nature of each formal parameter?
			d. Pre-condition - what are the assumptions about the formal parameters?
	
		Follow the online documentation style in the LinearSearch() example  
		function definition given below.
*/

// DO NOT remove or edit the #if and #endif processor directives
#if 0
/*
	Purpose: determine if the search key is in the array or not using a linear
	         search algorithm 
	Returns: either the (a) index of the array where the key was found or
	         (b) a -1 to indicate that the key was not found
	@param : key is the search key
	@param : A is the name of the array containing the universe of values
	@param : n is the number of array elements to check
	Pre-condition: the parameters contain valid values
*/
int 
Search(key, int A[], int n)
{
	int i; // indexing variable

	// compare the search key with an element in the array
	for (i = 0; i < n; i++)
		if (key == A[i])  
			return i;  // this means that the key was found	

	return -1; // -1 means that the key not found
}
#endif

int BinarySearch(StrDate date, int rows, stockType *ptr); // declare BinarySearch function prototype
/* TO DO: define the functions that you need below this comment. */

/*
	Purpose: Read input text file, then output to another text file the manipulated values derived from the input text file. The output text file will contain:
			 symbol, number of shares bought, buy date, close value of the buy date, close value of the reference date, P/L, and %P/L.
	Returns: void
	@param : portfolio_filename is the file name and extension of the input text file.
	@param : reference_date is the reference date to be used to compare the close values of the buy date, and also to compute for the P/L and %P/L corresponding to the close value of both dates.
	Pre-condition: The portfolio_filename denotes a text file that exists and contains a symbol, # of shares bought, and buy date for each row.
				   The reference_date must also denote a date that have a valid activity on it.
*/
void read_Portfolio(String50 portfolio_filename, StrDate reference_date){

	FILE *fp_portfolio; // file pointer for the input text file containing the SHD symbol, number of shares bought, and buy date.
	FILE *fp_reference; // file pointer for the actual SHD file of the corresponding symbol stored inside the SHD folder.
	FILE *fp_output; // file pointer for the file where the read values from fp_portfolio and fp_reference are to be written.
	
	String50 grpNum = "C:\\Users\\robi_\\OneDrive\\Desktop\\CCPROG 2 MPS\\50-"; // location of where this c source code is saved.
	strcat(grpNum, portfolio_filename); // concatenates the portfolio text file name to the location, for example: "C:\\Users\\robi_\\OneDrive\\Desktop\\CCPROG 2 MPS\\50-PORTFOLIO.txt"
										// to be used later for fp_output.

	StrStock code; // store the current symbol of the corresponding row in the input text file, which contains the SHD symbol, number of shares bought, and buy date.

	stockType temp;	// temporary struct to store the values of the actual SHD file containing 
					// the symbol and number of rows, then the date, OHLC, and volume values in each row.

	portfolioType tempPortfolio[50]; // temp struct to store the values of the input text file containing the SHD symbol, number of shares bought, and buy date.
	
	int buyDateIndex; // to store the index returned by the binary search, passing the buy date indicated in the input text file.
	int refDateIndex; // to store the index returned by the binary search, passing the reference date.

	double PL; // to store the P/L using the close value of the reference date and the buy date.
	double pPL; // to store the %P/L using the close value of the reference date and the buy date.
	
	fp_portfolio = fopen(portfolio_filename, "r"); // read mode: opens the input text file to be read, which is the file containing the SHD symbol, number of shares bought, and buy date.
	
	int i = 0;
	if (fp_portfolio != 0){ // if input file exists
		while (fscanf(fp_portfolio, "%s %lf %s", tempPortfolio[i].symbol, &tempPortfolio[i].shares, tempPortfolio[i].buydate) == 3){ // loop until there are still rows to be read 
		                                                                                                                             // from the input text file.
			i++;
		}	
		fclose(fp_portfolio); // close input text file.
	}
	else{ // if input file does not exist.
		fprintf(stderr, "%s does not exist.", portfolio_filename);
	}
	
	fp_output = fopen(grpNum, "w"); // write mode: opens the file where the output is to be written. If the file does not yet exist, the created new file will be stored and named 
								    // according to the grpNum string. Ex. "C:\\Users\\robi_\\OneDrive\\Desktop\\CCPROG 2 MPS\\50-PORTFOLIO.txt". note: it's double "\" because "\" is a special char.

	fprintf(fp_output, "PORTFOLIO PERFORMANCE AS OF %s\n\n", reference_date); // initial print of the output file, ex. "PORTFOLIO PERFORMANCE AS OF 04/01/2022"
	
	int j; // counter to be used for how many iterations the whole process needs to undergo. This is depending on how many rows are there in the input text file, which is stored in i;
	int k; // counter to be used for the storing of the actual SHD text file into the temp structure.

	for (j = 0; j < i; j++){ // loop until number of rows in the input text file are met.

		String50 folderLoc = "C:\\Users\\robi_\\OneDrive\\Desktop\\SHD\\"; // location of the SHD folder where the SHD text file(s) containing the actual data is stored.
		
		strcpy(code, tempPortfolio[j].symbol); // copies the symbol of the current row of the input text file to the string code.
		strcat(tempPortfolio[j].symbol, ".txt"); // concatenates the symbol with a .txt EX. AMZN -> AMZN.txt
		strcat(folderLoc, tempPortfolio[j].symbol); // concatenates the concatenated symbol with the location of the SHD folder. EX. "C:\\Users\\robi_\\OneDrive\\Desktop\\SHD\\AMZN.txt"
		
		fp_reference = fopen(folderLoc, "r"); // read mode: opens the actual SHD text file corresponding to the concatenated folderLoc string.
		
		fscanf(fp_reference, "%s %d", temp.symbol, &temp.rows); // initial scan of the SHD text file
		
		k = 0;
		while (fscanf(fp_reference, "%s %lf %lf %lf %lf %lf", 
									temp.SHD[k].date, &temp.SHD[k].open, &temp.SHD[k].high, &temp.SHD[k].low, &temp.SHD[k].close, &temp.SHD[k].volume) == 6){ // store the SHD text file into
																																							  // the temp structure.
									k++;	
									}
									
		buyDateIndex = BinarySearch(tempPortfolio[j].buydate, temp.rows, &temp); // pass the current buydate of the input file, along with the rows and the address of the temp structure.
		refDateIndex = BinarySearch(reference_date, temp.rows, &temp); // pass the reference_date, along with the rows and the address of the temp structure.
		
		PL = temp.SHD[refDateIndex].close - temp.SHD[buyDateIndex].close; // subtract the close value of the buydate to the close value of the reference date, which is the PL of the current row.
		pPL = PL/temp.SHD[buyDateIndex].close * 100; // divide the PL by the close value of the buydate and multiplies it by 100, which is the %P/L of the current row.
		
		fprintf(fp_output, "%-4s   %-12.6lf   %-4s   %-12.6lf   %-12.6lf   %-12.6lf   %-12.6lf\n", 
							code, tempPortfolio[j].shares, tempPortfolio[j].buydate, temp.SHD[buyDateIndex].close, temp.SHD[refDateIndex].close, PL, pPL); // prints the corresponding values to the
																																						   // output/destination file.
																																						   
		fclose(fp_reference); // close SHD text file.
	}

	fclose(fp_output); // close output/destination file.
}


/*
	You are required to implement and use a binary search algorithm for searching the buy date
	as search key.  Implement your binary search function after this comment...
*/

/*
	Purpose: search for the key, which in this case is a string date, in the temp structure. If it is found, will return the index where it was found,
			 otherwise will return -1.
	Returns: if found: returns mid, which is the index where it was found.
			 if not found: returns -1.
	@param : date is the string date to be searched in the temp structure.			 
	@param : ptr is a pointer to a structure, in this case pointing to the stockType temp structure in the read_Portfolio function.
	Pre-condition: the stockType temp structure already have values stored inside.
*/
int BinarySearch(StrDate date, int rows, stockType *ptr){
	int high = rows - 1;
	int low = 0;
	int mid;
	int nKey = numeric_date(date); // converts the string date into an integer with the format YYYYMMDD
	
	while (low <= high){
		mid = low + (high - low)/2;
		if (nKey == numeric_date(ptr->SHD[mid].date))
			return mid; // key was found
		else if (nKey > numeric_date(ptr->SHD[mid].date))
			high = mid - 1; // search lower half
		else
			low = mid + 1; // search upper half
	}
	
	return -1;
}



/*
	TO DO: Complete the body of the main() function.
*/
int
main()
{
	char portfolio_filename[100];
	char reference_date[11];
	// do NOT declare other variables 
	
	// Fill in the blank by supplying the name of the function that will process 
	// the contents of the portfolio text file based on the specified reference date.
	// 
	// Except for the required function names, you are NOT allowed to add any
	// other lines of codes.
	

	// Test #1: based on hardcoded actual parameters
	read_Portfolio("PORTFOLIO.txt", "04/01/2021");  

	
	// Test #2: based on actual parameters specified via scanf()
	printf("Input the name of your test portfolio file: ");
	scanf("%s", portfolio_filename);   // example: MYTEST.txt or other files that you may want 
	                                   // to use for testing

	printf("Input a reference date in MM/DD/YYYY format: ");
	scanf("%s", reference_date);  // example: 04/01/2022  or other dates you may want to use for testing
	
	read_Portfolio(portfolio_filename, reference_date);
	
	return 0;
}

