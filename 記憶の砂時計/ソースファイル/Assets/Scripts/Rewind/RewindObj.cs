using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RewindObj : MonoBehaviour
{
    List<PointInTime> pointsInTime;
    bool isRewinding = false;
    bool prevKinematic;

    RewindManager RM;
    StageManager SM;
    Rigidbody rb;


    void Start()
    {
        pointsInTime = new List<PointInTime>();
        RM = GameObject.Find("Director").GetComponent<RewindManager>();
        SM = GameObject.Find("Director").GetComponent<StageManager>();
        rb = GetComponent<Rigidbody>();
        prevKinematic = rb.isKinematic;
    }

    void FixedUpdate()
    {
        if(SM.GetCurrentState() != StageState.Main)
        {
            return;
        }

        if (RM.isRewinding())
        {
            if(!isRewinding)
            {
                StartRewinding();
            }
            Rewind();
        }
        else
        {
            if(isRewinding)
            {
                StopRewinding();
            }

            if (RM.isRecord())
            {
                Record();
            }
        }
    }

    void Rewind()
    {
        if(pointsInTime.Count > 0)
        {
            PointInTime pointInTime = pointsInTime[0];
            transform.position = pointInTime.position;
            transform.rotation = pointInTime.rotation;
            pointsInTime.RemoveAt(0);
        }
    }

    void Record()
    {
        pointsInTime.Insert(0, new PointInTime(transform.position, transform.rotation));
    }

    void StartRewinding()
    {
        rb.isKinematic = true;
        isRewinding = true;
    }

    void StopRewinding()
    {
        pointsInTime.Clear();
        rb.isKinematic = prevKinematic;
        isRewinding = false;
    }
}
