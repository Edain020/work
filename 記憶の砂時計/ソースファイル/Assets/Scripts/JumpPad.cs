using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class JumpPad : MonoBehaviour
{
    public float JumpPower;

    
    void Start()
    {
        
    }
    
    void Update()
    {
        
    }

    void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.tag == "Player" || collision.gameObject.tag == "PushGimmick")
        {
            collision.rigidbody.velocity = new Vector3(0, JumpPower, 0);                
        }
    }
}
