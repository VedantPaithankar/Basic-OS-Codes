#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define EMP_FILE	"emp.db"

typedef struct emp
{
	int id;
	char name[24];
	int sal;
}emp_t;

void accept_emp(emp_t *e)
{
	printf("enter id, name & sal : ");
	scanf("%d%s%d", &e->id, e->name, &e->sal);
}

void display_emp(emp_t *e)
{
	printf("%5d %-20s %8d\n", e->id, e->name, e->sal);
}

void add_emp()
{
	int fd, cnt;
	emp_t e;
	accept_emp(&e);

	fd = open(EMP_FILE, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if(fd == -1)
	{
		perror("open() failed");
		_exit(1);
	}

	cnt = write(fd, &e, sizeof(e));
	printf("num of bytes written : %d\n", cnt);

	close(fd);
}

void display_all()
{
	int fd;
	emp_t e;
	fd = open(EMP_FILE, O_RDONLY);
	if(fd == -1)
	{
		perror("open() failed");
		_exit(1);
	}

	while(read(fd, &e, sizeof(e)) > 0)
	{
		display_emp(&e);
	}

	close(fd);
}

void edit_emp()
{
	int fd, eid, found = 0;
	long size = sizeof(emp_t);
	emp_t e, n;

	printf("enter emp id to be edited : ");
	scanf("%d", &eid);

	fd = open(EMP_FILE, O_RDWR);
	if(fd == -1)
	{
		perror("open() failed");
		_exit(1);
	}

	while(read(fd, &e, sizeof(e)) > 0)
	{
		if(eid == e.id)
		{
			found = 1;
			break;
		}
	}

	if(found == 1)
	{
		printf("emp found.\n");
		display_emp(&e);

		printf("enter modified details : \n");
		accept_emp(&n);

		lseek(fd, -size, SEEK_CUR);

		write(fd, &n, sizeof(n));
	}

	close(fd);
}

int main()
{
	//add_emp();
	display_all();
	//edit_emp();
	return 0;
}


