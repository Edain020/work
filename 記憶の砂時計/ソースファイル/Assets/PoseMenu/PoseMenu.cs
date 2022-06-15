using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;
using UnityEngine.SceneManagement;

public class PoseMenu : MonoBehaviour
{
    [Header("UI")]
    [SerializeField, Tooltip("背景")]     Image poseMenuBG;
    [SerializeField, Tooltip("文字の背景")]   Image[] menuButton;

    [Header("Select")]
    [SerializeField, Tooltip("選択しているメニュー")] int selectNum;
    [SerializeField, Tooltip("拡縮の幅"), Range(0,1)] float scaleRate;
    [SerializeField, Tooltip("拡縮速度")]             float scaleSpeed;

    int menuButtonNum;
    float cnt;

    bool enableFlg;
    StageState prevState;
    StageManager sm;
    Fade fade;

    // SE関連
    [SerializeField] AudioClip PoseSE;
    [SerializeField] AudioClip ButtonA_SE;
    [SerializeField] AudioClip CursorSE;
    AudioSource audioSource;

    void Start()
    {
        poseMenuBG = GetComponent<Image>();
        if(poseMenuBG == null)
        {
            Debug.Log("PoseMenu.cs : PosemenuBG is not found");
        }

        menuButtonNum = 3;
        menuButton = new Image[menuButtonNum];

        menuButton[0] = transform.Find("BackToGame").GetComponent<Image>();
        if (menuButton[0] == null)
        {
            Debug.Log("PoseMenu.cs : BackToGame is not found");
        }


        menuButton[1] = transform.Find("Restart").GetComponent<Image>();
        if (menuButton[1] == null)
        {
            Debug.Log("PoseMenu.cs : Restart is not found");
        }


        menuButton[2] = transform.Find("ReturnToMapselect").GetComponent<Image>();
        if (menuButton[2] == null)
        {
            Debug.Log("PoseMenu.cs : ReturnToMapselect is not found");
        }


        sm = GameObject.Find("Director").GetComponent<StageManager>();
        fade = GameObject.Find("Fade").GetComponent<Fade>();

        SetEnable(false);

        // SE関連
        audioSource = GetComponent<AudioSource>();
    }

    void Update()
    {
        // ポーズ切り替え
        if (SandClockInput.getButtonDown(ButtonInputInfo.pose))
        {
            MenuSwitching();
        }

        // ここから下ポーズ画面での処理
        if(sm.GetCurrentState() != StageState.Pose)
            return;

        // 選択肢を変えたときの処理
        if (SandClockInput.getButtonDown(ButtonInputInfo.up))
        {
            selectNum = (int)Mod(selectNum - 1, menuButtonNum);           
            cnt = 0;
            audioSource.PlayOneShot(CursorSE);
        }
        if (SandClockInput.getButtonDown(ButtonInputInfo.down))
        {
            selectNum = (int)Mod(selectNum + 1, menuButtonNum);
            cnt = 0;
            audioSource.PlayOneShot(CursorSE);
        }

        // ボタンを押したときの処理
        if (SandClockInput.getButtonDown(ButtonInputInfo.select))
        {
            audioSource.PlayOneShot(ButtonA_SE);
            switch (selectNum)
            {
                case 0:
                    MenuSwitching();
                    return;

                case 1:
                    Time.timeScale = 1f;
                    Scene thisScene = SceneManager.GetActiveScene();
                    fade.SetFade(true, 0.5f, thisScene.name);
                    return;

                case 2:
                    Time.timeScale = 1f;
                    fade.SetFade(true, 0.5f, "SelectMap");
                    return;
            }            
        }

        // 強調処理用のカウンター
        cnt = Mod(cnt + scaleSpeed, 360);

        // 選択しているものを強調する処理
        for (int i = 0; i < menuButtonNum; ++i)
        {
            if (i == selectNum)
            {
                menuButton[i].rectTransform.localScale =
                    new Vector3(
                        1 + Mathf.Sin(cnt * Mathf.Deg2Rad) * scaleRate,
                        1 + Mathf.Sin(cnt * Mathf.Deg2Rad) * scaleRate,
                        1 + Mathf.Sin(cnt * Mathf.Deg2Rad) * scaleRate
                        );
            }
            else
            {
                menuButton[i].rectTransform.localScale = new Vector3(1, 1, 1);
            }
        }
    }
    

    void MenuSwitching()
    {
        switch(sm.GetCurrentState())
        {
            // ポーズ中ならポーズ解除
            case StageState.Pose:
                sm.SetCurrentState(prevState);
                SetEnable(false);
                Time.timeScale = 1f;
                return;

            // ポーズ中じゃないならポーズ
            case StageState.Main:               
            case StageState.EndRewind:
                prevState = sm.GetCurrentState();
                sm.SetCurrentState(StageState.Pose);
                SetEnable(true);
                Time.timeScale = 0f;

                selectNum = 0;

                audioSource.PlayOneShot(PoseSE);
                return;
        }
    }


    void SetEnable(bool flg)
    {
        poseMenuBG.enabled = flg;
        for (int i = 0; i < menuButtonNum; ++i)
        {
            menuButton[i].gameObject.SetActive(flg);
        }

        enableFlg = flg;
    }


    float Mod(float a, float b)
    {
        return a - Mathf.FloorToInt(a / b) * b;
    }
}
