#include "types.h"
#include "stat.h"
#include "user.h"

#include "processInfo.h"
int main()
{	
	// array containing burst times
	int t[10] = {40, 70, 10, 90, 60, 30, 20, 80, 100, 50};
	long x = 0;
	// setBurstTime(1);
	
	for(int i=0; i<10; i++)
	{
		int id = fork();
		if(id == 0)
		{
			x = setBurstTime(t[i]);
			
			
			if(x < 0)
			{
				printf(1, "Couldn't set burst time for process %d\n", getpid());
			}
			
			// CPU bound process
			if(i%2 == 0)
			{
				double y = 0;
				
				// code to add delay
				for(int i2=0; i2<t[i]*1000000/2; i2++)
				{
					y += 2.69*13.01;
				}
				x = y;
				
				printf(1, "CPU Bound(%d) / ",  x);
			}
			
			// IO bound process
			else
			{
				// mimicking IO wait
				for(int i2=0; i2<t[i]*10; i2++)
				{
					sleep(1);
				}
				printf(1, "IO Bound / ");
			}
			
			x = getBurstTime();
			struct processInfo *info;
			info = (struct processInfo*) malloc(sizeof(struct processInfo));
			getProcInfo(getpid(), info);
			printf(1, "PID: %d Burst Time: %d Context Switches: %d\n",getpid(), x, info->numberContextSwitches);
			exit();
						
		}
		
	}
	
	while(wait() != -1);
	exit();
}