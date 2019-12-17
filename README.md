## Sensor fusion Software based on Principal Component Analysis ##

The purpose of the sensor fusion software is to calculate a single aggregate fused value from a stream of sensor data input by essentially adapting a sensor fusion algorithm. Sensor fusion algorithm in consideration is “A Simple Multi-Sensor Data Fusion Algorithm Based on Principal Component Analysis” [1]  The software accepts csv file with time stamp, sensors and individual sesnor reading data as input, and performs principal component calculations to return a fused sensor output. The value generated by the algorithm is representative of the correct raw data from the sensors (i.e. there may be sensors giving wrong measures, sensor fusion algorithm analyses various different sensors and eliminate errors), The software also generates log information for every execution so that any errors during execution can be taken a deep look by end user for trooubleshooting 

[1] Hongyan, G.A.O., 2009, August. A simple multi-sensor data fusion algorithm based on principal component analysis. In 2009 ISECS International Colloquium on Computing, Communication, Control, and Management (Vol. 2, pp. 423-426). IEEE.

### Disclaimer

This software is a mere implementation of the research work presented in [1] and is not a reproduction of any sort. This project is soley meant for academic reasearch purpose only. As per authors best knowledge, no copyright violations were observed  

### Authors

1.  Jaspal Singh: jaspalsingh@cmail.carleton.ca
2.  Vinay Venkataramanachary: vinayvenkataramanach@cmail.carleton.ca

### Colloborators

1. Dr. Cristina Ruiz Martín
2. Scott Jordan
3. Tarun Panuganti

### Organization

Carleton Univresity, Ottawa, ON , Canada

### Folder Structure of the repository

![Folder Structure](/include/Folderstructure.png)



### Pre-Requisites to run the software

Platform compatibility : Linux Distributions Ubuntu 18.04, CentOS 7.4, MAC OS, Windows 10

1. Git
2. GNU packages (make, cmake)
2. gcc compiler
2. GSL library
3. Path varaibles set to to use GSL library

### Instructions to setup pre-requsites on Ubuntu 18.04 platform

1. Open Terminal Window in the desired directory

2. Install Git by using below command
```
sudo apt install git
```
3. Install GCC compiler by issuing below command
```
sudo apt install gcc
```
4. Install GNU packages by issuing below command 
```
sudo apt install build-essentials
```

5. Clone the repository by issuing below command
```
git clone https://github.com/jaspal-carleton/SensorFusionAlgorithm.git
```
6. Navigate to the Git Repository folder by issuing below command 
```
cd SensorFusionAlgorithm
```
6. Install GSL Environment setup by issuing below command 
```
./env_setup.sh
```
7. Set the newly installed GSL Library as a path variable by issuing below command 
```
source ~/.bashrc
```
or 

edit ~/.bashrc file using vi/vim and add a path variable pointing to lib/gsl/lib folder

### Instructions to run the software

Note: Please ensure that all pre-requsisted have been met.
If you are using Non Linux machine, Please ensure to meet all the pre requsities mentioned above 
Ensure to install make, cmake, wget packages in Cygwin to run the make commands

Step1 : Open a terminal with make access and navigate to the root  folder of repository 

Step2 : Clean residual files
```
make clean
```
Step2 : Build the project

```
make
```
Step 3 : Navigate to bin folder

Step 4 : run the build main file by issuing below command 
```
./main
```
Software exceutes and displays fused outputs on the terinal screen

### Output

Output will be displayed on the terminal upon execution of the build file
Apart from the terminal display, the output is also stored in a output folder /data/output/output.csv

Logs files captures log information for every execution and stores it at /logs folder

### Input

Input is stored in /data/input/input.csv
To obtain fused output for any desired csv files, uplaod desired input csv files to /data/iput/ folder and name it as input.csv

### Detailed end user documentation (WIP)

Detailed end user documentation can be found at /doc/user_manual.pdf

### Detailed developer documentation  (WIP)

Detailed developer  documentation can be found at /doc/developer_manual.pdf

### Coding Convention documentation  (WIP)

Detailed coding convention  documentation can be found at /doc/coding_convention.pdf

### Proposed Software Design Documentation  (WIP)

Detailed coding convention  documentation can be found at /doc/proposed_design_document.pdf