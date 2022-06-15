using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class SetBg : MonoBehaviour
{
    //定数宣言

    //変数宣言
    [SerializeField, Header("ステージ画像")] Sprite[] stageImages;
    [SerializeField, Header("画像格納オブジェクト")] Image thisImage;
    [SerializeField, Header("画像格納オブジェクト")] GameObject brotherObj;

    public int nowStage;       //変数値格納変数

    void Start()
    {
        //ステージナンバーを取得
         nowStage = SelectMapManager.MapNum;

        //イメージを取得
        thisImage = this.gameObject.GetComponent<Image>();
        thisImage.sprite = stageImages[nowStage];
    }

    private void Update()
    {
        
    }
}
