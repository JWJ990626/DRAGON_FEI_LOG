#define GLOBAL_INSTANCE 
#include "../include/GV.h"
#include <easyx.h>

extern int FLAG_MODE = 0;

//ループで必ず行う３大処理
int ProcessLoop(){
	if(ProcessMessage()!=0)return -1;//プロセス処理がエラーなら-1を返す
	if(ClearDrawScreen()!=0)return -1;//画面クリア処理がエラーなら-1を返す
	GetHitKeyStateAll_2();//現在のキー入力処理を行う
	GetHitPadStateAll();  //現在のパッド入力処理を行う
	return 0;
}

void menu()
{
	initgraph(1280, 720);
	//initgraph(1280,720 );

	IMAGE img;
	loadimage(&img, "C:\\Users\\WY\\Desktop\\ﾔﾓﾆﾟﾔﾓｰﾋ\\dat\\img\\LOGIN\\login.jpg");
	putimage(0, 0, &img);


	//closegraph();
	setfillstyle(BS_SOLID);

	MOUSEMSG m;
	//solidrectangle(740, 340, 1030, 3);

	int FLAG_WANYI = 1;
	

	while (FLAG_WANYI)
	{
		FLAG_WANYI = 1;
		m = GetMouseMsg();				// ﾅﾐｶﾏﾊﾇｷ�ｰｴﾏﾂﾊ�ｱ�
		if (m.x >= 740 && m.x <= 1030 && m.y >= 340 && m.y <= 390)
		{
			setlinecolor(BLUE);			// ﾑ｡ﾖﾐｿ�ｿ�ﾏﾟﾌ�ﾑﾕﾉｫ
			rectangle(740, 340, 1030, 390);
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				cleardevice();
				FLAG_WANYI = 0;
				FLAG_MODE = 0;

			}




			//login_gui();
		}
		else if (m.x >= 740 && m.x <= 1030 && m.y >= 410 && m.y <= 460)
		{
			setlinecolor(BLUE);			// ﾑ｡ﾖﾐｿ�ｿ�ﾏﾟﾌ�ﾑﾕﾉｫ
			rectangle(740, 410, 1030, 460);
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				cleardevice();
				FLAG_WANYI = 0;
				FLAG_MODE = 1;

			}
		}
		else if (m.x >= 740 && m.x <= 1030 && m.y >= 470 && m.y <= 530)
		{
			setlinecolor(BLUE);			// ﾑ｡ﾖﾐｿ�ｿ�ﾏﾟﾌ�ﾑﾕﾉｫ
			rectangle(740, 470, 1030, 530);
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				cleardevice();
				FLAG_WANYI = 0;


			}
		}
		else if (m.x >= 740 && m.x <= 1030 && m.y >= 550 && m.y <= 610)
		{
			setlinecolor(BLUE);			// ﾑ｡ﾖﾐｿ�ｿ�ﾏﾟﾌ�ﾑﾕﾉｫ
			rectangle(740, 550, 1030, 610);
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				cleardevice();
				FLAG_WANYI = 0;


			}
		}
		else if (m.x >= 740 && m.x <= 1030 && m.y >= 620 && m.y <= 680)
		{
			setlinecolor(BLUE);			// ﾑ｡ﾖﾐｿ�ｿ�ﾏﾟﾌ�ﾑﾕﾉｫ
			rectangle(740, 620, 1030, 680);
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				cleardevice();
				FLAG_WANYI = 0;


			}
		}

		else {
			setlinecolor(BLACK);
			rectangle(740, 340, 1030, 390), rectangle(740, 410, 1030, 460); rectangle(740, 470, 1030, 530); rectangle(740, 550, 1030, 610); rectangle(740, 620, 1030, 680);
		}


	}
}


int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow){
	
	
	menu();
	closegraph();
	ChangeWindowMode(FLAG_MODE);//ウィンドウモード
	if(DxLib_Init() == -1 || SetDrawScreen( DX_SCREEN_BACK )!=0) return -1;//初期化と裏画面化

	while(ProcessLoop()==0){//メインループ
		music_ini();
		switch(func_state){
			case 0://初回のみ入る処理
				load();		//データロード
				first_ini();//初回の初期化
				func_state=99;
				break;
			case 99://STGを始める前に行う初期化
				ini();
				load_story();
				func_state=100;
				break;
			case 100://通常処理
								
				calc_ch();       
				ch_move();       
				cshot_main();    
				enemy_main();	 
				boss_shot_main();
				shot_main();	 
				out_main();  	 
				effect_main();   
				calc_main();	 
				graph_main();    
				bgm_main();		 
				if(boss.flag==0)
					stage_count++;
				break;
			default:
				printfDx("不明なfunc_state\n");
				break;
		}
		music_play();			
		fps_wait();				 
		if(CheckStateKey(KEY_INPUT_ESCAPE)==1)break;//エスケープが入力されたらブレイク
		ScreenFlip();//裏画面反映
		count++;

	}
	DxLib_End();//ＤＸライブラリ終了処理
	return 0;
}
