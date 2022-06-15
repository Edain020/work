using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using UnityEngine.UI;


public class Sinkoudo : MonoBehaviour
{
    class CheckPoint
    {
        public Image image;
        public CheckPoints checkPoint;

        public CheckPoint(Image _image, CheckPoints _checkPoint)
        {
            image = _image;
            checkPoint = _checkPoint;
        }
    }

    class PosStoring
    {
        public bool use;
        public Vector2 v2StartPos;
        public Vector2 v2EndPos;
        public Vector2 v2Vector;
        public float   posSpeed;
        public float   fRotZ;
    }

    //----変数----//
    [Header("オブジェクト")]
    [SerializeField]  GameObject StartPoint, GoolPoint, PlayerPos;
    [SerializeField]  Image      StartImage, GoolImage, PlayerImage, _CheckPoint;
    [SerializeField]  Image     _prefabImageEffect;

    [SerializeField]  GameObject[] checkPoints;
    [SerializeField]  Image[]    effectImage;


    [Header("スクリプト")]
    [SerializeField] SunadokeiPosEffect SunadokeiPosEffect;


    [Header("変数")]
    [SerializeField] float speed = 1f;
    [SerializeField] float speedAcceleration = 1f;
    [SerializeField] float rotSpeed = 1f;



    float StartImagePosX;
    float ImageMaxPos;
    float ObjectMaxPos;
    public float ObjPosRate;
   

    //UIのスタート位置格納
//    Vector2[] EndPos = null;
    PosStoring[] PosStorings = null;


    
    List<CheckPoint> CheckPoints;

    void Start()
    {
        //UIプレイヤーの位置初期化
        PlayerImage.transform.position = StartImage.transform.position;

        //幅の最大値計算
        ImageMaxPos = StartImage.transform.position.x - GoolImage.transform.position.x;
        ObjectMaxPos = StartPoint.transform.position.x - GoolPoint.transform.position.x;

        //UI初期一の代入
        StartImagePosX = PlayerImage.transform.position.x;

        CheckPoints = new List<CheckPoint>();

        //チェックポイント探索
        checkPoints = GameObject.FindGameObjectsWithTag("CheckPoint");

        
        //移動エフェクトの初期化
        effectImage = new Image[checkPoints.Length];
        for(int i = 0; i < effectImage.Length; i++)
        {
            effectImage[i]= Instantiate(_prefabImageEffect, new Vector3(0, 0, 0), Quaternion.identity);
            effectImage[i].transform.SetParent(this.transform);
            effectImage[i].enabled = false;
        }


        //値格納クラスの初期化
        PosStorings = new PosStoring[checkPoints.Length];
        for (int i = 0; i < PosStorings.Length; i++)
        {
            PosStorings[i] = new PosStoring();
        }

        int num = 0;
        foreach (GameObject checkPoint in checkPoints)
        {
            //表示位置を計算
            float NowPos = checkPoint.transform.position.x - StartPoint.transform.position.x;
            ObjPosRate = NowPos / ObjectMaxPos;
            float PosX = StartImagePosX + (ImageMaxPos * ObjPosRate);

            //イメージの位置を設定
            Image instance = Instantiate(_CheckPoint, new Vector3(PosX, PlayerImage.transform.position.y, PlayerImage.transform.position.z), Quaternion.identity);
            instance.transform.SetParent(this.transform);

            //リストに追加
            CheckPoints.Add(new CheckPoint(instance.GetComponent<Image>(), checkPoint.GetComponent<CheckPoints>()));

            //最終位置を格納
            PosStorings[num].use = false;
            PosStorings[num].v2EndPos = new Vector2(PosX, PlayerImage.transform.position.y);
            PosStorings[num].posSpeed = speed;

            num++;
        }
    }

    void Update()
    {
        //現在のスタート位置から移動した量を計算
        float NowPos = PlayerPos.transform.position.x - StartPoint.transform.position.x;
        //全体進行度の割合計算
        ObjPosRate = NowPos / ObjectMaxPos;

        //画面端かどうか
        if (ObjPosRate >= -0.02f)
        {
            ObjPosRate = -0.02f;
        }

        if (ObjPosRate <= -0.98f)
        {
            ObjPosRate = -0.98f;
        }

        //UIに適用する位置計算
        float ImagePos = StartImagePosX + (ImageMaxPos * ObjPosRate);

        PlayerImage.transform.position = new Vector3(ImagePos, PlayerImage.transform.position.y, PlayerImage.transform.position.z);

        int num = 0;
        foreach (CheckPoint checkPoint in CheckPoints)
        {
            if (checkPoint.checkPoint.isActive())
            {
                //使用可能
                if (!PosStorings[num].use)
                {
                    num++;
                    continue;
                }

                //移動処理
                effectImage[num].rectTransform.position += new Vector3(PosStorings[num].v2Vector.x * PosStorings[num].posSpeed, PosStorings[num].v2Vector.y * PosStorings[num].posSpeed, 0f) * Time.deltaTime;
                effectImage[num].rectTransform.rotation *= Quaternion.AngleAxis(rotSpeed * Time.deltaTime, Vector3.forward);

                PosStorings[num].posSpeed = PosStorings[num].posSpeed + speedAcceleration;
                //目標位置を超えたか
                if (effectImage[num].rectTransform.position.y > PosStorings[num].v2EndPos.y)
                {
                    effectImage[num].rectTransform.position = PosStorings[num].v2EndPos;
                    checkPoint.image.enabled = true;
                    effectImage[num].enabled = false;
                    PosStorings[num].use = false;
                    SunadokeiPosEffect.SetEffect(num);
                }
            }
            else
            {
                checkPoint.image.enabled = false;
                effectImage[num].enabled = false;
            }
            num++;
        }

    }



    //ポジション適用
    public void SetPos(Vector3 pos)//GameObject gameObject)
    {
        int num = 0;
        //同じオブジェクトかを確認
        foreach (CheckPoint checkPoint in CheckPoints)
        {
           
            if (checkPoint.checkPoint.transform.position == pos)
            {
                //world座標系をscreen座標系に変換
                Vector3 position =new Vector3(checkPoint.checkPoint.transform.position.x, checkPoint.checkPoint.transform.position.y+1, checkPoint.checkPoint.transform.position.z);
                effectImage[num].rectTransform.position = RectTransformUtility.WorldToScreenPoint(Camera.main, position);

                //値を格納
                PosStorings[num].v2StartPos = effectImage[num].rectTransform.position;

                //方向ベクトルを計算
                Vector2 vector = PosStorings[num].v2EndPos - PosStorings[num].v2StartPos;
                PosStorings[num].v2Vector = vector.normalized;
                Debug.Log(PosStorings[num].v2Vector);

                //有効化
                effectImage[num].enabled = true;
                PosStorings[num].use = true;

                break;
            }
            num++;
        }
    }

    public int SunadokeiNum()
    {
        return CheckPoints.Count;
    }
    public Vector3 GetPos(int Num)
    {
        return CheckPoints[Num].image.transform.position;
    }
    public Quaternion GetRot(int Num)
    {
        return CheckPoints[Num].image.transform.rotation;
    }
}
