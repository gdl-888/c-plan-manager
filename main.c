//#include "basic.h"    // 사용하지 않음
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

#define vloop(i,s,d) for(i=s;i<=d;i++) // 코드 편의상 s부터 d까지 포문 돌리는 매크로
										   // 사용법: vloop([카운타 변수], [시작수], [끝수])
#define elseif else if // elseif는 else if와 동일
#define function(x) void x() // VOID 함수 선언 매크로 - 사용법: function([함수 이름])
#define cls system("cls") // 화면 지우기
#define forever while(1) // 무한 반복하기 매크로
#define spc 32 // 사이띄개 글쇠
#define up 72 // 위쪽 화살표 글쇠
#define down 80 // 아래쪽 화살표 글쇠
#define spaces(x) for(i=1;i<=x;i++){printf(" ");}; // 공백 여러 개 출력 spaces([갯수])

    
int cp=1; // 현재 페이지
    
FILE *tf, *f; // 화일변수 tf는 임시 f는 실제변수

typedef struct {
	char d[8]; // 날짜
	char t[4]; // 시간
	int imp; // 즁요도
	int grp; // 그룹
	char title[131]; // 제목
	char cont[131]; // 내용
} cal;

int spp,epp; // 페이지 넘기기 위한 변수. 표시 시작할 일정 번호, 표시 마지막 일정 번호
int cr=1; // 커서의 위치를 1부터 저장
int scrid=0; // 현재 화면. 0=목록 1=일정자세히 2=추가 3=수정

cal cale[7200]; // 구조체
int grps[5]; // 그룸 갯수 저장
    
char grpt[5][131]={"공부","상담","약속","휴식","기타"}; // 그룸 이름
    
int n=0/* 갯수 */, i/* FOR문 */;
int trash; // 쓰레기 변수
char trashs[1000]; // 쓰레기 문자열

void consize(int x, int y); // 콘솔 창 크기 변경
void gotoxy(int x, int y); // 커서 이동 함수
void setcolor(unsigned short text, unsigned short back); // 색 변경

void title(const char* t); // 창 제목 변경

COORD cur; // 현재 커서 위치

void error(const char* p) { // 오류 메시지 출력
	gotoxy(0,16); // 하단으로 이동
	printf("┌───┬─────────────────────────────────┐\n");
	printf("│ 오류 │ "); printf(p); gotoxy(76,17); printf("│\n");
	printf("└───┴─────────────────────────────────┘\n"); getch(); // 아무키나 누름기
	cr=1; // 선택된 항목 다시 1로
	printCalendar(); // 목록 출력
	scrid=0; // 현재 화면을 목록으로
}

function(printCalendar) { // 출력 함수
	cls; // 화면 지우기
	title("일정표"); // 창 제목
	consize(120,30); // 표 크기에 맞게 창 크기 조절
	gotoxy(0,29); 

	setcolor(0,7); printf("  SP/보기    I/만들기    E/바꾸기    D/지우기    R/새로 고침    N/다음    B/뒤로    O/나들이    X/끝내기"); spaces(1); printf("   %3d/%3d 쪽 ",cp,(n-1)/21+1);setcolor(7,0); gotoxy(0,0); // 회색 배경으로 단축키 목록, 현재 페이지
	printf("┌──┬───┬──────-┬───-┬────┬─────┬────────┬───────────────-┐\n");
    printf("│    │  ＃  │    날 짜    │ 시 간 │ 중요도 │   그룹   │      제목      │              내용             │\n");
    printf("├──┼───┼─────-─┼───-┼────┼─────┼────────┼───────────────-┤\n");
    vloop(i,spp,epp) {
    	if(i>=n) break; // 표시 끝낼 구역이 실제 갯수보다 크면 나가기
    	if( strcmp(cale[i].d,"")==0 ) continue; // 빈 일정이나 이상한 일정 건너뛰기
    	if(strlen(cale[i].cont)>28) // 내용 길이가 나무 크면 ...라 표시하고 자세히 보기 화면에서 출력
			printf("│    │ %4d │ %c%c%c%c.%c%c.%c%c. │ %c%c:%c%c │   %2d   │ %8s │ %14s │ %29s │\n", i+1,cale[i].d[0], cale[i].d[1],cale[i].d[2],cale[i].d[3],cale[i].d[4],cale[i].d[5],cale[i].d[6],cale[i].d[7],cale[i].t[0],cale[i].t[1],cale[i].t[2],cale[i].t[3],cale[i].imp,grpt[cale[i].grp],cale[i].title,"[내용이 너무 길음]"); // 출력
		else // 아니면 그냥 내용도 표에다 출력
		    printf("│    │ %4d │ %c%c%c%c.%c%c.%c%c. │ %c%c:%c%c │   %2d   │ %8s │ %14s │ %29s │\n", i+1,cale[i].d[0], cale[i].d[1],cale[i].d[2],cale[i].d[3],cale[i].d[4],cale[i].d[5],cale[i].d[6],cale[i].d[7],cale[i].t[0],cale[i].t[1],cale[i].t[2],cale[i].t[3],cale[i].imp,grpt[cale[i].grp],cale[i].title,cale[i].cont); // 출력
    }
    printf("└──┴───┴──────-┴───-┴────┴─────┴────────┴───────────────-┘\n");
    
    gotoxy(3,3); // 표ㅛ 첫 칸에 세모 표시
    cur.X=3, cur.Y=3; // 현재 커서 위치 저장
    cr=1; // "
    printf("▶"); // 표시
    gotoxy(6,3);
}

