//#include "basic.h"    // ������� ����
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

#define vloop(i,s,d) for(i=s;i<=d;i++) // �ڵ� ���ǻ� s���� d���� ���� ������ ��ũ��
										   // ����: vloop([ī��Ÿ ����], [���ۼ�], [����])
#define elseif else if // elseif�� else if�� ����
#define function(x) void x() // VOID �Լ� ���� ��ũ�� - ����: function([�Լ� �̸�])
#define cls system("cls") // ȭ�� �����
#define forever while(1) // ���� �ݺ��ϱ� ��ũ��
#define spc 32 // ���̶簳 �ۼ�
#define up 72 // ���� ȭ��ǥ �ۼ�
#define down 80 // �Ʒ��� ȭ��ǥ �ۼ�
#define spaces(x) for(i=1;i<=x;i++){printf(" ");}; // ���� ���� �� ��� spaces([����])

    
int cp=1; // ���� ������
    
FILE *tf, *f; // ȭ�Ϻ��� tf�� �ӽ� f�� ��������

typedef struct {
	char d[8]; // ��¥
	char t[4]; // �ð�
	int imp; // �O�䵵
	int grp; // �׷�
	char title[131]; // ����
	char cont[131]; // ����
} cal;

int spp,epp; // ������ �ѱ�� ���� ����. ǥ�� ������ ���� ��ȣ, ǥ�� ������ ���� ��ȣ
int cr=1; // Ŀ���� ��ġ�� 1���� ����
int scrid=0; // ���� ȭ��. 0=��� 1=�����ڼ��� 2=�߰� 3=����

cal cale[7200]; // ����ü
int grps[5]; // �׷� ���� ����
    
char grpt[5][131]={"����","���","���","�޽�","��Ÿ"}; // �׷� �̸�
    
int n=0/* ���� */, i/* FOR�� */;
int trash; // ������ ����
char trashs[1000]; // ������ ���ڿ�

void consize(int x, int y); // �ܼ� â ũ�� ����
void gotoxy(int x, int y); // Ŀ�� �̵� �Լ�
void setcolor(unsigned short text, unsigned short back); // �� ����

void title(const char* t); // â ���� ����

COORD cur; // ���� Ŀ�� ��ġ

void error(const char* p) { // ���� �޽��� ���
	gotoxy(0,16); // �ϴ����� �̵�
	printf("������������������������������������������������������������������������������\n");
	printf("�� ���� �� "); printf(p); gotoxy(76,17); printf("��\n");
	printf("������������������������������������������������������������������������������\n"); getch(); // �ƹ�Ű�� ������
	cr=1; // ���õ� �׸� �ٽ� 1��
	printCalendar(); // ��� ���
	scrid=0; // ���� ȭ���� �������
}

