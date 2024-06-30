using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using DG.Tweening;

public class ArrowMove : MonoBehaviour
{
    [SerializeField, Tooltip("移動速度")]
    private float m_moveSpeed = 1.0f;
    [SerializeField, Tooltip("移動幅")]
    private float m_moveRange;

    //  角度
    private float m_radian;
    //  最初の位置
    private Vector3 m_startPos;


    private void Start()
    {
        m_radian = 0.0f;

        m_startPos = gameObject.transform.position;
    }

    private void Update()
    {
        //  角度増減
        m_radian += Mathf.PI / 180.0f * m_moveSpeed * Time.deltaTime;
        if(m_radian >= 2 * Mathf.PI) m_radian = 0.0f;

        //  位置
        Vector3 pos = gameObject.transform.position;
        //  上下移動
        pos.y = m_startPos.y + Mathf.Sin(m_radian) * m_moveRange;
        //  位置更新
        gameObject.transform.position = pos;
    }
}