function(printDetails) { // 자세히 출력 함수
	cls;
	title(cale[cr-1+spp].title); // 창 제목
	consize(80,20); // 표 크기에 맞게 창 크기 조절
	gotoxy(0,19); setcolor(0,7); printf("  Q/목록    X/끝내기"); spaces(59); setcolor(7,0); gotoxy(0,0); // 회색 배경으로 단축키 목록
	printf("┌─────────────────────────────────────┐\n");
	printf("│ %s",cale[cr-1+spp].title); gotoxy(76,1); printf("│\n"); // 제목
	printf("├────┬────────────────────────────────┤\n");
	printf("│ 일  시 │ %c%c%c%c.%c%c.%c%c. %c%c:%c%c",cale[cr-1+spp].d[0], cale[cr-1+spp].d[1],cale[cr-1+spp].d[2],cale[cr-1+spp].d[3],cale[cr-1+spp].d[4],cale[cr-1+spp].d[5],cale[cr-1+spp].d[6],cale[cr-1+spp].d[7],cale[cr-1+spp].t[0],cale[cr-1+spp].t[1],cale[cr-1+spp].t[2],cale[cr-1+spp].t[3]); gotoxy(76,3); printf("│\n"); // 날짜시간 출력
	printf("│ 중요도 │ %d / 10",cale[cr-1+spp].imp); gotoxy(76,4); printf("│\n"); // 중요도 출력 이하도 동일한 설명
	printf("│ 그  룹 │ %s",grpt[cale[cr-1+spp].grp]); gotoxy(76,5); printf("│\n");
	printf("└────┴────────────────────────────────┘\n");
	printf(" 제목\n〓〓〓\n %s\n\n",cale[cr-1+spp].title); // 제목 출력
	printf(" 내용\n〓〓〓〓〓〓〓\n %s\n",cale[cr-1+spp].cont); // 내용 출료ㅕㄱ
	
//	gotoxy("")
	
}

