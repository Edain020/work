using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using UnityEngine.InputSystem;
using UnityEngine.InputSystem.Controls;

public class SelectStage : MonoBehaviour
{
    //定数宣言
    const float MAX_COLOR = 1f;
    const float MIDDLE_COLOR = 0.5f;
    const float MIN_COLOR = 0f;

    [SerializeField, Header("最大ステージ数")] int MaxStage = 5;

    //変数宣言

    [SerializeField, Header("親オブジェクト")]         GameObject[] ParentsStageImage;
    [SerializeField, Header("ステージ画像")]           Image[] stageImages;
    [SerializeField, Header("ステージナンバー画像")]   Image[] numImages;
    [SerializeField, Header("選択されているステージ")] public static int selectStageNum = 0;
    [SerializeField, Header("ステージクリア数")]       int stageClearNum = 0;
    [SerializeField, Header("マップ番号")]           　int mapNum = 0;
    [SerializeField] selectEffect EffectPos;

    Fade fade;

    private Vector3[] defaultImageSize;

    float cout = 0;

    // 入力クールタイム
    float fLastTimeInput;

    public int MapNum{
        get { return mapNum; }
        private set { mapNum = value; }
    }

    public int SelectStageNum
    {
        get { return selectStageNum; }
    }

    void Start()
    {
        stageClearNum = ClearManager.getClearNum();

        mapNum = SelectMapManager.MapNum;
        selectStageNum = 0;

        //配列の指定
        stageImages = new Image[ParentsStageImage.Length];
        numImages   = new Image[ParentsStageImage.Length];

        //子コンポーネントの取得
        for(int i = 0; i < MaxStage; i++)
        {
            stageImages[i] = ParentsStageImage[i].transform.Find("StageImage").GetComponent<Image>();
            numImages[i]   = ParentsStageImage[i].transform.Find("NumImage")  .GetComponent<Image>();
        }

        //ステージ色初期化
        for (int i = 0; i < MaxStage; i++)
        {
            stageImages[i].color = new Color(MIN_COLOR, MIN_COLOR, MIN_COLOR);
        }
        //ステージナンバー色初期化
        for(int i = 0; i < MaxStage; i++)
        {
            numImages[i].color = new Color(MIDDLE_COLOR, MIDDLE_COLOR, MIDDLE_COLOR);
        }


        //選べるステージ数を探索;
        MaxStage = stageClearNum - mapNum * 5;
        //オーバーフローした分を戻す
        if (MaxStage > 4)
        {
            MaxStage = 4;
        }

        //遊べるステージ色を設定
        for (int i = 0; i <= MaxStage; i++)
        {
            stageImages[i].color = new Color(MIDDLE_COLOR, MIDDLE_COLOR, MIDDLE_COLOR);
        }

        //1ステージ目を協調
        stageImages[0].color = new Color(MAX_COLOR, MAX_COLOR, MAX_COLOR);
        numImages[0].color = new Color(MAX_COLOR, MAX_COLOR, MAX_COLOR);
        EffectPos.setNextPos(stageImages[0].transform.position);

        //元のサイズを設定
        SetDefaultSize();

        // 入力CTの初期化
        fLastTimeInput = 0.0f;

        fade = GameObject.Find("Fade").GetComponent<Fade>();

    }

    //元のサイズ保存
    void SetDefaultSize()
    {
        defaultImageSize = new Vector3[ParentsStageImage.Length];

        for(int i = 0; i < ParentsStageImage.Length; i++)
        {
            defaultImageSize[i] = stageImages[i].GetComponent<Transform>().localScale;
        }
    }



    // Update is called once per frame
    void Update()
    {
        //画像の強調表示
        emphasisImage(selectStageNum);

        // 入力CT
        if(Time.time - fLastTimeInput > 0.15f)
        {
            //ステージの選択
            selectStage();
        }
        
        //シーン遷移
        SetScene();
    }



    //画像の強調表示
    void emphasisImage(int i)
    {
        //値計算
        Vector2 num;
        num.x = defaultImageSize[i].x + Mathf.Sin(cout) * 0.1f;
        num.y = defaultImageSize[i].y + Mathf.Sin(cout) * 0.1f;
        EffectPos.setNextPos(stageImages[i].transform.position);
        //適用
        stageImages[i].transform.localScale = num;
        //タイミング更新
        cout += 0.01f;
    }



    //ステージ選択
    void selectStage()
    {
        //右移動
        // ゲームパッドが接続されている
        if(SandClockInput.getButtonDown(ButtonInputInfo.right) && Time.time - fLastTimeInput > 0.15f)
        {
            // 選択処理
            SelectRight();
        }
        if(SandClockInput.getButtonDown(ButtonInputInfo.left) && Time.time - fLastTimeInput > 0.15f)
        {
            // 選択処理
            SelectLeft();
        }
    }



