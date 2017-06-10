#include<stdio.h>
#include <stdlib.h>//system()함수에 필요
#include <time.h>
#include <unistd.h>
#include<termio.h>//getch()함수에 필요
#define N 30
#define M 11

int replay_check = 0;
int undo[5][N][N];
char map_memory[5][N][N];
char map[5][N][N];//전역변수
char name[10]; //이름받을때 쓰는거
char p_map[30][30];
int x=0, y=0, z=0, i;
time_t start_time, end_time;
char key; // r,n,e 포함 나머지 입력 값들도 이 key변수로 받을 것.

//이름 입력받는 함수
void get_name()
{
	int i=0,a;
	printf("Start....\n input name : ");
	while(1){
		a = getchar();
		if(i==M){
			while((a=getchar()) != '\n')
				;
			printf("10자 이하의 이름을 입력해 주세요 : ");
			i = 0;
			continue;
		}
		if((a =='\n')||(a == EOF)) {
			name[i++] = '\0';
			break;
		}
		name[i++] = a;
	}
	printf("Hello %s", name);
}
//현재위치 찾는 함수?
int scanchar()
{
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			if(map[0][i][j]=='@'){
				x=j;
				y=i;
			}
	return 0;
}
//map.txt파일 스캔하는 함수(완성)
int mapscan()
{
	FILE *scan;
	char a;
	scan=fopen("map.txt","r");
	while(fscanf(scan,"%c",&a) != EOF){
		if(y==N){
			y=0;
			z++;
		}
		else if(a=='\n'){
			map[z][y][x]='\n';
			y++;
			x=0;
		}
		else if(a=='$'){
			map[z][y][x]='$';
			x++;
		}
		else if(a=='@'){
			map[z][y][x]='@';
			x++;
		}
		else if(a=='#'){
			map[z][y][x]='#';
			x++;
		}
		else if(a==' '){
			map[z][y][x]=' ';
			x++;
		}
		else if(a=='O'){
			map[z][y][x]='O';
			x++;
		}
		else
			;
	}
	fclose(scan);
	return 0;
}


void undo_scan()
{
	for(int y=0; y<N; y++)
	for(int x=0; x<N; x++){
		undo[4][y][x]= undo[3][y][x];
		undo[3][y][x]= undo[2][y][x];
		undo[2][y][x]= undo[1][y][x];
		undo[1][y][x]= undo[0][y][x];
		undo[0][y][x]= map[z][y][x];
	}
}

////// map출력 함수(거의 완성)
int mapprint1()
{
	int x,y,z=0;
	for(int y=0;y<N;y++){
		for(int x=0;x<N;x++)
			printf("%c",map[z][y][x]);
	}
	//다하면 mapprint2로 넘어가는 조건.
	return 0;
}

int mapprint2()
{
	int x,y,z=1;
	for(int y=0;y<N;y++){
		for(int x=0;x<N;x++)
			printf("%c",map[z][y][x]);
	}
	//다하면 mapprint3로 넘어가는 조건.
	return 0;
}

int mapprint3()
{
	int x,y,z=2;
	for(int y=0;y<N;y++){
		for(int x=0;x<N;x++)
			printf("%c",map[z][y][x]);
	}
	//다하면 mapprint4로 넘어가는 조건.
	return 0;
}

int mapprint4()
{
	int x,y,z=3;
	for(int y=0;y<N;y++){
		for(int x=0;x<N;x++)
			printf("%c",map[z][y][x]);
	}
	//다하면 mapprint5로 넘어가는 조건.
	return 0;
}

int mapprint5()
{
	int x,y,z=4;
	for(int y=0;y<N;y++){
		for(int x=0;x<N;x++)
			printf("%c",map[z][y][x]);
	}
	return 0;
}