function(printCalendar) { // ��� �Լ�
	cls; // ȭ�� �����
	title("����ǥ"); // â ����
	consize(120,30); // ǥ ũ�⿡ �°� â ũ�� ����
	gotoxy(0,29); 

	setcolor(0,7); printf("  SP/����    I/�����    E/�ٲٱ�    D/�����    R/���� ��ħ    N/����    B/�ڷ�    O/������    X/������"); spaces(1); printf("   %3d/%3d �� ",cp,(n-1)/21+1);setcolor(7,0); gotoxy(0,0); // ȸ�� ������� ����Ű ���, ���� ������
	printf("����������������������������-��������-������������������������������������������������������������������������-��\n");
    printf("��    ��  ��  ��    �� ¥    �� �� �� �� �߿䵵 ��   �׷�   ��      ����      ��              ����             ��\n");
    printf("��������������������������-����������-������������������������������������������������������������������������-��\n");
    vloop(i,spp,epp) {
    	if(i>=n) break; // ǥ�� ���� ������ ���� �������� ũ�� ������
    	if( strcmp(cale[i].d,"")==0 ) continue; // �� �����̳� �̻��� ���� �ǳʶٱ�
    	if(strlen(cale[i].cont)>28) // ���� ���̰� ���� ũ�� ...�� ǥ���ϰ� �ڼ��� ���� ȭ�鿡�� ���
			printf("��    �� %4d �� %c%c%c%c.%c%c.%c%c. �� %c%c:%c%c ��   %2d   �� %8s �� %14s �� %29s ��\n", i+1,cale[i].d[0], cale[i].d[1],cale[i].d[2],cale[i].d[3],cale[i].d[4],cale[i].d[5],cale[i].d[6],cale[i].d[7],cale[i].t[0],cale[i].t[1],cale[i].t[2],cale[i].t[3],cale[i].imp,grpt[cale[i].grp],cale[i].title,"[������ �ʹ� ����]"); // ���
		else // �ƴϸ� �׳� ���뵵 ǥ���� ���
		    printf("��    �� %4d �� %c%c%c%c.%c%c.%c%c. �� %c%c:%c%c ��   %2d   �� %8s �� %14s �� %29s ��\n", i+1,cale[i].d[0], cale[i].d[1],cale[i].d[2],cale[i].d[3],cale[i].d[4],cale[i].d[5],cale[i].d[6],cale[i].d[7],cale[i].t[0],cale[i].t[1],cale[i].t[2],cale[i].t[3],cale[i].imp,grpt[cale[i].grp],cale[i].title,cale[i].cont); // ���
    }
    printf("����������������������������-��������-������������������������������������������������������������������������-��\n");
    
    gotoxy(3,3); // ǥ�� ù ĭ�� ���� ǥ��
    cur.X=3, cur.Y=3; // ���� Ŀ�� ��ġ ����
    cr=1; // "
    printf("��"); // ǥ��
    gotoxy(6,3);
}

function(printDetails) { // �ڼ��� ��� �Լ�
	cls;
	title(cale[cr-1+spp].title); // â ����
	consize(80,20); // ǥ ũ�⿡ �°� â ũ�� ����
	gotoxy(0,19); setcolor(0,7); printf("  Q/���    X/������"); spaces(59); setcolor(7,0); gotoxy(0,0); // ȸ�� ������� ����Ű ���
	printf("������������������������������������������������������������������������������\n");
	printf("�� %s",cale[cr-1+spp].title); gotoxy(76,1); printf("��\n"); // ����
	printf("������������������������������������������������������������������������������\n");
	printf("�� ��  �� �� %c%c%c%c.%c%c.%c%c. %c%c:%c%c",cale[cr-1+spp].d[0], cale[cr-1+spp].d[1],cale[cr-1+spp].d[2],cale[cr-1+spp].d[3],cale[cr-1+spp].d[4],cale[cr-1+spp].d[5],cale[cr-1+spp].d[6],cale[cr-1+spp].d[7],cale[cr-1+spp].t[0],cale[cr-1+spp].t[1],cale[cr-1+spp].t[2],cale[cr-1+spp].t[3]); gotoxy(76,3); printf("��\n"); // ��¥�ð� ���
	printf("�� �߿䵵 �� %d / 10",cale[cr-1+spp].imp); gotoxy(76,4); printf("��\n"); // �߿䵵 ��� ���ϵ� ������ ����
	printf("�� ��  �� �� %s",grpt[cale[cr-1+spp].grp]); gotoxy(76,5); printf("��\n");
	printf("������������������������������������������������������������������������������\n");
	printf(" ����\n����\n %s\n\n",cale[cr-1+spp].title); // ���� ���
	printf(" ����\n��������\n %s\n",cale[cr-1+spp].cont); // ���� ���Ť�
	
//	gotoxy("")
	
}

