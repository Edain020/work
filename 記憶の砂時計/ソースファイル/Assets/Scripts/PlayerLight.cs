using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerLight : MonoBehaviour
{
    [Header("数値")]
    [SerializeField] float MaxIntensity;
    [SerializeField] float CurrentIntensity;

    [Header("設定")]
    [SerializeField] bool isTracking;

    Light _light;
    Timer _timer;
    StageManager SM;
    RewindManager RM;

    GameObject player;


    float timerCnt = 0f;

    void Start()
    {
        _light = GetComponent<Light>();
        _timer = GameObject.Find("Director").GetComponent<Timer>();
        SM = GameObject.Find("Director").GetComponent<StageManager>();
        RM = GameObject.Find("Director").GetComponent<RewindManager>();

        player = GameObject.Find("Player");

        CurrentIntensity = 0.0f;
        _light.intensity = CurrentIntensity;
    }

    private void FixedUpdate()
    {
        switch (SM.GetCurrentState())
        {
            case StageState.Main:
                if(!RM.isRewinding())
                {
                    if (_timer.GetCurrentTime() / _timer.GetRewindInterval() < 0.4f)
                    {
                        if (CurrentIntensity < MaxIntensity)
                        {
                            CurrentIntensity += MaxIntensity / 60.0f;
                            if (CurrentIntensity > MaxIntensity)
                            {
                                CurrentIntensity = MaxIntensity;
                            }
                        }
                    }
                    else
                    {
                        timerCnt += 360 / 60f;
                        CurrentIntensity = MaxIntensity + (Mathf.Cos(timerCnt * Mathf.Deg2Rad) * (MaxIntensity / 4f)) - (MaxIntensity / 4f);
                    }
                }
                else
                {
                    if (CurrentIntensity > 0.0f)
                    {
                        CurrentIntensity -= MaxIntensity / 60.0f;
                        if(CurrentIntensity < 0.0f)
                        {
                            CurrentIntensity = 0.0f;
                        }
                    }
                }

                if (isTracking)
                {
                    transform.position = new Vector3(player.transform.position.x, player.transform.position.y, -10);
                }

                break;
        }

        _light.intensity = CurrentIntensity;
    }
}

