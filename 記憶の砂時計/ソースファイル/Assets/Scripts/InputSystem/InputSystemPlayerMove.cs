using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;
using UnityEngine.InputSystem.Controls;

public class InputSystemPlayerMove : MonoBehaviour
{
    // プレーヤーの状態
    public enum PlayerState
    {
        Stay,   // 待機
        Walk,   // 歩く
        Jump,   // ジャンプ
        Ladder, // はしご
        Grab,   // 掴む
        Push,   // 押す
        Pull,   // 引っ張る
    }


    // ーーーーーーーーーー Unityに公開するパラメータ ーーーーーーーーーー
    [Header("プレイヤーの状態")]
    [SerializeField] PlayerState currentState;
    public PlayerState CurrentState { get { return currentState; } }

    [Header("数値")]
    [SerializeField] float fMaxMoveSpeed;       // 最大速度
    [SerializeField] float fMoveSpeed;          // 移動速度
    [SerializeField] float fJumpPower;          // ジャンプの高さ
    [SerializeField] float fReversePower;       // 慣性(進行方向と逆の力)
    [SerializeField] float fClimbSpeed;         // はしごを登るスピード           
    [SerializeField] float fSmooth;             // 回転の滑らかさ

    [Header("フラグ")]
    [SerializeField] bool ladderArriveFlg;     // はしごの位置に到達しているかのフラグ
    [SerializeField] bool isOnGround;          // 接地中かどうかのフラグ
    public bool IsOnGround { get { return isOnGround; } set { isOnGround = value; } }

    [Header("効果音")]
    [SerializeField] AudioClip JumpSE;          // ジャンプ音
    [SerializeField] AudioClip WalkSE;          // 足音



    // ーーーーーーーーーー Unityに公開しないパラメータ ーーーーーーーーーー
    Rigidbody rb;
    AudioSource audioSource;
    Animator anim;
    RewindManager RM;
    StageManager SM;

    GameObject ghost;
    GameObject Root;
    Quaternion PlayerRotation;
    

    // プレイヤーが向きたい方向
    Vector3 PlayerDir;
    float fAirMovePer = 0.1f;   // 空中での制御

    bool isRewinding = false;
    public bool bNearLadderArriveFlg;
    float timeOut;
    float timeElapsed;
    bool isJump;


    // Start is called before the first frame update
    void Start()
    {
        Root = transform.root.gameObject;

        // コンポーネントを取得
        rb = GetComponent<Rigidbody>();
        audioSource = GetComponent<AudioSource>();
        anim = transform.Find("Model").GetComponent<Animator>();
        RM = GameObject.Find("Director").GetComponent<RewindManager>();
        SM = GameObject.Find("Director").GetComponent<StageManager>();

        // オブジェクトを取得
        ghost = GameObject.Find("Ghost");

        // 数値初期化
        timeOut = 0.5f;
        timeElapsed = 0.0f;
        PlayerDir = new Vector3(1.0f, 0.0f, 0.0f);

        // フラグ初期化
        isOnGround = false;
        ladderArriveFlg = false;
        bNearLadderArriveFlg = false;
        isJump = false;
    }

    void Update()
    {
        Vector3 velocity = rb.velocity;
        velocity.x = 0f;
        rb.velocity = velocity;

        ClearAnimFlag();

        if (currentState == PlayerState.Stay && CurrentAnimName() == "Humikomi")
        {
            currentState = PlayerState.Jump;
        }

        switch (currentState)
        {
            case PlayerState.Walk:
                anim.SetBool("isWalk", true);
                break;
            case PlayerState.Jump:
                anim.SetBool("isJump", true);
                break;
            case PlayerState.Ladder:
                anim.SetBool("isLadder", true);
                break;
            case PlayerState.Grab:
                anim.SetBool("isGrab", true);
                break;
            case PlayerState.Push:
                anim.SetBool("isGrab", true);
                anim.SetBool("isPush", true);
                break;
            case PlayerState.Pull:
                anim.SetBool("isGrab", true);
                anim.SetBool("isPull", true);
                break;
        }
        anim.SetBool("OnGround", isOnGround);
    }


