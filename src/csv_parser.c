/**
 * \brief CSV Parser function to read given input csv file and store
 *  it into a 2D array and extract all sensor readings for unique
 *  time stamps and store it a 2D array with each row representing one unique time stamp
 * \limitations This CSV Parser can read maximum of 10 unique time stamps and each time
 *  stamp can have maximum of 20 sensor readings, therefore a total of maximum 200 
 *  sensor readings
 *  \Full CSV File can be accessed at csv[][3]
 	 First unique time stamp can be accessed at csv[0][0]
 	 Rest of the Individual unique time stamps can be accessed in csv[u_ts[]][0] 
     sensor readings for each unique time stamps can be accessed at sr[][] at row wise
     number of sensor readings at each time stamps can be accessed at sr_c[]   
 * \author Vinay Venkataramancahary vinayvenkataramanach@cmail.carleton.ca
 * \version 1.0
 * \date 2019-Dec-14
 */

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

/** Define the number of columns as 3 for storing CSV file into a 2D Array. 
 *  Input CSV file has 3 Columns Time Stamp, Sensor name, Sensor Reading */
	
#define COL 3 

/**
 * \brief Helper Function to get Sample CSV File Size
 * \details Use of File stream and File functions fseek and ftell to 
 *  compute the size
 * \param[in] Pointer to the File of Input CSV
 * \return Integer: Value representing Size of the file
 * \return Failure: No Error messages
 */
 
int getfilesize(char *fname){
  /*  Open the stream pointer to the file passed by the function call
   * and set cursor to end and count by using ftell
   */
	FILE *fp = fopen(fname, "r"); 
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    fclose(fp);
    return size;
}

/**
 * \brief Reads csv file into a local buffer
 * \details Tokenize string at comma, convert text data to integer and 
 *  write it into 2D buffer
 * \param[in] Pointer to the File of Input CSV, Pre-Initialized 2D Array
 *  named csv[Number of Columns], Integer with number of Rows
 * \return Integer: 2D Array with rowsx3 matrix where rows is equal to 
 *	number of time stamps read from Input CSV
 * \return Failure: No Error message built into it
 */
 
void read_csv(char *fname, float (*array)[COL], int rows){
    /* allocate memory buffer for file read 
    *  read csv file into buffer 
    */
    int size = getfilesize(fname);
    char *buf = malloc(size +1);
    FILE *fp = fopen(fname, "r");
    fread(buf, size, 1, fp);
    fclose(fp) ;
    /* structurized tokenize for comma or new line */
    char *tok = strtok(buf, ",\n");
    for(int i=0;i<rows;i++){
    	for(int j=0;j<COL;j++){
      		if(tok == NULL){
       			break;
       		}
      		/* convert text numeral to integer */
      		float val = atof(tok);
      		/* Store each fields of CSV file into array[][] */
      		array[i][j] = val;
 			/* tokenize at comma or newline */
     		tok = strtok(NULL, ",\n");
     	}
    }
	free(buf);
}

/**
 * \brief main function, accepts input CSV file and calls csv helper functions
 *  to obtain 2D array and extract sensor reading for each time stamp.
 * \details Call readcsv() function to parse CSV file in the form 
 *  of 2D array and perform array operations to extract sensor readings
 *  for each time stamp and store it in a 2D array
 * \param[in] CSV File
 * \return 2D array: csv[][] [rowsx3] matrix where rows is equal to 
 *  number of time stamp read from Input CSV
 * \return 2D array: sr[][] with all sensor readings for each time stamp
 * \return 1D array: u_ts[] position of unique time stamps in CSV file starting
     from 2nd Time stamp
 * \return 1D array: sr_c[] number of sensors in each individual time stamps 
 * \return Failure: No Error messages
 */
 
