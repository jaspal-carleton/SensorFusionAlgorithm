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
7. Provide permissions to run env_setup script 
```
chmod 777 env_setup.sh
```

8. Install GSL Environment setup by issuing below command 
```
./env_setup.sh
```
9. Set the newly installed GSL Library as a path variable by issuing below command 
```
source ~/.bashrc
```
or 

edit ~/.bashrc file using vi/vim and add a path variable pointing to lib/gsl/lib folder
