using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MoveNoise : MonoBehaviour
{
    [SerializeField, Tooltip("開始位置")]
    private Vector3 m_startPos;
    [SerializeField, Tooltip("終了位置")]
    private Vector3 m_endPos;

    [SerializeField, Tooltip("動く速度")]
    private float m_speed;

    //  動いている方向
    private bool m_flag;
    //  割合
    private float m_ratio;   
    
    void Start()
    {
        //  スタート位置に移動
        this.transform.localPosition = m_startPos;
    }

    void Update()
    {
        //  フラグに応じて_tに加算
        if (m_flag)
        {
            m_ratio += Time.deltaTime * m_speed;
        }
        else
        {
            m_ratio -= Time.deltaTime * m_speed;
        }

        //  一定値で方向転換
        if (m_ratio > 1f)  m_flag = false;
        else if (m_ratio < 0f) m_flag = true;

        //  リープ
        float x = Mathf.Lerp(m_startPos.x, m_endPos.x, m_ratio);

        this.transform.localPosition = new Vector3(
            x,
            this.transform.localPosition.y,
            this.transform.localPosition.z
        );
    }
}
