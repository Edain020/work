using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;
using UnityEngine.InputSystem.Controls;

public class InputSystemWoodenBox : MonoBehaviour
{
    bool bFlg;
    bool bGrab;
    float speed;

    GameObject player;
    InputSystemPlayerMove playerMove;

    Transform parent;
    bool isChild;

    void Start()
    {
        bFlg = false;

        player = GameObject.Find("Player");
        playerMove = player.GetComponent<InputSystemPlayerMove>();

        parent = transform.parent;
        isChild = false;
    }


    void Update()
    {
        // プレイヤーの座標を取得
        Vector3 PlayerPos = player.transform.position;

        // 木箱の座標
        Vector3 BoxPos = transform.position;

        // プレイヤーの座標と木箱の座標が1.5以内
        if (Mathf.Abs(PlayerPos.x - BoxPos.x) < 1.5f && Mathf.Abs(PlayerPos.y - BoxPos.y) < 1.0f)
        {
            if (!bFlg)
            {
                bFlg = true;
            }
        }
        else
        {
            if (bFlg)
            {
                bFlg = false;
                if (bGrab)
                {
                    playerMove.EndGrab();
                    transform.SetParent(parent);
                    bGrab = false;
                }
            }
        }
    }


    void FixedUpdate()
    {
        if (bFlg)
        {
            if (SandClockInput.getButton(ButtonInputInfo.grab))
            {
                if (!playerMove.isGrab() && playerMove.CanGrab(transform))
                {
                    playerMove.StartGrab();
                    transform.SetParent(player.transform);
                    bGrab = true;

                    if(isChild)
                    {
                        var emptyObject = transform.parent.gameObject;
                        transform.SetParent(parent);
                        Destroy(emptyObject);
                        isChild = false;
                    }
                }
            }
            else if (bGrab)
            {
                playerMove.EndGrab();
                transform.SetParent(parent);
                bGrab = false;
            }

            if(bGrab)
            {
                Vector3 pos = transform.position;
                Vector3 playerPos = player.transform.position;
                playerMove.SetPlayerDir((pos.x - playerPos.x) * 100);
            }
        }
    }


    private void OnCollisionStay(Collision col)
    {
        if (col.gameObject.tag == "MoveGround" && transform.parent.parent != col.transform)
        {
            if (!bGrab)
            {
                var emptyObject = new GameObject();
                emptyObject.transform.SetParent(col.transform);
                transform.SetParent(emptyObject.transform);
                isChild = true;
            }
        }
    }

    private void OnCollisionExit(Collision col)
    {
        if (isChild && col.gameObject.tag == "MoveGround")
        {
            var emptyObject = transform.parent.gameObject;
            transform.SetParent(parent);
            Destroy(emptyObject);
            isChild = false;
        }
    }
}
