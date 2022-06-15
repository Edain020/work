using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpearTrigger : MonoBehaviour
{
    GameObject SpearGimmick;
    Spear script;

    // Start is called before the first frame update
    void Start()
    {
        SpearGimmick = transform.parent.gameObject;
        script = SpearGimmick.GetComponent<Spear>();
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.tag == "Player")
        {
            script.SetFall();
        }
    }
}
