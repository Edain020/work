using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class Fade : MonoBehaviour
{
    //----- Unityに公開するもの -----
    [Header("フェードステータス")]
    [SerializeField, Tooltip("フェードしているかどうか")] bool isFade;
    [SerializeField, Tooltip("フェードインかどうか")]     bool isFadeIn;
    [SerializeField, Tooltip("フェード時間(秒)")]         float fadeTime;
    [SerializeField, Tooltip("現在の経過時間(秒)")]       float currentTime;
    [SerializeField, Tooltip("フェード先のシーン")]       string nextSceneName;

    //----- Unityに公開しないもの -----
    Material FadeMat;


    void Start()
    {
        SetFade(false, 0.5f, null);

        FadeMat = GetComponent<Image>().material;
    }

    void Update()
    {
        if (!isFade)
            return;

        if(isFadeIn)
        {
            currentTime += Time.deltaTime;
            if (currentTime >= fadeTime)
            {
                currentTime = fadeTime;
                EndFade();
            }
        }
        else
        {
            currentTime -= Time.deltaTime;
            if(currentTime <= 0f)
            {
                currentTime = 0f;
                EndFade();
            }
        }

        FadeMat.SetFloat("FadeTime", currentTime / fadeTime);
    }


    void EndFade()
    {
        if (isFadeIn)
            if (nextSceneName != null)
                SceneManager.LoadScene(nextSceneName);

        isFade = false;
    }

    public bool SetFade(bool _isFadeIn, float _fadeTime, string _nextSceneName)
    {
        // フェード中は受け付けない
        if (isFade)
            return false;

        isFade = true;
        if (isFadeIn = _isFadeIn)
            currentTime = 0f;
        else
            currentTime = _fadeTime;
        fadeTime = _fadeTime;
        nextSceneName = _nextSceneName;

        return true;
    }
}