function(addCal) { // ���� �߰�
	cls;
	title("���� �߰�"); // â ����
	consize(80,20); // ǥ ũ�⿡ �°� â ũ�� ����
	printf("������������������������������������������������������������������������������\n");
	printf("�� ������ �߰��մϴ�. ����� ���뿡 ������ �Ұ����մϴ�.                    ��\n");
	printf("������������������������������������������������������������������������������\n");
	printf("�� ��  ¥ ��                                                                ��\n");
	printf("�� ��  �� ��                                                                ��\n");
	printf("�� �߿䵵 ��                                                                ��\n");
	printf("�� ��  �� ��                                                                ��\n");
	printf("�� ��  �� ��                                                                ��\n");
	printf("�� ��  �� ��                                                                ��\n");
	printf("������������������������������������������������������������������������������\n");
	gotoxy(13,3);
	scanf("%s",cale[n].d); // ��¥ �Է�. ���� ���� ����
	if(strlen(cale[n].d)!=8) error("��¥�� yyyymmdd �������� �Է��ؾ� �մϴ�."); // ���Ŀ� ���� ������ ���� ���
	else{
	gotoxy(13,4);
	scanf("%s",cale[n].t);
	if(strlen(cale[n].t)!=4) error("�ð��� ttmm �������� �Է��ؾ� �մϴ�."); // ���Ŀ� ���� ������ ���� ���
	else{
	gotoxy(13,5);
	scanf("%d",&cale[n].imp);
	if(cale[n].imp>10||cale[n].imp<1) error("�߿䵵�� 1���� 10 �����̾�� �մϴ�."); // ���Ŀ� ���� ������ ���� ���
	else{
	gotoxy(13,6);
	scanf("%d",&cale[n].grp);
	if(cale[n].grp>4||cale[n].grp<0) error("�׷� ��ȣ�� 0���� 4 �����̾�� �մϴ�."); // ���Ŀ� ���� ������ ���� ���
	else{
	gotoxy(13,7);
	scanf("%s",cale[n].title);
	gotoxy(13,8);
	scanf("%s",cale[n].cont);
	n++; // ���� ���� ����
	f=fopen("data.txt","a"); // ������� ȭ�� ����
	
	fprintf(f,"\n%s %s %d %d %s %s",cale[n-1].d,cale[n-1].t,cale[n-1].imp,cale[n-1].grp,cale[n-1].title,cale[n-1].cont);
	fclose(f);
	cr=1; // ���õ� �׸� �ٽ� 1��
	printCalendar(); // ��� ���
	scrid=0; // ���� ȭ���� �������
	}
	}
	}
	}
}

function(editCal) { // ���� ����
	cls;
	char tit[9]="���� - "; // â ����
	title( strcat(tit,cale[cr-1+spp].title) ); // â ����
	int i; //�ݺ���
	consize(80,20); // ǥ ũ�⿡ �°� â ũ�� ����
	printf("������������������������������������������������������������������������������\n");
	printf("�� ������ �����մϴ�. �������� �������� ������ �Է��ϼ���.                  ��\n");
	printf("������������������������������������������������������������������������������\n");
	printf("�� ��  ¥ ��                                                                ��\n");
	printf("�� ��  �� ��                                                                ��\n");
	printf("�� �߿䵵 ��                                                                ��\n");
	printf("�� ��  �� ��                                                                ��\n");
	printf("�� ��  �� ��                                                                ��\n");
	printf("�� ��  �� ��                                                                ��\n");
	printf("������������������������������������������������������������������������������\n");
	gotoxy(13,3);
	// ���� ���. ���� ���� ����
	for(i=0;i<8;i++) printf("%c",cale[cr-1+spp].d[i]);
	printf(" => ");
	scanf("%s",cale[cr-1+spp].d); // ��¥ �Է�. ���� ���� ����
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
	f=fopen("data.txt","w"); // ������� ȭ�� ����
	
	vloop(i,0,n-1) {
		fprintf(f,"\n%s %s %d %d %s %s",cale[i].d,cale[i].t,cale[i].imp,cale[i].grp,cale[i].title,cale[i].cont);
	}
	fclose(f);
	cr=1; // ���õ� �׸� �ٽ� 1��
	printCalendar(); // ��� ���
	scrid=0; // ���� ȭ���� �������
}

