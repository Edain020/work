using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SwitchLight : MonoBehaviour
{
    [Header("フラグ")]
    [SerializeField, Tooltip("スイッチが押されているかどうか")] bool switchFlg = false;

    [Header("カラー")]
    [SerializeField, Tooltip("スイッチが押されていないときの色"), ColorUsage(false, true)] Color disableSwitchColor;
    [SerializeField, Tooltip("スイッチが押されているときの色"), ColorUsage(false, true)] Color enableSwitchColor;

    [Header("数値")]
    [SerializeField, Tooltip("明るさ")] float intensity;

    [Header("メッシュレンダラー")]
    [SerializeField] MeshRenderer r;

    // SE関連
    [SerializeField] AudioClip SwitchSE;
    AudioSource audioSource;

    private void Start()
    {
        r = GetComponent<MeshRenderer>();

        // マテリアルの変更するパラメータを事前に知らせる
        r.material.EnableKeyword("_EMISSION");

        // SE関連
        audioSource = GetComponent<AudioSource>();
    }

    void Update()
    {
        float factor = Mathf.Pow(2, intensity);

        // スイッチが押されていない
        if (!switchFlg)
        {
            r.material.SetColor("_EmissionColor", disableSwitchColor * factor);
        }
        // スイッチが押されている
        else
        {
            r.material.SetColor("_EmissionColor", enableSwitchColor * factor);
        }
    }

    public void setSwitchFlg(bool _flg)
    {
        audioSource.PlayOneShot(SwitchSE);
        switchFlg = _flg;
    }
}
