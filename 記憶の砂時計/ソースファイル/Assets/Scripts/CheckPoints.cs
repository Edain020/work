using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CheckPoints : MonoBehaviour
{
    [Header("フラグ")]
    [SerializeField] bool _isActive = false;
    [SerializeField] bool _isSet = false;

    [Header("ライト関係")]
    [SerializeField] bool _isLighting = false;
    [SerializeField] float MaxIntensity = 100;
    [SerializeField] float Intensity = 0;

    [Header("パーティクルシステム")]
    [SerializeField] ParticleSystem particle;

    [Header("スクリプト")]
    [SerializeField] Timer timer;
    [SerializeField] RewindManager RM;
    [SerializeField] Sunokei Clock;
    [SerializeField] Sinkoudo Sinkoudo;
    Light _light;


    void Start()
    {
        timer = GameObject.Find("Director").GetComponent<Timer>();
        RM = GameObject.Find("Director").GetComponent<RewindManager>();
        Clock = this.GetComponent<Sunokei>();

        _light = GetComponentInChildren<Light>();
        particle = GetComponentInChildren<ParticleSystem>();
        Sinkoudo = GameObject.Find("Sinkoudo").GetComponent<Sinkoudo>();
    }

    private void FixedUpdate()
    {
        Clock.SetActive(_isActive);

        if(_isLighting)
        {
            Intensity += MaxIntensity / 60;

            if(Intensity >= MaxIntensity)
            {
                Intensity = MaxIntensity;
                _isLighting = false;
            }
        }
        else
        {
            if (Intensity > 0.0f)
            {
                Intensity -= MaxIntensity / 60;

                if (Intensity < 0.0f)
                {
                    Intensity = 0.0f;
                }
            }
        }

        _light.intensity = Intensity;
    }

    private void OnTriggerEnter(Collider other)
    {
        // 霊体が接触
        if (other.gameObject.tag == "Ghost" && RM.isRewinding() && !_isActive)
        {
            _isActive = true;

            // 霊体が砂時計に接触したことが分かりやすいなにかを実装
            particle.Play();
            Sinkoudo.SetPos(this.transform.position);

            // 砂時計点灯
            _isLighting = true;
            _light.color = new Color(255, 0, 0, 255);
        }

        // プレイヤーが接触
        if(other.gameObject.tag == "Player" && !RM.isRewinding() && _isActive && !_isSet)
        {
            _isSet = true;
            // 砂時計点灯
            _isLighting = true;
            _light.color = new Color(255, 255, 0, 255);
            timer.SetCurrentTime(0f);
        }
    }

    public bool isActive()
    {
        return _isActive;
    }
}