function(delCal) { // ����
	// ���� Ȯ��
	gotoxy(0,26); // �ϴ����� �̵�
	printf("������������������������������������������������������������������������������\n");
	printf("�� ���� �� ������ �����ұ��? [yn]                                          ��\n");
	printf("������������������������������������������������������������������������������\n");
	int yn=getch(); //��������
	if(yn!='y'){
		//y �ƴϸ� �ǵ��ư���
		// ��ȭâ �����
		gotoxy(0,26); // ���������� �̵�
		printf("                                                                               \n");
		printf("                                                                               \n");
		printf("                                                                               \n");
		return;
	}
	
	int i; // �ݺ���
	vloop(i,cr-0+spp,n-1) { // �ն����
		strcpy(cale[i-1].d,cale[i].d);
		strcpy(cale[i-1].t,cale[i].t);
		cale[i-1].imp=cale[i].imp;
		cale[i-1].grp=cale[i].grp;
		strcpy(cale[i-1].title,cale[i].title);
		strcpy(cale[i-1].cont,cale[i].cont);
	}
	f=fopen("data.txt","w"); // ������� ȭ�� ����
	
	n--; // ���� 1�����
	
	vloop(i,0,n-1) {
		fprintf(f,"\n%s %s %d %d %s %s",cale[i].d,cale[i].t,cale[i].imp,cale[i].grp,cale[i].title,cale[i].cont);
	}
	fclose(f);
	
	printCalendar(); // �ٽ� ���
}

