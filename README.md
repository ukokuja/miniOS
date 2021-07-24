![alt text](https://www.hit.ac.il/.upload/academic-entrepreneurship/iris/partners/shenkarLogo.jpg "Shenkar")

## 🖥️‍ Course: Operating Systems ##
### Lecturer: **Raz Ben Yehuda**

Student name            | ID
| -------------         |-------------
| Daniel Modilevsky     | 312493000
| Saar Pernik           | 308491265
| Lucas Kujawski        | 345535330



Mini OS
=====================================

________________
#### 🏁 Instructions ####
1. ```$ make all```
2. ```$ ./miniOS -p<#processors> -n<#tasks> -c<#clock interval>```
   
i.e. ```$ ./miniOS -p3 -n4 -c2```

#### 🏃 Output ####
1. In order to see scheduler actions:
   
   ```$ tail -f  logAction.csv```
________________
### API ###

Method            | Location
| -------------     |-------------  
|void taskWake(OS *os, pid_t id) | OS/OS.h
|char taskShouldSuspend(OS *os, Task *task) | OS/OS.h
|void taskSetName(char *) | OS/OS.h
|void taskSetId(Task *task, pid_t _pid) | Task/Task.h
|char *taskGetName(Task *task)| Task/Task.h
|pid_t taskGetId(Task *task)| Task/Task.h
|void taskSuspend(Task *task)| Task/Task.h
|void taskWait(int t)| Task/Task.h
|int taskPrio(Task *task)| Task/Task.h

Defaults:

Argument            | Default       
| -------------     |-------------  
| # Tasks *         | -             
| # Processor       | 1             
| # Clock interval  | 1             
* field is mandatory

#### 💿‍ Class Diagram ####
![Class](https://i.imgur.com/y9iXWnx.png)
