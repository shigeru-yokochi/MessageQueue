#include	"stdio.h"
#include	"sys/msg.h"

int main()
{
int	qid;
struct	{
	long	mtype;
	char	mtext[512];
}buf;

	if((qid=msgget(123,0666|IPC_CREAT))==-1){
		perror("msgget");
		return -1;
	}

	while(1){
		if(msgrcv(qid,&buf,512,0L,0)==-1){
			perror("msgrcv");
			break;
		}
		printf("%s\n",buf.mtext);
		if(strcmp(buf.mtext,"end")==0){
			break;
		}
	}

	if(msgctl(qid,IPC_RMID,NULL)==-1){
		perror("msgctl");
		return -1;
	}
	return 0;
}
