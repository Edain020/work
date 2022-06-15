using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FallGround : MonoBehaviour
{
    [SerializeField] float FallTimer;
    private bool HitFlg = false;
    private float OnTimer = 0.0f;
    private bool FallFlg = false;
    Rigidbody rb;

    RewindManager RM;

    bool isRewinding = false;

    // Start is called before the first frame update
    void Start()
    {
        rb = GetComponent<Rigidbody>();

        // 逆再生コンポーネント？
        RM = GameObject.Find("Director").GetComponent<RewindManager>();
    }

    // Update is called once per frame
    void FixedUpdate()
    {
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
            rb.constraints = RigidbodyConstraints.FreezeAll;

            isRewinding = false;
            FallFlg = false;
            OnTimer = 0.0f;
            rb.useGravity = false;
            HitFlg = false;
        }

        if(HitFlg)
        {
            OnTimer += Time.deltaTime;           
        }

        if (OnTimer >= FallTimer)
        {
            rb.constraints = RigidbodyConstraints.None;
            rb.constraints = RigidbodyConstraints.FreezeRotation
                            | RigidbodyConstraints.FreezePositionX
                            | RigidbodyConstraints.FreezePositionZ;
            FallFlg = true;
        }

        if (FallFlg)
        {
            rb.useGravity = true;
        }
    }

    void OnCollisionStay(Collision collision)
    {
        if (collision.gameObject.tag == "Player")
        {
            int pointCnt = 0;

            float pointx = 0;
            float pointy = 0;
            float pointz = 0;

            foreach (ContactPoint point in collision.contacts)
            {
                pointCnt++;

                pointx += point.point.x;
                pointy += point.point.y;
                pointz += point.point.z;
            }

            pointx = pointx / pointCnt;
            pointy = pointy / pointCnt;
            pointz = pointz / pointCnt;

            if (pointx > transform.position.x - transform.localScale.x / 200 + 0.2 && pointx < transform.position.x + transform.localScale.x / 200 - 0.2)
            {
                HitFlg = true;
            }
        }
    }

    void OnCollisionExit(Collision collision)
    {
        //if (!FallFlg)
        //{
        //    OnTimer = 0;
        //}
    }
}
