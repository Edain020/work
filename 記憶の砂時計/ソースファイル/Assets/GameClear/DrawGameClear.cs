using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class DrawGameClear : MonoBehaviour
{
    //----定数----//
    static int MaxCout = 100;


    //----変数----//
    private TextMeshProUGUI ClearObj;

    public bool mode = false;
    public float speed = 1f;
    private int cout = 0;

    void Start()
    {
        ClearObj = this.GetComponent<TextMeshProUGUI>();
        ClearObj.transform.localScale = new Vector3(0f, 0f, 0f);
    }

    // Update is called once per frame
    void Update()
    {
        if (mode)
        {
            if (cout <= MaxCout)
            {
                float SetNum = cout / (float)MaxCout;
                ClearObj.transform.localScale = new Vector3(SetNum, SetNum, SetNum);
                ClearObj.transform.Rotate(new Vector3(0f, 0f, cout / 7.5f));
                ClearObj.alpha = SetNum;
            }
            else {
                mode = false;
                ClearObj.transform.rotation = Quaternion.Euler(new Vector3(0f, 0f, 15.0f));
            }
           cout++;
        }
    }

    public void DrawClear()
    {
        mode = true;
    }
}
