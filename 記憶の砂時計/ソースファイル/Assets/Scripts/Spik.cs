using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Spik : MonoBehaviour
{
    RewindManager RM;

    // SE関連
    [SerializeField] AudioClip DamageSE;
    AudioSource audioSource;

    void Start()
    {
        RM = GameObject.Find("Director").GetComponent<RewindManager>();

        // SE関連
        audioSource = GetComponent<AudioSource>();
    }

    void Update()
    {
    }

    private void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.tag == "Player")
        {
            RM.StartRewind();
            audioSource.PlayOneShot(DamageSE);
            Debug.Log("Danger!!");
        }
    }

    private void OnTriggerEnter(Collider col)
    {
        if (col.gameObject.tag == "Player")
        {
            RM.StartRewind();
            audioSource.PlayOneShot(DamageSE);
            Debug.Log("Danger!!");
        }
    }
}
