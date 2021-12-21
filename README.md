# Group 2 – COVID-19 ASSESSMENT & APPOINTMENT APPLICATION 
## Table of Contents
- [Team Members](https://github.com/owiekris/COVID-19-ASSESSMENT-APPOINTMENT-APPLICATION#team-members)

- [Application Description](https://github.com/owiekris/COVID-19-ASSESSMENT-APPOINTMENT-APPLICATION#application-description)

- [File Description](https://github.com/owiekris/COVID-19-ASSESSMENT-APPOINTMENT-APPLICATION#file-description)

- [Getting Started](https://github.com/owiekris/COVID-19-ASSESSMENT-APPOINTMENT-APPLICATION#getting-started)
    1. [Compilation Tools](https://github.com/owiekris/COVID-19-ASSESSMENT-APPOINTMENT-APPLICATION#1-compilation-tools)
    2.  [Building the Software](https://github.com/owiekris/COVID-19-ASSESSMENT-APPOINTMENT-APPLICATION#2-building-the-software)
    3. [Testing the Software](https://github.com/owiekris/COVID-19-ASSESSMENT-APPOINTMENT-APPLICATION#3-testing-the-software)
    4. [ Running the main application](https://github.com/owiekris/COVID-19-ASSESSMENT-APPOINTMENT-APPLICATION#4-running-the-main-application)

- [Documentation](https://github.com/owiekris/COVID-19-ASSESSMENT-APPOINTMENT-APPLICATION#documentation)

### Team Members
**Organization:** Carleton University

**Course:** SYSC 4006A - Software Development with C

**Authors:**
|Student |Github ID  |
--- | --- | 
|Christopher Owoicho|owiekris|
|Shailesh Sankdasariya |shailesh-229|
|Ritesh Panday |designerpanda|
|Gajan Satkunanathan |Gajansat10|

### Application Description
This software application provides a worry free, open source and reliable software for business owners to use to schedule appointments with their client in this unusual world dominated by the COVID 19 virus. This pplication provides the following services:
- Collect the identification information of a user using Predefined Dataset of questions and provide unique client identification number for further tracking of status.
- To develop an algorithm which can classify user based on given answer and allocate further task to be done. 
    - Symptomatic Users: Ask user to isolate and inform their steward. 
    - Asymptomatic Users (non-vaccinated/Partially): Find suitable slot and allocate appointment of user’s choice. 
    - Asymptomatic Users (vaccinated): Authenticate their vaccination status and terminate. 

- Create appointment booking system, which can allocate new booking or modify existing booking. 

- Update and Notify users with e-receipt as acknowledgement. 

- Create time-stamped reports of the allocated appointments. The report must synchronize & update if appointment status is changed. 

- Maintain an updated private database of all registered users. 

Detailed information about the application can be found [here](https://github.com/owiekris/COVID-19-ASSESSMENT-APPOINTMENT-APPLICATION/wiki).

### File Description
The Application file is arranged as follows:
|Main Folder Structure|Description|
| ---- | ---------- |
|/bin|  Executables for the application and the tests
|/build|contains compiler's build make files for the application and test cases|
|/data|  Contains all required data to run the application. It includes the database structure text files and database csv files|
|/doc|contains user and developer manuals|
|/html| contains doxygen documentation file.html| 
|/include| Subfolders for the application header| 
|/src| Function source code files|
|/test| Test sources and required data for testing|
|/video| video folder containing project user demo|
|/license|License of the application|
|README.md|contains details on the read me document|
|/lib|Contains the README file|
|main.c|main program file|
|/cmake| contains the cmake file|

### Getting Started
##### 1. Compilation Tools
We rely on third-party software to run our application. The main dependencies for each platform are as follows:
- Windows Users
    - Cygwin
    - GNU C Compiler, Git, Make, and CMake
    
- MacOS Users
    - Command Line Tools
    - GNU C Compiler, Git, Make, and CMake
    
- Linux Users
    - GNU C Compiler, Git, Make, and CMake

Detailed instructions about the installation of these dependencies are provided [here](https://github.com/owiekris/COVID-19-ASSESSMENT-APPOINTMENT-APPLICATION/wiki).

##### 2. Building the software
Once you have installed all the compilation tools, building the application should be straightforward.
-  Open a terminal (Windows users should use a Cygwin terminal)
- Download this repository in your home directory and move inside the repository:
```
cd git clone https://github.com/owiekris/COVID-19-ASSESSMENT-APPOINTMENT-APPLICATION.git
```
Once the process is finished, go to command prompt, open the directory and type :
```
make app
```
You should be able to see the below:

- a /bin directory with all the binaries (main function and tests) generated
Navigate to the bin folder and type:
```
app.exe
```
##### 3. Testing the software
For testing navigate to test folder and run:
Use make to run the tests:
```
cd build make test
```

##### 4. Running the main application
To run the main application, open and run the application make file. The database will be updated in real time as the valid inputs from the user is saved correctly.
```
cd bin app.exe
```

#### Documentation
All documentation regarding this application can be found in the project's GitHub repository. Please refer to the [user documentation](https://github.com/owiekris/COVID-19-ASSESSMENT-APPOINTMENT-APPLICATION/wiki/3.-User-Documentation:-How-to-Use) and [developer documentation](https://github.com/owiekris/COVID-19-ASSESSMENT-APPOINTMENT-APPLICATION/wiki/4.-Developer-Documentation).
