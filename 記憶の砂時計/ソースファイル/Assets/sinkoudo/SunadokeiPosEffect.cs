using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class SunadokeiPosEffect : MonoBehaviour
{
    //定数宣言
    const int MAX_COUT = 3 * 60;
    const int COUT1 = 60;
    const int COUT2 = 60 * 2;
    const int MAX_SIZE = 1;

    //変数宣言
    class Effects
    {
        public bool use;
        public Image image;
        public int cout;
    }
    [SerializeField] Effects[] effects;
    [SerializeField] Sinkoudo sinkoudo;
    [SerializeField] GameObject[] checkPoints;
    [SerializeField] Image image;
    [SerializeField] Vector3 pos;
    // Start is called before the first frame update
    void Start()
    {
        //砂時計の個数を取得
        checkPoints = GameObject.FindGameObjectsWithTag("CheckPoint");

        //配列初期化
        effects = new Effects[checkPoints.Length];
        for (int i = 0; i < checkPoints.Length; ++i)
            effects[i] = new Effects();

        //数値初期化
        foreach (Effects effect in effects)
        {
            effect.use = false;

            effect.image = Instantiate(image, new Vector3(500, 500, 0),Quaternion.identity);
            effect.image.transform.SetParent(this.transform);

            effect.image.color = new Color(1f, 1f, 1f, 0f);
            
            effect.cout = 0;
            Debug.Log(effect.image);
        }
    }

    // Update is called once per frame
    void Update()
    {
        
        foreach (Effects effect in effects)
        {
            //使用中確認
            if (!effect.use)
            {
                continue;
            }

            //アルファ値更新
            else if (effect.cout < COUT1)
            {
                effect.image.color = new Color(1f, 1f, 1f, (1f / COUT1) * effect.cout);
            }
            else if (effect.cout < COUT2)
            {
                effect.image.color = new Color(1f, 1f, 1f, 1f);
            }
            else if (effect.cout < MAX_COUT)
            {
                effect.image.color = new Color(1f, 1f, 1f, (1f - (1f / COUT1) * (effect.cout-COUT2)));
            }
            else if (effect.cout == MAX_COUT)
            {
                effect.image.color = new Color(1f, 1f, 1f, 0f);
                effect.use = false;
            }

            //サイズ更新
            float fNum = MAX_SIZE * ((1f / MAX_COUT) * effect.cout);
            effect.image.transform.localScale = new Vector3(fNum, fNum, fNum);

            //更新処理
            effect.cout++;
         }
    }

    //エフェクト呼び出し　
    public void SetEffect(int num)
    {
        effects[num].use = true;
        effects[num].image.transform.position = sinkoudo.GetPos(num);
        effects[num].image.transform.rotation = sinkoudo.GetRot(num);
        effects[num].image.transform.SetAsLastSibling();
        pos = effects[num].image.transform.position;
    }
}