    void FixedUpdate()
    {
        float Horizontal = SandClockInput.getHorizontal();
        float Vertical = SandClockInput.getVertical();
        Root = transform.root.gameObject;

        if (SM.GetCurrentState() != StageState.Main)
        {
            return;
        }

        if (RM.isRewinding())
        {
            if (!isRewinding)
            {
                isRewinding = true;
                ghost.SetActive(true);
                ghost.transform.position = transform.position;
            }
            return;
        }

        if (isRewinding)
        {
            isRewinding = false;
            ghost.SetActive(false);
        }

        

        // 移動速度を減衰
        if (isOnGround)
        {
            fMoveSpeed *= 0.7f;

            if (-0.1f < fMoveSpeed && fMoveSpeed < 0.1f)
            {
                fMoveSpeed = 0.0f;

                switch (currentState)
                {
                    case PlayerState.Walk:
                        currentState = PlayerState.Stay;
                        break;

                    case PlayerState.Push:
                    case PlayerState.Pull:
                        currentState = PlayerState.Grab;
                        break;
                }
            }
        }


        // ーーーーーーーーーー 移動処理 ーーーーーーーーーー
        // プレイヤーの状態が、「はしご」ではない場合
        if (currentState != PlayerState.Ladder)
        {
            if (SandClockInput.getButton(ButtonInputInfo.left) || SandClockInput.getButton(ButtonInputInfo.right))
            {
                // 接地していたら移動速度を加速
                if (isOnGround)
                {
                    //----- 移動速度更新 -----
                    fMoveSpeed = Horizontal * fMaxMoveSpeed;

                    // 音関係
                    timeElapsed += Time.deltaTime;

                    if (timeElapsed >= timeOut)
                    {
                        audioSource.PlayOneShot(WalkSE);
                        timeElapsed = 0.0f;
                    }

                    if (!anim.GetBool("isGrab"))
                    {
                        // プレイヤーを向かせる角度を入手
                        PlayerDir = new Vector3(fMoveSpeed, 0, -1.0f);
                    }

                    switch (currentState)
                    {
                        case PlayerState.Stay:
                            currentState = PlayerState.Walk;
                            break;

                        case PlayerState.Grab:
                            if (PlayerDir.x / Mathf.Abs(PlayerDir.x) == fMoveSpeed / Mathf.Abs(fMoveSpeed))
                            {
                                currentState = PlayerState.Push;
                            }
                            else
                            {
                                currentState = PlayerState.Pull;
                            }
                            break;
                    }
                }
                // 接地していない(ジャンプ中)
                else
                {
                    if (SandClockInput.getButton(ButtonInputInfo.left) || SandClockInput.getButton(ButtonInputInfo.right))
                    {
                        //----- 移動速度更新 -----
                        fMoveSpeed += Horizontal * fMaxMoveSpeed * fAirMovePer;

                        if (Mathf.Abs(fMoveSpeed) > fMaxMoveSpeed)
                        {
                            float code = fMoveSpeed / Mathf.Abs(fMoveSpeed);
                            fMoveSpeed = fMaxMoveSpeed * code;                                
                        }

                        // プレイヤーを向かせる角度を入手
                        PlayerDir = new Vector3(fMoveSpeed, 0, -1.0f);
                    }
                }
            }

            // 移動
            transform.position += new Vector3(fMoveSpeed, 0.0f, 0.0f) * Time.deltaTime;
        }

        
        // 接地中　かつ、プレイヤーの状態が「ジャンプ」の場合
        if (isOnGround && currentState == PlayerState.Jump)
        {
            // プレイヤーの状態を「待機」に変更
            currentState = PlayerState.Stay;
            // 「ジャンプ」のアニメーションを停止
            anim.SetBool("isJump", false);
        }

        // ーーーーーーーーーー ジャンプ処理 ーーーーーーーーーー
        // プレイヤーの状態が「はしご」ではない場合
        if (!ladderArriveFlg)
        {
            // 接地中
            if (isOnGround && !isJump && PlayerDir.z != 1.0f)
            {
                if (SandClockInput.getButton(ButtonInputInfo.jump))
                {
                    // プレイヤーの状態を「ジャンプ」に変更
                    currentState = PlayerState.Jump;
                    // 「ジャンプ」のモーションを開始
                    anim.SetBool("isJump", true);
                    // 0.1秒後に実際の処理を開始(座標移動)
                    Invoke("Jump", 0.1f);
                    isJump = true;
                }
            }
        }


        //---------- はしご関係 ----------

        // はしご昇降(はしご接触フラグが「true」)
        if (ladderArriveFlg)
        {
            // プレイヤーを入力された方向へ移動させる(Vertical)
            if(SandClockInput.getButton(ButtonInputInfo.up) || SandClockInput.getButton(ButtonInputInfo.down))
            {
                if (currentState != PlayerState.Ladder)
                {
                    currentState = PlayerState.Ladder;
                    PlayerDir = new Vector3(0.0f, 0.0f, 1.0f);
                    rb.isKinematic = true;
                }

                // 移動
                transform.position += new Vector3(0.0f, Vertical, 0.0f) * fClimbSpeed * Time.deltaTime;
                anim.SetFloat("AnimSpeed", Vertical);
            }
            else
            {
                if (currentState == PlayerState.Ladder)
                {
                    anim.SetFloat("AnimSpeed", 0.0f);
                }
            }


            // プレイヤーの状態が「はしご」の場合
            if (currentState == PlayerState.Ladder)
            {
                // 移動速度をゼロに
                fMoveSpeed = 0.0f;
            }


            // プレイヤーが「はしご」を掴んでいる状態で接地していて２階の床ではない
            if (currentState == PlayerState.Ladder && isOnGround && !bNearLadderArriveFlg)
            {
                currentState = PlayerState.Stay;
                rb.isKinematic = false;
                anim.SetFloat("AnimSpeed", 1.0f);
            }
        }


        // プレイヤーが「はしご」から降りた   (プレイヤーの状態が「はしご」かつ、はしごに到達していない)
        if (currentState == PlayerState.Ladder && !ladderArriveFlg)
        {
            // プレイヤーの状態を「待機」に変更
            currentState = PlayerState.Stay;
            // 物理演算の影響を受ける
            rb.isKinematic = false;

            anim.SetFloat("AnimSpeed", 1.0f);
        }


        //----- Z座標の補正(奥や手前にプレイヤーを行かせない) -----
        if (transform.position.z > 0)
        {
            // 元の位置に戻す
            transform.position = new Vector3(transform.position.x, transform.position.y, 0);
        }

        //----- プレイヤーの回転 -----
        // 物をつかんでいる(子オブジェクトに物がある)
        if(isGrab())
        {
            Transform child;

            for (int i = 0; i < transform.childCount; ++i)
            {
                if ((child = transform.GetChild(i)).gameObject.tag == "PushGimmick")
                {
                    child.SetParent(null);

                    // 滑らかに回転
                    PlayerRotation = Quaternion.LookRotation(PlayerDir);
                    transform.rotation = Quaternion.Lerp(transform.rotation, PlayerRotation, Time.deltaTime * fSmooth);

                    child.SetParent(transform);
                }
            }
        }
        else
        {
            // 滑らかに回転
            PlayerRotation = Quaternion.LookRotation(PlayerDir);
            transform.rotation = Quaternion.Lerp(transform.rotation, PlayerRotation, Time.deltaTime * fSmooth);

        }
    }


