#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct msgbuf
{
	long mtype;
	char mword[20];
};

int main()
{
	struct msgbuf mbuf;
	int msgid, size, fd[2], fd2[2], dzien, godzina;
	pipe(fd);
	key_t key = 45200;
	int pid = fork();
	if (pid == -1){ perror("Blad w utworzeniu potomka\n"); }
	if (pid == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		system("date +%u");
		exit(1);
	}
	else
	{
		wait(NULL);
		dup2(fd[0], 0);
		close(fd[1]);
		scanf("%d", &dzien);
	}
	if (dzien >= 5)
	{
		if (dzien == 5)
		{
			int pid2 = fork();
			pipe(fd2);
			if (pid2 == -1){ perror("Blad w utworzeniu potomka\n"); }
			if (pid2 == 0)
			{
				dup2(fd2[1], 1);
				close(fd2[0]);
				system("date +%H");
				exit(1);
			}
			else
			{
				wait(NULL);
				dup2(fd2[0], 0);
				close(fd2[1]);
				scanf("%d", &godzina);
				if (godzina < 17;
				{
					printf("Nie ma weekendu\n");
					return 0;
				}
			}
		}
		msgid = msgget(key, 0666);
		if (msgid == -1)
		{
			perror("Blad dolaczenia do kolejki komunikatow\n");
			exit(1);
		}
		if (msgrcv(msgid, &mbuf, sizeof mbuf.mword, 0, 0) == -1)
		{
			perror("Blad otrzymania komunikatu\n");
			exit(1);
		}
		int length = strlen(mbuf.mword);
		int i;
		for (i = 0; i < length; i++)
		{
			if (mbuf.mword[i]<32 || mbuf.mword[i]>126)
			{
				msgctl(msgid, IPC_RMID, NULL);
				printf("Niepoprawny komunikat");
				return 0;
			}
		}
		if (!((mbuf.mword[0] >= 'a' && mbuf.mword[0] <= 'z') || (mbuf.mword[0] >= 'A' && mbuf.mword[0] <= 'Z')))
		{
			msgctl(msgid, IPC_RMID, NULL);
			printf("Niepoprawny komunikat\n");
			return 0;
		}
		FILE *msg = fopen("msg.txt", "w");
		fwrite(mbuf.mword, length, 1, msg);
		fclose(msg);
	}
	else { printf("Nie ma weekendu\n"); }
	msgctl(msgid, IPC_RMID, NULL);
	return 0;
}
