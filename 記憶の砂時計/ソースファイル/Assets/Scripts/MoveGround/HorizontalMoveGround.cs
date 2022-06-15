using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HorizontalMoveGround : MonoBehaviour
{
    public bool bFlg;
    public float MaxRightPos;
    public float MaxLeftPos;
    public float MoveSpeed;
    public int StopTimer;
    public int Timer;

    private float Speed;
    private Vector3 DefaultPos = Vector3.zero;
    private Vector3 NowPos = Vector3.zero;


    Rigidbody rb;
    RewindManager RM;
    StageManager SM;

    bool isRewinding = false;       // 逆再生フラグ
    float FirstSpeed;



    // Start is called before the first frame update
    void Start()
    {
        // 初期位置を記憶
        DefaultPos = transform.position;

        // 現在の横移動床の座標を取得
        NowPos = DefaultPos;

        // 移動速度
        Speed = MoveSpeed;

        // 初速
        FirstSpeed = Speed;

        // リジッドボディを取得
        rb = GetComponent<Rigidbody>();

        // 逆再生コンポーネント？
        RM = GameObject.Find("Director").GetComponent<RewindManager>();

        SM = GameObject.Find("Director").GetComponent<StageManager>();

        // 初期座標がどちらかの端だった場合、停止処理を行わない
        //if(transform.position.x == MaxLeftPos || transform.position.x == MaxRightPos)
        //{
        //    Timer = 0;
        //}
        Timer = StopTimer;
    }



    // Update is called once per frame
    void FixedUpdate()
    {
        // ーーーーー 逆再生関連 ーーーーー
        if (RM.isRewinding())
        {
            if (!isRewinding)
            {
                isRewinding = true;
            }

            return;
        }

        if (isRewinding)
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
            // 床の座標が移動可能な場所の右端に達した
            if (NowPos.x >= MaxRightPos)
            {
                // 床一時停止処理
                MoveStopTimer();
            }

            // 床の座標が移動可能な場所の左端に達した
            else if (NowPos.x <= MaxLeftPos)
            {
                // 床一時停止処理
                MoveStopTimer();
            }

            // 右端でも左端でもない場合
            else
            {
                transform.position += new Vector3(Speed, 0.0f, 0.0f) * Time.deltaTime;
            }

            // タイマー終了後の移動
            //if (Timer >= StopTimer)
            //{
            //    transform.position += new Vector3(Speed, 0.0f, 0.0f) * Time.deltaTime;
            //    //rb.MovePosition(new Vector3(NowPos.x + Speed, NowPos.y, NowPos.z));
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
            transform.position += new Vector3(Speed, 0.0f, 0.0f) * Time.deltaTime;
        }
    }
}
