using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpearSwitch : MonoBehaviour
{
    GameObject SpearGimmick;
    Spear script;

    // Start is called before the first frame update
    void Start()
    {
        SpearGimmick = transform.parent.Find("Icicles").gameObject;
        script = SpearGimmick.GetComponent<Spear>();
    }

    // Update is called once per frame
    void Update()
    {
        
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

            Debug.Log("接点数:" + pointCnt);

            pointx = pointx / pointCnt;
            pointy = pointy / pointCnt;
            pointz = pointz / pointCnt;

            Debug.Log("接点中心座標:x = " + pointx + ", y = " + pointy + ", z = " + pointz);


            if (pointx > transform.position.x - transform.localScale.x / 2 + 0.2 && pointx < transform.position.x + transform.localScale.x / 2 - 0.2)
            {
                if (pointy - transform.position.y >= transform.localScale.y / 2 - 0.2)
                {
                    Debug.Log("当たった!");
                    script.SetFall();                    
                }
            }
        }
    }
}
