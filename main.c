//#include "basic.h"    // 餌辨ж雖 彊擠
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

#define vloop(i,s,d) for(i=s;i<=d;i++) // 囀萄 ら曖鼻 s睡攪 d梱雖 ん僥 給葬朝 衙觼煎
										   // 餌辨徹: vloop([蘋遴顫 滲熱], [衛濛熱], [部熱])
#define elseif else if // elseif朝 else if諦 翕橾
#define function(x) void x() // VOID л熱 摹樹 衙觼煎 - 餌辨徹: function([л熱 檜葷])
#define cls system("cls") // �飛� 雖辦晦
#define forever while(1) // 鼠и 奩犒ж晦 衙觼煎
#define spc 32 // 餌檜嗥偃 旋潸
#define up 72 // 嬪薹 �香嚂� 旋潸
#define down 80 // 嬴楚薹 �香嚂� 旋潸
#define spaces(x) for(i=1;i<=x;i++){printf(" ");}; // 奢寥 罹楝 偃 轎溘 spaces([偎熱])

    
int cp=1; // ⑷營 む檜雖
    
FILE *tf, *f; // �倣牬紡� tf朝 歜衛 f朝 褒薯滲熱

typedef struct {
	char d[8]; // 陳瞼
	char t[4]; // 衛除
	int imp; // Μ蹂紫
	int grp; // 斜瑜
	char title[131]; // 薯跡
	char cont[131]; // 頂辨
} cal;

int spp,epp; // む檜雖 剩晦晦 嬪и 滲熱. ル衛 衛濛й 橾薑 廓��, ル衛 葆雖虞 橾薑 廓��
int cr=1; // 醴憮曖 嬪纂蒂 1睡攪 盪濰
int scrid=0; // ⑷營 �飛�. 0=跡煙 1=橾薑濠撮�� 2=蹺陛 3=熱薑

cal cale[7200]; // 掘褻羹
int grps[5]; // 斜瑛 偎熱 盪濰
    
char grpt[5][131]={"奢睡","鼻氬","擒樓","�瑍�","晦顫"}; // 斜瑛 檜葷
    
int n=0/* 偎熱 */, i/* FOR僥 */;
int trash; // 噙溯晦 滲熱
char trashs[1000]; // 噙溯晦 僥濠翮

void consize(int x, int y); // 夔樂 璽 觼晦 滲唳
void gotoxy(int x, int y); // 醴憮 檜翕 л熱
void setcolor(unsigned short text, unsigned short back); // 儀 滲唳

void title(const char* t); // 璽 薯跡 滲唳

COORD cur; // ⑷營 醴憮 嬪纂

