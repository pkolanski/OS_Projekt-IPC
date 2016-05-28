#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msgbuf
{
	long mtype;
	char mword[20];
};

int main()
{
	struct msgbuf mbuf;
	int msgid, size;
	key_t key = 45200;
	msgid = msgget(key, IPC_CREAT | 0666);
	if (msgid == -1)
	{
		perror("Blad utworzenia kolejki komunikatow");
		exit(1);
	}
	mbuf.mtype = 1;
	printf("Podaj slowo,ktore chcesz wyslac do kolejki\n");
	scanf("%s", mbuf.mword);
	size = sizeof mbuf.mword;
	if (msgsnd(msgid, &mbuf, size, 0) == -1)
	{
		perror("Blad w wysylaniu komunikatu");
		exit(1);
	}
	return 0;
}
