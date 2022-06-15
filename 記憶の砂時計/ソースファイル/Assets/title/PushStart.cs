using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using TMPro;
using UnityEngine.InputSystem;
using UnityEngine.InputSystem.Controls;

public class PushStart : MonoBehaviour
{
    //変数宣言
    [Header("アタッチオブジェクト")]
    [SerializeField] Image image;
    [SerializeField] TextMeshProUGUI tmPro;
    [SerializeField] float fTime = 0;
    
    Fade fade;

    //グローバル変数
    static bool type = false;

    // SE関連
    [SerializeField] AudioClip PushSE;
    AudioSource audioSource;

    //ゲッターセッター
    public static bool startType{
        get { return type; }
        set { type = value; }
    }


    // Start is called before the first frame update
    void Start()
    {
        image.color = new Color(1f, 1f, 1f, 0f);
        tmPro.color = new Color(1f, 1f, 1f, 0f);

        fade = GameObject.Find("Fade").GetComponent<Fade>();

        // SE関連
        audioSource = GetComponent<AudioSource>();
    }

    // Update is called once per frame
    void Update()
    {
        if (type)
        {
            image.color = new Color(1f, 1f, 1f, 0.2f + (0.8f * (Mathf.Cos(fTime) / 2 + 0.5f)));
            //tmPro.color = new Color((Mathf.Cos(fTime) / 2 + 0.5f), (Mathf.Cos(fTime) / 2 + 0.5f), 1f, 0.2f + (0.8f * (Mathf.Cos(fTime) / 2 + 0.5f)));
            tmPro.color = new Color(1f,1f, 1f, 0.2f + (0.8f * (Mathf.Cos(fTime) / 2 + 0.5f)));
            fTime += Time.deltaTime*1.5f;

            if(SandClockInput.getButtonUp(ButtonInputInfo.select))
            {
                audioSource.PlayOneShot(PushSE);
                fade.SetFade(true, 0.5f, "SelectMap");
                type = false;
            }
        }
    }
}
