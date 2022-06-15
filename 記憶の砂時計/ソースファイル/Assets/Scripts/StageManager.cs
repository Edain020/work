using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.InputSystem;
using UnityEngine.InputSystem.Controls;

public enum StageState
{
 //   Fade,       // フェード中
    Start,      // ステージ開始演出
    Main,       // ステージ攻略中
    EndRewind,  // 逆再生終了時
    Pose,       // ポーズ画面
    Clear,      // ステージクリア演出
}

public class StageManager : MonoBehaviour
{
    [SerializeField, Header("ゲームの状態")] StageState currentState = StageState.Start;

    int _timer = 0;
    Fade fade;

    void Start()
    {
        fade = GameObject.Find("Fade").GetComponent<Fade>();
    }


    void Update()
    {

        switch (currentState)
        {
            case StageState.Clear:
                if (SandClockInput.getButtonUp(ButtonInputInfo.select))
                    fade.SetFade(true, 0.5f, "SelectStage");
                break;
        }
    }

    private void FixedUpdate()
    {
        if(currentState == StageState.Start)
        {
            _timer++;

            if(_timer >= 180)
            {
                _timer = 0;
                currentState = StageState.Main;
            }
        }
    }

    public StageState GetCurrentState()
    {
        return currentState;
    }

    public StageState SetCurrentState(StageState state)
    {
        return currentState = state;
    }
}