void error(const char* p) { // 螃盟 詭衛雖 轎溘
	gotoxy(0,16); // ж欽戲煎 檜翕
	printf("忙式式式成式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("弛 螃盟 弛 "); printf(p); gotoxy(76,17); printf("弛\n");
	printf("戌式式式扛式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n"); getch(); // 嬴鼠酈釭 援葷晦
	cr=1; // 摹鷗脹 о跡 棻衛 1煎
	printCalendar(); // 跡煙 轎溘
	scrid=0; // ⑷營 �飛橉� 跡煙戲煎
}

function(printCalendar) { // 轎溘 л熱
	cls; // �飛� 雖辦晦
	title("橾薑ル"); // 璽 薯跡
	consize(120,30); // ル 觼晦縑 蜃啪 璽 觼晦 褻瞰
	gotoxy(0,29); 

	setcolor(0,7); printf("  SP/爾晦    I/虜菟晦    E/夥紱晦    D/雖辦晦    R/億煎 堅藹    N/棻擠    B/菴煎    O/釭菟檜    X/部頂晦"); spaces(1); printf("   %3d/%3d 薹 ",cp,(n-1)/21+1);setcolor(7,0); gotoxy(0,0); // �蜓� 寡唳戲煎 欽蹴酈 跡煙, ⑷營 む檜雖
	printf("忙式式成式式式成式式式式式式-成式式式-成式式式式成式式式式式成式式式式式式式式成式式式式式式式式式式式式式式式-忖\n");
    printf("弛    弛  ㄒ  弛    陳 瞼    弛 衛 除 弛 醞蹂紫 弛   斜瑜   弛      薯跡      弛              頂辨             弛\n");
    printf("戍式式托式式式托式式式式式-式托式式式-托式式式式托式式式式式托式式式式式式式式托式式式式式式式式式式式式式式式-扣\n");
    vloop(i,spp,epp) {
    	if(i>=n) break; // ル衛 部鳥 掘羲檜 褒薯 偎熱爾棻 觼賊 釭陛晦
    	if( strcmp(cale[i].d,"")==0 ) continue; // 綴 橾薑檜釭 檜鼻и 橾薑 勒傘嗨晦
    	if(strlen(cale[i].cont)>28) // 頂辨 望檜陛 釭鼠 觼賊 ...塭 ル衛ж堅 濠撮�� 爾晦 �飛橦□� 轎溘
			printf("弛    弛 %4d 弛 %c%c%c%c.%c%c.%c%c. 弛 %c%c:%c%c 弛   %2d   弛 %8s 弛 %14s 弛 %29s 弛\n", i+1,cale[i].d[0], cale[i].d[1],cale[i].d[2],cale[i].d[3],cale[i].d[4],cale[i].d[5],cale[i].d[6],cale[i].d[7],cale[i].t[0],cale[i].t[1],cale[i].t[2],cale[i].t[3],cale[i].imp,grpt[cale[i].grp],cale[i].title,"[頂辨檜 傘鼠 望擠]"); // 轎溘
		else // 嬴棲賊 斜傖 頂辨紫 ル縑棻 轎溘
		    printf("弛    弛 %4d 弛 %c%c%c%c.%c%c.%c%c. 弛 %c%c:%c%c 弛   %2d   弛 %8s 弛 %14s 弛 %29s 弛\n", i+1,cale[i].d[0], cale[i].d[1],cale[i].d[2],cale[i].d[3],cale[i].d[4],cale[i].d[5],cale[i].d[6],cale[i].d[7],cale[i].t[0],cale[i].t[1],cale[i].t[2],cale[i].t[3],cale[i].imp,grpt[cale[i].grp],cale[i].title,cale[i].cont); // 轎溘
    }
    printf("戌式式扛式式式扛式式式式式式-扛式式式-扛式式式式扛式式式式式扛式式式式式式式式扛式式式式式式式式式式式式式式式-戎\n");
    
    gotoxy(3,3); // ル卞 羅 蘊縑 撮賅 ル衛
    cur.X=3, cur.Y=3; // ⑷營 醴憮 嬪纂 盪濰
    cr=1; // "
    printf("Ⅱ"); // ル衛
    gotoxy(6,3);
}

function(printDetails) { // 濠撮�� 轎溘 л熱
	cls;
	title(cale[cr-1+spp].title); // 璽 薯跡
	consize(80,20); // ル 觼晦縑 蜃啪 璽 觼晦 褻瞰
	gotoxy(0,19); setcolor(0,7); printf("  Q/跡煙    X/部頂晦"); spaces(59); setcolor(7,0); gotoxy(0,0); // �蜓� 寡唳戲煎 欽蹴酈 跡煙
	printf("忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("弛 %s",cale[cr-1+spp].title); gotoxy(76,1); printf("弛\n"); // 薯跡
	printf("戍式式式式成式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式扣\n");
	printf("弛 橾  衛 弛 %c%c%c%c.%c%c.%c%c. %c%c:%c%c",cale[cr-1+spp].d[0], cale[cr-1+spp].d[1],cale[cr-1+spp].d[2],cale[cr-1+spp].d[3],cale[cr-1+spp].d[4],cale[cr-1+spp].d[5],cale[cr-1+spp].d[6],cale[cr-1+spp].d[7],cale[cr-1+spp].t[0],cale[cr-1+spp].t[1],cale[cr-1+spp].t[2],cale[cr-1+spp].t[3]); gotoxy(76,3); printf("弛\n"); // 陳瞼衛除 轎溘
	printf("弛 醞蹂紫 弛 %d / 10",cale[cr-1+spp].imp); gotoxy(76,4); printf("弛\n"); // 醞蹂紫 轎溘 檜ж紫 翕橾и 撲貲
	printf("弛 斜  瑜 弛 %s",grpt[cale[cr-1+spp].grp]); gotoxy(76,5); printf("弛\n");
	printf("戌式式式式扛式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
	printf(" 薯跡\n㏑㏑㏑\n %s\n\n",cale[cr-1+spp].title); // 薯跡 轎溘
	printf(" 頂辨\n㏑㏑㏑㏑㏑㏑㏑\n %s\n",cale[cr-1+spp].cont); // 頂辨 轎猿勿丑
	
//	gotoxy("")
	
}

function(addCal) { // 橾薑 蹺陛
	cls;
	title("橾薑 蹺陛"); // 璽 薯跡
	consize(80,20); // ル 觼晦縑 蜃啪 璽 觼晦 褻瞰
	printf("忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("弛 橾薑擊 蹺陛м棲棻. 薯跡婁 頂辨縑 奢寥擎 碳陛棟м棲棻.                    弛\n");
	printf("戍式式式式成式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式扣\n");
	printf("弛 陳  瞼 弛                                                                弛\n");
	printf("弛 衛  除 弛                                                                弛\n");
	printf("弛 醞蹂紫 弛                                                                弛\n");
	printf("弛 斜  瑜 弛                                                                弛\n");
	printf("弛 薯  跡 弛                                                                弛\n");
	printf("弛 頂  辨 弛                                                                弛\n");
	printf("戌式式式式扛式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
	gotoxy(13,3);
	scanf("%s",cale[n].d); // 陳瞼 殮溘. 檜ж 翕橾 撲貲
	if(strlen(cale[n].d)!=8) error("陳瞼朝 yyyymmdd ⑽衝戲煎 殮溘п撿 м棲棻."); // ⑽衝縑 蜃雖 彊戲賊 縑楝 轎溘
	else{
	gotoxy(13,4);
	scanf("%s",cale[n].t);
	if(strlen(cale[n].t)!=4) error("衛除擎 ttmm ⑽衝戲煎 殮溘п撿 м棲棻."); // ⑽衝縑 蜃雖 彊戲賊 縑楝 轎溘
	else{
	gotoxy(13,5);
	scanf("%d",&cale[n].imp);
	if(cale[n].imp>10||cale[n].imp<1) error("醞蹂紫朝 1睡攪 10 餌檜檜橫撿 м棲棻."); // ⑽衝縑 蜃雖 彊戲賊 縑楝 轎溘
	else{
	gotoxy(13,6);
	scanf("%d",&cale[n].grp);
	if(cale[n].grp>4||cale[n].grp<0) error("斜瑛 廓�ㄣ� 0睡攪 4 餌檜檜橫撿 м棲棻."); // ⑽衝縑 蜃雖 彊戲賊 縑楝 轎溘
	else{
	gotoxy(13,7);
	scanf("%s",cale[n].title);
	gotoxy(13,8);
	scanf("%s",cale[n].cont);
	n++; // 橾薑 偎熱 隸陛
	f=fopen("data.txt","a"); // 噙晦賅萄煎 �倣� 翮晦
	
	fprintf(f,"\n%s %s %d %d %s %s",cale[n-1].d,cale[n-1].t,cale[n-1].imp,cale[n-1].grp,cale[n-1].title,cale[n-1].cont);
	fclose(f);
	cr=1; // 摹鷗脹 о跡 棻衛 1煎
	printCalendar(); // 跡煙 轎溘
	scrid=0; // ⑷營 �飛橉� 跡煙戲煎
	}
	}
	}
	}
}

function(editCal) { // 橾薑 熱薑
	cls;
	char tit[9]="熱薑 - "; // 璽 薯跡
	title( strcat(tit,cale[cr-1+spp].title) ); // 璽 薯跡
	int i; //奩犒僥
	consize(80,20); // ル 觼晦縑 蜃啪 璽 觼晦 褻瞰
	printf("忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("弛 橾薑擊 熱薑м棲棻. 熱薑ж雖 彊戲溥賊 錳獄擊 殮溘ж撮蹂.                  弛\n");
	printf("戍式式式式成式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式扣\n");
	printf("弛 陳  瞼 弛                                                                弛\n");
	printf("弛 衛  除 弛                                                                弛\n");
	printf("弛 醞蹂紫 弛                                                                弛\n");
	printf("弛 斜  瑜 弛                                                                弛\n");
	printf("弛 薯  跡 弛                                                                弛\n");
	printf("弛 頂  辨 弛                                                                弛\n");
	printf("戌式式式式扛式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
	gotoxy(13,3);
	// 錳獄 轎溘. 檜ж 撲貲 翕橾
	for(i=0;i<8;i++) printf("%c",cale[cr-1+spp].d[i]);
	printf(" => ");
	scanf("%s",cale[cr-1+spp].d); // 陳瞼 殮溘. 檜ж 翕橾 撲貲
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
	f=fopen("data.txt","w"); // 噙晦賅萄煎 �倣� 翮晦
	
	vloop(i,0,n-1) {
		fprintf(f,"\n%s %s %d %d %s %s",cale[i].d,cale[i].t,cale[i].imp,cale[i].grp,cale[i].title,cale[i].cont);
	}
	fclose(f);
	cr=1; // 摹鷗脹 о跡 棻衛 1煎
	printCalendar(); // 跡煙 轎溘
	scrid=0; // ⑷營 �飛橉� 跡煙戲煎
}

function(delCal) { // 餉薯
	// 試盪 �挫�
	gotoxy(0,26); // ж欽戲煎 檜翕
	printf("忙式式式成式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("弛 韓僥 弛 薑蜓煎 餉薯й梱蹂? [yn]                                          弛\n");
	printf("戌式式式扛式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
	int yn=getch(); //餉薯罹睡
	if(yn!='y'){
		//y 嬴棲賊 腎給嬴陛晦
		// 渠�倥� 雖辦晦
		gotoxy(0,26); // 衛濛薄戲煎 檜翕
		printf("                                                                               \n");
		printf("                                                                               \n");
		printf("                                                                               \n");
		return;
	}
	
	int i; // 奩犒僥
	vloop(i,cr-0+spp,n-1) { // 擅雄晦晦
		strcpy(cale[i-1].d,cale[i].d);
		strcpy(cale[i-1].t,cale[i].t);
		cale[i-1].imp=cale[i].imp;
		cale[i-1].grp=cale[i].grp;
		strcpy(cale[i-1].title,cale[i].title);
		strcpy(cale[i-1].cont,cale[i].cont);
	}
	f=fopen("data.txt","w"); // 噙晦賅萄煎 �倣� 翮晦
	
	n--; // 偎熱 1雖辦晦
	
	vloop(i,0,n-1) {
		fprintf(f,"\n%s %s %d %d %s %s",cale[i].d,cale[i].t,cale[i].imp,cale[i].grp,cale[i].title,cale[i].cont);
	}
	fclose(f);
	
	printCalendar(); // 棻衛 轎溘
}

int main()
{
	title("霞ч 醞..."); // 璽 薯跡
	n=0; //蟾晦��
	consize(120,30); // ル 觼晦縑 蜃啪 璽 觼晦 褻瞰(MS-DOS縑憮朝 ���素� 寰 腎堅 Windows縑憮朝 脾)
	
	/* 橾薑 偎熱 瓊晦 */
	tf=fopen("data.txt","r"); // 歜衛煎 �倣� 翮晦
	while(!feof(tf)){
		fscanf(tf,"%s %s %d %d %s %s",trashs,trashs,&trash,&trash,trashs,trashs); // 偎熱蒂 隸陛ж晦 嬪п 歜衛煎 噙溯晦 滲熱菟縑 高 盪濰
		n++; // 偎熱 隸陛
	}
	fclose(tf); // 蟾晦�倍蹀虞� だ橾 殘晦
	
	f=fopen("data.txt","r"); // 獄問 だ橾 翮晦
    vloop(i,0,n-1) {
		fscanf(f,"%s %s %d %d %s %s",cale[i].d,cale[i].t,&cale[i].imp,&cale[i].grp,cale[i].title,cale[i].cont); // �倣狤□� 殮溘
    }
    fclose(f); // �倣� 殘晦
    
    spp=0; epp=20; // 橾薑 跡煙縑 ル衛й 掘羲
    
    printCalendar(); // 轎溘 л熱
    
    int key=0; // 援腦朝 旋潸
    
    forever { // 鼠и 奩犒ж晦
		key=getch();
		if(key==224) key=getch();
		if(key==up){ // 嬪薹 援腦賊
			if(cr-1>0&&scrid==0){ // 嬪薹檜 檜鼻и 等陛 嬴棍 陽
					cr--;
				gotoxy(cur.X-1,cur.Y); // �香嚂� 擅戲煎 醴憮 衡晦晦
				printf("﹛"); // �香嚂� 雖辦晦
				gotoxy(cur.X, cur.Y-1); // 嬴楚薹縑 �香嚂�
				cur.Y-=1; // ⑷營 醴憮 嬪纂 盪濰
				printf("Ⅱ"); // 億 嬪纂縑 �香嚂�
			}
		} elseif(key==down) { // 嬴楚薹 援腦賊
			if(cr+1<=epp-spp+1&&cr+1<=n-spp&&scrid==0) { // 嬴楚薹檜 檜鼻и 等陛 嬴棍 陽
				cr++;
				gotoxy(cur.X-1,cur.Y); // �香嚂� 擅戲煎 醴憮 衡晦晦
				printf("﹛"); // �香嚂� 雖辦晦
				gotoxy(cur.X, cur.Y+1); // 嬴楚薹縑 �香嚂�
				cur.Y+=1; // ⑷營 醴憮 嬪纂 盪濰
				printf("Ⅱ"); // 億 嬪纂縑 �香嚂�
			}
		} elseif(key==spc) {
			if(scrid==0) { //跡煙縑憮 援蒂 ��
				scrid=1;
				printDetails(); // 濠撮�� 轎溘 л熱
			}
		} elseif(key=='q') { // q援蒂 陽 跡煙戲煎
			if(scrid==1||scrid==2) { // 橾薑 爾晦 鼻鷓檜賊
				cr=1; // 摹鷗脹 о跡 棻衛 1煎
				cp=1; // む檜雖 蟾晦��
				spp=0;
				epp=20;
				printCalendar(); // 跡煙 轎溘
				scrid=0; // ⑷營 �飛橉� 跡煙戲煎
			}
		} elseif(key=='i') { // q援蒂 陽 跡煙戲煎
			if(scrid==0) { // 跡煙 鼻鷓檜賊
				scrid=2; // ⑷營 �飛橉� 蹺陛(戲)煎
				addCal(); // 蹺陛 曄衝 �飛� 轎溘
			}
		} elseif(key=='e') {
			if(scrid==0) { // 跡煙 鼻鷓檜賊
				scrid=3; // ⑷營 �飛橉� 熱薑(戲)煎
				editCal(); // 熱薑 曄衝 �飛� 轎溘
			}
		} elseif(key=='d') {
			if(scrid==0) { // 跡煙 鼻鷓檜賊
				delCal();
			}
		} elseif(key=='r') { // 譆褐 薑爾煎 堅藹 晦棟
			main(); // 蟾晦��
		} elseif(key=='x') {
			title("謙猿 醞...");
			return 0; // 謙猿;
		} elseif(key=='n') { 
			if(scrid==0&&spp+20<n) { // 彰嬪 頂檜賊
				cp++; // む檜雖 廓�� 嬪煎
				spp=spp+21; // ル衛 彰嬪 夥紱晦
				epp=epp+21; // "
				printCalendar(); // 棻擠 む檜雖 ル衛
			}
		} elseif(key=='b') {
			if(scrid==0&&spp-20>=0){ // 彰嬪 頂檜賊
				cp--; // む檜雖 廓�� 嬴楚煎
				spp=spp-21; // ル衛 彰嬪 夥紱晦
				epp=epp-21; // "
				printCalendar(); // 棻擠 む檜雖 ル衛
			}
		} elseif(key=='o') { // DOS 釭菟檜
			if(scrid==0){ // 跡煙 �飛橦□飛� 陛棟
				cls;
				title("紫蝶 釭菟檜");
				printf("橾薑ル煎 給嬴陛溥賊 EXIT蒂 殮溘ж褊衛螃\n\n"); // 寰頂 僥掘
				system("cmd"); // Windows 95檜賊 COMMAND檜雖虜 雖旎 輿(詭檣) 遴艙 羹薯煎 Windows 95 噙朝 餌塋檜 獄檣夤縑 橈棻堅 っ欽腎橫 CMD煎..
				title("橾薑ル");
				printCalendar(); // 棻衛 轎溘
			}
		} elseif(key=='m') { // 葆雖虞 む檜雖
			if(scrid==0) {
				if((n-1)/21+1 != cp) { // ⑷營 む檜雖諦 部 む檜雖陛 偽雖 彊戲賊
					cp=1;
					spp=0;
					epp=21;
					vloop(i,2,(n-1)/21+1) { // 衛濛 む檜雖 掘ж晦
						cp++; // む檜雖 廓�� 嬪煎
						spp=spp+21; // ル衛 彰嬪 夥紱晦
						epp=epp+21; // " 
					}
					printCalendar(); // ル衛
				}
			}
		} elseif(key=='v') { // 羅 む檜雖煎
			if(scrid==0) {
				cp=1;
				spp=0;
				epp=21;
				printCalendar();
			}
		}
		gotoxy(4,3); // ル卞 羅 蘊縑 撮賅 ル衛
    }
    
    return 0;
}

void consize(int x, int y) { // 夔樂 璽 觼晦 滲唳(撲貲擎 в蹂 橈擊 蛭ж貊, 氈棻堅虜 憲賊 腆 蛭м棲棻)
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

void title(const char* t) // 暫貲擎 в蹂 橈朝 蛭м棲棻
{
	char cmds[151]="title ";
	strcat(cmds,t);
	system(cmds);
}

void gotoxy(int x, int y) // 醴憮 檜翕(撲貲擎 в蹂 橈擊 蛭ж貊, 氈棻堅虜 憲賊 腆 蛭м棲棻)
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