    void Jump()
    {
        // 上方向へ進む
        rb.velocity = transform.up * fJumpPower;
        // SE再生
        audioSource.PlayOneShot(JumpSE);

        isOnGround = false;
        Invoke("JumpDelay", 0.1f);
    }


    void JumpDelay()
    {
        isJump = false;
    }



    // 「はしご」との接触の判定
    private void OnTriggerEnter(Collider other)
    {
        // はしごに当たったらフラグをオン
        if (other.gameObject.tag == "Ladder")
        {
            // はしご接触フラグをオン
            ladderArriveFlg = true;
        }
    }
    

    // 「はしご」との非接触の判定
    private void OnTriggerExit(Collider other)
    {
        // はしごから離れたら
        if (other.gameObject.tag == "Ladder")
        {
            // はしご接触フラグをオフ
            ladderArriveFlg = false;
        }
    }

    public void SetPlayerDir(float _dir)
    {
        PlayerDir = new Vector3(_dir, 0.0f, 1.0f);
    }


    // アニメーションフラグ一斉クリア
    private void ClearAnimFlag()
    {
        anim.SetBool("isWalk", false);
        anim.SetBool("isJump", false);
        anim.SetBool("isLadder", false);
        anim.SetBool("isGrab", false);
        anim.SetBool("isPush", false);
        anim.SetBool("isPull", false);
        anim.SetBool("OnGround", false);
    }


    // プレイヤーの移動速度取得関数
    public float GetMoveSpeed()
    {
        // プレイヤーの移動速度を返す
        return fMoveSpeed;
    }


    public bool CanGrab(Transform pos)
    {
        if ((this.transform.position.x - pos.position.x < 0f && PlayerDir.x >  2.0f) ||
            (this.transform.position.x - pos.position.x > 0f && PlayerDir.x < -2.0f))
        {
            if(isOnGround)
            {
                return true;
            }
        }

        return false;
    }


    // 木箱を掴む(初め)
    public void StartGrab()
    {
        switch (currentState)
        {
            case PlayerState.Stay:
            case PlayerState.Walk:
                currentState = PlayerState.Grab;
                break;
        }
    }


    // 木箱を離す(終わり)
    public void EndGrab()
    {
        if (anim.GetBool("isGrab"))
        {
            currentState = PlayerState.Stay;
        }
    }
    

    // 木箱を掴んでいるかどうか
    public bool isGrab()
    {
        switch (currentState)
        {
            case PlayerState.Grab:
            case PlayerState.Push:
            case PlayerState.Pull:
                return true;
        }

        return false;
    }
    

    // ゴールアニメーション再生
    public void SetGoalAnim()
    {
        ClearAnimFlag();
        anim.SetTrigger("Goal");
        anim.SetBool("OnGround", true);
    }
    
    // 空中判定(アニメーション)
    public string CurrentAnimName()
    {
        return anim.GetCurrentAnimatorClipInfo(0)[0].clip.name;
    }



    private void OnCollisionStay(Collision other)
    {
        // 移動床接触判定
        if (other.gameObject.tag == "MoveGround" && !transform.parent)
        {
            var emptyObject = new GameObject();
            emptyObject.transform.SetParent(other.transform);
            transform.SetParent(emptyObject.transform);
        }
        

        if (other.gameObject.tag == "Near_Ladder")
        {
            bNearLadderArriveFlg = true;
        }
    }
    
    
    private void OnCollisionExit(Collision other)
    {
        // 移動床非接触判定
        if (other.gameObject.tag == "MoveGround" && transform.parent)
        {
            var emptyObject = transform.parent.gameObject;
            transform.SetParent(null);
            Destroy(emptyObject);
        }
    }
}

