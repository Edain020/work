using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FloatGround : MonoBehaviour
{
    public bool bFlg;
    public float MoveSpeed;
    public float MaxFloat;
    private float DefaultPos;
    private float MaxPos;

    Rigidbody rb;
    RewindManager RM;
    StageManager SM;

    bool isRewinding = false;
    float FirstSpeed;

    // Start is called before the first frame update
    void Start()
    {
        // リジッドボディを取得
        rb = GetComponent<Rigidbody>();

        DefaultPos = transform.position.y;
        MaxPos = DefaultPos + MaxFloat;

        // 逆再生コンポーネント？
        RM = GameObject.Find("Director").GetComponent<RewindManager>();

        SM = GameObject.Find("Director").GetComponent<StageManager>();
        //rb.velocity = new Vector3(0, MoveSpeed, 0);
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        if (bFlg)
        {
            rb.useGravity = false;
            if(MaxPos >= transform.position.y)
            {
                rb.velocity = new Vector3(0, MoveSpeed, 0);
                Debug.Log("Move");
            }
        }

        else
        {
            rb.useGravity = true;
        }
    }

    // スイッチのフラグ取得
    public void SetMoveFlg(bool flg)
    {
        bFlg = flg;
    }
}