    //シーン遷移関数
    void SetScene()
    {
        if (SandClockInput.getButtonUp(ButtonInputInfo.cancel))
        {
            // ゲームパッドの「B」ボタンが離された
            fade.SetFade(true, 0.5f, "SelectMap");
        }
        if(SandClockInput.getButtonUp(ButtonInputInfo.select))
        {
            // 選択されたステージへ遷移
            SceneTransition();
        }
    }



    // 右入力選択処理
    private void SelectRight()
    {
        //選択更新
        selectStageNum++;

        //端っこだった場合
        if (selectStageNum > MaxStage)
        {
            //外れた画像の初期化
            stageImages[MaxStage].color = new Color(MIDDLE_COLOR, MIDDLE_COLOR, MIDDLE_COLOR);
            numImages[MaxStage].color = new Color(MIDDLE_COLOR, MIDDLE_COLOR, MIDDLE_COLOR);
            stageImages[MaxStage].transform.localScale = defaultImageSize[MaxStage];

            //新たに選択された画像を協調
            stageImages[0].color = new Color(MAX_COLOR, MAX_COLOR, MAX_COLOR);
            numImages[0].color = new Color(MAX_COLOR, MAX_COLOR, MAX_COLOR);

            //オーバーフロー分を戻す
            selectStageNum = 0;
        }

        //通常時の更新
        else
        {
            //外れた画像の初期化
            stageImages[selectStageNum - 1].color = new Color(MIDDLE_COLOR, MIDDLE_COLOR, MIDDLE_COLOR);
            numImages[selectStageNum - 1].color = new Color(MIDDLE_COLOR, MIDDLE_COLOR, MIDDLE_COLOR);
            stageImages[selectStageNum - 1].transform.localScale = defaultImageSize[selectStageNum - 1];

            //新たに選択された画像を協調
            stageImages[selectStageNum].color = new Color(MAX_COLOR, MAX_COLOR, MAX_COLOR);
            numImages[selectStageNum].color = new Color(MAX_COLOR, MAX_COLOR, MAX_COLOR);
        }
        cout = 0;

        // 入力CT設定
        fLastTimeInput = Time.time;
    }



    // 左入力選択処理
    private void SelectLeft()
    {
        //選択更新
        selectStageNum--;

        //端の画像だった場合
        if (selectStageNum < 0)
        {
            //外れた画像の初期化
            stageImages[0].color = new Color(MIDDLE_COLOR, MIDDLE_COLOR, MIDDLE_COLOR);
            numImages[0].color = new Color(MIDDLE_COLOR, MIDDLE_COLOR, MIDDLE_COLOR);
            stageImages[0].transform.localScale = defaultImageSize[0];


            //新たに選択された画像を協調
            stageImages[MaxStage].color = new Color(MAX_COLOR, MAX_COLOR, MAX_COLOR);
            numImages[MaxStage].color = new Color(MAX_COLOR, MAX_COLOR, MAX_COLOR);

            //オーバーフロー分を戻す
            selectStageNum = MaxStage;
        }
        //通常時の更新
        else
        {
            //外れた画像の初期化
            stageImages[selectStageNum + 1].color = new Color(MIDDLE_COLOR, MIDDLE_COLOR, MIDDLE_COLOR);
            numImages[selectStageNum + 1].color = new Color(MIDDLE_COLOR, MIDDLE_COLOR, MIDDLE_COLOR);
            stageImages[selectStageNum + 1].transform.localScale = defaultImageSize[selectStageNum + 1];

            //新たに選択された画像を協調
            stageImages[selectStageNum].color = new Color(MAX_COLOR, MAX_COLOR, MAX_COLOR);
            numImages[selectStageNum].color = new Color(MAX_COLOR, MAX_COLOR, MAX_COLOR);
        }

        // 入力CT設定
        fLastTimeInput = Time.time;
    }



    // シーン遷移処理
    private void SceneTransition()
    {
        int i = selectStageNum + mapNum * 5;
        switch (i)
        {
            case 0:
                fade.SetFade(true, 0.5f, "Stage_1-1");
                break;
            case 1:
                fade.SetFade(true, 0.5f, "Stage_1-2");
                break;
            case 2:
                fade.SetFade(true, 0.5f, "Stage_1-3");
                break;
            case 3:
                fade.SetFade(true, 0.5f, "Stage_1-4");
                break;
            case 4:
                fade.SetFade(true, 0.5f, "Stage_1-5");
                break;
            case 5:
                fade.SetFade(true, 0.5f, "Stage_1-6");
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                break;
            case 10:
                break;
            case 11:
                break;
            case 12:
                break;
            case 13:
                break;
            case 14:
                break;
            case 15:
                break;
            case 16:
                break;
            case 17:
                break;
            case 18:
                break;
            case 19:
                break;
            case 20:
                break;
            case 21:
                break;
            case 22:
                break;
            case 23:
                break;
            case 24:
                break;
        }
    }
}


