using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Tutorial : MonoBehaviour
{
    //===== Unityに公開するもの =====
    [Header("Status")]
    [SerializeField, Tooltip("霊体時のチュートリアルかどうか")] bool isGhost;
    [SerializeField, Tooltip("切り替わる速度")] float fadeSpeed;
    [SerializeField, Tooltip("透過率"), Range(0f, 1f)] float alpha;

    //===== Unityに公開しないもの =====
    RewindManager rm;
    Material mat;


    void Start()
    {
        rm = GameObject.Find("Director").GetComponent<RewindManager>();
        mat = GetComponent<MeshRenderer>().material;

        if(rm.isRewinding())
        {
            if (isGhost)
                alpha = 1f;
            else
                alpha = 0f;
        }
        else
        {
            if (isGhost)
                alpha = 0f;
            else
                alpha = 1f;
        }

        SetMaterialStatus(alpha);
    }

    void Update()
    {
        if (fadeSpeed <= 0f)
            return;

        if(rm.isRewinding())
        {
            if(isGhost)
            {
                if(alpha < 1f)
                {
                    alpha += Time.deltaTime / fadeSpeed;
                    if (alpha > 1f)
                        alpha = 1f;
                }
            }
            else
            {
                if(alpha > 0f)
                {
                    alpha -= Time.deltaTime / fadeSpeed;
                    if (alpha < 0f)
                        alpha = 0f;
                }
            }
        }
        else
        {
            if (isGhost)
            {
                if (alpha > 0f)
                {
                    alpha -= Time.deltaTime / fadeSpeed;
                    if (alpha < 0f)
                        alpha = 0f;
                }
            }
            else
            {
                if (alpha < 1f)
                {
                    alpha += Time.deltaTime / fadeSpeed;
                    if (alpha > 1f)
                        alpha = 1f;
                }
            }
        }

        SetMaterialStatus(alpha);
    }

    void SetMaterialStatus(float _alpha)
    {
        mat.SetFloat("_timeAlpha", _alpha);

        if((_alpha -= 0.5f) < 0f)
            _alpha = 0f;

        mat.SetFloat("_timeImage", _alpha * 2f);
    }
}