function(addCal) { // 일정 추가
	cls;
	title("일정 추가"); // 창 제목
	consize(80,20); // 표 크기에 맞게 창 크기 조절
	printf("┌─────────────────────────────────────┐\n");
	printf("│ 일정을 추가합니다. 제목과 내용에 공백은 불가능합니다.                    │\n");
	printf("├────┬────────────────────────────────┤\n");
	printf("│ 날  짜 │                                                                │\n");
	printf("│ 시  간 │                                                                │\n");
	printf("│ 중요도 │                                                                │\n");
	printf("│ 그  룹 │                                                                │\n");
	printf("│ 제  목 │                                                                │\n");
	printf("│ 내  용 │                                                                │\n");
	printf("└────┴────────────────────────────────┘\n");
	gotoxy(13,3);
	scanf("%s",cale[n].d); // 날짜 입력. 이하 동일 설명
	if(strlen(cale[n].d)!=8) error("날짜는 yyyymmdd 형식으로 입력해야 합니다."); // 형식에 맞지 않으면 에러 출력
	else{
	gotoxy(13,4);
	scanf("%s",cale[n].t);
	if(strlen(cale[n].t)!=4) error("시간은 ttmm 형식으로 입력해야 합니다."); // 형식에 맞지 않으면 에러 출력
	else{
	gotoxy(13,5);
	scanf("%d",&cale[n].imp);
	if(cale[n].imp>10||cale[n].imp<1) error("중요도는 1부터 10 사이이어야 합니다."); // 형식에 맞지 않으면 에러 출력
	else{
	gotoxy(13,6);
	scanf("%d",&cale[n].grp);
	if(cale[n].grp>4||cale[n].grp<0) error("그룸 번호는 0부터 4 사이이어야 합니다."); // 형식에 맞지 않으면 에러 출력
	else{
	gotoxy(13,7);
	scanf("%s",cale[n].title);
	gotoxy(13,8);
	scanf("%s",cale[n].cont);
	n++; // 일정 갯수 증가
	f=fopen("data.txt","a"); // 쓰기모드로 화일 열기
	
	fprintf(f,"\n%s %s %d %d %s %s",cale[n-1].d,cale[n-1].t,cale[n-1].imp,cale[n-1].grp,cale[n-1].title,cale[n-1].cont);
	fclose(f);
	cr=1; // 선택된 항목 다시 1로
	printCalendar(); // 목록 출력
	scrid=0; // 현재 화면을 목록으로
	}
	}
	}
	}
}

function(editCal) { // 일정 수정
	cls;
	char tit[9]="수정 - "; // 창 제목
	title( strcat(tit,cale[cr-1+spp].title) ); // 창 제목
	int i; //반복문
	consize(80,20); // 표 크기에 맞게 창 크기 조절
	printf("┌─────────────────────────────────────┐\n");
	printf("│ 일정을 수정합니다. 수정하지 않으려면 원본을 입력하세요.                  │\n");
	printf("├────┬────────────────────────────────┤\n");
	printf("│ 날  짜 │                                                                │\n");
	printf("│ 시  간 │                                                                │\n");
	printf("│ 중요도 │                                                                │\n");
	printf("│ 그  룹 │                                                                │\n");
	printf("│ 제  목 │                                                                │\n");
	printf("│ 내  용 │                                                                │\n");
	printf("└────┴────────────────────────────────┘\n");
	gotoxy(13,3);
	// 원본 출력. 이하 설명 동일
	for(i=0;i<8;i++) printf("%c",cale[cr-1+spp].d[i]);
	printf(" => ");
	scanf("%s",cale[cr-1+spp].d); // 날짜 입력. 이하 동일 설명
	gotoxy(13,4);
	printf("X");for(i=1;i<4;i++) printf("%c",cale[cr-1+spp].t[i]);
	printf(" => ");
	scanf("%s",cale[cr-1+spp].t);
	gotoxy(13,5);
	printf("%d => ",cale[cr-1+spp].imp);
	scanf("%d",&cale[cr-1+spp].imp);
	gotoxy(13,6);
	printf("%d => ",cale[cr-1+spp].grp);
	scanf("%d",&cale[cr-1+spp].grp);
	gotoxy(13,7);
	printf("%s => ",cale[cr-1+spp].title);
	scanf("%s",cale[cr-1+spp].title);
	gotoxy(13,8);
	printf("%s => ",cale[cr-1+spp].cont);
	scanf("%s",cale[cr-1+spp].cont);
	f=fopen("data.txt","w"); // 쓰기모드로 화일 열기
	
	vloop(i,0,n-1) {
		fprintf(f,"\n%s %s %d %d %s %s",cale[i].d,cale[i].t,cale[i].imp,cale[i].grp,cale[i].title,cale[i].cont);
	}
	fclose(f);
	cr=1; // 선택된 항목 다시 1로
	printCalendar(); // 목록 출력
	scrid=0; // 현재 화면을 목록으로
}

