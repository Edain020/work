using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class SetMapNumText : MonoBehaviour
{

    [SerializeField, Header("ステージ番号")] TextMeshProUGUI MapNumText;
    // Start is called before the first frame update
    void Start()
    {
        MapNumText = this.GetComponent<TextMeshProUGUI>();
        MapNumText.text = "ステージ  "+(SelectMapManager.MapNum+1);
    }

    // Update is called once per frame
    void Update()
    {
        MapNumText.text = "ステージ  " + (SelectMapManager.MapNum+1);
    }
}
