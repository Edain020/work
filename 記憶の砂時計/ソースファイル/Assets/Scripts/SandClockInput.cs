using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;

public enum ButtonInputInfo
{
    select = 0, // 決定ボタン
    cancel,     // キャンセルボタン

    up,     // 上
    down,   // 下
    left,   // 左
    right,  // 右

    jump,   // ジャンプボタン
    grab,   // 掴みボタン

    pose,   // ポーズボタン

    Max,    // 入力の種類
}

public class SandClockInput : MonoBehaviour
{
    //===== Unityに公開するもの =====
    [Header("Status")]
    [SerializeField, Tooltip("スティックのしきい値"), Range(0f, 1f)] float StickThreshold;

    //===== Unityに公開しないもの =====
    Gamepad gamepad;

    static bool isGamepadActive;

    static float horizontal;
    static float vertical;

    static bool[] currentInfo;
    static bool[] prevInfo;


    void Start()
    {
        // ゲームパッドの接続確認
        gamepad = Gamepad.current;
        isGamepadActive = (gamepad != null);

        // 初期化
        horizontal = 0f;
        vertical = 0f;

        currentInfo = new bool[(int)ButtonInputInfo.Max];
        prevInfo = new bool[(int)ButtonInputInfo.Max];
    }

    void Update()
    {
        // 前回の入力の保持
        prevInfo = currentInfo;
        currentInfo = new bool[(int)ButtonInputInfo.Max];

        // ゲームパッドが接続されている場合
        if (isGamepadActive)
        {
            // 左スティックの値を取得
            Vector2 stick = gamepad.leftStick.ReadValue();

            currentInfo[(int)ButtonInputInfo.select] = gamepad.buttonSouth.isPressed;   // 決定ボタン
            currentInfo[(int)ButtonInputInfo.cancel] = gamepad.buttonEast.isPressed;    // キャンセルボタン

            currentInfo[(int)ButtonInputInfo.up]    = gamepad.dpad.up.isPressed;    // 上
            currentInfo[(int)ButtonInputInfo.down]  = gamepad.dpad.down.isPressed;  // 下
            currentInfo[(int)ButtonInputInfo.left]  = gamepad.dpad.left.isPressed;  // 左
            currentInfo[(int)ButtonInputInfo.right] = gamepad.dpad.right.isPressed; // 右

            currentInfo[(int)ButtonInputInfo.jump] = gamepad.buttonSouth.isPressed;     // ジャンプボタン
            currentInfo[(int)ButtonInputInfo.grab] = gamepad.rightShoulder.isPressed;   // 掴みボタン

            currentInfo[(int)ButtonInputInfo.pose] = gamepad.startButton.isPressed;     // ポーズボタン


            // スティック入力 上
            if(!currentInfo[(int)ButtonInputInfo.up])
                if (stick.y > StickThreshold)
                    currentInfo[(int)ButtonInputInfo.up] = true;

            // スティック入力 下
            if (!currentInfo[(int)ButtonInputInfo.down])
            {
                if (!currentInfo[(int)ButtonInputInfo.down])
                    if (stick.y < -StickThreshold)
                        currentInfo[(int)ButtonInputInfo.down] = true;
            }

            // スティック入力 左
            if(!currentInfo[(int)ButtonInputInfo.left])
            {
                if (!currentInfo[(int)ButtonInputInfo.left])
                    if (stick.x < -StickThreshold)
                        currentInfo[(int)ButtonInputInfo.left] = true;
            }

            // スティック入力 右
            if(!currentInfo[(int)ButtonInputInfo.right])
            {
                if (!currentInfo[(int)ButtonInputInfo.right])
                    if (stick.x < StickThreshold)
                        currentInfo[(int)ButtonInputInfo.right] = true;
            }
        }
        // ゲームパッドが接続されていない場合
        else
        {
            currentInfo[(int)ButtonInputInfo.select] = Input.GetKey(KeyCode.Return);    // 決定ボタン
            currentInfo[(int)ButtonInputInfo.cancel] = Input.GetKey(KeyCode.Backspace); // キャンセルボタン

            currentInfo[(int)ButtonInputInfo.up]    = Input.GetKey(KeyCode.UpArrow);    // 上
            currentInfo[(int)ButtonInputInfo.down]  = Input.GetKey(KeyCode.DownArrow);  // 下
            currentInfo[(int)ButtonInputInfo.left]  = Input.GetKey(KeyCode.LeftArrow);  // 左
            currentInfo[(int)ButtonInputInfo.right] = Input.GetKey(KeyCode.RightArrow); // 右

            currentInfo[(int)ButtonInputInfo.jump] = Input.GetKey(KeyCode.Space);   // ジャンプボタン
            currentInfo[(int)ButtonInputInfo.grab] = Input.GetKey(KeyCode.E);       // 掴みボタン

            currentInfo[(int)ButtonInputInfo.pose] = Input.GetKey(KeyCode.P);   // ポーズボタン
        }


        if(currentInfo[(int)ButtonInputInfo.right])
        {
            horizontal += Time.deltaTime * 4f;
            if (horizontal > 1f)
                horizontal = 1f;
        }
        else if(horizontal > 0f)
        {
            horizontal -= Time.deltaTime * 4f;
            if (horizontal < 0f)
                horizontal = 0f;
        }
        if(currentInfo[(int)ButtonInputInfo.left])
        {
            horizontal -= Time.deltaTime * 4f;
            if (horizontal < -1f)
                horizontal = -1f;
        }
        else if(horizontal < 0f)
        {
            horizontal += Time.deltaTime * 4f;
            if (horizontal > 0f)
                horizontal = 0f;
        }

        if (currentInfo[(int)ButtonInputInfo.up])
        {
            vertical += Time.deltaTime * 4f;
            if (vertical > 1f)
                vertical = 1f;
        }
        else if (vertical > 0f)
        {
            vertical -= Time.deltaTime * 4f;
            if (vertical < 0f)
                vertical = 0f;
        }
        if (currentInfo[(int)ButtonInputInfo.down])
        {
            vertical -= Time.deltaTime * 4f;
            if (vertical < -1f)
                vertical = -1f;
        }
        else if (vertical < 0f)
        {
            vertical += Time.deltaTime * 4f;
            if (vertical > 0f)
                vertical = 0f;
        }
    }

    public static bool getButton(ButtonInputInfo _button)
    {
        return currentInfo[(int)_button];
    }

    public static bool getButtonDown(ButtonInputInfo _button)
    {
        return currentInfo[(int)_button] && !prevInfo[(int)_button];
    }

    public static bool getButtonUp(ButtonInputInfo _button)
    {
        return !currentInfo[(int)_button] && prevInfo[(int)_button];
    }

    public static float getHorizontal()
    {
        return horizontal;
    }

    public static float getVertical()
    {
        return vertical;
    }
}
