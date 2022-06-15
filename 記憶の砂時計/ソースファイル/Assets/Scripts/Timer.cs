using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Timer : MonoBehaviour
{
    [SerializeField, Header("時間関係(フレーム単位)")] int RewindInterval = 1200;
    [SerializeField] float CurrentTime = 0;

    RewindManager RM;
    StageManager SM;

    void Start()
    {
        RM = GameObject.Find("Director").GetComponent<RewindManager>();
        SM = GameObject.Find("Director").GetComponent<StageManager>();
    }

    void FixedUpdate()
    {
        if (SM.GetCurrentState() != StageState.Main)
        {
            return;
        }

        if (!RM.isRewinding())
        {
            CurrentTime += 1.0f;

            if(CurrentTime > RewindInterval)
            {
                RM.StartRewind();
            }
        }
        else
        {
            CurrentTime -= RM.GetRewindSpeed();

            if(CurrentTime <= 0)
            {
                RM.StopRewind();
                CurrentTime = 0.0f;
                SM.SetCurrentState(StageState.EndRewind);
            }
        }
    }

    public int GetRewindInterval()
    {
        return RewindInterval;
    }

    public float GetCurrentTime()
    {
        return CurrentTime;
    }

    public void SetCurrentTime(float _time)
    {
        CurrentTime = _time;
    }
}
