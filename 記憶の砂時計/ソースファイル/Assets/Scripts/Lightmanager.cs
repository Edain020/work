using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Lightmanager : MonoBehaviour
{
    // Start is called before the first frame update
    GameObject DirectionalLightObj;
    GameObject PointLightObj;
    void Start()
    {
        DirectionalLightObj = GameObject.Find("Directional Light");
        PointLightObj = GameObject.Find("Point Light");
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKey(KeyCode.Q) && DirectionalLightObj.transform.localEulerAngles.x == 270) 
        {
            DirectionalLightObj.SetActive(true);
            PointLightObj.SetActive(false);
            DirectionalLightObj.transform.Rotate(new Vector3(160, 0, 0));
        }

        if (Input.GetKeyDown(KeyCode.E) && PointLightObj.activeSelf == false)
        {
            DirectionalLightObj.transform.Rotate(new Vector3(-160, 0, 0));
            PointLightObj.SetActive(true);
            DirectionalLightObj.SetActive(false);
        }
    }
}