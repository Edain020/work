using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;
using UnityEngine.InputSystem.Controls;

public class InputSystemLightmanager : MonoBehaviour
{
    GameObject DirectionalLightObj;
    GameObject PointLightObj;

    // Start is called before the first frame update
    void Start()
    {
        DirectionalLightObj = GameObject.Find("Directional Light");
        PointLightObj = GameObject.Find("Point Light");
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        // ゲームパッド
        var gamepad = Gamepad.current;


        //if (Input.GetKey(KeyCode.Q) && DirectionalLightObj.transform.localEulerAngles.x == 270)
        if(gamepad.leftShoulder.isPressed && DirectionalLightObj.transform.localEulerAngles.x == 270)
        {
            Debug.Log("LEFT_SHOULDER");
            DirectionalLightObj.SetActive(true);
            PointLightObj.SetActive(false);
            DirectionalLightObj.transform.Rotate(new Vector3(160, 0, 0));
        }

        //if (Input.GetKeyDown(KeyCode.E) && PointLightObj.activeSelf == false)
        if (gamepad.leftTrigger.isPressed && PointLightObj.activeSelf == false)
        {
            DirectionalLightObj.transform.Rotate(new Vector3(-160, 0, 0));
            PointLightObj.SetActive(true);
            DirectionalLightObj.SetActive(false);
        }

    }
}
