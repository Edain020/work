using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HorizontalMoveGroundSwitch : MonoBehaviour
{
    [SerializeField] GameObject MoveGround;      //Unityちゃんそのものが入る変数
    [SerializeField] HorizontalMoveGround script;  //UnityChanScriptが入る変数
    [SerializeField] SwitchLight _light;

    // スイッチに触れたフラグ
    private bool HitFlg = false;

    // Start is called before the first frame update
    void Start()
    {
        // 横移動床の情報を取得
        MoveGround = transform.parent.Find("×2_HMoveGround (1)").gameObject;

        // 横移動床の移動スクリプトを取得
        script = MoveGround.GetComponent<HorizontalMoveGround>();

        _light = transform.parent.GetComponentInChildren<SwitchLight>();
    }



    void OnCollisionStay(Collision collision)
    {
        if (collision.gameObject.tag == "Player" || collision.gameObject.tag == "PushGimmick")
        {
            int pointCnt = 0;

            float pointx = 0;
            float pointy = 0;
            float pointz = 0;

            foreach (ContactPoint point in collision.contacts)
            {
                pointCnt++;

                pointx += point.point.x;
                pointy += point.point.y;
                pointz += point.point.z;
            }

            Debug.Log("接点数:" + pointCnt);

            pointx = pointx / pointCnt;
            pointy = pointy / pointCnt;
            pointz = pointz / pointCnt;

            Debug.Log("接点中心座標:x = " + pointx + ", y = " + pointy + ", z = " + pointz);


            if (pointx > transform.position.x - transform.localScale.x / 2 + 0.2 && pointx < transform.position.x + transform.localScale.x / 2 - 0.2)
            {
                if (pointy - transform.position.y >= transform.localScale.y / 2 - 0.2)
                {
                    if (!HitFlg)
                    {
                        Debug.Log("当たった!");
                        script.SetMoveFlg(true);
                        _light.setSwitchFlg(true);
                        HitFlg = true;
                    }
                }
            }
        }
    }



    void OnCollisionExit(Collision collision)
    {
        if (collision.gameObject.tag == "Player" || collision.gameObject.tag == "PushGimmick")
        {
            if (HitFlg)
            {
                Debug.Log("離れた!");
                script.SetMoveFlg(false);
                _light.setSwitchFlg(false);
                HitFlg = false;
            }
        }
    }
}