////// ??
int getch()
{
	int ch;

	struct termios buf;
	struct termios save;

	tcgetattr(0, &save);
	buf = save;

	buf.c_lflag&=~(ICANON|ECHO);
	buf.c_cc[VMIN] = 1;
	buf.c_cc[VTIME] = 0;

	tcsetattr(0,TCSAFLUSH,&buf);
	ch = getchar();
	tcsetattr(0,TCSAFLUSH,&save);

	return ch;
}

////// 입력포함 모든 옵션 입력받는 함수.(이거 완성하면 끝)
void keyMove()
{

	int key;
	scanchar();
	key=getch();

	system("clear");

	switch(key){

		case 'u': //undo 미완성.

		case 'r':
			{
			if(z==0)
			{
				for(int y=0; y<N; y++)
					for(int x=0; x<N; x++)
					map[0][y][x] = map_memory[0][y][x];
			mapprint1();
			}

			if(z==1)
			{
				for(int y=0; y<N; y++)
					for(int x=0; x<N; x++)
					map[1][y][x] = map_memory[1][y][x];
			mapprint2();
			}

			if(z==2)
			{
				for(int y=0; y<N; y++)
					for(int x=0; x<N; x++)
					map[2][y][x] = map_memory[2][y][x];
			mapprint3();
			}

			if(z==3)
			{
				for(int y=0; y<N; y++)
					for(int x=0; x<N; x++)
					map[3][y][x] = map_memory[3][y][x];
			mapprint4();
			}

			if(z==4)
			{
				for(int y=0; y<N; y++)
					for(int x=0; x<N; x++)
					map[4][y][x] = map_memory[4][y][x];
			mapprint5();
			}

			break;
			}

		case 'n':
		{
		system("clear");
		start_time =0;
		for(int z=0; z<5; z++)
			for(int y=0; y<N; y++)
				for(int x=0; x<N; x++)
					map[z][y][x] = map_memory[z][y][x];

		mapprint1();
		time(&start_time);
		break;
		}

		case 'e':
		{
			file_save();
			exit(-1);
			break;
		}

		case 's': //

		case 'f': //

		case 't': //ranking

		case 'd':
		{
		system("clear");
		printf("h(왼쪽), j(아래), k(위), l(오른쪽)\n");
		printf("u(undo) \n");
		printf("r(replay) \n");
		printf("n(new) \n");
		printf("e(exit) \n");
		printf("s(save) \n");
		printf("f(file load) \n");
		printf("d(display help) \n");
		printf("t(top) \n");
		printf(" \n ※※※뒤로 가려면 q를 누르세요※※※ ");

		int key2;
		scanchar();
		key2=getch();

		if(key2=='q'){
			system("clear");
		break;
		}
		}

		case 'h':
			if(map[0][y][x-1] == '$'){
				if(map[0][y][x-2] == ' '){
					map[0][y][x-2]='$';
					map[0][y][x]=' ';
					map[0][y][x-=1]='@';
				}
				else if(map[0][y][x-2] == 'O'){
					map[0][y][x-2]='$';
					map[0][y][x]=' ';
					map[0][y][x-=1]='@';
				}
			}
			else if(map[0][y][x-1] == 'O'){
				map[0][y][x]=' ';
				map[0][y][x-=1]='@';
			}
			else if(map[0][y][x-1] == ' '){
				map[0][y][x]=' ';
				map[0][y][x-=1]='@';
			}
			break;

		case 'j':
			if(map[0][y+1][x] == '$'){
				if(map[0][y+2][x] == ' '){
					map[0][y+2][x]='$';
					map[0][y][x]=' ';
					map[0][y+=1][x]='@';
				}
				else if(map[0][y+2][x] == 'O'){
					map[0][y+2][x]='$';
					map[0][y][x]=' ';
					map[0][y+=1][x]='@';
				}
			}
			else if(map[0][y+1][x] == 'O'){
				map[0][y][x]=' ';
				map[0][y+=1][x]='@';
			}
			else if(map[0][y+1][x] == ' '){
				map[0][y][x]=' ';
				map[0][y+=1][x]='@';
			}
			break;

		case 'k':
			if(map[0][y-1][x] == '$'){
				if(map[0][y-2][x] == ' '){
					map[0][y-2][x]='$';
					map[0][y][x]=' ';
					map[0][y-=1][x]='@';
				}
				else if(map[0][y-2][x] == 'O'){
					map[0][y-2][x]='$';
					map[0][y][x]=' ';
					map[0][y-=1][x]='@';
				}
			}
			else if(map[0][y-1][x] == 'O'){
				map[0][y][x]=' ';
				map[0][y-=1][x]='@';
			}
			else if(map[0][y-1][x] == ' '){
				map[0][y][x]=' ';
				map[0][y-=1][x]='@';
			}
			break;

		case 'l':
			if(map[0][y][x+1] == '$'){
				if(map[0][y][x+2] == ' '){
					map[0][y][x+2]='$';
					map[0][y][x]=' ';
					map[0][y][x+=1]='@';
				}
				else if(map[0][y][x+2] == 'O'){
					map[0][y][x+2]='$';
					map[0][y][x]=' ';
					map[0][y][x+=1]='@';
				}
			}
			else if(map[0][y][x+1] == 'O'){
				map[0][y][x]=' ';
				map[0][y][x+=1]='@';
				}
			else if(map[0][y][x+1] == ' '){
				map[0][y][x]=' ';
				map[0][y][x+=1]='@';
			}
			break;
	}
}

