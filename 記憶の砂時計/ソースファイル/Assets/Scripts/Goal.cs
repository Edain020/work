using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Goal : MonoBehaviour
{
    StageManager SM;
    DrawGameClear ClearText;

    GameObject PushEnter;


    void Start()
    {
        SM = GameObject.Find("Director").GetComponent<StageManager>();
        ClearText = GameObject.Find("Canvas").transform.Find("ClearText").GetComponent<DrawGameClear>();

        PushEnter = GameObject.Find("Canvas").transform.Find("PushEnter").gameObject;
        PushEnter.SetActive(false);
    }

    private void OnCollisionEnter(Collision collision)
    {
        if(collision.gameObject.tag == "Player")
        {
            SM.SetCurrentState(StageState.Clear);
            ClearText.DrawClear();
            PushEnter.SetActive(true);
            collision.transform.GetComponent<InputSystemPlayerMove>().SetGoalAnim();
            NewClear();
        }
    }

    //初めてクリアしたかどうか(nuclearでは0)
    void NewClear()
    {
        int ClearNum = ClearManager.getClearNum();
        int SelectNum = SelectMapManager.MapNum * 5 + SelectStage.selectStageNum;
        if (ClearNum == SelectNum)
        {
            ClearManager.Add();
        }
    }
}
