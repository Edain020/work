using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;


public class PrintStageName : MonoBehaviour
{
    //----定数----//
    const float TitleLimit  = 0.25f;
    const float ChapterLimit= 0.25f + TitleLimit;
    const float WaitLimit   = 0.25f + ChapterLimit;
    const float OuteLimit   = 0.25f + WaitLimit;

    const float MaxColorNum = 1f;


    //----変数----//
    public TextMeshProUGUI TitleObject, ChapterObject;
    public Vector4 color=new Vector4(255,255,255,0f);

    public bool mode = false;
    public float Speed = 1.0f;
    public float cout;

    StageManager sm;


    // Start is called before the first frame update
    void Start()
    {
        TitleObject.color = new Color(color.x, color.y, color.z, 0);
        ChapterObject.color = new Color(color.x, color.y, color.z, 0);
        cout = 0;

        sm = GameObject.Find("Director").GetComponent<StageManager>();

        mode = true;
    }


    // Update is called once per frame
    void Update()
    {
        if (sm.GetCurrentState() == StageState.Pose)
            return;

        if (mode)
        {
            //タイトル表示
            if (cout <= TitleLimit)
            {
                TitleObject.color = new Color(color.x, color.y, color.z, cout * (1f/0.25f)); 
            }

            //チャプター表示
            else if (cout <= ChapterLimit)
            {
                ChapterObject.color = new Color(color.x, color.y, color.z, (cout - TitleLimit) * (1f / 0.25f));
            }

            //待機時間
            else if (cout <= WaitLimit)
            {

            }

            //フェイドアウト
            else if (cout <= OuteLimit)
            {
                TitleObject.color     = new Color(color.x, color.y, color.z, MaxColorNum - ((cout - WaitLimit) * (1f / 0.25f)));
                ChapterObject.color   = new Color(color.x, color.y, color.z, MaxColorNum - ((cout - WaitLimit) * (1f / 0.25f)));
            }

            //終了
            else
            {
                TitleObject.color = new Color(color.x, color.y, color.z,0);
                ChapterObject.color = new Color(color.x, color.y, color.z,0);
                mode = false;
            }

            //時間更新
            cout += 0.001f * Speed;
        }
        color = TitleObject.color;
    }
}
