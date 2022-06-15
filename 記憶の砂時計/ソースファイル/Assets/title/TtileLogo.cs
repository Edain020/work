using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class TtileLogo : MonoBehaviour
{
    //クラス宣言
    public class TitleParame
    {
        public Vector3 v3StartPos;
        public Vector3 v3EndPos;
        public float   fAlpha;
    }

    class TitleImage
    {
        public bool bUse;
        public Image image;
        public TitleParame parame;

        public TitleImage(TitleImage _titleImage)
        {
            bUse = _titleImage.bUse;
            image = _titleImage.image;
            parame = _titleImage.parame;
        }
        public TitleImage(bool _use, Image _image, TitleParame _titleParame)
        {
            bUse = _use;
            image = _image;
            parame = _titleParame;
        }
        public TitleImage(bool _use, Image _image)
        {
            bUse = _use;
            image = _image;
        }
    }
    
    //定数宣言
    [SerializeField] float speed = 1; //使用開始確認
//    [SerializeField] float Uppos = 1; //使用開始確認
    [SerializeField] Vector3 UpPos; //使用開始確認
    [SerializeField] Vector3 framePos; //使用開始確認

    //変数宣言
    [Header("オブジェクト")]
    [SerializeField] Image[] images; //使用開始確認

    [Header("マテリアル")]
    [SerializeField] Material kiokunoMaterial;
    [SerializeField] Material sunadkeiMaterial;


    [Header("変数")]
    [SerializeField] static bool bStart = true; //使用開始確認
    [SerializeField] float  nCout  = 0; //使用開始確認
    float fSkipTime = 0;

    
    [Header("リスト")]
    [SerializeField] List<TitleImage> titleImages;




    //ゲッター,セッター
    public static bool start
    {
        get { return bStart; }
        set { bStart = value; }
    }

    // Start is called before the first frame update
    void Start()
    {
        titleImages = new List<TitleImage>();
        bStart = true;
        nCout = 0;
        fSkipTime = 0;
        foreach (Image image in images)
        {
            TitleParame Num = new TitleParame();
            Num.v3StartPos = image.rectTransform.position;
            Num.v3EndPos   = image.rectTransform.position;
            Num.fAlpha     = 0f;
            image.color = new Color(1f, 1f, 1f, 0f);

            titleImages.Add(new TitleImage(false, image, Num));
        }
        titleImages[1].parame.v3StartPos   += UpPos;
        titleImages[3].parame.v3StartPos   += framePos;
        titleImages[4].parame.v3StartPos   -= framePos;

        //マテリアル抽出
        kiokunoMaterial = titleImages[1].image.GetComponent<Image>().material;
        kiokunoMaterial.SetFloat("_Vector", 0f);

        sunadkeiMaterial = titleImages[2].image.GetComponent<Image>().material;
        sunadkeiMaterial.SetFloat("_timeImage", 0f);
        sunadkeiMaterial.SetFloat("_timeAlpha", 0f);
    }

    // Update is called once per frame
    void Update()
    {
        if (bStart)
        {
            if (nCout == 0)
            {
                //初期化
                titleImages[0].bUse = true;
            }
            //BG
            if (0 <= nCout && nCout < 1)
            {
                //更新
                titleImages[0].image.color =new Color(1f, 1f, 1f, nCout);
            }
            if (nCout >= 1 && titleImages[0].bUse == true)
            {
                //終了
                titleImages[0].bUse = false;
                titleImages[0].image.color = new Color(1f, 1f, 1f, 1f);
                //初期化
                titleImages[1].image.rectTransform.position = titleImages[1].parame.v3EndPos;
                titleImages[1].bUse = true;
            }
            //記憶
            if (1 <= nCout && nCout < 2)
            {
                //更新
                kiokunoMaterial.SetFloat("_Vector", (nCout % 1));
            }
            if (nCout >= 2 && titleImages[1].bUse == true)
            {
                //終了
                kiokunoMaterial.SetFloat("_Vector",1f);
                titleImages[1].bUse = false;
                
                //初期化
                titleImages[2].bUse = true;
                nCout = 2f;
            }
            //砂時計
            if (2 <= nCout && nCout < 3)
            {
                //マテリアルパラメーター初期化
                if (nCout - 2f > 0.7f)
                {
                    sunadkeiMaterial.SetFloat("_timeImage", ((nCout % 1f) -0.7f)*3.3f);
                }
                sunadkeiMaterial.SetFloat("_timeAlpha", nCout % 1f);
            }
            if (nCout >= 3 && titleImages[2].bUse == true)
            {
                nCout -= Time.deltaTime/2 * speed;
                //終了
                sunadkeiMaterial.SetFloat("_timeImage", 0.99f);
                sunadkeiMaterial.SetFloat("_timeAlpha", 0.99f);
                titleImages[2].bUse = false;

                //初期化
                titleImages[3].image.transform.position = titleImages[3].parame.v3StartPos;
                titleImages[4].image.transform.position = titleImages[4].parame.v3StartPos;
                titleImages[3].image.color = new Color (1f,1f,1f,1f);
                titleImages[4].image.color = new Color (1f,1f,1f,1f);

                titleImages[5].image.transform.rotation = Quaternion.Euler(new Vector3(0f, 0f, 0f));

                titleImages[3].bUse = true;
                nCout = 3f;
            }
            //「フレーム」との
            if (3 <= nCout && nCout < 4)
            {
                nCout += Time.deltaTime * speed;
                titleImages[3].image.transform.position = titleImages[3].parame.v3StartPos - framePos * (nCout % 1f);
                titleImages[4].image.transform.position = titleImages[4].parame.v3StartPos + framePos * (nCout % 1f);
                titleImages[5].image.transform.Rotate(new Vector3(0f, 0f, 1.5f * (15 - nCout)));
                titleImages[5].image.color = new Color(1f, 1f, 1f, nCout % 1f);
            }
            if (nCout >= 4 && titleImages[3].bUse == true)
            {
                //終了
                titleImages[3].bUse = false;
                titleImages[3].image.transform.position = titleImages[3].parame.v3EndPos;
                titleImages[4].image.transform.position = titleImages[4].parame.v3EndPos;
                titleImages[5].image.transform.rotation = Quaternion.Euler(new Vector3(0f, 0f, 0f));
                titleImages[5].image.color = new Color(1f, 1f, 1f, 1f);
                PushStart.startType = true;
                bStart = false;
            }
            nCout += Time.deltaTime*speed;

            if (SandClockInput.getButtonDown(ButtonInputInfo.select))
            {
                SetDefaultPos();
            }
        }
        else
        {
            if (fSkipTime > 0.1f)
            {
                PushStart.startType = true;
            }
            fSkipTime += Time.deltaTime;
        }
    }

    void SetDefaultPos()
    {
        foreach(TitleImage image in titleImages)
        {
            image.image.color = new Color(1f, 1f, 1f, 1f);
            image.image.transform.position = image.parame.v3EndPos;
            image.image.transform.rotation = Quaternion.Euler(new Vector3(0f, 0f, 0f));
        }
        sunadkeiMaterial.SetFloat("_timeImage", 0.99f);
        sunadkeiMaterial.SetFloat("_timeAlpha", 0.99f);

        kiokunoMaterial.SetFloat("_Vector", 1f);
        bStart = false;
    }
}
