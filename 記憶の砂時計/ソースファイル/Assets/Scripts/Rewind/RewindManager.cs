using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RewindManager : MonoBehaviour
{
    [SerializeField, Header("逆再生中か")] bool _isRewinding = false;

    [SerializeField, Header("逆再生の速度(倍率)"), Range(1, 10)] float rewindSpeed = 1f;

    [Header("ライト")]
    [SerializeField] Light _light;
    [SerializeField] float Intensity;


    Timer timer;
    StageManager SM;

    void Start()
    {
        _light = GameObject.Find("Directional Light").GetComponent<Light>();
        timer = GameObject.Find("Director").GetComponent<Timer>();
        SM = GameObject.Find("Director").GetComponent<StageManager>();

        Intensity = _light.intensity;
    }

    private void FixedUpdate()
    {
        if(SM.GetCurrentState() != StageState.Main)
        {
            return;
        }

        if(_isRewinding)
        {
            if(Intensity < 1.0f)
            {
                Intensity += 1.0f / 60;

                if(Intensity > 1.0f)
                {
                    Intensity = 1.0f;
                }
            }
        }
        else
        {
            if(Intensity > 0.0f)
            {
                Intensity -= 1.0f / 60;

                if(Intensity < 0.0f)
                {
                    Intensity = 0.0f;
                }
            }
        }

        _light.intensity = Intensity;
    }


    public bool isRecord()
    {
        return timer.GetCurrentTime() % rewindSpeed == 0f;
    }

    public void StartRewind()
    {
        _isRewinding = true;
    }

    public void StopRewind()
    {
        _isRewinding = false;
    }


    public bool isRewinding()
    {
        return _isRewinding;
    }

    public float GetRewindSpeed()
    {
        return rewindSpeed;
    }
}
