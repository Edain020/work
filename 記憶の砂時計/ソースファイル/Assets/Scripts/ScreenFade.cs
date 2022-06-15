using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ScreenFade : MonoBehaviour
{
    //===== Unityに公開するもの =====
    [Header("Flags")]
    [SerializeField] bool isfadeOut = false;
    [SerializeField] bool isfadeIn = false;

    [Header("Status")]
    [SerializeField, Tooltip("フェードの時間(フェードイン、フェードアウト合計)")] float fadeTime;
    [SerializeField] float alpha;

    //===== Unityに公開しないもの =====
    float red, green, blue;
    float fadeSpeed = 0f;

    Image fadeImage;

    Flash_Light FL;
    RewindManager RM;
    bool isRewind;


    void Start()
    {
        fadeImage = GetComponent<Image>();
        red= fadeImage.color.r;
        green = fadeImage.color.g;
        blue = fadeImage.color.b;
        alpha = fadeImage.color.a;

        FL = GameObject.Find("Flash").GetComponent<Flash_Light>();
        RM = GameObject.Find("Director").GetComponent<RewindManager>();
        isRewind = false;
    }
    
    void Update()
    {
        if (!isRewind && RM.isRewinding())
        {
            StartFade();
            FL.StartFlash(fadeTime);
            Debug.Log("Flash!!");
        }

        isRewind = RM.isRewinding();


        if (isfadeOut)
        {
            FadeOut();
        }
        else if (isfadeIn)
        {
            FadeIn();
        }
    }

    public void StartFade()
    {
        fadeSpeed = 1.0f / (fadeTime / 2f);
        fadeImage.enabled = true;
        isfadeOut = true;
    }


    void FadeOut()
    {
        alpha += fadeSpeed * Time.deltaTime;

        if (alpha >= 1f)
        {
            isfadeOut = false;
            isfadeIn = true;
        }

        SetAlpha();
    }

    void FadeIn()
    {
        alpha -= fadeSpeed * Time.deltaTime;

        if (alpha <= 0f)
        {
            isfadeIn = false;
            fadeImage.enabled = false;
        }

        SetAlpha();
    }

    void SetAlpha()
    {
        fadeImage.color = new Color(red, green, blue, alpha);
    }
}
