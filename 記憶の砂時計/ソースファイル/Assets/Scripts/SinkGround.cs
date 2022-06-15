using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SinkGround : MonoBehaviour
{
    public bool OnFlg = false;
    public bool PosFlg = true;
    private Vector3 DefaultPos;
    public float SinkSpeed;
    Rigidbody rb;

    // Start is called before the first frame update
    void Start()
    {
        DefaultPos = transform.position;
        rb = GetComponent<Rigidbody>();
    }

    // Update is called once per frame
    void Update()
    {
        if (OnFlg)
        {

            rb.velocity = new Vector3(0, (float)(rb.velocity.y), 0);
        }
        else
        {
            if (transform.position.y >= DefaultPos.y)
            {
                PosFlg = true;
                rb.constraints = RigidbodyConstraints.FreezePosition;
            }
            else
            {
                PosFlg = false;
            }

            if (!PosFlg)
            {
                rb.velocity = new Vector3(0, SinkSpeed, 0);
            }
        }
    }

    void OnCollisionEnter(Collision collision)
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

            if (pointx > transform.position.x - transform.localScale.x / 2 + 0.2 && pointx < transform.position.x + transform.localScale.x / 2 - 0.2)
            {
                if (pointy - transform.position.y >= transform.localScale.y / 2 - 0.2)
                {
                    OnFlg = true;
                    rb.useGravity = true; rb.useGravity = true;                    
                    rb.constraints = RigidbodyConstraints.None;
                    rb.constraints = RigidbodyConstraints.FreezeRotation;
                    rb.constraints = RigidbodyConstraints.FreezePositionX;
                }
            }
        }
    }

    void OnCollisionExit(Collision collision)
    {
        OnFlg = false;
        rb.useGravity = false;
    }
}
