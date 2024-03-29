## Sensor fusion Software based on Principal Component Analysis ##

The purpose of the sensor fusion software is to calculate a single aggregate fused value from a stream of sensor data input by essentially adapting a sensor fusion algorithm. Sensor fusion algorithm in consideration is “A Simple Multi-Sensor Data Fusion Algorithm Based on Principal Component Analysis” [1]  The software accepts csv file with time stamp, sensors and individual sesnor reading data as input, and performs principal component calculations to return a fused sensor output. The value generated by the algorithm is representative of the correct raw data from the sensors (i.e. there may be sensors giving wrong measures, sensor fusion algorithm analyses various different sensors and eliminate errors), The software also generates log information for every execution so that any errors during execution can be taken a deep look by end user for trooubleshooting 

[1] Hongyan, G.A.O., 2009, August. A simple multi-sensor data fusion algorithm based on principal component analysis. In 2009 ISECS International Colloquium on Computing, Communication, Control, and Management (Vol. 2, pp. 423-426). IEEE.

### Disclaimer

This software is a mere implementation of the research work presented in [1] and is not a reproduction of any sort. This project is soley meant for academic reasearch purpose only. As per authors best knowledge, no copyright violations were observed.

### Authors

1.  Jaspal Singh: jaspalsingh@cmail.carleton.ca
2.  Vinay Venkataramanachary: vinayvenkataramanach@cmail.carleton.ca

### Colloborators

1. Dr. Cristina Ruiz Martín
2. Scott Jordan
3. Tarun Panuganti

### Organization

Carleton University, Ottawa, ON , CANADA

### Folder Structure of the repository

```bash
│   .gitignore
│   CHANGELOG.md
│   env_setup.sh
│   Install.md
│   LICENSE.md
│   makefile
│   README.md
│
├───data
│   ├───input
│   │       input.csv
│   │
│   └───output
│           output.csv
│
├───doc
│       1. user_manual.pdf
│       2. developer_manual.pdf
│       3. coding_conventions.pdf
│       4. proposed_design_document.pdf
│
├───include
│       log_handling.h
│       sensor_fusion.h
│
├───logs
│       samplelog.txt
│
├───src
│       log_handling.c
│       main.c
│       sensor_fusion.c
│
└───test
    ├───data
    │       manual_testing_summary.xlsx
    │       manual_test_results.xlsx
    │       sample.csv
    │
    ├───include
    │       test.h
    │
    └───src
            test.c
```

### Input

Input is stored in /data/input/input.csv
To obtain fused output for any desired csv files, uplaod desired input csv files to /data/iput/ folder and name it as input.csv

### Output

Output will be displayed on the terminal upon execution of the build file.
Apart from the terminal display, the output is also stored in a output folder /data/output/output.csv

### Pre-Requisites to run the software

Platform compatibility : Linux Distributions Ubuntu 18.04, CentOS 7.4; MAC OS 10.14 Mojave; Windows 10.

1. Git
2. GNU packages (make, cmake)
2. gcc compiler
2. GSL library
3. Path varaibles set to to use GSL library

### Instructions to setup pre-requsites on Ubuntu 18.04 platform/ MAC OS

Refer to Install.md file

### Instructions to run the software

Note: Please ensure that all pre-requsisted have been met.
If you are using Non Linux machine, Please ensure to meet all the pre requsities mentioned above 
Ensure to install make, cmake, wget packages in Cygwin to run the make commands

Step 1 : Open a terminal with make access and navigate to the root  folder of repository 

Step 2 : Clean residual files
```
make clean
```
Step 3 : Build the project (Ignore warnings if any)

```
make
```

Step 4 : Navigate to bin folder
```
cd bin
```

Step 5 : run the build main file by issuing below command 
```
./main
```
Software exceutes and displays fused outputs on the terminal screen

### Instructions to perform testing of the functions

Step 1 : Open a terminal with make access and navigate to the root  folder of repository 

Step 2 : Clean residual files
```
make clean
```
Step 3 : Build the project (Ignore warnings if any)

```
make
```

Step 4 : Navigate to bin folder
```
cd bin
```

Step 5 : For testing the various sensor APIs issue below command 

```
./main -t
```

Test Cases will exceute and display the result on terminal or screen


### Additional feature of the software

Logging feature

Log files are generated for each execution and is stored on /logs folder
Log files are named after execution time stamp. 
Expectation of Log files: All the execution related information will be stored in log information which includes input, output and execution time
(In current release, log files with execution timetstamp is getting generated however due to some bugs, we are not able store any information into these log files)

### Manual testing Results

12 manual test cases were performed on the software, relevant test file locations are described as below

1. Summary of manual testing can be found on /test/data/manual_testing_summary.xlsx
2. Results of all 12 manual test cases can be found on /test/data/manual_test_results.xlsx

### Detailed end user documentation

For detailed end user documentation click link below

<https://github.com/jaspal-carleton/SensorFusionAlgorithm/blob/master/doc/1.%20user_manual.pdf>


### Detailed developer documentation

For detailed developer documentation click link below

<https://github.com/jaspal-carleton/SensorFusionAlgorithm/blob/master/doc/2.%20developer_manual.pdf>

### Coding Convention documentation

For detailed coding convention documentation click link below

<https://github.com/jaspal-carleton/SensorFusionAlgorithm/blob/master/doc/3.%20coding_conventions.pdf>

### Proposed Software Design Documentation (Deliverable 1)

For detailed coding convention documentation click link below

<https://github.com/jaspal-carleton/SensorFusionAlgorithm/blob/master/doc/4.%20proposed_design_document.pdf>