using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.InputSystem;
using UnityEngine.InputSystem.Controls;

public class SetButtonImage : MonoBehaviour
{
    const float MAX_COLOR = 1f;
    const float MIDDLE_COLOR = 0.5f;

    //変数宣言
    // Start is called before the first frame update
    [SerializeField, Header("next親")] GameObject Next;
    [SerializeField, Header("back親")] GameObject Back;

    [SerializeField, Header("next親")] Image aButtonImage;
    [SerializeField, Header("back親")] Image bButtonImage;

    [SerializeField, Header("Aボタン画像")] Sprite[] aButtonSprite;
    [SerializeField, Header("Bボタン画像")] Sprite[] bButtonSprite;

    // SE関連
    [SerializeField] AudioClip ButtonA_SE;
    [SerializeField] AudioClip ButtonB_SE;
    AudioSource audioSource;

    void Start()
    {
        //親を取得
        Next = this.transform.Find("Next").gameObject;
        Back = this.transform.Find("Back").gameObject;

        //Button画像を取得
        aButtonImage = Next.transform.Find("Image").GetComponent<Image>();
        bButtonImage = Back.transform.Find("Image").GetComponent<Image>();

        //初期画像を適用  
        aButtonImage.sprite = aButtonSprite[0];
        bButtonImage.sprite = bButtonSprite[0];

        //色の初期化
        aButtonImage.color = new Color(MAX_COLOR, MAX_COLOR, MAX_COLOR);
        bButtonImage.color = new Color(MAX_COLOR, MAX_COLOR, MAX_COLOR);

        // SE関連
        audioSource = GetComponent<AudioSource>();
    }

    // Update is called once per frame
    void Update()
    {
        aButtonSetSprit();
        bButtonSetSprit();
    }

    //aボタン設定
    void aButtonSetSprit()
    {
        if (SandClockInput.getButtonDown(ButtonInputInfo.select))
        {
            aButtonImage.sprite = aButtonSprite[1];
            aButtonImage.color = new Color(MIDDLE_COLOR, MIDDLE_COLOR, MIDDLE_COLOR);
            audioSource.PlayOneShot(ButtonA_SE);
        }
        else if (SandClockInput.getButtonUp(ButtonInputInfo.select))
        {
            aButtonImage.sprite = aButtonSprite[0];
            aButtonImage.color = new Color(MAX_COLOR, MAX_COLOR, MAX_COLOR);
        }
    }

    //Bボタン設定
    void bButtonSetSprit()
    {
        if (SandClockInput.getButtonDown(ButtonInputInfo.cancel))
        {
            bButtonImage.sprite = bButtonSprite[1];
            bButtonImage.color = new Color(MIDDLE_COLOR, MIDDLE_COLOR, MIDDLE_COLOR);
            audioSource.PlayOneShot(ButtonB_SE);
        }
        else if (SandClockInput.getButtonUp(ButtonInputInfo.cancel))
        {
            bButtonImage.sprite = bButtonSprite[0];
            bButtonImage.color = new Color(MAX_COLOR, MAX_COLOR, MAX_COLOR);
        }
    }
}

