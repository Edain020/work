using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class SetImage : MonoBehaviour
{
    //定数宣言


    //変数宣言
    [SerializeField, Header("ステージ画像")]         Sprite[]   stageImages;
    [SerializeField, Header("画像格納オブジェクト")] Image      childrenImage;
    [SerializeField, Header("画像格納オブジェクト")] GameObject parentObj;

    public int nowStage;       //変数値格納変数

    // Start is called before the first frame update
    void Start()
    {
        //ステージナンバー取得    
        nowStage = SelectMapManager.MapNum;

        //画像の差し替え
        childrenImage = transform.Find("StageImage").GetComponent<Image>();
        childrenImage.sprite = stageImages[nowStage];
    }
}
