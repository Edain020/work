using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Spear : MonoBehaviour
{
    Rigidbody rb;
    RewindManager RM;

    bool isRewinding = false;

    // SE関連
    [SerializeField] AudioClip DamageSE;
    AudioSource audioSource;

    // Start is called before the first frame update
    void Start()
    {
        rb = GetComponent<Rigidbody>();
        RM = GameObject.Find("Director").GetComponent<RewindManager>();

        // SE関連
        audioSource = GetComponent<AudioSource>();
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        if (RM.isRewinding())
        {
            if (!isRewinding)
            {
                isRewinding = true;
            }

            return;
        }

        if (isRewinding)
        {
            // 逆再生終了時の処理
            isRewinding = false;
            rb.useGravity = false;
        }
    }

    public void SetFall()
    {
        rb.useGravity = true;
    }

    //void OnCollisionEnter(Collision collision)
    //{
    //    if (collision.gameObject.tag == "Player")
    //    {
    //        if(rb.velocity.y > 0.5f)
    //        {
    //            RM.StartRewind();
    //            Debug.Log("Danger!!");
    //        }           
    //    }
    //}

    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.tag == "Player")
        {
            Debug.Log("ああああああああああああああああああ");
            if (rb.velocity.y > 0.5f)
            {
                RM.StartRewind();

                audioSource.PlayOneShot(DamageSE);
                Debug.Log("Danger!!");
            }
        }
    }
}
