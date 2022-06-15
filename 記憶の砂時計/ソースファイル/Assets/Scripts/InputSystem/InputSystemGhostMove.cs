using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;
using UnityEngine.InputSystem.Controls;

public class InputSystemGhostMove : MonoBehaviour
{
    [SerializeField, Header("移動速度")] float MoveSpeed;

    StageManager SM;
    GameObject Player;
    Vector3 beforePos;

    GameObject wall_Left;
    GameObject wall_Right;
    GameObject wall_Bottom;
    GameObject wall_Top;

    Vector3 LeftPos;
    Vector3 RightPos;
    Vector3 BottomPos;
    Vector3 TopPos;

    int MoveCnt = 0;

    [SerializeField] bool setNotActive;

    // Start is called before the first frame update
    void Start()
    {
        SM = GameObject.Find("Director").GetComponent<StageManager>();
        Player = GameObject.Find("Player");

        // 移動制限オブジェクト
        wall_Left = GameObject.Find("StartWall");
        wall_Right = GameObject.Find("GoalWall");
        wall_Bottom = GameObject.Find("Dead_Under");
        wall_Top = GameObject.Find("Ceiling");

        LeftPos = wall_Left.transform.position;
        RightPos = wall_Right.transform.position;
        BottomPos = wall_Bottom.transform.position;
        TopPos = wall_Top.transform.position;
    }

    // Update is called once per frame
    void FixedUpdate()
    {   
        if(setNotActive)
        {
            this.gameObject.SetActive(false);
            setNotActive = false;
        }

        if (SM.GetCurrentState() == StageState.Main)
        {
            //===== 移動処理 =====
            if (SandClockInput.getButton(ButtonInputInfo.right))
                transform.position += transform.right * MoveSpeed * Time.deltaTime;
            if (SandClockInput.getButton(ButtonInputInfo.left))
                transform.position -= transform.right * MoveSpeed * Time.deltaTime;
            if (SandClockInput.getButton(ButtonInputInfo.up))
                transform.position += transform.up * MoveSpeed * Time.deltaTime;
            if (SandClockInput.getButton(ButtonInputInfo.down))
                transform.position -= transform.up * MoveSpeed * Time.deltaTime;
        }        

        else if (SM.GetCurrentState() == StageState.EndRewind)
        {
            transform.position = Vector3.Lerp(transform.position, new Vector3(Player.transform.position.x, Player.transform.position.y, 0), 3.0f * Time.deltaTime);
            MoveCnt++;

            if (MoveCnt >= 30)
            {
                MoveCnt = 0;
                SM.SetCurrentState(StageState.Main);
            }
        }

        transform.position = (new Vector3(Mathf.Clamp(transform.position.x, LeftPos.x, RightPos.x),
               Mathf.Clamp(transform.position.y, BottomPos.y, TopPos.y), transform.position.z));
    }
}
