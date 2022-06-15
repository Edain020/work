using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SwiichMoveStop : MonoBehaviour
{
    [SerializeField] GameObject moveObj;
    [SerializeField] SwitchLight _light;
    [SerializeField] Vector3 endVector;
    Vector3 vector;
    Vector3 DefaultPos;

    [SerializeField] float speed;
    bool bMode;



    // Start is called before the first frame update
    void Start()
    {
        DefaultPos = moveObj.transform.position;
        _light = transform.parent.GetComponentInChildren<SwitchLight>();
        bMode = false;
        vector = endVector;
        vector.Normalize();
    }
    private void Update()
    {
        if (bMode)
        {
            if (endVector.y >= 0)
            {
                if (moveObj.transform.position.y < DefaultPos.y + endVector.y) 
                    moveObj.transform.position += new Vector3(0.0f, vector.y*speed, 0.0f) * Time.deltaTime;
                else
                    moveObj.transform.position = new Vector3(moveObj.transform.position.x, DefaultPos.y + endVector.y, moveObj.transform.position.z);
            }
            if (endVector.y < 0)
            {
                if (moveObj.transform.position.y > DefaultPos.y + endVector.y)
                    moveObj.transform.position += new Vector3(0.0f, vector.y*speed, 0.0f) * Time.deltaTime;
                else
                    moveObj.transform.position = new Vector3(moveObj.transform.position.x, DefaultPos.y + endVector.y, moveObj.transform.position.z);
            }
        }
    }

    void OnCollisionStay(Collision collision)
    {
        if (collision.gameObject.tag == "Player" || collision.gameObject.tag == "PushGimmick")
        {
            _light.setSwitchFlg(true);
            bMode = true;
        }
    }

    void OnCollisionExit(Collision collision)
    {
        if (collision.gameObject.tag == "Player" || collision.gameObject.tag == "PushGimmick")
        {
            _light.setSwitchFlg(false);
            bMode = false;
        }
    }
}