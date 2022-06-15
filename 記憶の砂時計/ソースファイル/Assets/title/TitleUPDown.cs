using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TitleUPDown : MonoBehaviour
{
    [Header("スピード")]
    [SerializeField] float speed;
    [SerializeField] float movement;
    [SerializeField] Vector2 vector;

    private Vector3 DefaultPos;
    private float cout;
    // Start is called before the first frame update
    void Start()
    {
        DefaultPos = transform.position;
        vector.Normalize();
    }

    // Update is called once per frame
    void Update()
    {
        cout += 0.1f * Time.deltaTime * speed;
        this.transform.position = DefaultPos + new Vector3(Mathf.Sin(cout) * vector.x, Mathf.Sin(cout) * vector.y, 0.0f) * movement;
    }
}
