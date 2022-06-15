using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerCameraMove : MonoBehaviour
{ 
    // ーーーー Unityに公開するパラメータ ーーーー
    [SerializeField] RewindManager RM;
    [SerializeField] StageManager SM;

    [SerializeField] GameObject Player;
    [SerializeField] GameObject Ghost;

    void Start()
    {
        RM = GameObject.Find("Director").GetComponent<RewindManager>();
        SM = GameObject.Find("Director").GetComponent<StageManager>();

        Player = GameObject.Find("Player");
        Ghost = GameObject.Find("Ghost");
    }

    void Update()
    {
        switch(SM.GetCurrentState())
        {
            case StageState.Start:
                transform.position = Vector3.Lerp(transform.position, new Vector3(Player.transform.position.x, Player.transform.position.y + 2, -7), 1.0f * Time.deltaTime);
                break;

            case StageState.Main:
            case StageState.EndRewind:
                if (!RM.isRewinding())
                {
                    // プレイヤーに追従
                    transform.position = Vector3.Lerp(transform.position, new Vector3(Player.transform.position.x, Player.transform.position.y + 2, -7), 2.0f * Time.deltaTime);
                }
                else
                {
                    // ゴーストに追従
                    transform.position = Vector3.Lerp(transform.position, new Vector3(Ghost.transform.position.x, Ghost.transform.position.y + 2, -10), 2.0f * Time.deltaTime);
                }
                break;
        }
    }
}
