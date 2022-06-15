using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Flash_Light : MonoBehaviour
{
    //Unityに公開する情報
    [Header("Flags")]
    [SerializeField] bool isfadeOut = false;    //ライトの発光開始の管理フラグ
    [SerializeField] bool isfadeIn = false;     //ライトの発光終了の管理フラグ

    [Header("Status")]
    [SerializeField] float MaxInstensity = 100.0f;  //ライトの強さの最大値
    [SerializeField] float MaxRange = 50.0f;        //ライトの範囲の最大値

    //Unityに公開しない情報
    float addInstensity = 0f;   //ライトの強さの増加量
    float addLightRange = 0f;   //光の広がる速度

    Light _light;
    GameObject Player;


    void Start()
    {
        _light = GetComponent<Light>();
        _light.intensity = 0.0f;
        _light.range = 0.0f;
        Player = GameObject.Find("Player");
    }

    void Update()
    {
        _light.transform.position = Player.transform.position;

        if (isfadeOut)
        {
            FadeOut();
        }
        else if (isfadeIn)
        {
            FadeIn();
        }
    }

    void FadeOut()
    {
        _light.intensity += addInstensity * Time.deltaTime;
        _light.range += addLightRange * Time.deltaTime;

        if (_light.intensity >= MaxInstensity || _light.range >= MaxRange)
        {
            _light.range = MaxRange;
            _light.intensity = MaxInstensity;
            isfadeOut = false;
            isfadeIn = true;
        }
    }

    void FadeIn()
    {
        _light.intensity -= addInstensity * Time.deltaTime;
        _light.range -= addLightRange * Time.deltaTime;

        if (_light.intensity <= 0f || _light.range <= 0f)
        {
            _light.intensity = 0;
            _light.range = 0;
            isfadeIn = false;
        }
    }

    public void StartFlash(float _fadeTime)
    {
        addInstensity = MaxInstensity / (_fadeTime / 2f);
        addLightRange = MaxRange / (_fadeTime / 2f);
        isfadeOut = true;
    }
}
