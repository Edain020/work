using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BGMManager : MonoBehaviour
{
    public AudioClip BGM1;
    public AudioClip BGM2;
    public AudioClip ClearBGM;

    AudioSource audioSource;

    GameObject Director; //Unityちゃんそのものが入る変数
    RewindManager script; //UnityChanScriptが入る変数
    private bool bFlg;
    private bool beforeFlg;
    private bool clearFlg;
    private bool ClearTrueFlg;

    StageManager SM;

    // Start is called before the first frame update
    void Start()
    {
        audioSource = GetComponent<AudioSource>();
        Director = GameObject.Find("Director");
        script = Director.GetComponent<RewindManager>();
        bFlg = script.isRewinding();
        beforeFlg = bFlg;
        ClearTrueFlg = false;
        audioSource.clip = BGM1;
        audioSource.Play();
        SM = GameObject.Find("Director").GetComponent<StageManager>();
    }

    // Update is called once per frame
    void Update()
    {
        bFlg = script.isRewinding();

        if(SM.GetCurrentState() == StageState.Clear)
        {
            clearFlg = true;
        }
        if (!clearFlg)
        {
            if (beforeFlg != bFlg)
            {
                if (bFlg)
                {
                    Debug.Log("切り替え１");
                    audioSource.Stop();
                    audioSource.clip = BGM2;
                    audioSource.Play();
                }
                else
                {
                Debug.Log("切り替え２");
                audioSource.Stop();
                audioSource.clip = BGM1;
                audioSource.Play();
                }
            }
            beforeFlg = bFlg;
        }
        else
        {
            if(beforeFlg != clearFlg)
            {
                if (!ClearTrueFlg)
                {
                    audioSource.Stop();
                    audioSource.clip = ClearBGM;
                    audioSource.Play();
                    ClearTrueFlg = true;
                }
            }
        }
    }
}
