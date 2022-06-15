using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using UnityEngine.InputSystem;
using UnityEngine.InputSystem.Controls;

public class SelectMapManager : MonoBehaviour
{
    //定数宣言
    const float MultiplySizeImage = 1.2f;//選択中増やす倍率

    const float MAX_COLOR = 1f;
    const float MIDDLE_COLOR = 0.5f;
    const float MIN_COLOR = 0f;


    //変数宣言
    [SerializeField, Header("親オブジェクト")] GameObject[] ParentObj; //親一覧
    public Image[] MapImages;          //変更するマップ画像配列
    [SerializeField] float Stick;      // スティックの入力感度設定用変数
    [SerializeField]selectEffect EffectPos;

    Vector3[] DefaultMapImagesSize;   //元のマップ画像の大きさ配列
    float cout;
    int stageClearNum;
    int MapClearNum;
    float fLastTimeInput;

    private static int mapNum;

    Fade fade;

    // SE関連
    [SerializeField] AudioClip CursorSE;
    AudioSource audioSource;

    //ゲッターセッター
    public static int MapNum
    {
        get { return mapNum; }
        private set { mapNum = value; }
    }

    // Start is called before the first frame update
    void Start()
    {
        //配列数を初期化
        ParentObj = new GameObject[this.transform.childCount];
        MapImages = new Image[ParentObj.Length];
        DefaultMapImagesSize = new Vector3[ParentObj.Length];

        //値を格納
        for (int i = 0; i < this.transform.childCount; i++)
        {
            //親を取得
            ParentObj[i] = this.transform.GetChild(i).gameObject;
            //変更する画像を取得
            MapImages[i] = ParentObj[i].transform.Find("MapImage").GetComponent<Image>();
            Debug.Log(i);
            //元の大きさを取得
            DefaultMapImagesSize[i] = MapImages[i].GetComponent<Transform>().localScale;
        }
        //変数初期化
        cout = 0;
        mapNum = 0;
        stageClearNum = ClearManager.getClearNum();
        MapClearNum = stageClearNum / 5;

        //選択されてる画像のポジションの位置を格納
        EffectPos.setNextPos(MapImages[MapNum].transform.position);
        
        //色変更
        SetDefaultColor();

        // 入力のCT
        fLastTimeInput = 0.0f;

        fade = GameObject.Find("Fade").GetComponent<Fade>();

        // SE関連
        audioSource = GetComponent<AudioSource>();
    }

    //色初期化
    void SetDefaultColor()
    {
        for (int i = ParentObj.Length - 1; i > MapClearNum; i--)
        {
            MapImages[i].color = new Color(MIN_COLOR, MIN_COLOR, MIN_COLOR);
        }

        for (int i = (ParentObj.Length - 1)- MapClearNum; i > 0; i--)
        {
            MapImages[i].color = new Color(MIDDLE_COLOR, MIDDLE_COLOR, MIDDLE_COLOR);
        }

        MapImages[0].color = new Color(MAX_COLOR, MAX_COLOR, MAX_COLOR);
    }


    // Update is called once per frame
    void Update()
    {
        emphasisImage(MapNum);

        if(Time.time - fLastTimeInput > 0.15f)
        {
            selectMap();
        }

        SetMap();
    }


    //画像の強調
    void emphasisImage(int i)
    {
        //値計算
        Vector2 num;
        num.x = DefaultMapImagesSize[i].x + Mathf.Sin(cout) * 0.1f;
        num.y = DefaultMapImagesSize[i].y + Mathf.Sin(cout) * 0.1f;
        EffectPos.setNextPos(MapImages[i].transform.position);
        //適用
        MapImages[i].transform.localScale = num;
        //ゲッターで返す値を格納
     
        //タイミング更新
        cout += 0.01f;
    }


    //マップ選択
    void selectMap()
    {
        //右移動
        if (SandClockInput.getButtonDown(ButtonInputInfo.right) && Time.time - fLastTimeInput > 0.15f)
        {
            //選択更新
            MapNum++;

            //オバーフローした場合
            if (MapNum > MapClearNum)
            {
                //オーバーフロー分を戻す
                MapNum = 0;
                //外れた画像の初期化
                MapImages[MapClearNum].color = new Color(MIDDLE_COLOR, MIDDLE_COLOR, MIDDLE_COLOR);
                //新たに選ばれた画像を強調
                MapImages[MapNum].color = new Color(MAX_COLOR, MAX_COLOR, MAX_COLOR);
            }
            //通常時
            else
            {
                audioSource.PlayOneShot(CursorSE);
                //外れた画像の初期化
                MapImages[MapNum - 1].color = new Color(MIDDLE_COLOR, MIDDLE_COLOR, MIDDLE_COLOR);
                //新たに選ばれた画像を強調
                MapImages[MapNum].color = new Color(MAX_COLOR, MAX_COLOR, MAX_COLOR);
            }

            //タイマー初期化
            cout = 0;
            fLastTimeInput = Time.time;
        }

        // 左移動
        if (SandClockInput.getButtonDown(ButtonInputInfo.left) && Time.time - fLastTimeInput > 0.15f)
        {
            //選択更新
            MapNum--;

            //オバーフローした場合
            if (MapNum < 0)
            {
                //オーバーフロー分を戻す
                MapNum = MapClearNum;
                //外れた画像の初期化
                MapImages[0].color = new Color(MIDDLE_COLOR, MIDDLE_COLOR, MIDDLE_COLOR);
                //新たに選ばれた画像を強調
                MapImages[MapNum].color = new Color(MAX_COLOR, MAX_COLOR, MAX_COLOR);
            }
            //通常時
            else
            {
                audioSource.PlayOneShot(CursorSE);
                //外れた画像の初期化
                MapImages[MapNum + 1].color = new Color(MIDDLE_COLOR, MIDDLE_COLOR, MIDDLE_COLOR);
                //新たに選ばれた画像を強調
                MapImages[MapNum].color = new Color(MAX_COLOR, MAX_COLOR, MAX_COLOR);
            }

            //タイマー初期化
            cout = 0;
            fLastTimeInput = Time.time;
        }
    }

    void SetMap()
    {
        if (SandClockInput.getButtonUp(ButtonInputInfo.select))
            fade.SetFade(true, 0.5f, "SelectStage");
        if (SandClockInput.getButtonUp(ButtonInputInfo.cancel))
            fade.SetFade(true, 0.5f, "Title");
    }
}


