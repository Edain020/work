/// =================================================
/// 砂時計制御プログラム
/// -------------------------------------------------
/// 班 ：303
/// 制作：眞鍋大輔
/// =================================================
/// < 内容 >
/// 砂時計用のシェーダーグラフで設定した変数を
/// 制御するプログラム
/// 
/// -------------------------------------------------
/// < 更新日 >
/// 2021/03/17 制作開始
///            完成
/// 
/// -------------------------------------------------
/// < メモ >
/// 
/// =================================================
/// 
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

static class SunadokeiDefine
{
    public const float ErrorTime = 0.1f;
}

public class Sunokei : MonoBehaviour
{
    //変数宣言
    [SerializeField, Header("オブジェクト")] GameObject SunadokeiUp;  //砂時計上部分のマテリアル
    [SerializeField] GameObject SunadokeiDown;                        //砂時計下部分のマテリアル
    [SerializeField] GameObject DropSand;                        //砂時計下部分のマテリアル

    [SerializeField, Header("時間"), Range(0, 1)] float time = 0;     //経過時間格納用
    private Material Up, Down, Drop;   //マテリアル格納用
    private bool MainMode = true;    //モード選択（通常再生か、逆再生か）
//    private bool DropMode = true;   //落ちている砂の消える向き
    private int AnimMode = 0;
    private float DropTime = 0f;

    Timer timer;


    void Start()
    {
        //マテリアルの抽出
        Up = SunadokeiUp.GetComponent<Renderer>().material;
        Down = SunadokeiDown.GetComponent<Renderer>().material;
        Drop = DropSand.GetComponent<Renderer>().material;

        timer = GameObject.Find("Director").GetComponent<Timer>();
    }



    void Update()
    {
        //----時間更新
        time = timer.GetCurrentTime() / timer.GetRewindInterval();

        //switch (MainMode) {
        //    case true:
        //        time += Time.deltaTime/5.0f;
        //        break;
        //
        //    case false:
        //        time -= Time.deltaTime/5.0f;
        //        break;
        //
        //    default:
        //        break;
        //}

        //---- 経過時間をシェーダーに適用


        SetAnimMode();

        switch (AnimMode)
        {
            case 0:
                Drop.SetFloat   ("_DropTime"            ,1.0f-(time * 10f));
                Drop.SetInt     ("_DropMode"            ,1);
                Up.SetFloat     ("_SundadokeiUpTime"    ,0.03f);
                Down.SetFloat   ("_SundadokeiDownTime"  , 1.0f);
                break;
            case 1:

                Up.SetFloat     ("_SundadokeiUpTime"    , time+0.03f);
                Down.SetFloat   ("_SundadokeiDownTime"  , 1.0f - time);
                break;
            case 2:
                DropTime += Time.deltaTime / 5.0f;
                Drop.SetFloat   ("_DropTime"            , DropTime*10f);
                Drop.SetInt     ("_DropMode"            , 0);
                Up.SetFloat     ("_SundadokeiUpTime"    , 1.0f);
                Down.SetFloat   ("_SundadokeiDownTime"  ,  0.04f);
                break;

            case 3:
                Drop.SetFloat("_DropTime", 1.0f - (time * 10f));
                Drop.SetInt("_DropMode", 1);
                Up.SetFloat("_SundadokeiUpTime", 0.03f);
                Down.SetFloat("_SundadokeiDownTime", 1f);
                break;
            case 4:
                Up.SetFloat("_SundadokeiUpTime", time + 0.03f);
                Down.SetFloat("_SundadokeiDownTime", 1f - time);
                break;
            case 5:
                DropTime -= Time.deltaTime / 5.0f;
                Drop.SetFloat("_DropTime", DropTime * 10f);
                Drop.SetInt("_DropMode", 0);
                Up.SetFloat("_SundadokeiUpTime", 1f);
                Down.SetFloat("_SundadokeiDownTime", 0.04f);
                break;

            default:
                break;
        }



        //----モード切り替え＆パラメーターリセット
        if (time >= 1f)
        {
            time = 1f;

            Drop.SetFloat("_DropSandDirection", -1f);

            MainMode = false;
        }
        if(time <= 0f)
        {
            time = 0f;

            Drop.SetFloat("_DropSandDirection", 1f);
            DropTime = 0;

            MainMode = true;
        }
    }


    void SetAnimMode()
    { 
        switch (MainMode)
        {
            case true:
                if (time <= 0.1f)
                {
                    AnimMode = 0;
                    break;
                }

                if (time > 0.1f && time <= 0.96)
                {
                    AnimMode = 1;
                    break;
                }

                if (time > 0.96 && time <1.0f)
                {
                    AnimMode = 2;
                    break;
                }
                break;


            case false:
                if (time <= 0.1f)
                {
                    AnimMode = 3;
                    break;
                }

                if (time > 0.1f && time <= 0.96)
                {
                    AnimMode = 4;
                    break;
                }

                if (time > 0.96 && time < 1.0f)
                {
                    AnimMode = 5;
                    break;
                }
                break;
        }
    }


    public void SetActive(bool isActive)
    {
        SunadokeiUp.SetActive(isActive);
        SunadokeiDown.SetActive(isActive);
        DropSand.SetActive(isActive);
    }
}