int main()
{
	title("���� ��..."); // â ����
	n=0; //�ʱ�ȭ
	consize(120,30); // ǥ ũ�⿡ �°� â ũ�� ����(MS-DOS������ ȣȯ�� �� �ǰ� Windows������ ��)
	
	/* ���� ���� ã�� */
	tf=fopen("data.txt","r"); // �ӽ÷� ȭ�� ����
	while(!feof(tf)){
		fscanf(tf,"%s %s %d %d %s %s",trashs,trashs,&trash,&trash,trashs,trashs); // ������ �����ϱ� ���� �ӽ÷� ������ �����鿡 �� ����
		n++; // ���� ����
	}
	fclose(tf); // �ʱ�ȭ������ ���� �ݱ�
	
	f=fopen("data.txt","r"); // ���� ���� ����
    vloop(i,0,n-1) {
		fscanf(f,"%s %s %d %d %s %s",cale[i].d,cale[i].t,&cale[i].imp,&cale[i].grp,cale[i].title,cale[i].cont); // ȭ�Ͽ��� �Է�
    }
    fclose(f); // ȭ�� �ݱ�
    
    spp=0; epp=20; // ���� ��Ͽ� ǥ���� ����
    
    printCalendar(); // ��� �Լ�
    
    int key=0; // ������ �ۼ�
    
    forever { // ���� �ݺ��ϱ�
		key=getch();
		if(key==224) key=getch();
		if(key==up){ // ���� ������
			if(cr-1>0&&scrid==0){ // ������ �̻��� ���� �ƴ� ��
					cr--;
				gotoxy(cur.X-1,cur.Y); // ȭ��ǥ ������ Ŀ�� �ű��
				printf("��"); // ȭ��ǥ �����
				gotoxy(cur.X, cur.Y-1); // �Ʒ��ʿ� ȭ��ǥ
				cur.Y-=1; // ���� Ŀ�� ��ġ ����
				printf("��"); // �� ��ġ�� ȭ��ǥ
			}
		} elseif(key==down) { // �Ʒ��� ������
			if(cr+1<=epp-spp+1&&cr+1<=n-spp&&scrid==0) { // �Ʒ����� �̻��� ���� �ƴ� ��
				cr++;
				gotoxy(cur.X-1,cur.Y); // ȭ��ǥ ������ Ŀ�� �ű��
				printf("��"); // ȭ��ǥ �����
				gotoxy(cur.X, cur.Y+1); // �Ʒ��ʿ� ȭ��ǥ
				cur.Y+=1; // ���� Ŀ�� ��ġ ����
				printf("��"); // �� ��ġ�� ȭ��ǥ
			}
		} elseif(key==spc) {
			if(scrid==0) { //��Ͽ��� ���� ��
				scrid=1;
				printDetails(); // �ڼ��� ��� �Լ�
			}
		} elseif(key=='q') { // q���� �� �������
			if(scrid==1||scrid==2) { // ���� ���� �����̸�
				cr=1; // ���õ� �׸� �ٽ� 1��
				cp=1; // ������ �ʱ�ȭ
				spp=0;
				epp=20;
				printCalendar(); // ��� ���
				scrid=0; // ���� ȭ���� �������
			}
		} elseif(key=='i') { // q���� �� �������
			if(scrid==0) { // ��� �����̸�
				scrid=2; // ���� ȭ���� �߰�(��)��
				addCal(); // �߰� ��� ȭ�� ���
			}
		} elseif(key=='e') {
			if(scrid==0) { // ��� �����̸�
				scrid=3; // ���� ȭ���� ����(��)��
				editCal(); // ���� ��� ȭ�� ���
			}
		} elseif(key=='d') {
			if(scrid==0) { // ��� �����̸�
				delCal();
			}
		} elseif(key=='r') { // �ֽ� ������ ��ħ ���
			main(); // �ʱ�ȭ
		} elseif(key=='x') {
			title("���� ��...");
			return 0; // ����;
		} elseif(key=='n') { 
			if(scrid==0&&spp+20<n) { // ���� ���̸�
				cp++; // ������ ��ȣ ����
				spp=spp+21; // ǥ�� ���� �ٲٱ�
				epp=epp+21; // "
				printCalendar(); // ���� ������ ǥ��
			}
		} elseif(key=='b') {
			if(scrid==0&&spp-20>=0){ // ���� ���̸�
				cp--; // ������ ��ȣ �Ʒ���
				spp=spp-21; // ǥ�� ���� �ٲٱ�
				epp=epp-21; // "
				printCalendar(); // ���� ������ ǥ��
			}
		} elseif(key=='o') { // DOS ������
			if(scrid==0){ // ��� ȭ�鿡���� ����
				cls;
				title("���� ������");
				printf("����ǥ�� ���ư����� EXIT�� �Է��Ͻʽÿ�\n\n"); // �ȳ� ����
				system("cmd"); // Windows 95�̸� COMMAND������ ���� ��(����) � ü���� Windows 95 ���� ����� ���ιۿ� ���ٰ� �ǴܵǾ� CMD��..
				title("����ǥ");
				printCalendar(); // �ٽ� ���
			}
		} elseif(key=='m') { // ������ ������
			if(scrid==0) {
				if((n-1)/21+1 != cp) { // ���� �������� �� �������� ���� ������
					cp=1;
					spp=0;
					epp=21;
					vloop(i,2,(n-1)/21+1) { // ���� ������ ���ϱ�
						cp++; // ������ ��ȣ ����
						spp=spp+21; // ǥ�� ���� �ٲٱ�
						epp=epp+21; // " 
					}
					printCalendar(); // ǥ��
				}
			}
		} elseif(key=='v') { // ù ��������
			if(scrid==0) {
				cp=1;
				spp=0;
				epp=21;
				printCalendar();
			}
		}
		gotoxy(4,3); // ǥ�� ù ĭ�� ���� ǥ��
    }
    
    return 0;
}

void consize(int x, int y) { // �ܼ� â ũ�� ����(������ �ʿ� ���� ���ϸ�, �ִٰ� �˸� �� ���մϴ�)
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

void title(const char* t) // �ȸ��� �ʿ� ���� ���մϴ�
{
	char cmds[151]="title ";
	strcat(cmds,t);
	system(cmds);
}

void gotoxy(int x, int y) // Ŀ�� �̵�(������ �ʿ� ���� ���ϸ�, �ִٰ� �˸� �� ���մϴ�)
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
