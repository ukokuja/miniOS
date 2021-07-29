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


Defaults:

Argument            | Default
| -------------     |-------------  
| # Tasks *         | -
| # Processor       | 1
| # Clock interval  | 1
* field is mandatory

#### 🏃 Output ####
1. In order to see scheduler actions:
   
   ```$ tail -f  logAction.csv```

![Class](https://i.imgur.com/iy8f2Q7.png)

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


#### 💿‍ Class Diagram ####
![Class](https://i.imgur.com/y9iXWnx.png)

Explanation
=============
* Scheduler: The scheduler wakes up every t seconds, pops one task from the queue and releases the lock.
  Each task in the queue is locked by mutex. Only the current task is unlocked and running in the OS.
  Every task suspends himself on the main task.
  
* Queue: The queue was implemented using an array and have FIFO behaviour. The first sorting is by priority, and after
  an interrupt (signal) is sequencially. 

* Buffer: The buffer modification is considered a critical section. It is protected by the OS Mutex. 