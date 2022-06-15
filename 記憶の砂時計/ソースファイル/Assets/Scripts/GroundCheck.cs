using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

public class GroundCheck : MonoBehaviour
{
    // 接地数
    public int EnterNum = 0;

    public AudioClip SE1;
    AudioSource audioSource;

    InputSystemPlayerMove playerMove;

    bool isPlaySE = false;


    void Start()
    {
        audioSource = GetComponent<AudioSource>();
        playerMove = GetComponentInParent<InputSystemPlayerMove>();
    }


    void Update()
    {
        // 地面に触れているのに接地判定が切れている
        if (EnterNum != 0 && !playerMove.IsOnGround)
        {
            EnterNum = 0;
        }

    }

    // 接地した
    private void OnTriggerEnter(Collider Collision)
    {
        if (Collision.gameObject.tag == "Ladder" ||
            Collision.gameObject.tag == "Player" ||
            Collision.gameObject.tag == "CheckPoint" ||
            Collision.gameObject.tag == "Transparent"||
            Collision.gameObject.tag == "Spear")
        {
            return;
        }

        if (EnterNum == 0)
        {
            playerMove.IsOnGround = true;
            playerMove.bNearLadderArriveFlg = false;
            if (isPlaySE)
            {
                audioSource.PlayOneShot(SE1);
            }
            else
            {
                isPlaySE = true;
            }
        }

        EnterNum++;
    }

    private void OnTriggerStay(Collider Collision)
    {
        if (Collision.gameObject.tag == "Ladder" ||
            Collision.gameObject.tag == "Player" ||
            Collision.gameObject.tag == "CheckPoint" ||
            Collision.gameObject.tag == "Transparent" ||
            Collision.gameObject.tag == "Spear")
        {
            return;
        }

        if (EnterNum == 0)
        {
            playerMove.IsOnGround = true;
            playerMove.bNearLadderArriveFlg = false;

            EnterNum++;
        }
    }

    // 地面から離れた
    private void OnTriggerExit(Collider Collision)
    {
        if (Collision.gameObject.tag == "Ladder" ||
            Collision.gameObject.tag == "Player" ||
            Collision.gameObject.tag == "CheckPoint" ||
            Collision.gameObject.tag == "Transparent" ||
            Collision.gameObject.tag == "Spear")
        {
            return;
        }

        EnterNum--;

        // 接地している数が0個なら処理を行う
        if (EnterNum <= 0)
        {
            playerMove.IsOnGround = false;
            EnterNum = 0;
        }
    }
}