function(delCal) { // 삭제
	// 먼저 확인
	gotoxy(0,26); // 하단으로 이동
	printf("┌───┬─────────────────────────────────┐\n");
	printf("│ 질문 │ 정말로 삭제할까요? [yn]                                          │\n");
	printf("└───┴─────────────────────────────────┘\n");
	int yn=getch(); //삭제여부
	if(yn!='y'){
		//y 아니면 되돌아가기
		// 대화창 지우기
		gotoxy(0,26); // 시작점으로 이동
		printf("                                                                               \n");
		printf("                                                                               \n");
		printf("                                                                               \n");
		return;
	}
	
	int i; // 반복문
	vloop(i,cr-0+spp,n-1) { // 앞땡기기
		strcpy(cale[i-1].d,cale[i].d);
		strcpy(cale[i-1].t,cale[i].t);
		cale[i-1].imp=cale[i].imp;
		cale[i-1].grp=cale[i].grp;
		strcpy(cale[i-1].title,cale[i].title);
		strcpy(cale[i-1].cont,cale[i].cont);
	}
	f=fopen("data.txt","w"); // 쓰기모드로 화일 열기
	
	n--; // 갯수 1지우기
	
	vloop(i,0,n-1) {
		fprintf(f,"\n%s %s %d %d %s %s",cale[i].d,cale[i].t,cale[i].imp,cale[i].grp,cale[i].title,cale[i].cont);
	}
	fclose(f);
	
	printCalendar(); // 다시 출력
}

