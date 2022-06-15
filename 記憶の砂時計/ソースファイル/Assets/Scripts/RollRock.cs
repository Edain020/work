using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RollRock : MonoBehaviour
{
    private Vector3 DefaultPos;
    Rigidbody rb;
    public float RollSpeed;
    RewindManager RM;
    StageManager SM;

    bool isRewinding = false;       // 逆再生フラグ

    // SE関連
    [SerializeField] AudioClip DamageSE;
    AudioSource audioSource;

    // Start is called before the first frame update
    void Start()
    {
        rb = GetComponent<Rigidbody>();
        RM = GameObject.Find("Director").GetComponent<RewindManager>();
        DefaultPos = transform.position;

        // 逆再生コンポーネント？
        RM = GameObject.Find("Director").GetComponent<RewindManager>();

        SM = GameObject.Find("Director").GetComponent<StageManager>();

        // SE関連
        audioSource = GetComponent<AudioSource>();
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        // ーーーーー 逆再生関連 ーーーーー
        if (RM.isRewinding())
        {
            if (!isRewinding)
            {
                isRewinding = true;
            }

            return;
        }

        // 逆再生終了時に行う処理
        if (isRewinding)
        {
            isRewinding = false;
        }

        // ステージスタート時は動かない
        if (SM.GetCurrentState() != StageState.Main)
        {
            // 物理演算を無効
            rb.isKinematic = true;
            return;
        }
        else
        {
            // 物理演算を有効
            rb.isKinematic = false;
            rb.AddForce(RollSpeed, 0, 0);
        }

    }

    void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.tag == "Under")
        {
            transform.position = DefaultPos;
            rb.velocity = new Vector3(RollSpeed, 0, 0);
            Debug.Log("スポーン");
        }

        if (collision.gameObject.tag == "Spik")
        {
            transform.position = DefaultPos;
            rb.velocity = new Vector3(RollSpeed, 0, 0);
            Debug.Log("スポーン");
        }

        if (collision.gameObject.tag == "Player")
        {
            RM.StartRewind();
            audioSource.PlayOneShot(DamageSE);
            Debug.Log("Danger!!");
        }
    }

    private void OnTriggerEnter(Collider collider)
    {
        if (collider.gameObject.tag == "Spik")
        {
            transform.position = DefaultPos;
            rb.velocity = new Vector3(RollSpeed, 0, 0);
            Debug.Log("スポーン");
        }
    }
}
