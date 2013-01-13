#include <string.h>
#include <sys/types.h>
#include <sys/sysinfo.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#define clear system("clear")

void Create_Process();
void Kill_Process();
void Status_Read(char *);
void Process_Read();
void View_Process();
void Change_Priority();
void About_CURRENT_PROCESS_USER();
void System_Info();

//Reading the Status Files of each Process
void Status_Read(char *path){
    DIR *dip;
    struct dirent *dit;
    int i = 0,lines=5;;
    FILE *fs;
    char details[25]="/proc/";
    strcat(details,path);
    if ((dip = opendir(details)) == NULL)
    {
	    perror("opendir");
	    return;
    }
    strcat(details,"/status");
    fs=fopen(details,"r");
    while(lines--){
    fgets(details,25,fs);
    printf("%s",details);
    }
    if (closedir(dip) == -1)
    {
	    perror("closedir");
	    return;
    }
}

//Reading each Virtual Directory inside /proc/
void Process_Read(){
    DIR *dip;
    struct dirent *dit;
    int i = 0;
    if ((dip = opendir("/proc/")) == NULL)
    {
	    perror("opendir");
	    return;
    }
    while ((dit = readdir(dip)) != NULL)
    {
	    pid_t pid;
	    if((pid=atoi(dit->d_name))>0)
	    {
		  Status_Read(dit->d_name);
		  i++;
	    }
    }
    printf("\n\nTotal no. of processes: %i \n", i);
    if (closedir(dip) == -1)
    {
	    perror("closedir");
	    return;
    }
}

//Creating a process
void Create_Process(){
	clear;
	char process[25];
	printf("\nEnter the name of the process to start :");
	scanf("%s",process);
	system(process);
}
//Killing the process
void Kill_Process(){
	clear;
	char cmd[10] = "kill ",pid[15];
	printf("\nEnter the Process ID to kill : ");
	scanf("%s",pid);
	strcat(cmd,pid);
	system(cmd);
	printf("\nProcess killed");
}

//Listing out the processes
void View_Process(){
clear;
while(1){
Process_Read();
sleep(5);
}
}

//About the Memory and CPU Usage
void System_Info(){
  clear;
  printf("\t\tSystem Resource Usage and Status\n");
  int days, hours, mins;
  struct sysinfo sys_info;
  if(sysinfo(&sys_info) != 0)
    perror("sysinfo");
  days = sys_info.uptime / 86400;
  hours = (sys_info.uptime / 3600) - (days * 24);
  mins = (sys_info.uptime / 60) - (days * 1440) - (hours * 60);
  printf("Uptime: %ddays, %dhours, %dminutes, %ldseconds\n",
                      days, hours, mins, sys_info.uptime % 60);
  printf("Load Avgs: 1min(%ld) 5min(%ld) 15min(%ld)\n",
          sys_info.loads[0], sys_info.loads[1], sys_info.loads[2]);
  printf("Total Ram: %ldk\tFree: %ldk\n", sys_info.totalram / 1024,
                                        sys_info.freeram / 1024);
  printf("Shared Ram: %ldk\n", sys_info.sharedram / 1024);
  printf("Buffered Ram: %ldk\n", sys_info.bufferram / 1024);
  printf("Total Swap: %ldk\tFree: %ldk\n", sys_info.totalswap / 1024,
                                           sys_info.freeswap / 1024);
  printf("Number of processes: %d\n", sys_info.procs);
}

//Changing the priority of the processes(Administrator previlage needed)
void Change_Priority(){
clear;
char pid[25],priority[25],cmd[25]="renice ";
int pcheck,prio;
printf("\nEnter the Process ID whose priority to be changed:");
scanf("%s",pid);
	    if((pcheck=atoi(pid))>0)
	    {
		printf("\nCurrent priority : %d" ,getpriority(pcheck));
		printf("\nEnter the Priority to be given :");
		scanf("%s",priority);
		strcat(cmd,priority);
		strcat(cmd," ");
		strcat(cmd,pid);
		system(cmd);
	    }
}

void About_CURRENT_PROCESS_USER(){
	clear;
	pid_t mypid;
	uid_t myuid;
	mypid = getpid();
	printf("\t\t\tTask Manager Details");
	printf("\nPID of this process : %d",mypid);
	printf("\nParent PID of this process : %d", getppid());
	myuid = getuid();
	printf("\nOwner(User ID) of this process : %d",myuid);
}

void task_manager(){
int choice;
	clear;
	while(1)
	{
	printf("\n\t\t\tTask Manager\n\n1.Create a process\n2.Kill a Process\n3.View the current running processes\n4.Change the priority of the process(Be Super user to change)\n5.About the Current user and peocess\n6.System Information\n7.Exit\n\nEnter the option to go with : ");
	scanf("%d",&choice);
	switch(choice){
		case 1:
			Create_Process();
			break;
		case 2:
			Kill_Process();
			break;
		case 3:
			View_Process();
			break;
		case 4:
			Change_Priority();
			break;
		case 5:
			About_CURRENT_PROCESS_USER();
			break;
		case 6:
			System_Info();
			break;
		case 7:
			exit(0);
		default:
			printf("\n\n\t\t\tSorry,Invalid choice.Try Again!!!\n");
		}
	}
}
