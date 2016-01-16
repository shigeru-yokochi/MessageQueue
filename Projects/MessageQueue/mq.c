#include	<stdio.h>
//#include	<sys/types.h>
//#include	<sys/ipc.h>
#include	<sys/msg.h>

int main()
{
int qid;
struct{
	long mtype;
	char mtext[512];
}buf;

int nVal=0;
	if((qid=msgget(123,0666|IPC_CREAT))==-1){
		perror("msgget");
		return -1;
	}

	while(1){
		nVal++;
		sprintf(buf.mtext,"%u",nVal);
		sleep(1);
//		gets(buf.mtext);
		buf.mtype=1L;
		if(msgsnd(qid,&buf,sizeof(buf.mtext)-sizeof(buf.mtype),0)==-1){
			perror("msgsnd");
			break;
		}
		if(strcmp(buf.mtext,"end")==0){
			break;
		}
	}
	return 0;
}
