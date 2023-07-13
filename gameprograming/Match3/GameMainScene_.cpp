#include"GameMainScene.h"
#include"DxLib.h"
#include"Stage.h"
#include"SceneManager.h"

/************************************
*マクロ定義
*************************************/
#define TIMELIMIT         (3600*3)//制限時間
#define NUMBER_IMAGE_MAX (10)     //数字画面数

/************************************
*型定義
*************************************/

/************************************
*変数宣言
*************************************/
int GameScore;
int GameLevel;
int GameMission;
int GameTime;
int GameCount;  //初期化されないようにするためのカウント
int ReStartFlag;

intNUmberIMage[NUMBER_IMAGE_MAX];   //数字用画像

/************************************
*プロトタイプ宣言
*************************************/

/************************************
* ゲームメイン画面：初期化処理
* 引数：なし
* 戻り値：エラー情報
*************************************/
int GameMainScene_Intialize(void)
{
	int ret = 0;

	int i;


   //画像読み込み
   LoadDivGraph("images/number.png", NUMBER_IMAGE_MAX,
	NUMBER_IMAGE_MAX, 1, 60, 120, NumberImage);

    //ステージ機能初期化
    ret = StageInitialize();

  //エラーチェック
  for (i = 0; i < NUMBER_IMAGE_MAX; i++)
  {
	if (NumberImage[i] == D_ERROR)
	{
		ret = D_ERROR;
		break;
	}
  }
  //ゲームプレイが初回かどうか
  if (GameCount == 0)
  {
	GameScore = 0;         //スコアの初期化
	GameLevel = 1;         //ゲームレベルの初期化
	SetStageMIssion(3);    //ミッションの初期化
	GameCount++;           //次回の設定
  }
  else
  {
	GameLevel++;         //ゲームレベルの更新
	Set_StageMission(3); //ミッションを増やす
  }
   GameTime = TIMELIMIT;

   return ret;
}
/***********************************
*ゲームメイン画面：更新処理
* 引数：なし
* 戻り値：なし
************************************/
void GameMainScene_Update(void)
{
	switch (GetStageState())
	{
		case 0:
		    SelectBlock();
		    break;
   
		case 2:
			MoveBlock();
			break;

		case 3
			CheckBlock();
			break;

		case 4:
			CheakClear();
			break;
	
		default:
			break;
	}

	//制限時間の更新
	GameTime--;

	//制限時間が無くなったら、ゲームオーバーに簡易する
	if (GameTime < 0)
	{
		Cange_Scene(E_GAME_OVER);
	}
	//ミッションを達成したら、ゲームクリア
	if (Get_StageClearFlag())
	{
		Change_Scene(E_GAME_CLEAR);
	}
}
/**************************************
*ゲームメイン画面：描画処理
* 引数：なし
* 戻り値：なし
***************************************/
void GameMainScene_Draw(void)
{
	int PosX = 600;
	int tmp_level = GameLevel;
	int tmp_score = Get_StageScore();

	//ステージを描画
	StageDraw();

	//フェードアウト状態か
	if (Get_StageState() == 1)
	{
		FadeOutBlock();   //フェードアウトする
	}
	//レベルを描画
	do {
		DrawRotaGraph(PosX, 80, 0.5f, 0, NUmberImage[tmp_level % 10], TRUE);
	}
 }