int main()
{
	/** Define variables to store sensor readings for each time stamp
	 * 	 1) csv file, csv[][] stores csv file as a 2D array 
	 *   2) Sensor reading 2D array, sr[10][10] represents 2D array which 
	 *      will store sensor raedings for each time stamps row wise. (upto 10)
	 *      ex. sr[0][] will have all sensor readings for timestamp1
	 *   3) Unique time stamps counter u_ts[] points to position of unique 
	 		time stamps in csv[][]
	 		unique time stamps can be accessed at csv[0][0] and csv[u_ts[]][0]
	 *   4) sr_c[20] stores no of sensor readings in a individual time 
	 *      stamp ex. sr_c[0]=2 represents 2 sensor readings in time stamp0
	 */
	float sr[10][10] = {0};
    int sr_c[20] = {0};
    int u_ts[10];
   	int count=0;
    char line[1024];
    FILE *lp;
    lp = fopen("sample.csv", "r");
    /** Count number of rows in CSV file */
    while (fgets(line, 1024, lp )) {
			count++;
		}
	int ROWS = count;
	float csv[ROWS][COL];
	/** Initialize csv[][] to 0 */
	for(int i=0;i<ROWS;i++){
		for(int j=0;j<COL;j++){
			csv[i][j]=0;
		}
	}
	/** Input CSV file name */
	char *fname = "sample.csv";
	/* Call read_csv function to read input csv file
	 * and store it as a 2D array csv[][] */
	read_csv(fname, (float(*)[COL])csv, ROWS);
	/** Display CSV File from csv[][] as three coumns describing each columns  */
	printf("\nCSV File stoted as a 2D array in csv[][3],\n1st Column"
		   "is time stamp, 2nd column is Sensor," 
		    "3rd Column is Sensor reading:\n");
	for(int i=0;i<ROWS;i++){
		for(int j=0;j<COL;j++){
			printf("%f |", csv[i][j]);
		}
		printf("\n");
	}
    /* Identify unique time stamps and compute number of sensor readings in each unique time stamp
    * and store all the sensor readings into a 2D array where each row represents one time stamp
    * For ex: sr[0][] row will contain all sensor readings for 1st time stamp of the csv file
    * sr[1][] will contain all sensor readings for 2nd time stamp
    * sr_c[] will contain number of sensors in each time stamp. For ex: value stored in ts_c[0] 
    * represents number of sensor readings in time stamp0
	* Extract sensor readings for time stamp 0 and store in sr[0][]
	* u_ts points to position of unique time stamps in csv[][]
	*/
	for(int i=0;i<ROWS;i++){
		if (csv[i][0]== csv[0][0]){
			sr[0][i] = csv[i][2];
			sr_c[0]++;
			u_ts[0] = sr_c[0];
		}
		/* Extract sensor eadings for time stamp 1 and store in sr[1][]*/
		else if (csv[i][0]== csv[u_ts[0]][0]){
			sr[1][sr_c[1]] = csv[i][2];
			sr_c[1]++;
			u_ts[1] = sr_c[0]+sr_c[1];
		}
		/* Extract sensor eadings for time stamp 2 and store in sr[2][]*/
		else if (csv[i][0]== csv[u_ts[1]][0]){
			sr[2][sr_c[2]] = csv[i][2];
			sr_c[2]++;
			u_ts[2] = sr_c[0]+sr_c[1]+sr_c[2];
		}
		/* Extract sensor eadings for time stamp 3 and store in sr[3][]*/
		else if (csv[i][0]== csv[u_ts[2]][0]){
			sr[3][sr_c[3]] = csv[i][2];
			sr_c[3]++;
			u_ts[3] = sr_c[0]+sr_c[1]+sr_c[2]+sr_c[3];
		}
		/* Extract sensor eadings for time stamp 4 and store in sr[4][]*/
		else if (csv[i][0]== csv[u_ts[3]][0]){
			sr[4][sr_c[4]] = csv[i][2];
			sr_c[4]++;
			u_ts[4] = sr_c[0]+sr_c[1]+sr_c[2]+sr_c[3]+
			       sr_c[4];
		}
		/* Extract sensor eadings for time stamp 5 and store in sr[5][]*/
		else if (csv[i][0]== csv[u_ts[4]][0]){
			sr[5][sr_c[5]] = csv[i][2];
			sr_c[5]++;
			u_ts[5] = sr_c[0]+sr_c[1]+sr_c[2]+sr_c[3]+
			       sr_c[4]+sr_c[5];
		}
		/* Extract sensor eadings for time stamp 6 and store in sr[6][]*/
		else if (csv[i][0]== csv[u_ts[5]][0]) {
			sr[6][sr_c[6]] = csv[i][2];
			sr_c[6]++;
			u_ts[6] = sr_c[0]+sr_c[1]+sr_c[2]+sr_c[3]+
				   sr_c[4]+sr_c[5]+sr_c[6];
		}
		/* Extract sensor eadings for time stamp 7 and store in sr[7][]*/
		else if (csv[i][0]== csv[u_ts[6]][0]) {
			sr[7][sr_c[7]] = csv[i][2];
			sr_c[7]++;
			u_ts[7] = sr_c[0]+sr_c[1]+sr_c[2]+sr_c[3]+
				   sr_c[4]+sr_c[5]+sr_c[6]+sr_c[7];
		}
		/* Extract sensor eadings for time stamp 8 and store in sr[8][]*/
		else if (csv[i][0]== csv[u_ts[7]][0]) {
			sr[8][sr_c[8]] = csv[i][2];
			sr_c[8]++;
			u_ts[8] = sr_c[0]+sr_c[1]+sr_c[2]+sr_c[3]+
				   sr_c[4]+sr_c[5]+sr_c[6]+sr_c[7]+
				   sr_c[8];
		}
		/* Extract sensor eadings for time stamp 9 and store in sr[9][]*/	
		else if (csv[i][0]== csv[u_ts[8]][0]) {
			sr[9][sr_c[9]] = csv[i][2];
			sr_c[9]++;
			u_ts[9] = sr_c[0]+sr_c[1]+sr_c[2]+sr_c[3]+
			       sr_c[4]+sr_c[5]+sr_c[6]+sr_c[7]+
			       sr_c[8]+sr_c[9];
			}
	}
	/* Print each individual rows in sr[][] array to confirm the 
	 * sensor readings stored for each time stamp*/
	/* Print row 0 of sr[0][] array to display sensor readings 
	* of time stamp 0 (csv[0][0]) */
	printf("\nSensor readings for timestamp0 {%f} stored in sr[0][]"
			"array in row 0 (ranging from 0 to time stamp1" 
			" counter sr_c[0]) is\n", csv[0][0]);
	for(int i=0;i<sr_c[0];i++) {
		printf("%f \n",sr[0][i]);
	}
	/* Print row 1 of sr[1][] array to display sensor readings 
	* of time stamp 1 (csv[u_ts[0]][0]) */
	printf("\nSensor readings for timestamp1 {%f} stored in sr[1][]"
			"array in row 1 (ranging from 0 to time stamp2" 
			" counter sr_c[1]) is\n",csv[u_ts[0]][0]);
	for(int i=0;i<sr_c[1];i++) {
		printf("%f \n",sr[1][i]);
	}
	/* Print row 2 of sr[2][] array to display sensor readings 
	* of time stamp 2 (csv[u_ts[1]][0]) */
	printf("\nSensor readings for timestamp2 {%f} stored in sr[2][]"
		  "array in row 2 (ranging from 0 to time stamp3"
		  " counter sr_c[2]) is\n", csv[u_ts[1]][0]);
	for(int i=0;i<sr_c[2];i++) {
		printf("%f \n",sr[2][i]);
	}
	/* Print row 3 of sr[3][] array to display sensor readings 
	* of time stamp 3 (csv[u_ts[2]][0]) */
	printf("\nSensor readings for timestamp3 {%f} stored in sr[3][]"
		    "array in row 3 (ranging from 0 to time stamp4" 
		    " counter sr_c[3]) is\n", csv[u_ts[2]][0]);
	for(int i=0;i<sr_c[3];i++) {
		printf("%f \n",sr[3][i]);
	}
		/* Print row 4 of sr[4][] array to display sensor readings 
	* of time stamp 4 (csv[u_ts[3]][0]) */
	printf("\nSensor readings for timestamp4 {%f} stored in sr[4][]"
		    "array in row 4 (ranging from 0 to time stamp5" 
		    " counter sr_c[4]) is\n", csv[u_ts[3]][0]);
	for(int i=0;i<sr_c[4];i++) {
		printf("%f \n",sr[4][i]);
	}
    /* Print row 5 of sr[5][] array to display sensor readings 
	* of time stamp 5 (csv[u_ts[4]][0]) */
	printf("\nSensor readings for timestamp5 {%f} stored in sr[5][]"
				"array in row 5 (ranging from 0 to time stamp6" 
				" counter sr_c[5]) is\n", csv[u_ts[4]][0] );
	for(int i=0;i<sr_c[5];i++) {
		printf("%f \n",sr[5][i]);
	}
	  /* Print row 6 of sr[6][] array to display sensor readings 
	* of time stamp 6 (csv[u_ts[5]][0]) */
	printf("\nSensor readings for timestamp6 {%f} stored in sr[6][]" 
			"array in row 6 (ranging from 0 to time stamp7" 
			" counter sr_c[6]) is\n", csv[u_ts[5]][0]);
	for(int i=0;i<sr_c[6];i++) {
		printf("%f \n",sr[6][i]);
	}
	  /* Print row 7 of sr[7][] array to display sensor readings 
	* of time stamp 7 (csv[u_ts[6]][0]) */
	printf("\nSensor readings for timestamp7 {%f} stored in sr[7][]"
			"array in row 7 (ranging from 0 to time stamp8" 
			" counter sr_c[7]) is\n", csv[u_ts[6]][0]);
	for(int i=0;i<sr_c[7];i++) {
		printf("%f \n",sr[7][i]);
	}
	/* Print row 8 of sr[8][] array to display sensor readings 
	* of time stamp 8 (csv[u_ts[7]][0]) */
	printf("\nSensor readings for timestamp8 {%f} stored in sr[8][]"
			"array in row 8 (ranging from 0 to time stamp9" 
			" counter sr_c[8]) is\n", csv[u_ts[7]][0]);
	for(int i=0;i<sr_c[8];i++) {
		printf("%f \n",sr[8][i]);
	}
	/* Print row 9 of sr[9][] array to display sensor readings 
	* of time stamp 9 (csv[u_ts[8]][0]) */
	printf("\nSensor readings for timestamp9 {%f} stored in sr[9][]"
			"array in row 9 (ranging from 0 to time stamp10"
			" counter sr_c[9]) is\n", csv[u_ts[8]][0]);
	for(int i=0;i<sr_c[9];i++) {
		printf("%f \n",sr[9][i]);
	}	
}