int main()
{
	title("진행 중..."); // 창 제목
	n=0; //초기화
	consize(120,30); // 표 크기에 맞게 창 크기 조절(MS-DOS에서는 호환이 안 되고 Windows에서는 됨)
	
	/* 일정 갯수 찾기 */
	tf=fopen("data.txt","r"); // 임시로 화일 열기
	while(!feof(tf)){
		fscanf(tf,"%s %s %d %d %s %s",trashs,trashs,&trash,&trash,trashs,trashs); // 갯수를 증가하기 위해 임시로 쓰레기 변수들에 값 저장
		n++; // 갯수 증가
	}
	fclose(tf); // 초기화용으로 파일 닫기
	
	f=fopen("data.txt","r"); // 본격 파일 열기
    vloop(i,0,n-1) {
		fscanf(f,"%s %s %d %d %s %s",cale[i].d,cale[i].t,&cale[i].imp,&cale[i].grp,cale[i].title,cale[i].cont); // 화일에서 입력
    }
    fclose(f); // 화일 닫기
    
    spp=0; epp=20; // 일정 목록에 표시할 구역
    
    printCalendar(); // 출력 함수
    
    int key=0; // 누르는 글쇠
    
    forever { // 무한 반복하기
		key=getch();
		if(key==224) key=getch();
		if(key==up){ // 위쪽 누르면
			if(cr-1>0&&scrid==0){ // 위쪽이 이상한 데가 아닐 때
					cr--;
				gotoxy(cur.X-1,cur.Y); // 화살표 앞으로 커서 옮기기
				printf("　"); // 화살표 지우기
				gotoxy(cur.X, cur.Y-1); // 아래쪽에 화살표
				cur.Y-=1; // 현재 커서 위치 저장
				printf("▶"); // 새 위치에 화살표
			}
		} elseif(key==down) { // 아래쪽 누르면
			if(cr+1<=epp-spp+1&&cr+1<=n-spp&&scrid==0) { // 아래쪽이 이상한 데가 아닐 때
				cr++;
				gotoxy(cur.X-1,cur.Y); // 화살표 앞으로 커서 옮기기
				printf("　"); // 화살표 지우기
				gotoxy(cur.X, cur.Y+1); // 아래쪽에 화살표
				cur.Y+=1; // 현재 커서 위치 저장
				printf("▶"); // 새 위치에 화살표
			}
		} elseif(key==spc) {
			if(scrid==0) { //목록에서 누를 떄
				scrid=1;
				printDetails(); // 자세히 출력 함수
			}
		} elseif(key=='q') { // q누를 때 목록으로
			if(scrid==1||scrid==2) { // 일정 보기 상태이면
				cr=1; // 선택된 항목 다시 1로
				cp=1; // 페이지 초기화
				spp=0;
				epp=20;
				printCalendar(); // 목록 출력
				scrid=0; // 현재 화면을 목록으로
			}
		} elseif(key=='i') { // q누를 때 목록으로
			if(scrid==0) { // 목록 상태이면
				scrid=2; // 현재 화면을 추가(으)로
				addCal(); // 추가 양식 화면 출력
			}
		} elseif(key=='e') {
			if(scrid==0) { // 목록 상태이면
				scrid=3; // 현재 화면을 수정(으)로
				editCal(); // 수정 양식 화면 출력
			}
		} elseif(key=='d') {
			if(scrid==0) { // 목록 상태이면
				delCal();
			}
		} elseif(key=='r') { // 최신 정보로 고침 기능
			main(); // 초기화
		} elseif(key=='x') {
			title("종료 중...");
			return 0; // 종료;
		} elseif(key=='n') { 
			if(scrid==0&&spp+20<n) { // 범위 내이면
				cp++; // 페이지 번호 위로
				spp=spp+21; // 표시 범위 바꾸기
				epp=epp+21; // "
				printCalendar(); // 다음 페이지 표시
			}
		} elseif(key=='b') {
			if(scrid==0&&spp-20>=0){ // 범위 내이면
				cp--; // 페이지 번호 아래로
				spp=spp-21; // 표시 범위 바꾸기
				epp=epp-21; // "
				printCalendar(); // 다음 페이지 표시
			}
		} elseif(key=='o') { // DOS 나들이
			if(scrid==0){ // 목록 화면에서만 가능
				cls;
				title("도스 나들이");
				printf("일정표로 돌아가려면 EXIT를 입력하십시오\n\n"); // 안내 문구
				system("cmd"); // Windows 95이면 COMMAND이지만 지금 주(메인) 운영 체제로 Windows 95 쓰는 사람이 본인밖에 없다고 판단되어 CMD로..
				title("일정표");
				printCalendar(); // 다시 출력
			}
		} elseif(key=='m') { // 마지막 페이지
			if(scrid==0) {
				if((n-1)/21+1 != cp) { // 현재 페이지와 끝 페이지가 같지 않으면
					cp=1;
					spp=0;
					epp=21;
					vloop(i,2,(n-1)/21+1) { // 시작 페이지 구하기
						cp++; // 페이지 번호 위로
						spp=spp+21; // 표시 범위 바꾸기
						epp=epp+21; // " 
					}
					printCalendar(); // 표시
				}
			}
		} elseif(key=='v') { // 첫 페이지로
			if(scrid==0) {
				cp=1;
				spp=0;
				epp=21;
				printCalendar();
			}
		}
		gotoxy(4,3); // 표ㅛ 첫 칸에 세모 표시
    }
    
    return 0;
}

void consize(int x, int y) { // 콘솔 창 크기 변경(설명은 필요 없을 듯하며, 있다고만 알면 될 듯합니다)
    if(x>999||y>999) return;
    char cmds[34]={'m','o','d','e',' ','c','o','n',' ','c','o','l','s','=','0','0','0',' ','l','i','n','e','s','=','0','0','0'};
    cmds[14]=(x/100)+48;
    cmds[15]=((x%100)/10)+48;
    cmds[16]=(x%10)+48;
    
    cmds[24]=(y/100)+48;
    cmds[25]=((y%100)/10)+48;
    cmds[36]=(y%10)+48;
    
    system(cmds);
}

void title(const char* t) // 셜명은 필요 없는 듯합니다
{
	char cmds[151]="title ";
	strcat(cmds,t);
	system(cmds);
}

void gotoxy(int x, int y) // 커서 이동(설명은 필요 없을 듯하며, 있다고만 알면 될 듯합니다)
{
    COORD Pos;
    Pos.X = x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Pos);

}

void setcolor(unsigned short text, unsigned short back)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}
