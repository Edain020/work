using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class VerticalMoveGround : MonoBehaviour
{
    public bool bFlg;
    public float MaxDownPos;
    public float MaxUpPos;
    public float MoveSpeed;
    public int StopTimer;
    public int Timer;

    private float Speed;
    private Vector3 DefaultPos = Vector3.zero;
    private Vector3 NowPos = Vector3.zero;

    Rigidbody rb;
    RewindManager RM;
    StageManager SM;

    bool isRewinding = false;
    float FirstSpeed;


    void Start()
    {
        // 初期位置を記憶
        DefaultPos = transform.position;

        // 現在の横移動床の座標を取得
        NowPos = transform.position;

        // 移動速度
        Speed = MoveSpeed;

        // 初速
        FirstSpeed = Speed;

        // リジッドボディを取得
        rb = GetComponent<Rigidbody>();

        // 逆再生コンポーネント？
        RM = GameObject.Find("Director").GetComponent<RewindManager>();

        SM = GameObject.Find("Director").GetComponent<StageManager>();

        Timer = 60;
    }
    

    void FixedUpdate()
    {
        // ーーーーー 逆再生関連 ーーーーー
        if (RM.isRewinding())
        {
            if(!isRewinding)
            {
                isRewinding = true;
            }

            return;
        }

        if(isRewinding)
        {
            // 逆再生終了時の処理
            Speed = FirstSpeed;

            transform.position = DefaultPos;

            NowPos = DefaultPos;

            Timer = StopTimer;

            isRewinding = false;
        }

        // ステージの状態がmainじゃない場合
        if (SM.GetCurrentState() != StageState.Main)
        {
            // 処理しない
            return;
        }

        // 現在の座標を更新
        NowPos = transform.position;

        // スイッチが作動している
        if (bFlg)
        {
            // 床の座標が移動可能な場所の下限に達した
            if (NowPos.y <= MaxDownPos)
            {
                // 床一時停止処理
                MoveStopTimer();

                //// 移動方向を反転させる
                //Speed = MoveSpeed;
            }

            // 床の座標が移動可能な場所の上限に達した
            else if (NowPos.y >= MaxUpPos)
            {
                // 床一時停止処理
                MoveStopTimer();

                //// 移動方向を反転させる
                //Speed = -MoveSpeed;
            }

            // 右端でも左端でもない場合
            else
            {
                transform.position += new Vector3(0.0f, Speed, 0.0f) * Time.deltaTime;
            }

            // タイマー終了後の移動
            //if (Timer >= StopTimer)
            //{
            //    // 移動
            //    transform.position += new Vector3(0.0f, Speed, 0.0f) * Time.deltaTime;
            //}

            //else
            //{
            //    // 停止
            //    rb.velocity = new Vector3(0, 0, 0);
            //}
        }

        // スイッチが作動していない
        else
        {
            // 停止
            rb.velocity = new Vector3(0, 0, 0);
        }
    }



    // スイッチのフラグ取得
    public void SetMoveFlg(bool flg)
    {
        bFlg = flg;
    }



    // 床一時停止処理
    void MoveStopTimer()
    {
        // タイマースタート
        Timer--;

        // タイマーが終了
        if (Timer <= 0)
        {
            // タイマー初期化
            Timer = StopTimer;

            // 向き反転
            Speed *= -1;

            // 移動
            transform.position += new Vector3(0.0f, Speed, 0.0f) * Time.deltaTime;
        }
    }
}
