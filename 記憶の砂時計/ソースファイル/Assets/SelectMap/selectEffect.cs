using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class selectEffect : MonoBehaviour
{
    [SerializeField] GameObject obj;
    [SerializeField] Vector2 movePos;
    [SerializeField] float moveSpeed;
    [SerializeField] Vector2 Speed;
    [SerializeField] float NextMoveSpeed;
    [SerializeField] float NextMoveFastSpeed;
    [SerializeField] bool bMode =true;

    //中心位置系
    Vector3 CenterPos;

    //次の位置を求める移動
    Vector3 NewCenterPos;
    Vector3 moveVector;

    //時間関係パラメーター
    float fTime;



    // Start is called before the first frame update
    void Start()
    {
        CenterPos = obj.transform.position;
    }

    // Update is called once per frame
    void Update()
    {
        if (bMode)
        {
            //移動更新
            obj.transform.position = CenterPos + (new Vector3(Mathf.Sin(fTime * Speed.x) * movePos.x, Mathf.Sin(fTime * 2f * Speed.y) * movePos.y, 0f));
            //時間更新
        }
        else
        {
            obj.transform.position += (moveVector * fTime * NextMoveSpeed)+ moveVector*NextMoveFastSpeed;


            if (moveVector.x >= 0 && NewCenterPos.x < obj.transform.position.x)
            {
                CenterPos = NewCenterPos;
                obj.transform.position = CenterPos;
                fTime = 0;
                bMode = true;
            }
            else if (moveVector.x < 0 && NewCenterPos.x > obj.transform.position.x)
            {
                CenterPos = NewCenterPos;
                obj.transform.position = CenterPos;
                fTime = 0;
                bMode = true;
            }
        }
        fTime += Time.deltaTime * moveSpeed;
    }

    public void setNextPos(Vector3 pos)
    {
        if (pos!=CenterPos)
        {
            NewCenterPos = pos;
            moveVector = NewCenterPos - obj.transform.position;
            moveVector.Normalize();
            fTime = 0f;
            //モード切り替え
            bMode = false;
        }
    }
}