//////파일 저장하기(미완성)
void file_save()
{
	time_t stop_time;
	time(&stop_time);
	//double difftime(stop_time,start_time);
	double d_diff_stop = difftime(stop_time,start_time);

	FILE *file_save;
	file_save=fopen("sokoban.txt","w");

	fprintf(file_save,"%s",name);  //이름
	fprintf(file_save," ");

	fprintf(file_save,"%.1f",d_diff_stop); //시간
	fprintf(file_save,"\n");

	for(int y=0;y<30;y++)
		for(int x=0;x<30;x++)
			fprintf(file_save,"%c",map[z][y][x]); //맵

	fclose(file_save);
}


//////저장한 파일 불러오기(미완성)
void file_load()
{
	FILE *file_save;
	file_save=fopen("sokoban.txt","r");
	double d_diff_stop;
	char space;
	for(int z=0;z<30;z++)
		for(int y=0;y<30;y++)
			for(int x=0;x<30;x++)
				fscanf(file_save,"%c",&map[z][y][x]);

	fscanf(file_save,"%s %.1f", name, d_diff_stop);

	fscanf(file_save,"%c",map[z][y][x]);
	fclose(file_save);
}

int replay()
{
	if (replay_check == 0){
	for(int z=0; z<5; z++ )
		for(int y=0; y<N; y++ )
			for(int x=0; x<N; x++)
			map_memory[z][y][x] = map[z][y][x];
		}
		x=0,y=0,z=0;
}

//////main 함수.
int main(void)
{
	get_name();
	system("clear");
	printf("\n\n");

	mapscan();
	mapprint1();
	time(&start_time);

	while(1){
		replay();
		replay_check = 1 ; //움직임을 입력.

		keyMove();
		mapprint1();

		//if (보관함 개수 == 0)
		//while(1) keyMove(),mapprint2()

		//~반복

	}
	time(&end_time);
	//double difftime(end_time, start_time);
	double d_diff = difftime(end_time, start_time);

	return 0;
}

//sokobar 678행 참고.
//undo_scan , undo_print -> 옵션 r과 n 모두 할 수 있을듯?
//undo로 !!!처음 맵을 저장!!!해놓는다면 원래 O위치에 아무것도 없을 때 다시 O가능?
//e
//keymove(hjkl) 보관함 사라지는 문제
//save, load
//ranking -> 옵션 t