using UnityEngine;

public class PointInTime
{
    public Vector3 position;
    public Quaternion rotation;

    public PointInTime(Vector3 _posision, Quaternion _rotation)
    {
        position = _posision;
        rotation = _rotation;
    }
}
